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

    pub fn solve(&self) -> Option<usize> {
        let lines = utils::read_file_to_lines(self.path)?;
        let (mut ranges, _) = utils::get_ranges_and_food(lines);

        ranges.sort_unstable();
        let merged_ranges = Self::merge_intervals(&mut ranges);

        let mut count = 0;

        for range in merged_ranges {
            count += range.1 - range.0 + 1;
        }

        Some(count)
    }

    fn merge_intervals(ranges: &mut Vec<(usize, usize)>) -> Vec<(usize, usize)> {
        if ranges.is_empty() {
            return vec![];
        }

        let mut merged = Vec::new();
        let mut current_start = ranges[0].0;
        let mut current_end = ranges[0].1;

        for &(start, end) in ranges.iter().skip(1) {
            if start <= current_end {
                current_end = current_end.max(end);
            } else {
                merged.push((current_start, current_end));
                current_start = start;
                current_end = end;
            }
        }

        merged.push((current_start, current_end));
        merged
    }
}
