use std::collections::{HashMap, VecDeque};
use std::path::Path;

use crate::solution::utils::{lines_to_graph, read_file_to_lines};

pub struct SolutionP1<'a> {
    path: &'a Path,
}

impl SolutionP1<'_> {
    pub fn new(path: &str) -> SolutionP1<'_> {
        SolutionP1 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<u32> {
        let lines = read_file_to_lines(self.path)?;
        let graph = lines_to_graph(&lines);
        let result = self.dfs(&graph, "you", "out");

        Some(result)
    }

    fn dfs(&self, graph: &HashMap<String, Vec<String>>, start: &str, end: &str) -> u32 {
        let mut stack = VecDeque::new();
        let mut result = 0;

        stack.push_back(start);

        while let Some(current) = stack.pop_back() {
            if current == end {
                result += 1;
                continue;
            }

            if let Some(neighbours) = graph.get(current) {
                for neighbour in neighbours {
                    stack.push_back(neighbour);
                }
            }
        }

        result
    }
}
