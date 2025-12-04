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

    pub fn solve(&self) -> Option<usize> {
        let lines = read_file_to_lines(self.path)?;
        let valid_forklifts_position = self.find_valid_forklifts_position(lines);

        Some(valid_forklifts_position.len())
    }

    fn find_valid_forklifts_position(&self, lines: Vec<String>) -> Vec<(usize, usize)> {
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

    fn count_paper_rolls(&self, lines: &Vec<String>, x: usize, y: usize) -> usize {
        if lines[x].chars().nth(y).unwrap_or('0') != '@' {
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
                if lines[i].chars().nth(j).unwrap_or('0') == '@' {
                    count += 1;
                }
            }
        }

        count - 1
    }
}
