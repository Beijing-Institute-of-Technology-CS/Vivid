//
// Created by William Zhang on 2019-08-30.
//

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

void MainController::onLoginSuccessCallback() {
    loginController.dismissLoginView();
    startMainView();
}

void MainController::start() {
    loginController.showLoginView();
    NetworkController::setCallback(this);
    std::thread thread(NetworkController::startServer);
    thread.detach();
    NetworkUtils::client_ready = true;
    NetworkController::netLogin(233, "pwd");
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

}

void MainController::netRegisterFailed() {

}

void MainController::netLoginSuccess(char *username) {

}

void MainController::netLoginFailed() {

}

void MainController::netGetInfoFailed() {

}

void MainController::netGetMessageSuccess(std::vector<Message> messages) {

}

void MainController::netGetMessageFailed() {

}

void MainController::connectFailed() {

}
