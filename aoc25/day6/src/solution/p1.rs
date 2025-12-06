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

    pub fn solve(&self) -> Option<u64> {
        let lines = utils::read_file_to_lines(self.path)?;
        let lines = utils::process_lines1(&lines);

        let answer_of_columns = self.count_columns(&lines);
        let result = answer_of_columns.iter().sum();

        Some(result)
    }

    fn count_columns(&self, lines: &Vec<Vec<&str>>) -> Vec<u64> {
        let n = lines.len();
        let m = lines[0].len();
        let mut result = vec![0; m];

        for i in 0..m {
            match lines[n - 1][i] {
                "*" => result[i] += 1,
                _ => {}
            }
        }

        for i in 0..n - 1 {
            for j in 0..m {
                match lines[n - 1][j] {
                    "*" => result[j] *= lines[i][j].parse::<u64>().unwrap_or(1),
                    "+" => result[j] += lines[i][j].parse::<u64>().unwrap_or(0),
                    _ => {}
                }
            }
        }

        result
    }
}
