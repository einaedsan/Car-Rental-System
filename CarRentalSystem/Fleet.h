#pragma once
#ifndef FLEET_H
#define FLEET_H

#include "CarList.h"
#include "AVLTree.h"
#include "RentalQueue.h"

class Fleet {
private:
    CarList cars;    
    AVLTree index;    

public:
    Fleet();

    CarList& getCarList();
    const CarList& getCarList() const;
    void addCar(Car* car);
    void showCarList() const;                 // فهرست ساده
    void showCarDetails(int carId, RentalQueue& rentals) const;   // جزئیات کامل (AVL)
    void filterCars(const char* brand, const char* type, double maxPrice) const;  // فیلتر
    void showAllBrands() const;
    void showAllTypes() const;
    void showCarsByBrand(const string& brand) const;
    void showCarsByType(const string& type) const;

    Car* findCarById(int carId);
};

#endif

