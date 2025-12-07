use std::path::Path;

pub fn read_file_to_lines(path: &Path) -> Option<Vec<Vec<char>>> {
    std::fs::read_to_string(path)
        .ok()?
        .lines()
        .map(|line| line.chars().collect::<Vec<char>>())
        .collect::<Vec<Vec<char>>>()
        .into()
}
