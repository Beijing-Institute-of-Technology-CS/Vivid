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

}

void MainController::netGetInfoFailed() {

}

void MainController::netGetMessageSuccess(std::vector<Message> messages) {

}

void MainController::netGetMessageFailed() {

}

void MainController::netSendMessageSuccess(Message message) {

}

void MainController::netSendMessageFailed() {

}

void MainController::netReceiveMessage(Message message) {

}

void MainController::connectFailed() {

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
