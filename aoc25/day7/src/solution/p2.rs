use crate::solution::utils::read_file_to_lines;
use std::{collections::VecDeque, path::Path};

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
        let lines = read_file_to_lines(self.path)?;
        let n = lines.len();
        let m = lines[0].len();
        let mut start = 0;

        for j in 0..m {
            if lines[0][j] == 'S' {
                start = j;
                break;
            }
        }

        let mut q = VecDeque::new();
        let mut visited = vec![vec![false; m]; n];
        let mut dp = vec![vec![0u64; m]; n];
        dp[0][start] = 1;
        visited[0][start] = true;
        q.push_back(start);

        for i in 1..n {
            let mut next_q = VecDeque::new();

            while !q.is_empty() {
                let j = q.pop_front().unwrap();

                if lines[i][j] == '.' {
                    dp[i][j] += dp[i - 1][j];

                    if !visited[i][j] {
                        visited[i][j] = true;
                        next_q.push_back(j);
                    }
                } else if lines[i][j] == '^' {
                    if j > 0 {
                        dp[i][j - 1] += dp[i - 1][j];

                        if !visited[i][j - 1] {
                            visited[i][j - 1] = true;
                            next_q.push_back(j - 1);
                        }
                    }

                    if j + 1 < m {
                        dp[i][j + 1] += dp[i - 1][j];

                        if !visited[i][j + 1] {
                            visited[i][j + 1] = true;
                            next_q.push_back(j + 1);
                        }
                    }
                }
            }
            q = next_q;
        }

        let result = dp[n - 1].iter().sum();

        Some(result)
    }
}
