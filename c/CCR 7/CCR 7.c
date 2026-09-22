#include <stdio.h>

/* Global variable: the current inventory must remain
   available throughout the entire program. */
int currentInventory = 0;

/* Function prototypes */
void getStartingInventory(void);
int processSale(void);
void displayReport(int inventoryBeforeSale, int quantitySold);

int main(void) {
  int quantitySold;
  int inventoryBeforeSale;

  /* Step 1: Employee enters the current inventory quantity. */
  getStartingInventory();

  /* Remember the inventory as it was before the sale, so the
     report can show a clear "before" and "after" comparison. */
  inventoryBeforeSale = currentInventory;

  /* Step 2: Employee enters the quantity purchased, and the
     program updates the inventory to reflect the sale. */
  quantitySold = processSale();

  /* Step 3: Display a clear, professionally formatted report. */
  displayReport(inventoryBeforeSale, quantitySold);

  return 0;
}

/* Prompts the employee for the current inventory quantity and
   stores it in the global inventory variable. */
void getStartingInventory(void) {
  printf("Enter the current inventory quantity: ");
  scanf("%d", &currentInventory);
}

/* Handles a single customer purchase.
   The quantity purchased is LOCAL to this function because it
   is only needed while this one sale is being processed.
   Updates the global inventory and returns the quantity sold
   so the report can display it. */
int processSale(void) {
  int quantityPurchased;

  printf("Enter the quantity purchased by the customer: ");
  scanf("%d", &quantityPurchased);

  /* Update the global inventory to reflect the sale. */
  currentInventory = currentInventory - quantityPurchased;

  return quantityPurchased;
}

/* Displays a clear, professionally formatted transaction
   summary, matching the format requested by the customer. */
void displayReport(int inventoryBeforeSale, int quantitySold) {
  printf("\n----------------------------------------\n");
  printf("Green Valley Supply Company\n");
  printf("Inventory Transaction Summary\n");
  printf("----------------------------------------\n");
  printf("Inventory Before Sale : %d\n", inventoryBeforeSale);
  printf("Products Sold         : %d\n", quantitySold);
  printf("Inventory Remaining   : %d\n", currentInventory);
}
