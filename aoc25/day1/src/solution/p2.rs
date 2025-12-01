use super::utils::{extract_direction_and_distance, read_file_to_vec, Direction};
use std::path::Path;

pub struct P2<'a> {
    path: &'a Path,
}

impl<'a> P2<'a> {
    pub fn new(path: &'static str) -> Self {
        P2 {
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
            let (distance, zero_passed) = Self::get_distance(&direction, distance);

            let prev_distance = current_distance;
            current_distance = (current_distance + distance) % MAX_DISTANCE;
            password += zero_passed;

            match direction {
                Direction::Left => {
                    if current_distance > prev_distance {
                        password += 1;
                    }
                }

                Direction::Right => {
                    if current_distance < prev_distance {
                        password += 1;
                    }
                }
            }
        }

        Some(password)
    }

    fn get_distance(direction: &Direction, distance: i32) -> (i32, i32) {
        const MAX_DISTANCE: i32 = 100;

        let zero_passed = distance / MAX_DISTANCE;

        match direction {
            Direction::Left => (MAX_DISTANCE - (distance % MAX_DISTANCE), zero_passed),
            Direction::Right => (distance, zero_passed),
        }
    }
}
