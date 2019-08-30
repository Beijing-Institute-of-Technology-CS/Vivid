//
// Created by William Zhang on 2019-08-30.
//

#include "LoginController.h"

LoginController::LoginController() {
    loginView.setLoginClickedCallback(this);
}

void LoginController::showLoginView() {
    loginView.create();
    loginView.show();
}

void LoginController::dismissLoginView() {
    loginView.destroy();
}

bool LoginController::checkLogin(const char *username, const char *password) {
    //todo: check login
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);
    if (strcmp(password, "123") == 0) {
        return true;
    } else {
        return false;
    }
}

void LoginController::onLoginSuccess() {
    printf("Login Success!\n");
    loginSuccessCallback->onLoginSuccessCallback();
}

void LoginController::onLoginFailed() {
    printf("Login Failed!\n");
}

void LoginController::onButtonLoginClicked() {
    const char *username;
    const char *password;
    loginView.get_input_login_content(username, password);
    if (checkLogin(username, password)) {
        onLoginSuccess();
    } else {
        onLoginFailed();
    }
}

void LoginController::setLoginSuccessCallback(OnLoginSuccessCallback *loginSuccessCallback) {
    LoginController::loginSuccessCallback = loginSuccessCallback;
}
