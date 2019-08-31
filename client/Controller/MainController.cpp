//
// Created by William Zhang on 2019-08-30.
//

#include "MainController.h"
#include "../View/MainView/MainView.h"

MainController::MainController() {
    //设置回调
    loginController.setLoginSuccessCallback(this);
    loginController.setApplicationExitCallback(this);
    testView.setExitCallback(this);
}

void MainController::onLoginSuccessCallback() {
    loginController.dismissLoginView();
    //todo: 只是为了演示 实际会有controller
    MainView mainView;
    mainView.show();
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
