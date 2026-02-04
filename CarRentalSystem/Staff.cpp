#include "Staff.h"

Staff* Staff::instance = NULL;

Staff::Staff(): User("staff", "123staff") {}

Staff* Staff::getInstance() {
    if (instance == NULL)
        instance = new Staff();
    return instance;
}