mod solution;

use crate::solution::p1::SolutionP1;

fn main() {
    let solver1 = SolutionP1::new("input/input.txt");
    let result1 = solver1.solve();

    match result1 {
        Some(value) => println!("Solution P1: {}", value),
        None => println!("Solution P1: No result"),
    }
}
