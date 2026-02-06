#include "StaffMenu.h"

void StaffMenu::show() {
    bool exitMenu = false;
    while (!exitMenu) {
        std::cout << "\n=== Staff Menu ===\n";
        std::cout << "1. Convert Reservation to Rental\n";
        std::cout << "2. Process Car Return\n";
        std::cout << "3. Process Reservation Queue\n";
        std::cout << "4. Add/Edit Car Fleet\n";
        std::cout << "0. Logout\n";
        std::cout << "Select option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Convert Reservation to Rental coming soon...\n";
            break;
        case 2:
            std::cout << "Process Car Return coming soon...\n";
            break;
        case 3:
            std::cout << "Process Reservation Queue coming soon...\n";
            break;
        case 4:
            std::cout << "Add/Edit Car Fleet coming soon...\n";
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            std::cout << "Invalid option! Try again.\n";
        }
    }
}
