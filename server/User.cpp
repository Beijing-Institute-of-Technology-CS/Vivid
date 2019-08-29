//
// Created by YichengChen on 8/28/19.
//

#include "User.h"

bool User::isInUse() const {
    return is_in_use;
}

void User::setIsInUse(bool isInUse) {
    is_in_use = isInUse;
}

int User::getSd() const {
    return sd;
}

void User::setSd(int sd) {
    User::sd = sd;
}

const char *User::getName() const {
    return name;
}

const char *User::getBuffer() const {
    return buffer;
}

User::User() {
    is_in_use = false;
}
