mod path_finding;

use std::fs;

const DATA_FILE: &str = "0082_matrix.txt";


use path_finding::Graph;
use path_finding::build_graph;
use path_finding::sum_values;
use path_finding::lowest_cost_path;

fn parse_matrix(mat:&String) -> (Graph<i32,3>,Vec<usize>,Vec<usize>) {
    let mut vals : Vec<i32> = Vec::new();
    let mut edges : Vec<[Option<usize>;3]> = Vec::new();
    let rows = mat.lines();
    let n = rows.clone().count();
    let mut left_hand_edge: Vec<usize> = Vec::new();
    let mut right_hand_edge: Vec<usize> = Vec::new();
    for (i,row) in rows.enumerate() {
        let entry = row.split(",");
        for (j,entry) in entry.enumerate() {
            let parse_result = entry.parse();
            let entry_val = match parse_result {
                Ok(v) => v,
                Err(_e) => panic!("Malformed matrix string {}", entry)
            };
            vals.push(entry_val);
            let node_edges = [if i == 0 {None} else {Some(n*(i-1)+j) },
                              if j == (n-1) {None} else {Some(n*i+j+1)},
                              if i == (n-1) {None} else {Some(n*(i+1)+j)}];
            edges.push(node_edges);

            if j == 0 {
                left_hand_edge.push(vals.len()-1);
            }
            else if j == n-1 {
                right_hand_edge.push(vals.len()-1);
            }
        }
    }
    return (build_graph(vals.into_iter(),edges.into_iter()),left_hand_edge,right_hand_edge);
}


fn main(){
    let raw_matrix = fs::read_to_string(DATA_FILE);

    let (matrix, left_hand_edge,right_hand_edge) = match raw_matrix {
        Ok(s) => parse_matrix(&s),
        Err(_e) => panic!("Failed to open data file"),
    };

    let mut min_distance = i32::MAX;

    const DELTA: i32 = 200;

    for source in &left_hand_edge{
        let (source_distances,_) = path_finding::delta_stepping(&matrix,*source,DELTA,1);

        for destination in &right_hand_edge{
            let distance_to_destination = match source_distances[*destination] {
                Some(x) => x,
                None => panic!("No path found between nodes {} and {}",source,destination),
            };
            if distance_to_destination < min_distance {
                min_distance = distance_to_destination;
            }
        }
    }

    print!("Minimum distance across matrix: {}\n", min_distance);
}