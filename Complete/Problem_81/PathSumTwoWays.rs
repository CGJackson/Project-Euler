mod path_finding;

use std::fs;

const DATA_FILE: &str = "0081_matrix.txt";


use path_finding::Graph;
use path_finding::build_graph;
use path_finding::sum_values;
use path_finding::lowest_cost_path;

fn parse_matrix(mat:&String) -> Graph<i32,2> {
    let mut vals : Vec<i32> = Vec::new();
    let mut edges : Vec<[Option<usize>;2]> = Vec::new();
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
            let node_edges = [if i == (n-1) {None} else {Some(n*(i+1)+j)}, if j == (n-1) {None} else {Some(n*i+j+1)}];
            edges.push(node_edges);
        }
    }
    return build_graph(vals.into_iter(),edges.into_iter());
}

fn main(){
    let raw_matrix = fs::read_to_string(DATA_FILE);

    let matrix : Graph<i32,2> = match raw_matrix {
        Ok(s) => parse_matrix(&s),
        Err(_e) => panic!("Failed to open data file"),
    };

    let shortest_path = match lowest_cost_path(&matrix,0,matrix.n_nodes()-1) {
        Some(path) => path,
        None => panic!("Failed to find path from start to end"),
    };
    let path_total = sum_values(&matrix, shortest_path);
    println!("{:?}", path_total);
}