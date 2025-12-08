use crate::solution::utils::{
    UnionFind, generate_distances, lines_to_junction_boxes, read_file_to_lines,
};
use std::cmp::Reverse;
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
        let lines = read_file_to_lines(self.path)?;
        let junction_boxes = lines_to_junction_boxes(&lines);
        let mut distances = generate_distances(&junction_boxes);
        let mut uf = UnionFind::new(junction_boxes.len());
        let result;

        loop {
            if let Some(Reverse((_, i, j))) = distances.pop() {
                uf.union(i, j);

                if uf.all_connected() {
                    result = junction_boxes[i].0 * junction_boxes[j].0;
                    break;
                }
            }
        }

        Some(result)
    }
}
