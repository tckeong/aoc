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

    pub fn solve(&self) -> Option<i64> {
        let lines = utils::read_file_to_lines(self.path)?;
        let tiles = utils::lines_to_tiles(&lines);
        let area = self.find_area(&tiles);

        let max_area = area.iter().map(|(a, _, _)| *a).max()?;
        Some(max_area)
    }

    fn find_area(&self, tiles: &Vec<(i64, i64)>) -> Vec<(i64, usize, usize)> {
        let n = tiles.len();
        let mut result = Vec::new();

        for i in 0..n {
            for j in (i + 1)..n {
                let (x1, y1) = tiles[i];
                let (x2, y2) = tiles[j];
                let area = ((x2 - x1).abs() + 1) * ((y2 - y1).abs() + 1);

                result.push((area, i, j));
            }
        }

        result
    }
}
