use crate::solution::utils::{Machine, lines_to_machines, read_file_to_lines};
use good_lp::{Solution, SolverModel, default_solver, variable, variables};
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
        let machines = lines_to_machines(&lines);
        let mut result = 0;

        for (i, machine) in machines.iter().enumerate() {
            let min_toggle = self.solve_with_lp(machine);
            result += min_toggle.unwrap_or(0) as u64;

            println!("Machine {i} done.");
        }

        Some(result)
    }

    pub fn solve_with_lp(&self, machine: &Machine) -> Option<u64> {
        let mut vars = variables!();

        // 1. Create a variable for each button (x0, x1, x2...)
        let button_vars: Vec<_> = (0..machine.buttons.len())
            .map(|_| vars.add(variable().min(0).integer()))
            .collect();

        // 2. Define the Objective: Minimize the sum of all button presses
        let objective = button_vars.iter().sum::<good_lp::Expression>();

        // 3. Initialize the problem with the objective
        let mut problem = vars.minimise(objective).using(default_solver);

        // 4. Add Constraints: One equation per bit (voltage dimension)
        // We have 16 dimensions (bits 0 to 15)
        for i in 0..16 {
            let mut expression = good_lp::Expression::from(0);

            // Check which buttons affect this specific bit index 'i'
            let bitmask = 1 << (15 - i); // Calculate bitmask once per row

            for (btn_idx, &button_val) in machine.buttons.iter().enumerate() {
                // If button has this bit set, it contributes to this row
                if (button_val & bitmask) != 0 {
                    expression += button_vars[btn_idx];
                }
            }

            // The sum of all button contributions for this bit must equal the target
            let target_val = *machine.joltage.get(i).unwrap_or(&0) as i32;
            problem.add_constraint(expression.eq(target_val));
        }

        match problem.solve() {
            Ok(solution) => {
                let total_presses: f64 = button_vars.iter().map(|v| solution.value(*v)).sum();
                Some(total_presses as u64)
            }
            Err(_) => None,
        }
    }
}
