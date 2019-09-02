//
// Created by YichengChen on 9/1/19.
//

#ifndef SERVER_GROUP_H
#define SERVER_GROUP_H

#include <vector>

#include "User.h"

class Group {
public:
    int getGId() const;
    void setGId(int gId);

    const std::vector<User> &getUsers() const;

    void setUsers(const std::vector<User> users);

private:
    int gId;

    std::vector<User> users;
};


#endif //SERVER_GROUP_H
