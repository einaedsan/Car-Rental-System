#pragma once
#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include "UserList.h"

class AuthManager {
public:
    static void signUp(UserList& users);
    static User* login(UserList& users);
    static bool loginManager();
    static bool loginStaff();

};

#endif
