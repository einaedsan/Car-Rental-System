#pragma once
#ifndef USER_NODE_H
#define USER_NODE_H

#include "User.h"

struct UserNode {
    User* data;
    UserNode* next;
    UserNode* prev;
};

#endif