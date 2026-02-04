#include "Manager.h"

Manager* Manager::instance = NULL;

Manager::Manager(): User("admin", "123admin") {}

Manager* Manager::getInstance() {
    if (instance == NULL)
        instance = new Manager();
    return instance;
}
