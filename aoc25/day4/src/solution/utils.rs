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
