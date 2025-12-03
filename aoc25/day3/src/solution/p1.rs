use crate::solution::utils::read_file_to_lines;
use std::path::Path;

pub struct SolutionP1<'a> {
    path: &'a Path,
}

impl SolutionP1<'_> {
    pub fn new(path: &str) -> SolutionP1 {
        SolutionP1 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<u32> {
        let lines = read_file_to_lines(self.path)?;
        let max_batteries = lines.iter().map(|line| self.find_max_batteries(line)).sum();

        Some(max_batteries)
    }

    fn find_max_batteries(&self, line: &str) -> u32 {
        let mut max_battery = 0;
        let line = line.chars().collect::<Vec<char>>();
        let n = line.len();

        for i in 0..n {
            for j in i + 1..n {
                let first_digit = line[i].to_digit(10).unwrap_or(0);
                let second_digit = line[j].to_digit(10).unwrap_or(0);
                let battery = first_digit * 10 + second_digit;

                max_battery = max_battery.max(battery);
            }
        }

        max_battery
    }
}
