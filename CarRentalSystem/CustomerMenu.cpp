#include "CustomerMenu.h"
#include "AuthManager.h"

using namespace std;

void CustomerMenu::show(UserList& users) {
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n=== Customer Menu ===\n";
        cout << "1. Create Reservation\n";
        cout << "2. View Reservations & Rentals\n";
        cout << "3. Extend Rental\n";
        cout << "4. Pay Fees\n";
        cout << "5. Search Cars\n";
        cout << "6. Show Car Details\n";
        cout << "0. Logout\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "[Placeholder] Create Reservation feature coming soon...\n";
            break;
        case 2:
            cout << "[Placeholder] View Reservations & Rentals feature coming soon...\n";
            break;
        case 3:
            cout << "[Placeholder] Extend Rental feature coming soon...\n";
            break;
        case 4:
            cout << "[Placeholder] Pay Fees feature coming soon...\n";
            break;
        case 5:
            cout << "[Placeholder] Search Cars feature coming soon...\n";
            break;
        case 6:
            cout << "[Placeholder] Show Car Details feature coming soon...\n";
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
