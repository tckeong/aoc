use super::utils::{extract_direction_and_distance, read_file_to_vec, Direction};
use std::path::Path;

pub struct P1<'a> {
    path: &'a Path,
}

impl<'a> P1<'a> {
    pub fn new(path: &'static str) -> Self {
        P1 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<i32> {
        let lines = read_file_to_vec(self.path).ok()?;
        let directions_and_distances = lines
            .iter()
            .filter_map(|line| extract_direction_and_distance(line))
            .collect::<Vec<(Direction, i32)>>();

        const MAX_DISTANCE: i32 = 100;

        let mut current_distance = 50;
        let mut password = 0;

        for (direction, distance) in directions_and_distances {
            current_distance =
                (current_distance + Self::get_distance(&direction, distance)) % MAX_DISTANCE;

            if current_distance == 0 {
                password += 1;
            }
        }

        Some(password)
    }

    fn get_distance(direction: &Direction, distance: i32) -> i32 {
        const MAX_DISTANCE: i32 = 100;

        match direction {
            Direction::Left => MAX_DISTANCE - (distance % MAX_DISTANCE),
            Direction::Right => distance,
        }
    }
}
