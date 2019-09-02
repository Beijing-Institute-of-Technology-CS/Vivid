//
// Created by William Zhang on 2019-09-02.
//

#ifndef CLIENT_NETWORKCALLBACKTESTING_H
#define CLIENT_NETWORKCALLBACKTESTING_H


#include "../Controller/NetworkController/NetworkController.h"

class NetworkCallbackTesting {
public:
    static void setCallback(NetworkCallback *callback);

    static void startTestingThread();

private:
    static void testThread();
    static NetworkCallback * callback;
};


#endif //CLIENT_NETWORKCALLBACKTESTING_H
