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

pub fn get_ranges_and_food(lines: Vec<String>) -> (Vec<(usize, usize)>, Vec<usize>) {
    let mut ranges = Vec::new();
    let mut foods = Vec::new();

    for line in lines {
        let parts: Vec<&str> = line.split('-').collect();

        if parts.len() == 2 {
            let start = parts[0].parse::<usize>().unwrap_or(0);
            let end = parts[1].parse::<usize>().unwrap_or(0);
            ranges.push((start, end));
        } else if parts.len() == 1 {
            let food = parts[0].parse::<usize>().unwrap_or(0);
            foods.push(food);
        } else {
            continue;
        }
    }

    (ranges, foods)
}
