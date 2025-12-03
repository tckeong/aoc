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
            .enumerate()
            .map(|(i, line)| self.find_max_batteries(line, i))
            .sum();

        Some(max_batteries)
    }

    fn find_max_batteries(&self, line: &str, line_number: usize) -> u64 {
        let line = line.chars().collect::<Vec<char>>();
        let n = line.len();
        let mut max_battery = 0;

        fn backtracking(
            line: &Vec<char>,
            n: usize,
            index: usize,
            cur_size: usize,
            cur_value: u64,
            max_battery: &mut u64,
        ) {
            if cur_size == 12 {
                *max_battery = (*max_battery).max(cur_value);
                return;
            }

            let max_battery_value = *max_battery / 10u64.pow((12 - cur_size) as u32);

            if index >= n || cur_value < max_battery_value {
                return;
            }

            let digit = line[index].to_digit(10).unwrap() as u64;

            backtracking(
                line,
                n,
                index + 1,
                cur_size + 1,
                cur_value * 10 + digit,
                max_battery,
            );

            backtracking(line, n, index + 1, cur_size, cur_value, max_battery);
        }

        backtracking(&line, n, 0, 0, 0, &mut max_battery);

        println!("Max battery for line {}: {}", line_number + 1, max_battery);

        max_battery
    }
}
