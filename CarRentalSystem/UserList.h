#pragma once
#ifndef USER_LIST_H
#define USER_LIST_H

#include "UserNode.h"

class UserList {

private:

    UserNode* head;
    UserNode* tail;
    int lastId;

public:

    UserList();
    void syncLastId(int id);
    int generateNextId();
    void add(User* user);
    User* findByUsername(string username);
    UserNode* getHead() const;
};

#endif

