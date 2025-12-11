use std::collections::HashMap;
use std::path::Path;

use crate::solution::utils::{lines_to_graph, read_file_to_lines};

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
        let graph = lines_to_graph(&lines);
        let (adj, id_map) = self.convert_to_int_graph(&graph);

        let start_id = *id_map.get("svr")?;
        let end_id = *id_map.get("out")?;
        let dac_id = *id_map.get("dac")?;
        let fft_id = *id_map.get("fft")?;

        // 3. Initialize Cache: memo[node_idx][state_mask]
        // State Mask: 0 = None, 1 = DAC, 2 = FFT, 3 = Both
        let mut memo = vec![vec![None; 4]; adj.len()];

        let result = self.count_paths_dp(&adj, start_id, end_id, dac_id, fft_id, 0, &mut memo);
        Some(result)
    }

    fn count_paths_dp(
        &self,
        adj: &Vec<Vec<usize>>,
        current: usize,
        end: usize,
        dac_id: usize,
        fft_id: usize,
        state: usize,
        memo: &mut Vec<Vec<Option<u64>>>,
    ) -> u64 {
        if let Some(cached_count) = memo[current][state] {
            return cached_count;
        }

        // 2. Update State (Bitmask logic)
        // 00 (0) | 01 (1) = 01 (Has DAC)
        // 01 (1) | 10 (2) = 11 (Has Both)
        let mut new_state = state;
        if current == dac_id {
            new_state |= 1;
        }
        if current == fft_id {
            new_state |= 2;
        }

        if current == end {
            // Return 1 if we have visited both (mask is 3), else 0
            return if new_state == 3 { 1 } else { 0 };
        }

        let mut count = 0;
        if let Some(neighbours) = adj.get(current) {
            for &neighbour in neighbours {
                count += self.count_paths_dp(adj, neighbour, end, dac_id, fft_id, new_state, memo);
            }
        }

        memo[current][state] = Some(count);
        count
    }

    fn convert_to_int_graph(
        &self,
        raw_graph: &HashMap<String, Vec<String>>,
    ) -> (Vec<Vec<usize>>, HashMap<String, usize>) {
        let mut id_map: HashMap<String, usize> = HashMap::new();
        let mut next_id = 0;

        for (node, neighbours) in raw_graph {
            if !id_map.contains_key(node) {
                id_map.insert(node.clone(), next_id);
                next_id += 1;
            }

            for neighbour in neighbours {
                if !id_map.contains_key(neighbour) {
                    id_map.insert(neighbour.clone(), next_id);
                    next_id += 1;
                }
            }
        }

        let mut adj = vec![Vec::new(); next_id];
        for (node_str, neighbours_str) in raw_graph {
            let u = id_map[node_str];

            for v_str in neighbours_str {
                let v = id_map[v_str];
                adj[u].push(v);
            }
        }

        (adj, id_map)
    }
}
