#pragma once
#ifndef USER_LIST_H
#define USER_LIST_H

#include "UserNode.h"
struct HashNode {
    User* data;
    HashNode* next;
};

class UserHashTable {
private:
    static const int TABLE_SIZE = 100;
    HashNode* table[TABLE_SIZE];
public:
    UserHashTable();                 // سازنده
    int hash(const string& username);
    void insert(User* user);
    User* find(const string& username);
};

class UserList {

private:

    UserNode* head;
    UserNode* tail;
    int lastId;
    UserHashTable hashTable; // جدول هش داخلی برای جستجوی سریع


public:

    UserList();
    void syncLastId(int id);
    int generateNextId();
    void add(User* user);
    User* findByUsername(string username);
    UserNode* getHead() const;
};




#endif

