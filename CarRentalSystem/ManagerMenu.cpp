#include "ManagerMenu.h"
#include "Manager.h"
#include "ConsoleColor.h"



void ManagerMenu::show(Fleet& fleet, RentalQueue& rentals, UserList& users, MaintenanceList& maintenance, ReservationPriorityQueue& reservations) {
    bool exitMenu = false;
    while (!exitMenu) {
        setTextColor(TC_DARK_YELLOW);
        std::cout << "\n=== Manager Menu ===\n";
        std::cout << "1. View Income & Performance\n";
        std::cout << "2. Manage Problematic Users\n";
        std::cout << "3. Backup System\n";
        std::cout << "4. Restore System\n";
        std::cout << "0. Logout\n";
        std::cout << "Select option: ";
        resetColor();

        int choice;
        std::cin >> choice;
        Manager* manager = Manager::getInstance();


        switch (choice) {
        case 1: {
            manager->generateReport(fleet, rentals);
            break;
        }
        case 2: {
            bool exitUserMenu = false;
            while (!exitUserMenu) {
                // 1. لیست همه کاربران
                UserNode* cur = users.getHead();
                std::cout << "\n=== Users List ===\n";
                while (cur) {
                    User* u = cur->data;
                    std::cout << "ID: " << u->getId()
                        << " | Name: " << u->getName()
                        << " | Debt: " << u->getDebt()
                        << " | Active Rentals: " << u->getActiveRentalsCount()
                        << " | Blocked: " << (u->blocked() ? "Yes" : "No")
                        << "\n";
                    cur = cur->next;
                }

                // 2. انتخاب کاربر برای بلاک/آنبلاک
                std::cout << "\nEnter user ID to block/unblock (0 to return to main menu): ";
                int userId;
                std::cin >> userId;
                if (userId == 0) break; // خروج از این منوی داخلی

                User* target = users.findById(userId);
                if (!target) {
                    std::cout << "User not found.\n";
                    continue; // دوباره از اول بپرس
                }

                // 3. تغییر وضعیت بلاک
                target->setBlocked(!target->blocked());
                std::cout << "User " << target->getName()
                    << " is now " << (target->blocked() ? "BLOCKED" : "UNBLOCKED") << ".\n";

                // 4. ذخیره خودکار تغییر در CSV
                UserStorage::saveToCSV(users, "users.csv");

                // می‌تونی اینجا یه پیام کوچیک بدی که مدیر بتونه تصمیم بگیره ادامه بده یا نه
                std::cout << "Do you want to manage another user? (1=Yes, 0=No): ";
                int cont;
                std::cin >> cont;
                if (cont == 0) exitUserMenu = true;
            }
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
