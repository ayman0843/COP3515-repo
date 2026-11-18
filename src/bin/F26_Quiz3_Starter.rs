// Quiz 3 starter program: University Bookstore
// This program accepts up to 10 books, calculates a subtotal,
// displays a receipt, and saves the receipt to a text file.

use std::fs;
use std::io::{self, Write};

const MAX_ITEMS: usize = 10;
const RECEIPT_FILE: &str = "receipt.txt";
const DISCOUNT_MIN_BOOKS: usize = 5; // NEW
const DISCOUNT_RATE: f64 = 0.10; // NEW: 10% discount
const TAX_RATE: f64 = 0.07; // NEW: 7% sales tax

fn read_line(prompt: &str) -> String {
    print!("{prompt}");
    io::stdout().flush().expect("Could not flush output");

    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Could not read input");

    input.trim().to_string()
}

fn calculate_total(items: &Vec<(String, f64)>) -> f64 {
    let mut total = 0.0;

    for item in items {
        total += item.1;
    }

    total
}

// NEW: returns the most expensive book, or None if the list is empty.
fn find_most_expensive(items: &Vec<(String, f64)>) -> Option<&(String, f64)> {
    let mut best: Option<&(String, f64)> = None;

    for item in items {
        match best {
            Some(current) if current.1 >= item.1 => {} // keep current best
            _ => best = Some(item),                    // first book or a pricier one
        }
    }

    best
}

fn main() {
    let store_name = String::from("USF Bookstore");
    let categories = ["Fiction", "Science", "History"];

    println!(
        "{} | Categories: {}, {}, {}",
        store_name, categories[0], categories[1], categories[2]
    );

    let mut items: Vec<(String, f64)> = Vec::new();
    let mut keep_going = true;

    // Continue until the employee enters "done" or reaches the item limit.
    while keep_going && items.len() < MAX_ITEMS {
        let name = read_line("Book name (or 'done'): ");

        if name.to_lowercase() == "done" {
            keep_going = false;
        } else if name.len() == 0 {
            println!("Book name cannot be blank.");
        } else {
            let price: f64 = loop {
                let price_text = read_line("Price in dollars: ");

                match price_text.parse::<f64>() {
                    Ok(value) if value >= 0.0 => break value,
                    Ok(_) => println!("Price cannot be negative."),
                    Err(_) => println!("Enter a numeric price, such as 12.50."),
                }
            };

            items.push((name, price));
        }
    }

    let subtotal = calculate_total(&items);
    let item_count = items.len();

    // NEW: 10% discount only for five or more books.
    let discount_amount = if item_count >= DISCOUNT_MIN_BOOKS {
        subtotal * DISCOUNT_RATE
    } else {
        0.0
    };

    // NEW: tax is calculated on the amount after the discount.
    let discounted_amount = subtotal - discount_amount;
    let tax_amount = discounted_amount * TAX_RATE;
    let final_total = subtotal - discount_amount + tax_amount;

    // NEW: build the most-expensive-book line from the actual entered data.
    let most_expensive_line = match find_most_expensive(&items) {
        Some((name, price)) => format!("Most expensive: {name} (${price:.2})"),
        None => String::from("Most expensive: N/A"),
    };

    let mut receipt = String::new();
    receipt.push_str(&format!("{store_name}\n"));

    for (name, price) in &items {
        receipt.push_str(&format!("{name}: ${price:.2}\n"));
    }

    receipt.push_str(&format!("Items: {item_count}\n"));
    receipt.push_str(&format!("Subtotal: ${subtotal:.2}\n"));
    receipt.push_str(&format!("Discount: ${discount_amount:.2}\n")); // NEW
    receipt.push_str(&format!("Tax: ${tax_amount:.2}\n")); // NEW
    receipt.push_str(&format!("Final total: ${final_total:.2}\n")); // NEW
    receipt.push_str(&format!("{most_expensive_line}\n")); // NEW

    println!("\n{receipt}");

    fs::write(RECEIPT_FILE, &receipt).expect("Could not write receipt");

    let saved_receipt = fs::read_to_string(RECEIPT_FILE).expect("Could not read saved receipt");

    println!("Saved {} bytes to {}.", saved_receipt.len(), RECEIPT_FILE);

    let transaction_ready = item_count > 0 && subtotal >= 0.0;
    let needs_review = !transaction_ready || subtotal > 500.0;

    if transaction_ready {
        println!("Transaction ready.");
    } else {
        println!("No books were entered.");
    }

    if needs_review {
        println!("This transaction needs review.");
    } else {
        println!("No additional review is needed.");
    }

    let transaction_size = match item_count {
        0 => "Empty",
        1..=4 => "Small",
        _ => "Large",
    };

    println!("Transaction size: {transaction_size}");
}
