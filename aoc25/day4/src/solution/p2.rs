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

    pub fn solve(&self) -> Option<usize> {
        let lines = read_file_to_lines(self.path)?;
        let mut lines = lines
            .iter()
            .map(|s| s.chars().collect::<Vec<char>>())
            .collect::<Vec<Vec<char>>>();
        let mut valid_forklifts_position = self.find_valid_forklifts_position(&lines);
        let mut result = 0;

        while valid_forklifts_position.len() > 0 {
            result += valid_forklifts_position.len();
            self.remove_paper_rolls(&mut lines, &valid_forklifts_position);
            valid_forklifts_position = self.find_valid_forklifts_position(&lines);
        }

        Some(result)
    }

    fn find_valid_forklifts_position(&self, lines: &Vec<Vec<char>>) -> Vec<(usize, usize)> {
        let mut valid_forklifts_position = vec![];
        let n = lines.len();
        let m = lines[0].len();

        for i in 0..n {
            for j in 0..m {
                let paper_rolls = self.count_paper_rolls(&lines, i, j);
                if paper_rolls < 4 {
                    valid_forklifts_position.push((i, j));
                }
            }
        }

        valid_forklifts_position
    }

    fn count_paper_rolls(&self, lines: &Vec<Vec<char>>, x: usize, y: usize) -> usize {
        if lines[x][y] != '@' {
            return usize::MAX;
        }

        let n = lines.len();
        let m = lines[0].len();
        let mut count = 0;

        let x_start = 0.max(x as i32 - 1) as usize;
        let x_end = (n - 1).min(x + 1);
        let y_start = 0.max(y as i32 - 1) as usize;
        let y_end = (m - 1).min(y + 1);

        for i in x_start..=x_end {
            for j in y_start..=y_end {
                if lines[i][j] == '@' {
                    count += 1;
                }
            }
        }

        count - 1
    }

    fn remove_paper_rolls(&self, lines: &mut Vec<Vec<char>>, positions: &Vec<(usize, usize)>) {
        for &(x, y) in positions {
            lines[x][y] = '.';
        }
    }
}
