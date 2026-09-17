#include <stdio.h>

int main(void) {
  const double RATE_PER_HOUR = 2.00;
  int vehicleCount = 0;
  int hoursParked;
  double charge;
  double totalRevenue = 0.0;
  double averageFee;
  char moreVehicles;

  printf("----------------------------------------\n");
  printf("Downtown Parking Services\n");
  printf("Parking Summary\n");
  printf("----------------------------------------\n");

  while (1) {
    vehicleCount++;

    printf("\nVehicle %d Hours Parked: ", vehicleCount);
    scanf("%d", &hoursParked);

    charge = hoursParked * RATE_PER_HOUR;
    totalRevenue += charge;

    printf("Vehicle %d Charge : $%.2f\n", vehicleCount, charge);

    printf("More vehicles? (Y/N): ");
    scanf(" %c", &moreVehicles);

    if (moreVehicles == 'N' || moreVehicles == 'n') {
      break;
    }
  }

  printf("\n----------------------------------------\n");
  printf("Vehicles Processed : %d\n", vehicleCount);
  printf("Total Revenue      : $%.2f\n", totalRevenue);
  averageFee = totalRevenue / vehicleCount;
  printf("Average Parking Fee: $%.2f\n", averageFee);

  return 0;
}
