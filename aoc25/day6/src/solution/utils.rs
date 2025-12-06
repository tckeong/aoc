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

pub fn process_lines1(lines: &Vec<String>) -> Vec<Vec<&str>> {
    lines
        .iter()
        .map(|s| {
            s.split(' ')
                .map(|c| c.trim())
                .filter(|c| !c.is_empty())
                .collect::<Vec<&str>>()
        })
        .collect()
}

pub fn process_lines2(lines: &Vec<String>) -> Vec<Vec<&str>> {
    let split_points = find_split_points(lines);
    let mut result = Vec::new();

    for line in lines {
        let mut row = Vec::new();
        let mut last_index = 0;

        for &split_index in &split_points {
            let segment = &line[last_index..split_index];
            row.push(segment);
            last_index = split_index + 1;
        }

        let segment = &line[last_index..];
        row.push(segment);

        result.push(row);
    }

    result
}

fn find_split_points(lines: &Vec<String>) -> Vec<usize> {
    let lines = lines
        .iter()
        .map(|s| s.chars().collect::<Vec<char>>())
        .collect::<Vec<Vec<char>>>();

    let n = lines.len();
    let m = lines[0].len();
    let mut split_points = Vec::new();

    for j in 0..m {
        let mut is_split = true;

        for i in 0..n {
            if lines[i][j] != ' ' {
                is_split = false;
                break;
            }
        }

        if is_split {
            split_points.push(j);
        }
    }

    split_points
}
