//
// Created by William Zhang on 2019-09-02.
//

#include <thread>
#include <iostream>
#include <zconf.h>
#include "NetworkCallbackTesting.h"

NetworkCallback * NetworkCallbackTesting::callback = nullptr;

void NetworkCallbackTesting::setCallback(NetworkCallback *callback) {
    NetworkCallbackTesting::callback = callback;
}

void NetworkCallbackTesting::startTestingThread() {
    std::thread thread(testThread);
    thread.detach();
}

void NetworkCallbackTesting::testThread() {
    std::cout<<"NetworkTestingThreadStarted"<<std::endl;
    int arg;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        scanf("%d", &arg);
        switch (arg) {
            case 0:
                callback->connectFailed();
            case 1:
                callback->netRegisterSuccess(666);
                break;
            case 2:
                callback->netRegisterFailed();
                break;
            case 3:
                callback->netLoginSuccess("NAME!!");
                break;
            case 4:
                callback->netLoginFailed();
                break;
            case 5: {
                std::vector<User> contacts;
                std::vector<Group> groups;

                User user1;
                user1.setUId(1);
                user1.setUName("U1");
                user1.setFIconFile(0);
                contacts.push_back(user1);

                User user2;
                user2.setUId(2);
                user2.setUName("U2");
                user2.setFIconFile(0);
                contacts.push_back(user2);

                Group group1;
                group1.setGId(1);
                groups.push_back(group1);

                Group group2;
                group2.setGId(2);
                groups.push_back(group2);

                callback->netGetInfoSuccess(contacts, groups);
            }
                break;
            default:
                break;
        }
    }
#pragma clang diagnostic pop
}
