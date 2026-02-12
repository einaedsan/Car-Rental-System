#include "UserList.h"

UserList::UserList() {
    head = NULL;
    tail = NULL;
    lastId = 0;
}

void UserList::syncLastId(int id) {
    lastId = id;
}

int UserList::generateNextId() {
    return ++lastId;
}

void UserList::add(User* user) {
    // اضافه کردن به لیست دوتایی
    UserNode* node = new UserNode;
    node->data = user;
    node->next = nullptr;
    node->prev = tail;

    if (head == nullptr) head = node;
    else tail->next = node;
    tail = node;

    // اضافه کردن به هش تیبل
    hashTable.insert(user);
}

User* UserList::findByUsername(string username) {
    // به جای جستجوی خطی، از هش تیبل استفاده می‌کنیم
    return hashTable.find(username);
}


UserNode* UserList::getHead() const {
    return head;
}

UserHashTable::UserHashTable() {
    for (int i = 0;i < TABLE_SIZE;i++)
        table[i] = nullptr;
}

int UserHashTable::hash(const string& username) {
    int sum = 0;
    for (char c : username)
        sum += c;
    return sum % TABLE_SIZE;
}

void UserHashTable::insert(User* user) {
    int idx = hash(user->getUsername());
    HashNode* node = new HashNode;
    node->data = user;
    node->next = table[idx];  // اضافه کردن به ابتدای لیست
    table[idx] = node;
}

User* UserHashTable::find(const string& username) {
    int idx = hash(username);
    HashNode* cur = table[idx];
    while (cur != nullptr) {
        if (cur->data->getUsername() == username)
            return cur->data;
        cur = cur->next;
    }
    return nullptr;
}
User* UserList::findById(int id) {
    UserNode* cur = head;
    while (cur) {
        if (cur->data->getId() == id)
            return cur->data;
        cur = cur->next;
    }
    return nullptr;
}
