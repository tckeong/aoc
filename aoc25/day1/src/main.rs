mod solution;
use solution::{p1::P1, p2::P2};

fn main() {
    let solver1 = P1::new("input/input.txt");
    let solver2 = P2::new("input/input.txt");

    let password1 = solver1.solve();
    let password2 = solver2.solve();

    match password1 {
        Some(pw) => println!("The password1 is: {}", pw),
        None => println!("Failed to compute the password1."),
    }

    match password2 {
        Some(pw) => println!("The password2 is: {}", pw),
        None => println!("Failed to compute the password2."),
    }
}
