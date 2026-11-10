use std::io;

const LINE: &str = "----------------------------------------";

fn main() {
    // Stores every customer in the order they were entered.
    let mut waiting_list: Vec<String> = Vec::new();

    // Controls the main entry loop.
    let mut add_another = true;

    while add_another {
        // ---- Get a customer name (re-ask if left blank) ----
        let mut name = String::new();

        while name.is_empty() {
            println!("Customer Name:");

            let mut input = String::new();
            io::stdin()
                .read_line(&mut input)
                .expect("Failed to read input");

            name = input.trim().to_string();

            if name.is_empty() {
                println!("Customer name cannot be blank. Please try again.");
            }
        }

        waiting_list.push(name);

        // ---- Ask whether to add another (re-ask until Y or N) ----
        let mut answered = false;

        while !answered {
            println!("Add another customer? (Y/N)");

            let mut input = String::new();
            io::stdin()
                .read_line(&mut input)
                .expect("Failed to read input");

            let answer = input.trim();

            if answer == "Y" || answer == "y" {
                answered = true;
            } else if answer == "N" || answer == "n" {
                answered = true;
                add_another = false;
            } else {
                println!("Please enter Y or N.");
            }
        }
    }

    // ---- Display the report ----
    let total = waiting_list.len();

    println!();
    println!("{}", LINE);
    println!("Harbor View Restaurant");
    println!("Waiting List Summary");
    println!("Version 1.0");
    println!("{}", LINE);
    println!("Customers Waiting");

    let mut i = 0;
    while i < total {
        println!("{}. {}", i + 1, waiting_list[i]);
        i += 1;
    }

    println!("{}", LINE);
    println!("Total Customers : {}", total);
    println!("First Customer : {}", waiting_list[0]);
    println!("Last Customer : {}", waiting_list[total - 1]);
    println!();
    println!("Waiting list completed successfully.");
}
