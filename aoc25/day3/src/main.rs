mod solution;

use solution::p1::SolutionP1;
use solution::p2::SolutionP2;

fn main() {
    let solver1 = SolutionP1::new("input/input.txt");
    let solver2 = SolutionP2::new("input/input.txt");

    let result1 = solver1.solve();
    let result2 = solver2.solve();

    match result1 {
        Some(value) => println!("Part 1 Result: {}", value),
        None => println!("Part 1 could not be solved."),
    }

    match result2 {
        Some(value) => println!("Part 2 Result: {}", value),
        None => println!("Part 2 could not be solved."),
    }
}
