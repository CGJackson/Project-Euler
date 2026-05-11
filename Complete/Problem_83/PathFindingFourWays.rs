mod path_finding;

use std::fs;

const DATA_FILE: &str = "0083_matrix.txt";


use path_finding::Graph;
use path_finding::build_graph;
use path_finding::sum_values;
use path_finding::lowest_cost_path;

fn parse_matrix(mat:&String) -> Graph<i32,4> {
    let mut vals : Vec<i32> = Vec::new();
    let mut edges : Vec<[Option<usize>;4]> = Vec::new();
    let rows = mat.lines();
    let n = rows.clone().count();
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
                              if j == 0 {None} else {Some(n*i + j -1)},
                              if j == (n-1) {None} else {Some(n*i+j+1)},
                              if i == (n-1) {None} else {Some(n*(i+1)+j)}];
            edges.push(node_edges);
        }
    }
    return build_graph(vals.into_iter(),edges.into_iter());
}


fn main(){
    let raw_matrix = fs::read_to_string(DATA_FILE);

    let matrix = match raw_matrix {
        Ok(s) => parse_matrix(&s),
        Err(_e) => panic!("Failed to open data file"),
    };

    const DELTA: i32 = 800;

    let (source_distances,_) = path_finding::delta_stepping(&matrix,0,DELTA,4);

    print!("Minimum distance across matrix: {}\n", source_distances.last().unwrap().expect("Could not find path between start and end node"));
}