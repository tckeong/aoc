use crate::solution::utils::read_file_to_lines;
use std::path::Path;

pub struct SolutionP2<'a> {
    path: &'a Path,
}

impl SolutionP2<'_> {
    pub fn new(path: &str) -> SolutionP2 {
        SolutionP2 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<u64> {
        let lines = read_file_to_lines(self.path)?;
        let max_batteries = lines
            .iter()
            .map(|line| self.find_max_battery_for_line(line))
            .sum::<Option<u64>>();

        max_batteries
    }

    fn find_max_battery_for_line(&self, line: &str) -> Option<u64> {
        let total_digits = 12;
        let line = line
            .chars()
            .map(|c| c.to_digit(10).map(|d| d))
            .collect::<Option<Vec<u32>>>()?;
        let mut max_battery = 0;

        let mut buf = vec![0u32; total_digits];

        fn find_max_battery(buf: &mut [u32], digit: u32, idx: usize, total_digits: usize) {
            if idx >= total_digits || digit < buf[idx] {
                return;
            }

            let next_digit = buf[idx];
            buf[idx] = digit;
            find_max_battery(buf, next_digit, idx + 1, total_digits);
        }

        for (i, &c) in line.iter().rev().enumerate() {
            if i < total_digits {
                buf[total_digits - 1 - i] = 0;
            } else {
                find_max_battery(&mut buf, c, 0, total_digits);
            }

            let battery = buf.iter().fold(0u64, |acc, &d| acc * 10 + d as u64);
            max_battery = max_battery.max(battery);
        }

        Some(max_battery)
    }
}
