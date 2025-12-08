use crate::solution::utils::{
    UnionFind, generate_distances, lines_to_junction_boxes, read_file_to_lines,
};
use std::cmp::Reverse;
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

    pub fn solve(&self, merge_times: usize) -> Option<u64> {
        let lines = read_file_to_lines(self.path)?;
        let junction_boxes = lines_to_junction_boxes(&lines);
        let mut distances = generate_distances(&junction_boxes);
        let mut uf = UnionFind::new(junction_boxes.len());

        for _ in 0..merge_times {
            if let Some(Reverse((_, i, j))) = distances.pop() {
                uf.union(i, j);
            }
        }

        let three_largest_sizes = uf.get_n_largest_sizes(3);
        let product = three_largest_sizes.iter().map(|&x| x as u64).product();

        Some(product)
    }
}
