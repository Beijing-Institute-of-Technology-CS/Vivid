//
// Created by William Zhang on 2019-08-30.
//

#include <thread>
#include "MainController.h"
#include "../TestUtils/NetworkCallbackTesting.h"
#include "../Network/NetworkUtils.h"

MainController::MainController() {
    NetworkController::setCallback(this);
    NetworkCallbackTesting::setCallback(this);
    NetworkCallbackTesting::startTestingThread();
    mainView.setCallback(this);
}

void MainController::startMainView() {
    mainView.create();
    mainView.show();
}


/*====================NetworkCallback========================*/

void MainController::netRegisterSuccess(int id) {
    LoginController::getInstance().registerSuccess(id);
}

void MainController::netRegisterFailed() {
    LoginController::getInstance().registerFailed();
}

void MainController::netLoginSuccess(char *username) {
    LoginController::getInstance().loginSuccess(username);
}

void MainController::netLoginFailed() {
    LoginController::getInstance().loginFailed();
}

void MainController::netGetInfoSuccess(std::vector<User> contacts, std::vector<Group> groups) {
    //更新数据库contacts信息
    for (auto i : contacts) {
        insert_friend(i.getUId(), i.getUName(), 0);
    }
    //更新数据库groups信息
    for (auto i : groups) {
        insert_Group(i.getGId(), LoginController::getInstance().userId);
    }
    //通知刷新联系人界面
    gdk_threads_add_idle(refreshContacts, nullptr);
    //通知刷新群聊界面
    gdk_threads_add_idle(refreshGroups, nullptr);
}

void MainController::netGetInfoFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_GET_INFO_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}

void MainController::netGetMessageSuccess(std::vector<Message> messages) {
    //更新数据库messages信息
    for (auto i : messages) {
        addMsgToDB(i);
    }
    //通知刷新消息界面
    gdk_threads_add_idle(refreshMessage, nullptr);
}

void MainController::netGetMessageFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_GETMESSAGE_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}

void MainController::netSendMessageSuccess(Message message) {
    //将信息插入数据库
    addMsgToDB(message);
    //todo: 通知刷新消息界面
    gdk_threads_add_idle(refreshMessage, nullptr);
}

void MainController::netSendMessageFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_SEND_MSG_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}

void MainController::netReceiveMessage(Message message) {
    //将消息插入数据库
    addMsgToDB(message);
    //todo: 通知刷新消息界面
    gdk_threads_add_idle(refreshMessage, nullptr);
}

void MainController::connectFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_CONNECT_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}
/*====================End===NetworkCallback========================*/

void MainController::start() {
    LoginController::getInstance().startLoginView();
    std::thread thread(startNetworkConnect);
    thread.detach();
}

void MainController::startNetworkConnect() {
//    NetworkUtils::start_client(BITCS);
}

void MainController::selectUser(int uId, std::string uName) {
    chatView.show(uName.c_str());
    chatView.currentId = uId;
    chatView.isGroup = false;
}

void MainController::selectGroup(int gId) {
    std::string title = "Group: " + std::to_string(gId);
    chatView.show(title.c_str());
    chatView.currentId = gId;
    chatView.isGroup = true;
}

void MainController::addMsgToDB(Message message) {
    if (!message.isGroupMessage()) {
        insert_Usermessage(message.getMId(), message.getUFromId(), LoginController::getInstance().userId, message.getMContent(), message.getMTime());
    } else {
        insert_Groupmessage(message.getMId(), message.getUFromId(), LoginController::getInstance().userId, message.getMContent(), message.getMTime(), message.getGId());
    }
}

gboolean MainController::refreshMessage(gpointer data) {
    //todo:
    std::vector<Group> groups;
    std::vector<Message> groupMsgs;
    std::vector<Message> userMsgs;
    show_Usermessage(LoginController::getInstance().userId, &userMsgs);
    return 0;
}

gboolean MainController::refreshContacts(gpointer data) {
    //todo:
    std::vector<User> contacts;
    show_friend(LoginController::getInstance().userId, &contacts);
    return 0;
}

gboolean MainController::refreshGroups(gpointer data) {
    //todo:
    std::vector<Group> groups;
    show_Groupinfo(LoginController::getInstance().userId, &groups);
    return 0;
}

gboolean MainController::showTip(gpointer commandPtr) {
    std::string msg;
    int command = *(int*)commandPtr;
    free(commandPtr);
    switch (command) {
        case TIP_GET_INFO_FAILED:
            msg = "获取网络数据失败";
            break;
        case TIP_GETMESSAGE_FAILED:
            msg = "获取最新信息失败";
            break;
        case TIP_SEND_MSG_FAILED:
            msg = "信息发送失败";
            break;
        case TIP_CONNECT_FAILED:
            msg = "网络连接失败";
            break;
        default:
            break;
    }
    TipView::showSimpleTipView(msg.c_str());
    return 0;
}
