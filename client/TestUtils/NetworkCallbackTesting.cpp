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
            case 6:
                callback->netGetMessageFailed();
                break;
            case 7: {
                std::vector<Message> messages;
                Message message1;
                message1.setMId(101);
                message1.setMContent("M101");
                message1.setGroupMessage(true);
                message1.setGId(1);
                message1.setUFromId(11);
                message1.setUFromUsername("U11");
                message1.setFId(0);
                message1.setMTime("TIME!!!!");
                messages.push_back(message1);

                Message message2;
                message2.setMId(102);
                message2.setMContent("M102");
                message2.setGroupMessage(true);
                message2.setGId(1);
                message2.setUFromId(22);
                message2.setUFromUsername("U22");
                message2.setFId(0);
                message2.setMTime("TIME!!!!");
                messages.push_back(message2);

                Message message3;
                message3.setMId(103);
                message3.setMContent("M103");
                message3.setGroupMessage(true);
                message3.setGId(2);
                message3.setUFromId(11);
                message3.setUFromUsername("U11");
                message3.setFId(0);
                message3.setMTime("TIME!!!!");
                messages.push_back(message3);

                Message message4;
                message4.setMId(104);
                message4.setMContent("M104");
                message4.setGroupMessage(false);
                message4.setGId(0);
                message4.setUFromId(11);
                message4.setUFromUsername("U11");
                message4.setFId(0);
                message4.setMTime("TIME!!!!");
                messages.push_back(message4);

                Message message5;
                message5.setMId(105);
                message5.setMContent("M105");
                message5.setGroupMessage(false);
                message5.setGId(0);
                message5.setUFromId(12);
                message5.setUFromUsername("U12");
                message5.setFId(0);
                message5.setMTime("TIME!!!!");
                messages.push_back(message5);

                Message message6;
                message6.setMId(106);
                message6.setMContent("M106");
                message6.setGroupMessage(false);
                message6.setGId(0);
                message6.setUFromId(11);
                message6.setUFromUsername("U11");
                message6.setFId(0);
                message6.setMTime("TIME!!!!");
                messages.push_back(message6);

                callback->netGetMessageSuccess(messages);
            }
                break;
            default:
                break;
        }
    }
#pragma clang diagnostic pop
}
