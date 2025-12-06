use crate::solution::utils;
use std::path::Path;

pub struct SolutionP2<'a> {
    path: &'a Path,
}

impl SolutionP2<'_> {
    pub fn new(path: &str) -> SolutionP2<'_> {
        SolutionP2 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<u64> {
        let lines = utils::read_file_to_lines(self.path)?;
        let lines = utils::process_lines2(&lines);

        let answer_of_columns = self.count_columns(&lines);
        let result = answer_of_columns.iter().sum();

        Some(result)
    }

    fn count_columns(&self, lines: &Vec<Vec<&str>>) -> Vec<u64> {
        let n = lines.len();
        let m = lines[0].len();
        let lines = lines
            .iter()
            .map(|row| {
                row.iter()
                    .map(|s| s.chars().collect::<Vec<char>>())
                    .collect::<Vec<Vec<char>>>()
            })
            .collect::<Vec<Vec<Vec<char>>>>();
        let mut result = vec![0; m];

        for i in 0..m {
            match lines[n - 1][i][0] {
                '*' => result[i] = 1,
                _ => {}
            }
        }

        for j in 0..m {
            let l = lines[0][j].len();

            for k in 0..l {
                let mut num = 0;

                for i in 0..n - 1 {
                    if lines[i][j][k] == ' ' {
                        continue;
                    }

                    num = num * 10 + lines[i][j][k].to_digit(10).unwrap_or(0) as u64;
                }

                match lines[n - 1][j][0] {
                    '*' => result[j] *= num,
                    '+' => result[j] += num,
                    _ => {}
                }
            }
        }

        result
    }
}
