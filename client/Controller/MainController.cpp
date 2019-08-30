//
// Created by William Zhang on 2019-08-30.
//

#include "MainController.h"
#include "../View/TestView/TestView.h"

MainController::MainController() {
    loginController.setLoginSuccessCallback(this);
    loginController.setLoginWindowCloseCallback(this);
    testView.setExitCallback(this);
}

void MainController::onLoginSuccessCallback() {
    loginController.dismissLoginView();
    //todo: 只是为了演示 实际会有controller
    testView.show_main_view();
}

void MainController::start() {
    loginController.showLoginView();
}

void MainController::setExitApplicationFunc(void (*exitApplication)()) {
    exit_application = exitApplication;
}

void MainController::onTestViewExit() {
    exit_application();
}

void MainController::onLoginWindowClose() {
    exit_application();
}
