#include "GuestMenu.h"
#include "CustomerMenu.h"
#include "StaffMenu.h"
#include "ManagerMenu.h"
#include "AuthManager.h"
#include "UserList.h"
#include "Fleet.h"

#include "ReservationPriorityQueue.h"
#include "RentalQueue.h"
#include <iostream>

using namespace std;

void GuestMenu::show(UserList& users, Fleet& fleet,
    ReservationPriorityQueue& reservations,
    RentalQueue& rentals)
{
    AuthManager auth;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n=== Guest Menu ===\n";
        cout << "1. Register / Login\n";
        cout << "2. Search Cars\n";
        cout << "3. Show Car \n";
        cout << "0. Exit\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: { // Register/Login
            cout << "\nAre you:\n1. Customer\n2. Staff\n3. Manager\nSelect option: ";
            int roleChoice;
            cin >> roleChoice;

            switch (roleChoice) {
            case 1: { // Customer
                int hasAccount;
                cout << "Do you have an account? (1=Yes, 2=No): ";
                cin >> hasAccount;

                User* user = nullptr;

                if (hasAccount == 1) {
                    user = AuthManager::login(users);
                }
                else if (hasAccount == 2) {
                    AuthManager::signUp(users);
                    user = AuthManager::login(users);
                }

                if (user) {
                    CustomerMenu menu;          // فقط سازنده پیش‌فرض
                    menu.show(user, fleet, rentals, users);

                }
                break;
            }

            case 2: // Staff
                if (AuthManager::loginStaff()) {
                    StaffMenu::show(fleet, reservations, rentals, users);
                }
                break;

            case 3: // Manager
                if (AuthManager::loginManager()) {
                    ManagerMenu::show();
                }
                break;

            default:
                cout << "Invalid role option!\n";
                break;
            } // ← پایان switch roleChoice
            break; // ← break برای case 1 اصلی (Register/Login)
        }

        case 2: { // Search Cars
            bool exitFilterMenu = false;
            while (!exitFilterMenu) {
                cout << "\n=== Filter Cars ===\n";
                cout << "1. By Brand\n";
                cout << "2. By Type\n";
                cout << "3. By Price\n";
                cout << "0. Back\n";
                cout << "Select option: ";
                int filterChoice;
                cin >> filterChoice;

                switch (filterChoice) {
                case 1: {
                    fleet.showAllBrands();
                    cout << "Enter brand: ";
                    string brand;
                    cin >> brand;
                    fleet.showCarsByBrand(brand);

                    while (true) {
                        cout << "\nEnter car ID for details (0 to return): ";
                        int id;
                        cin >> id;
                        if (id == 0) break;
                        fleet.showCarDetails(id, rentals);
                    }
                    break;
                }

                case 2: {
                    fleet.showAllTypes();
                    cout << "Enter type: ";
                    string type;
                    cin >> type;
                    fleet.showCarsByType(type);

                    while (true) {
                        cout << "\nEnter car ID for details (0 to return): ";
                        int id;
                        cin >> id;
                        if (id == 0) break;
                        fleet.showCarDetails(id, rentals);

                    }
                    break;
                }

                case 3: {
                    double price;
                    cout << "Enter max price: ";
                    cin >> price;

                    fleet.filterCars(nullptr, nullptr, price);

                    while (true) {
                        cout << "\nEnter car ID for details (0 to return): ";
                        int id;
                        cin >> id;
                        if (id == 0) break;
                        fleet.showCarDetails(id, rentals);

                    }
                    break;
                }

                case 0:
                    exitFilterMenu = true;
                    break;

                default:
                    cout << "Invalid option.\n";
                    break;
                }
            }
            break;
        }

        case 3: { // Show all cars
            fleet.showCarList();
            while (true) {
                cout << "\nEnter car ID to view details (0 to return): ";
                int carId;
                cin >> carId;
                if (carId == 0) break;
                fleet.showCarDetails(carId, rentals);

            }
            break;
        }

        case 0:
            exitMenu = true;
            break;

        default:
            cout << "Invalid option! Try again.\n";
            break;
        } // ← پایان switch(choice)
    }
}
