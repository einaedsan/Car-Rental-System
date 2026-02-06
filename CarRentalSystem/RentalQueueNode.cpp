#include "RentalQueueNode.h"

RentalQueueNode::RentalQueueNode(Rental* r)
    : rental(r), next(nullptr) {
}
