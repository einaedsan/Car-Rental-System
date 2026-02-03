#pragma once
#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

enum UserRole {
    CUSTOMER,
    STAFF,
    MANAGER
};

class User {
protected:
    int userId;
    string name;
    string username;
    string passwordHash;
    UserRole role;
    bool isBlocked;

public:
    User();
    User(int id, string n, string u, string hash, UserRole r);

    int getUserId() const;
    string getUsername() const;
    UserRole getRole() const;
    bool blocked() const;
    void setBlocked(bool status);

    virtual ~User() {}
};

#endif
