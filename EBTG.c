#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_SEATS 40

FILE *fp;
// Structure to hold seat information
typedef struct {
    int number;
    int is_booked;
} Seat;

// Structure to hold bus information
typedef struct {
    int bus_id;
    char origin[20];
    char destination[20];
    int fare;
    int num_seats;
    Seat seats[MAX_SEATS];
} Bus;

// Global array to hold buses
Bus buses[MAX_BUSES];
int num_buses = 0;
// Add Buses from file bus.txt
void addBusesFromFile() {
    fp=fopen("bus.txt","r");
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %d %d",&buses[i].bus_id,buses[i].origin,buses[i].destination,&buses[i].fare,&buses[i].num_seats);
        for (int j = 0; j < buses[i].num_seats; j++) {
            buses[i].seats[j].number = j + 1;
            buses[i].seats[j].is_booked = 0;
        }
        i++;
    }
    num_buses=i;
    fclose(fp);
}
// Function to display available buses for a route
void displayBuses(char *origin, char *destination) {
    printf("Available buses for %s to %s route:\n", origin, destination);
    int count = 0;
    for (int i = 0; i < num_buses; i++) {
        if (strcmp(buses[i].origin, origin) == 0 && strcmp(buses[i].destination, destination) == 0) {
            printf("%d. Bus ID: %d, Fare: %d\n", count + 1, buses[i].bus_id, buses[i].fare);
            count++;
        }
    }
    if (count == 0) {
        printf("No buses found for %s to %s route.\n", origin, destination);
    }
}

// Function to add a new bus
void addBus() {
    if (num_buses == MAX_BUSES) {
        printf("Maximum number of buses reached.\n");
        return;
    }
    printf("Enter bus ID: ");
    scanf("%d", &buses[num_buses].bus_id);
    printf("Enter origin: ");
    scanf("%s", buses[num_buses].origin);
    printf("Enter destination: ");
    scanf("%s", buses[num_buses].destination);
    printf("Enter fare: ");
    scanf("%d", &buses[num_buses].fare);
    printf("Enter number of seats: ");
    scanf("%d", &buses[num_buses].num_seats);
    for (int i = 0; i < buses[num_buses].num_seats; i++) {
        buses[num_buses].seats[i].number = i + 1;
        buses[num_buses].seats[i].is_booked = 0;
    }
    fp=fopen("bus.txt","a");
    fprintf(fp,"%d %s %s %d %d\n",buses[num_buses].bus_id,buses[num_buses].origin,buses[num_buses].destination,buses[num_buses].fare,buses[num_buses].num_seats);
    num_buses++;
    fclose(fp);
    printf("Bus added successfully.\n");
}

// Function to book a seat
void bookSeat(int bus_id, int seat_number) {
    for (int i = 0; i < num_buses; i++) {
        if (buses[i].bus_id == bus_id) {
            if (seat_number < 1 || seat_number > buses[i].num_seats) {
                printf("Invalid seat number.\n");
                return;
            }
            if (buses[i].seats[seat_number - 1].is_booked) {
                printf("Sorry! Seat already booked.\n");
                return;
            }
            buses[i].seats[seat_number - 1].is_booked = 1;
            printf("Seat %d booked successfully.\n", seat_number);
            return;
        }
    }
    fp=fopen("bus.txt","r");
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %d %d",&buses[i].bus_id,buses[i].origin,buses[i].destination,&buses[i].fare,&buses[i].num_seats);
        if(buses[i].bus_id==bus_id)
        {
            if (seat_number < 1 || seat_number > buses[i].num_seats) {
                printf("Invalid seat number.\n");
                return;
            }
            if (buses[i].seats[seat_number - 1].is_booked) {
                printf("Sorry! Seat already booked.\n");
                return;
            }
            buses[i].seats[seat_number - 1].is_booked = 1;
            printf("Seat %d booked successfully.\n", seat_number);
            return;
        }
        i++;
    }
    fclose(fp);
    printf("Bus not found.\n");
}

// Function to cancel a seat
void cancelSeat(int bus_id, int seat_number) {
    for (int i = 0; i < num_buses; i++) {
        if (buses[i].bus_id == bus_id) {
            if (seat_number < 1 || seat_number > buses[i].num_seats) {
                printf("Invalid seatnumber.\n");
                return;
}
if (!buses[i].seats[seat_number - 1].is_booked) {
printf("Seat not booked.\n");
return;
}
buses[i].seats[seat_number - 1].is_booked = 0;
fp=fopen("bus.txt","r");
printf("Seat %d cancelled successfully.\n", seat_number);
return;
}
}
printf("Bus not found.\n");
}

// Function to delete a bus
void deleteBus(int bus_id) {
for (int i = 0; i < num_buses; i++) {
if (buses[i].bus_id == bus_id) {
for (int j = i; j < num_buses - 1; j++) {
buses[j] = buses[j + 1];
}
num_buses--;
printf("Bus with ID %d deleted successfully.\n", bus_id);
return;
}
}
printf("Bus Not Found.\n");
}

// Function to update a bus
void updateBus(int bus_id) {
for (int i = 0; i < num_buses; i++) {
if (buses[i].bus_id == bus_id) {
printf("Enter new origin: ");
scanf("%s", buses[i].origin);
printf("Enter new destination: ");
scanf("%s", buses[i].destination);
printf("Enter new fare: ");
scanf("%d", &buses[i].fare);
printf("Bus with ID %d updated successfully.\n", bus_id);
return;
}
}
printf("Bus not found.\n");
}

// Main function
int main() {
int choice, bus_id, seat_number;
char origin[20], destination[20];
addBusesFromFile();
while (1) {
    printf("\nElectronic Bus Ticket Generator\n");
    printf("1. Display available buses for a route\n");
    printf("2. Add new bus\n");
    printf("3. Book seat\n");
    printf("4. Cancel seat\n");
    printf("5. Delete a Particular bus\n");
    printf("6. Update a particular bus\n");
    printf("7. Exit\n");
    printf("Enter a Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter origin: ");
            scanf("%s", origin);
            printf("Enter destination: ");
            scanf("%s", destination);
            displayBuses(origin, destination);
            break;
        case 2:
            addBus();
            break;
        case 3:
            printf("Enter bus ID: ");
            scanf("%d", &bus_id);
            printf("Enter Seat Number: ");
            scanf("%d", &seat_number);
            bookSeat(bus_id, seat_number);
            break;
        case 4:
            printf("Enter bus ID: ");
            scanf("%d", &bus_id);
            printf("Enter seat number: ");
            scanf("%d", &seat_number);
            cancelSeat(bus_id, seat_number);
            break;
        case 5:
            printf("Enter Bus id: ");
            scanf("%d", &bus_id);
            deleteBus(bus_id);
            break;
        case 6:
            printf("Enter bus ID: ");
            scanf("%d", &bus_id);
            updateBus(bus_id);
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice.\n");
    }
}

return 0;
}