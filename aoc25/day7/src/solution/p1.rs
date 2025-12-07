use crate::solution::utils::read_file_to_lines;
use std::{collections::VecDeque, path::Path};

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
        let lines = read_file_to_lines(self.path)?;
        let n = lines.len();
        let m = lines[0].len();
        let mut start = 0;
        let mut result = 0;

        for j in 0..m {
            if lines[0][j] == 'S' {
                start = j;
                break;
            }
        }

        let mut q = VecDeque::new();
        let mut visited = vec![vec![false; m]; n];
        q.push_back((1, start));

        while !q.is_empty() {
            let (i, j) = q.pop_front().unwrap();

            if i >= n || j >= m || visited[i][j] {
                continue;
            }

            visited[i][j] = true;

            if lines[i][j] == '.' {
                q.push_back((i + 1, j));
            } else if lines[i][j] == '^' {
                q.push_back((i + 1, j - 1));
                q.push_back((i + 1, j + 1));
                result += 1;
            }
        }

        Some(result)
    }
}
