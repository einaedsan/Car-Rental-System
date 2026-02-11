#include "ReservationLoader.h"
#include "Car.h"
#include "ReservationPriorityQueue.h"

void loadReservationsForCars(CarList* carList, const std::string& filename) {
    // 1. یک صف رزرو موقت بساز
    ReservationPriorityQueue pq;
    ReservationStorage::loadFromCSV(pq, filename); // همه رزروها رو بخون

    // 2. اضافه کردن به ماشین مربوطه
    for (int i = 0; i < pq.getSize(); i++) {
        Reservation* r = pq.getAt(i);
        Car* car = carList->findById(r->getCarId()); // ماشین مربوطه
        if (car) {
            car->getReservationQueue().addReservation(r); // اضافه کردن
        }
    }
}
