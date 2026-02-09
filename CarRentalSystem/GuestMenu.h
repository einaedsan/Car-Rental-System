#pragma once
#ifndef GUESTMENU_H
#define GUESTMENU_H
#include "UserList.h"
#include "AuthManager.h"
#include "Fleet.h"
#include <iostream>

class GuestMenu {

public:

    static void show(UserList& users, Fleet& fleet);
};

#endif
