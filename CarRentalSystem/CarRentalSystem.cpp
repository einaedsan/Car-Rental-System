#include "UserList.h"
#include "UserStorage.h"
#include "GuestMenu.h"

int main() {
    UserList users;

    // Load users from CSV
    UserStorage::loadFromCSV(users, "users.csv");

    // Show guest menu
    GuestMenu::show(users);

    // Save users on exit
    UserStorage::saveToCSV(users, "users.csv");

    return 0;
}
