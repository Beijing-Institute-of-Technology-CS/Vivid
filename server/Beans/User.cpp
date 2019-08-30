//
// Created by YichengChen on 8/29/19.
//

#include "User.h"

User::User() {}

User::User(int uId, char *uName, char *uPassword, int fIconFile) : uId(uId), uName(uName), uPassword(uPassword),
                                                                     fIconFile(fIconFile) {}

int User::getUId() const {
    return uId;
}

void User::setUId(int uId) {
    User::uId = uId;
}

char *User::getUName() const {
    return uName;
}

void User::setUName(char *uName) {
    User::uName = uName;
}

char *User::getUPassword() const {
    return uPassword;
}

void User::setUPassword(char *uPassword) {
    User::uPassword = uPassword;
}

int User::getFIconFile() const {
    return fIconFile;
}

void User::setFIconFile(int fIconFile) {
    User::fIconFile = fIconFile;
}

int User::getFd() const {
    return fd;
}

void User::setFd(int fd) {
    User::fd = fd;
}
