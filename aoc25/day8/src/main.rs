mod solution;

use solution::p1::SolutionP1;
use solution::p2::SolutionP2;

fn main() {
    let solver1 = SolutionP1::new("input/input.txt");
    let result1 = solver1.solve(1000);

    let solver2 = SolutionP2::new("input/input.txt");
    let result2 = solver2.solve();

    match result1 {
        Some(value) => println!("Part 1 Solution: {}", value),
        None => println!("Part 1 Solution: No solution found"),
    }

    match result2 {
        Some(value) => println!("Part 2 Solution: {}", value),
        None => println!("Part 2 Solution: No solution found"),
    }
}
