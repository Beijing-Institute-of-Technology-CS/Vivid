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
    //todo: 更新数据库contacts信息
    //todo: 更新数据库groups信息
    //todo: 通知刷新联系人界面
    //todo: 通知刷新群聊界面
}

void MainController::netGetInfoFailed() {
    //todo: tip
}

void MainController::netGetMessageSuccess(std::vector<Message> messages) {
    //todo: 更新数据库messages信息
    //todo: 通知刷新消息界面
}

void MainController::netGetMessageFailed() {
    //todo: tip
}

void MainController::netSendMessageSuccess(Message message) {
    //todo: 将信息插入数据库
    //todo: 通知刷新消息界面
}

void MainController::netSendMessageFailed() {
    //todo: tip
}

void MainController::netReceiveMessage(Message message) {
    //todo: 将消息插入数据库
    //todo: 通知刷新消息界面
}

void MainController::connectFailed() {
    //todo: tip
}
/*====================End===NetworkCallback========================*/

void MainController::start() {
    LoginController::getInstance().startLoginView();
    std::thread thread(startNetworkConnect);
    thread.detach();
}

void MainController::startNetworkConnect() {
    NetworkUtils::start_client(BITCS);
}
