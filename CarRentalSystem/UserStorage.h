#pragma once
#ifndef USER_STORAGE_H
#define USER_STORAGE_H

#include <string>
#include "UserList.h"

class UserStorage {

public:
    static void saveToCSV(const UserList& users, const std::string& filename);
    static void loadFromCSV(UserList& users, const std::string& filename);
};

#endif
