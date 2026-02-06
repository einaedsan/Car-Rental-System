#include "GuestMenu.h"
#include "CustomerMenu.h"
#include "StaffMenu.h"
#include "ManagerMenu.h"
#include "AuthManager.h"
#include "UserList.h"
#include <iostream>

using namespace std;

void GuestMenu::show(UserList& users) {
    AuthManager auth;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n=== Guest Menu ===\n";
        cout << "1. Register / Login\n";
        cout << "2. Search Cars\n";
        cout << "3. Show Car Details\n";
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
                    CustomerMenu::show(user);
                }
                break; // ← این break برای case 1
            }

            case 2: // Staff
                if (AuthManager::loginStaff())
                    StaffMenu::show();
                break;

            case 3: // Manager
                if (AuthManager::loginManager())
                    ManagerMenu::show();
                break;

            default:
                cout << "Invalid option!\n";
                break;
            }

        case 2:
            cout << "Search Cars feature coming soon...\n";
            break;
        case 3:
            cout << "Show Car Details feature coming soon...\n";
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
        }
    }
}
    