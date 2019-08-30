//
// Created by YichengChen on 8/30/19.
//

#include "Client.h"

Client::Client() {
    fd = 0;
    uId = 0;
}

int Client::getFd() const {
    return fd;
}

void Client::setFd(int fd) {
    Client::fd = fd;
}

int Client::getUId() const {
    return uId;
}

void Client::setUId(int uId) {
    Client::uId = uId;
}
