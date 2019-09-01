//
// Created by William Zhang on 2019-09-01.
//

#ifndef CLIENT_NETWORKCONTROLLER_H
#define CLIENT_NETWORKCONTROLLER_H

#include "../../Beans/User.h"
#include "../../Beans/Message.h"

class NetworkCallback;

class NetworkController {
public:
    static void setCallback(NetworkCallback *callback);
    static void startServer();

    static void netRegister(char * username, char * password);
    static void netLogin(int uId, char * password);
    static void netGetInfo(int uId, char * password);
    static void netGetMessages(int uId, char * password, int lastCalledMsg);
    static void netSendMessage(int uId, char * password, bool isGroup, int uToId, int gToId, char * content);

    /**
     * Network Callbacks
     * @param json
     */
    static void netRegisterSuccess(char * json);
    static void netRegisterFailed();
    static void netLoginSuccess(char * json);
    static void netLoginFailed();
    static void netGetInfoSuccess(char * json);
    static void netGetInfoFailed();
    static void netGetMessageSuccess(char * json);
    static void netGetMessageFailed();
    static void netSendMessageSuccess(char * json);
    static void netSendMessageFailed();
    static void netReceiveMessage(char * json);

    static void connectFailed();

private:
    static NetworkCallback * callback;
};

class NetworkCallback {
public:
    //todo: complete callback
    virtual void netRegisterSuccess(int id) = 0;
    virtual void netRegisterFailed() = 0;
    virtual void netLoginSuccess(char * username) = 0;
    virtual void netLoginFailed() = 0;
//    virtual void netGetInfoSuccess(std::vector<User> contacts) = 0;
    virtual void netGetInfoFailed() = 0;
    virtual void netGetMessageSuccess(std::vector<Message> messages) = 0;
    virtual void netGetMessageFailed() = 0;
//    virtual void netSendMessageSuccess(int mId) = 0;
//    virtual void netSendMessageFailed() = 0;
//    virtual void netReceiveMessage(Message message) = 0;

    virtual void connectFailed() = 0;
};

#endif //CLIENT_NETWORKCONTROLLER_H
