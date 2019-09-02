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
            default:
                break;
        }
    }
#pragma clang diagnostic pop
}
