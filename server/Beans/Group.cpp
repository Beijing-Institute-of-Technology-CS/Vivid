//
// Created by YichengChen on 9/1/19.
//

#include "Group.h"

int Group::getGId() const {
    return gId;
}

void Group::setGId(int gId) {
    Group::gId = gId;
}

const std::vector<User> &Group::getUsers() const {
    return users;
}

void Group::setUsers(const std::vector<User> users) {
    Group::users = users;
}
