//
// Created by William Zhang on 2019-08-30.
//

#include "MainController.h"
#include "../View/MainView/MainView.h"

MainController::MainController() {
    loginController.setLoginSuccessCallback(this);
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
