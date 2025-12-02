use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;

pub fn read_file_to_lines(path: &Path) -> Vec<String> {
    let mut lines = Vec::new();

    if let Ok(file) = File::open(path) {
        let reader = BufReader::new(file);
        for line in reader.lines() {
            if let Ok(l) = line {
                lines.push(l);
            }
        }
    }

    lines
}

pub fn lines_to_first_last_id(lines: Vec<String>) -> Vec<(i64, i64)> {
    let lines = lines
        .iter()
        .flat_map(|s| s.split(','))
        .filter(|s| !s.is_empty())
        .map(|s| {
            let parts: Vec<&str> = s.split('-').collect();
            if parts.len() == 2 {
                let first = parts[0].parse::<i64>().unwrap_or(0);
                let last = parts[1].parse::<i64>().unwrap_or(0);
                (first, last)
            } else {
                (0, 0)
            }
        })
        .collect::<Vec<(i64, i64)>>();

    lines
}
