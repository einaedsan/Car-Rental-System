#include "StaffMenu.h"
#include "Staff.h"
#include <iostream>

using namespace std;

void StaffMenu::show(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals) {
    Staff* staff = Staff::getInstance();  // Singleton Staff

    bool exitMenu = false;
    while (!exitMenu) {
        cout << "\n=== Staff Menu ===\n";
        cout << "1. Convert Reservation to Rental\n";
        cout << "2. Process Car Return\n";
        cout << "3. Process Reservation Queue\n";
        cout << "4. Add/Edit Car Fleet\n";
        cout << "5. Send Car To Maintenance\n";
        cout << "6. Finish Maintenance\n";
        cout << "7. Register Maintenance\n";
        cout << "0. Logout\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            staff->convertReservationToRental(fleet, reservations, rentals);
            break;

        case 2:
            staff->processCarReturn(fleet, rentals);
            break;

        case 3:
            staff->processReservationQueue(fleet, reservations, rentals);
            break;

        case 4:
            staff->addEditCar(fleet);
            break;

        case 5:
            staff->sendCarToMaintenance(fleet);
            break;

        case 6:
            staff->finishMaintenance(fleet);
            break;

        case 7:
            staff->registerMaintenance(fleet);
            break;

        case 0:
            exitMenu = true;
            cout << "Logging out...\n";
            break;

        default:
            cout << "Invalid option! Try again.\n";
        }
    }
}
