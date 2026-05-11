use std::iter::zip;
use std::collections::BinaryHeap;

#[derive(Debug)]
struct Node<T,const N:usize> {
    val: T,
    children: [Option<usize> ; N]
}

#[derive(Debug)]
pub struct Graph<T,const N:usize> {
    nodes: Vec<Node<T,N>>,
}

impl<T,const N:usize> Graph<T,N> {
    pub fn n_nodes(&self)->usize{
        return self.nodes.len();
    }

    pub fn get_val(&self,idx:usize) -> &T {
        return &self.nodes[idx].val;
    }

    pub fn get_children(&self, idx:usize) -> &[Option<usize> ; N]{
        return &self.nodes[idx].children;
    }

    fn get_node(&self, idx:usize) -> &Node<T,N>{
        return &self.nodes[idx];
    }

}

pub fn build_graph<I1,I2,T, const E:usize>(vals : I1, edges: I2 )-> Graph<T,E> 
where
    T: Clone,
    I1 : Iterator<Item = T>,
    I2 : Iterator<Item = [Option<usize>;E]>,
    {
    let mut nodes : Vec<Node<T,E>> = Vec::new();
    for (v, node_edges) in zip(vals,edges) {
        let n = Node{val : v.clone(), children : node_edges};
        nodes.push(n);
    }
    return Graph{nodes : nodes}
}

pub fn sum_values<'a,T,It, const N:usize>(graph:&Graph<T,N>, nodes_to_sum:It ) -> T
    where
        T: std::ops::Add<Output=T> + From<i32> + Clone,
        It: IntoIterator<Item = usize>,
    {
        let mut total : T = T::from(0);
        for n in nodes_to_sum{
            total = total + graph.get_val(n).clone();
        }
        total
}

use std::cmp::Ordering;

#[derive(Debug)]
struct PathWithLength<T>
where
    T : std::cmp::Ord + std::fmt::Debug
{
    path_length : T,
    path : Vec<usize>
}
impl<T> Ord for PathWithLength<T> 
where
    T:Ord + std::fmt::Debug
{
    fn cmp(&self, other : &Self) -> Ordering {
        //self.path_length.cmp(&other.path_length)
        match self.path_length.cmp(&other.path_length) {
            Ordering::Less => Ordering::Greater,
            Ordering::Equal => Ordering::Equal,
            Ordering::Greater => Ordering::Less,
        }
    }
}

impl<T> PartialOrd for PathWithLength<T>
where
    T:Ord + std::fmt::Debug
{
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl<T> PartialEq for PathWithLength<T>
where
    T:Ord + std::fmt::Debug
{
    fn eq(&self, other: &Self) -> bool {
        self.cmp(other) == Ordering::Equal
    }
}

impl<T> Eq for PathWithLength<T>
where
    T:Ord + std::fmt::Debug
    {}

pub fn lowest_cost_path<T,const N:usize>(graph:&Graph<T,N>, start:usize,end:usize) -> Option<Vec<usize>> 
where
    T : std::ops::Add<Output=T> + std::cmp::Ord + Clone + std::fmt::Debug
{
    let mut node_already_reached : Vec<bool> = vec![false ; graph.n_nodes()];
    let mut live_paths : BinaryHeap<PathWithLength<T>>= BinaryHeap::new();
    let initial_path : PathWithLength<T> = PathWithLength{path_length : graph.get_val(start).clone(),path : vec![start.clone()]};
    live_paths.push(initial_path);
    loop {
        let PathWithLength::<T>{path : current_path,path_length : current_length} = match live_paths.pop() {
            Some(path_with_length) => path_with_length,
            None => return None, // If the queue is empty then you have explored everywhere reachable from start without reaching end
        };
        let current_end = *current_path.last().expect("Encountered empty path");

        // If a node has been reached previously, the previous path will have been shorter, so do not consider again
        if !node_already_reached[current_end] {
            node_already_reached[current_end] = true;
        }
        else {
            continue;
        }

        for child in graph.get_children(current_end) {
            //println!("{:?} : {:?} : {:?}",current_end, child, current_length);
            let next_idx = match child {
                Some(kid) => if *kid == end {let mut final_path = current_path;
                                            final_path.push(end);
                                            return Some(final_path);}
                            else {*kid},
                None => continue,
            };
            let next_val = graph.get_val(next_idx);
            let mut new_path = current_path.clone();
            new_path.push(next_idx);
            live_paths.push(PathWithLength{path : new_path,path_length : current_length.clone() + next_val.clone()}); 
        }


    }
}

pub fn delta_stepping<T,const N:usize>(graph : &Graph<T,N>,source :usize, delta : T,max_threads : u32) -> (Vec<Option<T>>,Vec<Option<Vec<usize>>>) 
    where
        T: std::ops::Add<Output=T> + std::cmp::Ord + Clone + std::fmt::Debug + std::ops::Div<Output = T> + std::convert::TryInto<usize> + std::marker::Send + std::marker::Sync
    {
    use std::collections::BTreeSet;
    use std::collections::BTreeMap;
    use std::thread;
    use std::sync::Mutex;

    let tentative_distances_mutex:Mutex<Vec<Option<T>>> = Mutex::new(vec![None;graph.n_nodes()]);
    {
        let tentative_distances = &mut tentative_distances_mutex.lock().unwrap();
        tentative_distances[source] = Some(graph.get_val(source).clone());
    }
    let tentative_paths_mutex:Mutex<Vec<Option<Vec<usize>>>> = Mutex::new(vec![None;graph.n_nodes()]);
    {
        let tentative_paths = &mut tentative_paths_mutex.lock().unwrap();
        tentative_paths[source] = Some(vec![source]);
    }
    let buckets_mutex : Mutex<BTreeMap<T,BTreeSet<usize>>> = Mutex::new(BTreeMap::new());
    {
        let buckets = &mut buckets_mutex.lock().unwrap();
        buckets.insert(graph.get_val(source).clone()/delta.clone(),{let mut first_bucket = BTreeSet::new();
                                                        first_bucket.insert(source);
                                                        first_bucket});
    }

    let relax = |start_node: usize,end_node :usize, bckts_mutex :&Mutex<BTreeMap<T,BTreeSet<usize>>>| {
        let mut tentative_distances = tentative_distances_mutex.lock().unwrap();
        let proposed_distance = tentative_distances[start_node].clone().unwrap() + graph.get_val(end_node).clone();
        if tentative_distances[end_node].is_none() || *tentative_distances[end_node].as_ref().unwrap() > proposed_distance {
            {
                let mut bckts = bckts_mutex.lock().unwrap();
                match &tentative_distances[end_node] {
                    Some(d) => {
                                bckts.get_mut(&(d.clone()/delta.clone())).unwrap().remove(&end_node)
                                },
                    None => false,
                };
                bckts.entry(proposed_distance.clone()/delta.clone()).or_insert(BTreeSet::new()).insert(end_node);
            }
            tentative_distances[end_node] = Some(proposed_distance);
            drop(tentative_distances);
            {
                let tentative_paths = &mut tentative_paths_mutex.lock().unwrap();
                tentative_paths[end_node] = tentative_paths[start_node].clone();
                tentative_paths.get_mut(end_node).unwrap().as_mut().unwrap().push(end_node);
            }
        }
    };

    let mut redundant_buckets_lock = Some(buckets_mutex.lock().unwrap());
    while !(*redundant_buckets_lock.as_ref().unwrap()).is_empty() {

        let (next_bucket_index,next_bucket) = redundant_buckets_lock.unwrap().pop_first().unwrap();
        redundant_buckets_lock = None;
        let next_bucket_mutex = Mutex::new(next_bucket);
        let to_relax_heavy_mutex:Mutex<BTreeSet<usize>>= Mutex::new(BTreeSet::new());

        thread::scope(|s|{
            for _i in 0..max_threads{
                s.spawn(||{
                    let mut next_bucket = Some(next_bucket_mutex.lock().unwrap());
                    while !(*next_bucket.as_ref().unwrap()).is_empty() {
                        let next_node_index = match (*next_bucket.unwrap()).pop_first(){
                            Some(idx) => idx,
                            None => break,
                        };
                        next_bucket = None; // releases lock
                        let next_node_children = graph.get_children(next_node_index);
                        for child in next_node_children {
                            let g = match child {
                                Some(v) => *v,
                                None => continue,
                            };
                            if *graph.get_val(g) > delta{
                                continue;
                            }
                            relax(next_node_index, g,&buckets_mutex)
                        }
                        {
                            let mut to_relax_heavy = to_relax_heavy_mutex.lock().unwrap();
                            to_relax_heavy.insert(next_node_index);
                        }
                        next_bucket = Some(next_bucket_mutex.lock().unwrap()) // reaquire lock
                    }
                });
            }
        });


        thread::scope(|s|{
            for _i in 0..max_threads{
                s.spawn(||{
                    let mut to_relax_heavy = Some(to_relax_heavy_mutex.lock().unwrap());
                    while !(*to_relax_heavy.as_ref().unwrap()).is_empty() {
                        let next_node_index = (*to_relax_heavy.unwrap()).pop_first().unwrap();
                        to_relax_heavy = None;

                        let next_node_children = graph.get_children(next_node_index);
                        for child in next_node_children {
                            let g = match child {
                                Some(v) => *v,
                                None => continue,
                            };
                            if *graph.get_val(g) <= delta{
                                continue;
                            }
                            relax(next_node_index, g,&buckets_mutex)
                        }
                        to_relax_heavy = Some(to_relax_heavy_mutex.lock().unwrap());
                    }
                });
            }
        });


        redundant_buckets_lock = Some(buckets_mutex.lock().unwrap());
    }

    
    return (tentative_distances_mutex.lock().unwrap().to_vec(),tentative_paths_mutex.lock().unwrap().to_vec());
    
}