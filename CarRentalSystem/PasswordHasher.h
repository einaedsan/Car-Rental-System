#pragma once
#ifndef PASSWORD_HASHER_H
#define PASSWORD_HASHER_H

#include <string>
using namespace std;

class PasswordHasher {
public:
    static string hash(const string& password);
};

#endif
