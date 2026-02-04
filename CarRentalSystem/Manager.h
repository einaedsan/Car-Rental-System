#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"

class Manager : public User {
private:
    static Manager* instance;   

    Manager();                  

public:
    static Manager* getInstance();

};

#endif
