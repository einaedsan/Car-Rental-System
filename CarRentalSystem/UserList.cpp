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
    UserNode* node = new UserNode;
    node->data = user;
    node->next = NULL;
    node->prev = tail;

    if (head == NULL) {
        head = node;
        tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }
}

User* UserList::findByUsername(string username) {
    UserNode* cur = head;
    while (cur != NULL) {
        if (cur->data->getUsername() == username)
            return cur->data;
        cur = cur->next;
    }
    return NULL;
}

UserNode* UserList::getHead() const {
    return head;
}

