#include "StaffMenu.h"
using namespace std;

void StaffMenu::show() {
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n=== Staff Menu ===\n";
        cout << "1. Convert Reservation to Rental\n";
        cout << "2. Process Car Return and Late Fees\n";
        cout << "3. Process Reservation Queue\n";
        cout << "4. Add/Edit Cars in Fleet\n";
        cout << "0. Logout\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "[Placeholder] Convert reservation to rental...\n";
            break;
        case 2:
            cout << "[Placeholder] Process car return and calculate late fees...\n";
            break;
        case 3:
            cout << "[Placeholder] Process reservation queue...\n";
            break;
        case 4:
            cout << "[Placeholder] Add/Edit cars in fleet...\n";
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    }
}
