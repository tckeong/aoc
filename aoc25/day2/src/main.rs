mod solution;

use solution::{p1::SolutionP1, p2::SolutionP2};

fn main() {
    let solver1 = SolutionP1::new("input/input.txt");
    let result1 = solver1.solve();

    println!("Result for part 1: {}", result1);

    let solver2 = SolutionP2::new("input/input.txt");
    let result2 = solver2.solve();

    println!("Result for part 2: {}", result2);
}
