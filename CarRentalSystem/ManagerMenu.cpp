#include "ManagerMenu.h"
#include "Manager.h"


void ManagerMenu::show(Fleet& fleet, RentalQueue& rentals, User& users) {
    bool exitMenu = false;
    while (!exitMenu) {
        std::cout << "\n=== Manager Menu ===\n";
        std::cout << "1. View Income & Performance\n";
        std::cout << "3. Backup System\n";
        std::cout << "4. Restore System\n";
        std::cout << "0. Logout\n";
        std::cout << "Select option: ";

        int choice;
        std::cin >> choice;
        Manager* manager = Manager::getInstance();


        switch (choice) {
        case 1: {
            manager->generateReport(fleet, rentals);
            break;
        }
        case 3:
            manager->exportAllData(fleet, users, rentals, maintenance, reservations);
            break;

        case 4:
            manager->importAllData(fleet, users, rentals, maintenance, reservations);
            break;

        case 0:
            exitMenu = true;
            break;
        default:
            std::cout << "Invalid option! Try again.\n";
        }
    }
}
