#include "Manager.h"
#include "UserStorage.h"
#include "FleetStorage.h"
#include "RentalStorage.h"
#include "MaintenanceStorage.h"
#include "ReservationStorage.h"

Manager* Manager::instance = NULL;

Manager::Manager(): User("admin", "123admin") {}

Manager* Manager::getInstance() {
    if (instance == NULL)
        instance = new Manager();
    return instance;
}

void Manager::generateReport(Fleet& fleet, RentalQueue& rentals) {

    double totalIncome = rentals.calculateTotalIncome();

    int totalCars = fleet.getTotalCars();
    int rentedCars = fleet.getRentedCarsCount();

    double utilizationRate = 0;
    if (totalCars > 0)
        utilizationRate = (double)rentedCars / totalCars * 100;

    std::cout << "\n======= MANAGER REPORT =======\n";
    std::cout << "Total Income: " << totalIncome << "\n";
    std::cout << "Total Cars: " << totalCars << "\n";
    std::cout << "Currently Rented Cars: " << rentedCars << "\n";
    std::cout << "Utilization Rate: " << utilizationRate << "%\n";
}

void Manager::exportAllData(Fleet& fleet, UserList& users, RentalQueue& rentals, MaintenanceList& maintenance, ReservationPriorityQueue& reservations) {

    UserStorage::saveToCSV(users, "users.csv");
    FleetStorage::saveCars(fleet, "cars.csv");
    RentalStorage::saveToCSV(rentals, "rentals.csv");
    MaintenanceStorage::save(maintenance, "maintenance.csv");
    ReservationStorage::saveToCSV(reservations, "reservations.csv");

    std::cout << "✅ Full system backup completed.\n";
}

void Manager::importAllData(Fleet& fleet, UserList& users, RentalQueue& rentals, MaintenanceList& maintenance, ReservationPriorityQueue& reservations)
{

    UserStorage::loadFromCSV(users, "users.csv");
    FleetStorage::loadCars(fleet, "cars.csv");
    MaintenanceStorage::load(maintenance, "maintenance.csv");
    RentalStorage::loadFromCSV(rentals, "rentals.csv");
    ReservationStorage::loadFromCSV(reservations, "reservations.csv");

    std::cout << "✅ Full system restored successfully.\n";
}
