use crate::solution::utils;
use std::path::Path;

pub struct SolutionP1<'a> {
    path: &'a Path,
}

impl SolutionP1<'_> {
    pub fn new(path: &str) -> SolutionP1<'_> {
        SolutionP1 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<usize> {
        let lines = utils::read_file_to_lines(self.path)?;
        let (ranges, foods) = utils::get_ranges_and_food(lines);

        let mut count = 0;

        for food in foods {
            for &(start, end) in &ranges {
                if food >= start && food <= end {
                    count += 1;
                    break;
                }
            }
        }

        Some(count)
    }
}
