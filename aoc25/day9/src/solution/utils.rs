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

pub fn lines_to_tiles(lines: &Vec<String>) -> Vec<(i64, i64)> {
    lines
        .iter()
        .map(|line| {
            let parts: Vec<&str> = line.split(',').collect();
            let x = parts[0].parse::<i64>().unwrap_or(0);
            let y = parts[1].parse::<i64>().unwrap_or(0);
            (x, y)
        })
        .collect()
}
