#include "CustomerMenu.h"

void CustomerMenu::show(User* user) {
    bool exitMenu = false;
    while (!exitMenu) {
        std::cout << "\n=== Customer Menu ===\n";
        std::cout << "1. Create Reservation\n";
        std::cout << "2. View Reservations\n";
        std::cout << "3. Renew Rental\n";
        std::cout << "4. Pay Fees\n";
        std::cout << "0. Logout\n";
        std::cout << "Select option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Create Reservation feature coming soon...\n";
            break;
        case 2:
            std::cout << "View Reservations feature coming soon...\n";
            break;
        case 3:
            std::cout << "Renew Rental feature coming soon...\n";
            break;
        case 4:
            std::cout << "Pay Fees feature coming soon...\n";
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            std::cout << "Invalid option! Try again.\n";
        }
    }
}
