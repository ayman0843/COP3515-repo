use std::io::{self, Write};

const HOSPITAL_NAME: &str = "Memorial Community Hospital";
const REPORT_TITLE: &str = "Patient Summary Report";
const VERSION: &str = "Version 1.0";
const DIVIDER: &str = "----------------------------------------";

struct Patient {
    id: u32,
    name: String,
    temperature: f64,
    blood_pressure: String,
}

// Prompts the user and returns the trimmed line they typed.
fn read_text(prompt: &str) -> String {
    print!("{}", prompt);
    io::stdout().flush().expect("Failed to flush output");

    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read input");

    input.trim().to_string()
}

// Prompts for a whole number.
fn read_whole_number(prompt: &str) -> usize {
    let text = read_text(prompt);
    text.parse::<usize>().expect("Please enter a whole number")
}

// Prompts for a decimal number (used for temperature).
fn read_decimal(prompt: &str) -> f64 {
    let text = read_text(prompt);
    text.parse::<f64>().expect("Please enter a valid number")
}

// Asks for one patient's information and returns the finished record.
fn read_patient(number: usize) -> Patient {
    println!();
    println!("Patient {}", number);

    let id = read_whole_number("  ID: ") as u32;
    let name = read_text("  Name: ");
    let temperature = read_decimal("  Temperature (F): ");
    let blood_pressure = read_text("  Blood Pressure (e.g. 120/80): ");

    Patient {
        id,
        name,
        temperature,
        blood_pressure,
    }
}

// Works on a slice, so it can average any portion of the patient list.
fn average_temperature(patients: &[Patient]) -> f64 {
    let mut total = 0.0;
    for patient in patients {
        total += patient.temperature;
    }
    total / patients.len() as f64
}

// Prints one patient's block of the report.
fn print_patient(patient: &Patient) {
    println!("{:<15}: {}", "Patient ID", patient.id);
    println!("{:<15}: {}", "Name", patient.name);
    println!("{:<15}: {:.1}°F", "Temperature", patient.temperature);
    println!("{:<15}: {}", "Blood Pressure", patient.blood_pressure);
    println!("{}", DIVIDER);
}

// Prints the full report for the selected slice of patients.
fn print_report(selected: &[Patient], total_patients: usize) {
    println!();
    println!("{}", DIVIDER);
    println!("{}", HOSPITAL_NAME);
    println!("{}", REPORT_TITLE);
    println!("{}", VERSION);
    println!("{}", DIVIDER);

    for patient in selected {
        print_patient(patient);
    }

    println!(
        "Displaying {} of {} patients.",
        selected.len(),
        total_patients
    );
    println!(
        "{:<20}: {:.2}°F",
        "Average Temperature",
        average_temperature(selected)
    );
    println!();
    println!("Report completed successfully.");
}

fn main() {
    println!("{}", HOSPITAL_NAME);
    println!("Patient Entry");
    println!();

    // Number of patients (must be at least 1)
    let mut count = read_whole_number("Number of Patients: ");
    while count < 1 {
        println!("Please enter at least 1 patient.");
        count = read_whole_number("Number of Patients: ");
    }

    // Enter every patient for today, in the order they were admitted.
    let mut patients: Vec<Patient> = Vec::new();
    for number in 1..=count {
        let patient = read_patient(number);
        patients.push(patient);
    }

    // Choose which portion of the list to display (1-based, inclusive).
    println!();
    println!("Choose the patients to display (1 to {}).", count);

    let mut start = read_whole_number("Display patients starting at: ");
    while start < 1 || start > count {
        println!("Start must be between 1 and {}.", count);
        start = read_whole_number("Display patients starting at: ");
    }

    let mut end = read_whole_number("Display patients through: ");
    while end < start || end > count {
        println!("End must be between {} and {}.", start, count);
        end = read_whole_number("Display patients through: ");
    }

    // A slice of just the requested patients (no copying).
    let selected: &[Patient] = &patients[(start - 1)..end];

    print_report(selected, count);
}
