#include "PasswordHasher.h"

string PasswordHasher::hash(const string& password) {
    unsigned long hash = 5381;
    for (char c : password)
        hash = ((hash << 5) + hash) + c;
    return to_string(hash);
}
