#pragma once
#ifndef STAFF_H
#define STAFF_H

#include "User.h"

class Staff : public User {
private:
    static Staff* instance;
    Staff();

public:
    static Staff* getInstance();

};

#endif