use std::io;

const LINE: &str = "----------------------------------------";
const VERSION: &str = "1.0";

// Assumption (see questions for the customer): spaces count as characters.
// Set to false to count only non-space characters.
const COUNT_SPACES: bool = true;

fn print_header() {
    println!("{}", LINE);
    println!("Precision Document Editing Services");
    println!("Document Analysis Summary");
    println!("Version {}", VERSION);
    println!("{}", LINE);
}

// Characters that belong inside a word. Everything else (periods, commas,
// quotes, etc.) is ignored when measuring a word's length.
fn is_word_char(c: char) -> bool {
    c.is_alphanumeric() || c == '\'' || c == '-'
}

fn count_characters(text: &str) -> u32 {
    let mut characters = 0;
    for c in text.chars() {
        if COUNT_SPACES || !c.is_whitespace() {
            characters += 1;
        }
    }
    characters
}

// A word is any group of characters separated by whitespace.
fn count_words(text: &str) -> u32 {
    let mut words = 0;
    let mut in_word = false;
    for c in text.chars() {
        if c.is_whitespace() {
            in_word = false;
        } else if !in_word {
            in_word = true;
            words += 1;
        }
    }
    words
}

// Returns the longest word (punctuation removed). If several words tie,
// the first one encountered is kept because only ">" replaces the winner.
fn find_longest_word(text: &str) -> String {
    let mut longest = String::new();
    let mut longest_len: u32 = 0;
    let mut current = String::new();
    let mut current_len: u32 = 0;

    // A trailing space guarantees the final word gets checked.
    let mut padded = String::from(text);
    padded.push(' ');

    for c in padded.chars() {
        if c.is_whitespace() {
            if current_len > longest_len {
                longest.clear();
                longest.push_str(&current);
                longest_len = current_len;
            }
            current.clear();
            current_len = 0;
        } else if is_word_char(c) {
            current.push(c);
            current_len += 1;
        }
    }

    longest
}

fn main() {
    println!("Enter Paragraph:");

    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read input");

    // Remove the Enter key's newline and any leading/trailing spaces.
    let paragraph = input.trim();

    let characters = count_characters(paragraph);
    let words = count_words(paragraph);
    let longest_word = find_longest_word(paragraph);

    println!();
    print_header();
    println!("{:<12} : {}", "Characters", characters);
    println!("{:<12} : {}", "Words", words);
    if words == 0 {
        println!("{:<12} : (none)", "Longest Word");
    } else {
        println!("{:<12} : {}", "Longest Word", longest_word);
    }
    println!();
    println!("Analysis completed successfully.");
}
