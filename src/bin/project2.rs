fn main() {
    // ---------- Application information ----------
    // Immutable variables: these values never change while the program runs.
    let title: &str = "University Equipment Rental System";
    let version: &str = "1.0";

    // ---------- Equipment record 1 ----------
    let id_1: u32 = 1001;
    let name_1: &str = "Laptop";
    let category_1: &str = "Computer";
    let available_1: bool = true;

    // ---------- Equipment record 2 ----------
    let id_2: u32 = 1002;
    let name_2: &str = "Camera";
    let category_2: &str = "Photography";
    let available_2: bool = true;

    // ---------- Equipment record 3 ----------
    let id_3: u32 = 1003;
    let name_3: &str = "Projector";
    let category_3: &str = "Classroom";
    let available_3: bool = false;

    // ---------- Convert booleans to user-friendly text ----------
    // An if/else expression turns each bool into "Yes" or "No" for display.
    let available_text_1: &str = if available_1 { "Yes" } else { "No" };
    let available_text_2: &str = if available_2 { "Yes" } else { "No" };
    let available_text_3: &str = if available_3 { "Yes" } else { "No" };

    // ---------- Report header ----------
    println!("------------------------------------------------");
    println!("{}", title);
    println!("Version {}", version);
    println!("------------------------------------------------");
    println!("Equipment Inventory");
    println!();

    // ---------- Report body ----------
    println!("ID: {}", id_1);
    println!("Name: {}", name_1);
    println!("Category: {}", category_1);
    println!("Available: {}", available_text_1);
    println!();

    println!("ID: {}", id_2);
    println!("Name: {}", name_2);
    println!("Category: {}", category_2);
    println!("Available: {}", available_text_2);
    println!();

    println!("ID: {}", id_3);
    println!("Name: {}", name_3);
    println!("Category: {}", category_3);
    println!("Available: {}", available_text_3);
}
