#include "ManagerMenu.h"

void ManagerMenu::show() {
    bool exitMenu = false;
    while (!exitMenu) {
        std::cout << "\n=== Manager Menu ===\n";
        std::cout << "1. View Income & Performance\n";
        std::cout << "2. Manage Problematic Users\n";
        std::cout << "0. Logout\n";
        std::cout << "Select option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "View Income & Performance coming soon...\n";
            break;
        case 2:
            std::cout << "Manage Problematic Users coming soon...\n";
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            std::cout << "Invalid option! Try again.\n";
        }
    }
}
