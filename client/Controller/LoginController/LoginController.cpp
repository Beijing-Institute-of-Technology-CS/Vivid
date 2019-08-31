//
// Created by William Zhang on 2019-08-30.
//

#include "LoginController.h"

LoginController::LoginController() : loginFailedTip("用户名或密码错误") {
    loginView.setLoginClickedCallback(this);
    loginView.setCloseCallback(this);
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
    isLoginSuccess = true;
    printf("Login Success!\n");
    if (loginSuccessCallback == nullptr) {
        return;
    }
    loginSuccessCallback->onLoginSuccessCallback();
}

void LoginController::onLoginFailed() {
    isLoginSuccess = false;
    printf("Login Failed!\n");
    loginFailedTip.show();
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

void LoginController::onLoginWindowClose() {
    printf("LOGIN WINDOW CLOSE CALLBACK\n");
    if (!isLoginSuccess) {
        if (loginWindowCloseCallback == nullptr) {
            return;
        }
        loginWindowCloseCallback->onLoginWindowClose();
    }
}

void LoginController::setLoginWindowCloseCallback(OnLoginWindowCloseCallback *loginWindowCloseCallback) {
    LoginController::loginWindowCloseCallback = loginWindowCloseCallback;
}
