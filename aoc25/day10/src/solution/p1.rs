use crate::solution::utils::{Machine, lines_to_machines, read_file_to_lines};
use std::collections::{HashSet, VecDeque};
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

    pub fn solve(&self) -> Option<u32> {
        let lines = read_file_to_lines(self.path)?;
        let machines = lines_to_machines(&lines);
        let mut result = 0;

        for machine in machines {
            let min_toggle = self.bfs(&machine);
            result += min_toggle.unwrap_or(0);
        }

        Some(result)
    }

    fn bfs(&self, machine: &Machine) -> Option<u32> {
        let mut queue: VecDeque<(u32, u16)> = VecDeque::new();
        let mut visited: HashSet<u16> = HashSet::new();
        let n = machine.buttons.len();

        queue.push_back((0, 0));
        visited.insert(0);

        while let Some((toggles, current_lights)) = queue.pop_front() {
            if current_lights == machine.indicator_lights {
                return Some(toggles);
            }

            for i in 0..n {
                let button = machine.buttons[i];
                let next_lights = current_lights ^ button;

                if !visited.contains(&next_lights) {
                    visited.insert(next_lights);
                    queue.push_back((toggles + 1, next_lights));
                }
            }
        }

        None
    }
}
