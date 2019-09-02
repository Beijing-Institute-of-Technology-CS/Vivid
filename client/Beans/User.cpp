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

const char *User::getUName() const {
    return uName;
}

const char *User::getUPassword() const {
    return uPassword;
}

int User::getFIconFile() const {
    return fIconFile;
}

void User::setFIconFile(int fIconFile) {
    User::fIconFile = fIconFile;
}

void User::setUName (char * a){
    User::uName=a;
}

void User::setUPWD(char * a){
    User::uPassword=a;
}
