#include "Car.h"

int Car::nextId = 1;

Car::Car(string Plate, string Brand, string Model, string Type, double Price)
{
    id = nextId++;
    plate = Plate;
    brand = Brand;
    model = Model;
    type = Type;
    pricePerDay = Price;
    status = AVAILABLE;
  
    maintenanceHistory = new MaintenanceList();
    totalMaintenanceCost = 0;

}

Car::Car(int Id, string Plate, string Brand, string Model,
    string Type, double Price, CarStatus Status)
    : id(Id), plate(Plate), brand(Brand), model(Model),
    type(Type), pricePerDay(Price), status(Status)
{
    if (Id >= nextId)
        nextId = Id + 1;

    maintenanceHistory = new MaintenanceList();

    totalMaintenanceCost = 0;
}

Car::~Car()
{
    delete maintenanceHistory;
}

int Car::getId() const {
    return id;
}

string Car::getPlate() const{
    return plate;
}

string Car::getBrand() const {
    return brand;
}

string Car::getModel() const {
    return model;
}

string Car::getType() const { 
    return type; 
}

double Car::getPricePerDay() const {
    return pricePerDay;
}

CarStatus Car::getStatus() const {
    return status;
}

void Car::setStatus(CarStatus s) { 
    status = s;
}

//ReservationQueue* Car::getReservationQueue() const {
//    return reservationQueue;
//}
//
MaintenanceList* Car::getMaintenanceHistory() const {
    return maintenanceHistory;
}

void Car::syncNextId(int maxId) {
    nextId = maxId + 1;
}

ReservationPriorityQueue& Car::getReservationQueue() {
    return reservations;
}

bool Car::isAvailable(int startDay, int endDay, RentalQueue& rentals) const {

    // 1️⃣ اگر تعمیره، کلاً غیر قابل رزرو
    if (status == MAINTENANCE)
        return false;

    // 2️⃣ چک تداخل با رزروهای قبلی
    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* r = reservations.getAt(i);

        if (!(endDay <= r->getStartDay() || startDay >= r->getEndDay())) {
            return false;
        }
    }

    // 3️⃣ چک تداخل با رنت فعال
    Rental* activeRental = rentals.findByCarId(id);

    if (activeRental && activeRental->isActive()) {

        int rentStart = activeRental->getStartDay();
        int rentEnd = activeRental->getExpectedReturnDay();

        if (!(endDay <= rentStart || startDay >= rentEnd)) {
            return false;
        }
    }

    return true;
}


void Car::addMaintenance(Maintenance* m)
{
    if (!m) return;

    maintenanceHistory->addMaintenance(m);
    totalMaintenanceCost += m->getCost();
    status = MAINTENANCE; 
}


void Car::loadMaintenance(Maintenance* m) {
    if (!m) return;

    maintenanceHistory->addMaintenance(m);
    totalMaintenanceCost += m->getCost();
    // اینجا status تغییر نمیکنیم چون از فایل لود شده
}

double Car::getTotalMaintenanceCost() const 
{
    return totalMaintenanceCost;
}

// بررسی وضعیت ماشین بر اساس رزرو، رنت و تعمیرات
void Car::updateStatus(RentalQueue& rentals) {
    // اگر رنت فعال وجود دارد
    Rental* r = rentals.findByCarId(id);
    if (r && r->isActive()) {
        status = RENTED;
        return;
    }

    // اگر رزرو وجود دارد
    if (!reservations.isEmpty()) {
        status = RESERVED;
        return;
    }

    // اگر تعمیرات در انتظار وجود دارد
    if (maintenanceHistory && maintenanceHistory->hasPendingMaintenance()) {
        status = MAINTENANCE;
        return;
    }

    // در غیر اینصورت آزاد است
    status = AVAILABLE;
}

bool Car::isAvailableForExtension(int oldEnd, int newEnd) const {
    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* r = reservations.getAt(i);
        if (r->getEndDay() == oldEnd) // رزرو فعلی خود رنت
            continue;
        if (r->overlaps(oldEnd, newEnd))
            return false;
    }
    return true;
}

bool Car::isAvailableForPeriod(int startDay, int endDay, int ignoreRentalId) const {
    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* r = reservations.getAt(i);

        // اگر مربوط به همون رنتاله، ردش کن
        if (r->getReservationId() == ignoreRentalId)
            continue;

        // چک تداخل
        if (!(endDay <= r->getStartDay() || startDay >= r->getEndDay())) {
            return false;
        }
    }

    return true;
}

void Car::showMaintenanceHistory() {
    cout << "\n=== Maintenance History for Car ID: " << id << " ===\n";

    if (!maintenanceHistory || !maintenanceHistory->getHead()) {
        cout << "No maintenance records found.\n";
        return;
    }

    MaintenanceNode* current = maintenanceHistory->getHead();
    double total = 0;

    while (current) {
        Maintenance* m = current->data;

        cout << "Maintenance ID: " << m->getId()
            << " | Day: " << m->getDay()
            << " | Description: " << m->getDescription()
            << " | Cost: " << m->getCost()
            << endl;

        total += m->getCost();
        current = current->next;
    }

    cout << "-----------------------------------\n";
    cout << "Total Maintenance Cost: " << total << endl;
}

