//
// Created by William Zhang on 2019-08-30.
//

#include <iostream>
#include <thread>
#include <vector>
#include "MainController.h"
#include "../View/MainView/MainView.h"
#include "NetworkController/NetworkController.h"
#include "../Network/NetworkUtils.h"

MainController::MainController() {
    //设置回调
    loginController.setLoginSuccessCallback(this);
    loginController.setApplicationExitCallback(this);
}

void MainController::onLoginSuccessCallback(int id, char * password) {
    userId = id;
    userPwd = password;
    loginController.dismissLoginView();
    startMainView();
}

void MainController::start() {
    loginController.showLoginView();
    NetworkController::setCallback(this);
    std::thread thread(NetworkController::startServer);
    thread.detach();
}

void MainController::setExitApplicationFunc(void (*exitApplication)()) {
    exit_application = exitApplication;
}

void MainController::exitApplication() {
    if (exit_application != nullptr) {
        exit_application();
    }
}

void MainController::startMainView() {
    mainView.create();
    mainView.show();
}

void MainController::netRegisterSuccess(int id) {
    loginController.onRegisterSuccess(id);
}

void MainController::netRegisterFailed() {
    loginController.onRegisterFailed();
}

void MainController::netLoginSuccess(char *username) {
    username = username;
    loginController.onLoginSuccess();
}

void MainController::netLoginFailed() {
    loginController.onLoginFailed();
}

void MainController::netGetInfoFailed() {

}

void MainController::netGetMessageSuccess(std::vector<Message> messages) {

}

void MainController::netGetMessageFailed() {

}

void MainController::connectFailed() {
    std::cout<<"CONNECT_FAILED"<<std::endl;
}

void MainController::netGetInfoSuccess(std::vector<User> contacts, std::vector<Group> groups) {

}

void MainController::netSendMessageSuccess(Message message) {

}

void MainController::netSendMessageFailed() {

}

void MainController::netReceiveMessage(Message message) {

}
