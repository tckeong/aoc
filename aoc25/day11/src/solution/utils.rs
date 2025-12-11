use std::collections::HashMap;
use std::fs;
use std::path::Path;

pub fn read_file_to_lines(path: &Path) -> Option<Vec<String>> {
    fs::read_to_string(path)
        .ok()?
        .lines()
        .map(|line| line.to_string())
        .collect::<Vec<String>>()
        .into()
}

pub fn lines_to_graph(lines: &Vec<String>) -> HashMap<String, Vec<String>> {
    lines
        .into_iter()
        .map(|line| {
            let parts: Vec<&str> = line.split(":").collect();
            let node = parts[0].trim().to_string();
            let connections = parts[1]
                .trim()
                .split_whitespace()
                .map(|s| s.to_string())
                .collect::<Vec<String>>();

            (node, connections)
        })
        .collect()
}
