mod solution;

use solution::p1::SolutionP1;
use solution::p2::SolutionP2;

fn main() {
    let solver1 = SolutionP1::new("input/input.txt");
    let result1 = solver1.solve();

    let solver2 = SolutionP2::new("input/input.txt");
    let result2 = solver2.solve();

    match result1 {
        Some(count) => println!("Solution for Part 1: {}", count),
        None => println!("Failed to solve the problem."),
    }

    match result2 {
        Some(count) => println!("Solution for Part 2: {}", count),
        None => println!("Failed to solve the problem."),
    }
}
