mod solution;

use solution::p1::SolutionP1;
use solution::p2::SolutionP2;

fn main() {
    let solver1 = SolutionP1::new("input/input.txt");
    let result1 = solver1.solve();

    let solver2 = SolutionP2::new("input/input.txt");
    let result2 = solver2.solve();

    match result1 {
        Some(value) => println!("Solution P1: {}", value),
        None => println!("No solution found for P1"),
    }

    match result2 {
        Some(value) => println!("Solution P2: {}", value),
        None => println!("No solution found for P2"),
    }
}
