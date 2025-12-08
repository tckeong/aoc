use std::cmp::Reverse;
use std::collections::{BinaryHeap, HashSet};
use std::fs;
use std::path::Path;

pub fn read_file_to_lines(path: &Path) -> Option<Vec<String>> {
    fs::read_to_string(path)
        .ok()?
        .lines()
        .map(|line| line.to_string())
        .collect::<Vec<String>>()
        .into()
}

pub fn lines_to_junction_boxes(lines: &Vec<String>) -> Vec<(u64, u64, u64)> {
    lines
        .iter()
        .filter_map(|line| {
            let parts: Vec<&str> = line.split(',').collect();
            if parts.len() != 3 {
                return None;
            }
            let x = parts[0].parse::<u64>().ok()?;
            let y = parts[1].parse::<u64>().ok()?;
            let z = parts[2].parse::<u64>().ok()?;
            Some((x, y, z))
        })
        .collect()
}

pub fn generate_distances(
    junction_boxes: &Vec<(u64, u64, u64)>,
) -> BinaryHeap<Reverse<(u64, usize, usize)>> {
    let mut distances = BinaryHeap::new();
    let n = junction_boxes.len();

    for i in 0..n {
        for j in (i + 1)..n {
            let (x1, y1, z1) = junction_boxes[i];
            let (x2, y2, z2) = junction_boxes[j];

            let dist = ((x1 as i64 - x2 as i64).pow(2)
                + (y1 as i64 - y2 as i64).pow(2)
                + (z1 as i64 - z2 as i64).pow(2)) as u64;

            distances.push(Reverse((dist, i, j)));
        }
    }

    distances
}

pub struct UnionFind {
    parent: Vec<usize>,
    size: Vec<usize>,
}

impl UnionFind {
    pub fn new(n: usize) -> Self {
        UnionFind {
            parent: (0..n).collect(),
            size: vec![1; n],
        }
    }

    pub fn find(&mut self, x: usize) -> usize {
        if self.parent[x] != x {
            self.parent[x] = self.find(self.parent[x]);
        }

        self.parent[x]
    }

    pub fn union(&mut self, a: usize, b: usize) {
        let mut pa = self.find(a);
        let mut pb = self.find(b);

        if pa == pb {
            return;
        }

        if self.size[pa] < self.size[pb] {
            std::mem::swap(&mut pa, &mut pb);
        }

        self.parent[pb] = pa;
        self.size[pa] += self.size[pb];
    }

    pub fn get_n_largest_sizes(&mut self, n: usize) -> Vec<usize> {
        let mut set_sizes = Vec::new();
        let mut seen = HashSet::new();

        for i in 0..self.parent.len() {
            let root = self.find(i);
            if !seen.contains(&root) {
                seen.insert(root);
                set_sizes.push(self.size[root]);
            }
        }

        set_sizes.sort_unstable_by(|a, b| b.cmp(a));
        set_sizes.into_iter().take(n).collect()
    }

    pub fn all_connected(&mut self) -> bool {
        let root = self.find(0);

        for i in 1..self.parent.len() {
            if self.find(i) != root {
                return false;
            }
        }

        true
    }
}
