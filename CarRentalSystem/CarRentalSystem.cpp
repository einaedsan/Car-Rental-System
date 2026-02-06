#include "UserList.h"
#include "UserStorage.h"
#include "GuestMenu.h"
#include "Fleet.h"

int main() {
    UserList users;
    Fleet fleet;

    // Load users from CSV
    UserStorage::loadFromCSV(users, "users.csv");

    // Show guest menu
    GuestMenu::show(users, fleet);

    // Save users on exit
    UserStorage::saveToCSV(users, "users.csv");

    return 0;
}
