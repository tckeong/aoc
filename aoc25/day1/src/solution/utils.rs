use std::io::{self, BufRead, BufReader};
use std::{fs::File, path::Path};

#[derive(Debug)]
pub enum Direction {
    Left,
    Right,
}

impl Direction {
    pub fn from_str(s: &str) -> Option<Direction> {
        match s {
            "L" => Some(Direction::Left),
            "R" => Some(Direction::Right),
            _ => None,
        }
    }
}

pub fn read_file_to_vec(file_path: &Path) -> io::Result<Vec<String>> {
    let file = File::open(file_path)?;
    let reader = BufReader::new(file);
    let lines: Vec<String> = reader.lines().collect::<Result<_, _>>()?;

    Ok(lines)
}

pub fn extract_direction_and_distance(line: &str) -> Option<(Direction, i32)> {
    let direction_str = &line[0..1];
    let distance_str = &line[1..];

    let direction = Direction::from_str(direction_str)?;
    let distance = distance_str.parse::<i32>().ok()?;

    Some((direction, distance))
}
