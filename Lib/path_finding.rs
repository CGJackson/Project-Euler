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