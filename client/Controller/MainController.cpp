//
// Created by William Zhang on 2019-08-30.
//

#include "MainController.h"
#include "../View/MainView/MainView.h"

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
