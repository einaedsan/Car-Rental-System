#pragma once
#pragma once
#ifndef RENTAL_QUEUE_NODE_H
#define RENTAL_QUEUE_NODE_H

#include "Rental.h"

struct RentalQueueNode {
    Rental* rental;           // اشاره‌گر به شی Rental
    RentalQueueNode* next;

    RentalQueueNode(Rental* r);
};

#endif
