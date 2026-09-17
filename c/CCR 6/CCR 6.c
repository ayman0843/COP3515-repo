#include <stdio.h>

const double DISCOUNT_RATE = 0.10;
const double SALES_TAX_RATE = 0.06;

double calculateDiscount(double orderAmount) {
  return orderAmount * DISCOUNT_RATE;
}

double calculateSalesTax(double discountedAmount) {
  double salesTax = discountedAmount * SALES_TAX_RATE;

  return (int)(salesTax * 100.0 + 0.5) / 100.0;
}

double calculateFinalAmount(double orderAmount, double discount,
                            double salesTax) {
  return orderAmount - discount + salesTax;
}

int main(void) {
  double orderAmount;
  double discount;
  double discountedAmount;
  double salesTax;
  double finalAmount;

  printf("Enter order amount: $");
  if (scanf("%lf", &orderAmount) != 1 || orderAmount < 0) {
    printf("Invalid order amount. Please enter a nonnegative number.\n");
    return 1;
  }

  discount = calculateDiscount(orderAmount);
  discountedAmount = orderAmount - discount;
  salesTax = calculateSalesTax(discountedAmount);
  finalAmount = calculateFinalAmount(orderAmount, discount, salesTax);

  printf("\n----------------------------------------\n");
  printf("Sweet Delights Bakery\n");
  printf("Customer Receipt\n");
  printf("----------------------------------------\n");
  printf("Original Order : $%.2f\n", orderAmount);
  printf("Discount       : $%.2f\n", discount);
  printf("Sales Tax      : $%.2f\n", salesTax);
  printf("-------------------------------\n");
  printf("Final Total    : $%.2f\n", finalAmount);

  return 0;
}
