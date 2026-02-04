#pragma once
#ifndef USER_H
#define USER_H

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[36m"
#include <string>
using namespace std;

class User {
protected:

    int id;
    string name;
    string username;
    string passwordHash;
    bool isBlocked;

public:
    User();
    User(int Id, const string& n, const string& u, const string& pas);
    User(const string& u, const string& pas);


    int getId() const;
    string getName() const;
    string getUsername() const;
    bool blocked() const;
    void setBlocked(bool status);
    string getPasswordHash() const;


    virtual ~User() {}
};

#endif
