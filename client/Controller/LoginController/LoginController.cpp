//
// Created by William Zhang on 2019-08-30.
//

#include "LoginController.h"
#include "../NetworkController/NetworkController.h"
#include <string>

LoginController::LoginController() {
    loginView.setLoginClickedCallback(this);
    loginView.setCloseCallback(this);
    registerView.setSubmitCallback(this);
}

void LoginController::showLoginView() {
    loginView.create();
    loginView.show();
}

void LoginController::dismissLoginView() {
    loginView.destroy();
}

void LoginController::onLoginSuccess() {
    isLoginSuccess = true;
    printf("Login Success!\n");
    if (loginSuccessCallback == nullptr) {
        return;
    }
    loginSuccessCallback->onLoginSuccessCallback(userId, userPwd);
}

void LoginController::onLoginFailed() {
    isLoginSuccess = false;
    printf("Login Failed!\n");
    TipView::showSimpleTipView("用户名或密码错误");
}

void LoginController::onButtonLoginClicked() {
    const char *username;
    const char *password;
    loginView.get_input_login_content(username, password);
    if (strlen(username) <= 0) {
        onLoginFailed();
        return;
    }
    for (int i = 0; i < strlen(username); ++i) {
        if (username[i] < '0' || username[i] > '9') {
            onLoginFailed();
            return;
        }
    }
    userId = std::stoi(username);
    userPwd = (char *)malloc((strlen(password)+1) * sizeof(password));
    strcpy(userPwd, password);
    //todo: debug only
    printf("id: %s\n", username);
    printf("Password: %s\n", password);
    if (strcmp(password, "123") == 0) {
        onLoginSuccess();
    } else {
        onLoginFailed();
    }
//    NetworkController::netLogin(userId, password);
}

void LoginController::setLoginSuccessCallback(OnLoginSuccessCallback *loginSuccessCallback) {
    LoginController::loginSuccessCallback = loginSuccessCallback;
}

void LoginController::onLoginWindowClose() {
    printf("LOGIN WINDOW CLOSE CALLBACK\n");
    if (!isLoginSuccess) {
        if (applicationExitCallback == nullptr) {
            return;
        }
        applicationExitCallback->exitApplication();
    }
}

void LoginController::setApplicationExitCallback(ApplicationExitCallback *applicationExitCallback) {
    LoginController::applicationExitCallback = applicationExitCallback;
}

void LoginController::onButtonRegisterClicked() {
    registerView.show();
}

void LoginController::onRegisterSubmit(const char *username, const char *password) {
    doRegister(username, password);
}

bool LoginController::doRegister(const char *username, const char *password) {
    //todo: 注册
    if (strlen(username) < 5) {
        onRegisterSuccess(strlen(username));
        return true;
    }
    onRegisterFailed();
    return false;
}

void LoginController::onRegisterSuccess(int id) {
    registerView.destroy();
    std::string s = "注册成功\n您的id是: " + std::to_string(id);
    TipView::showSimpleTipView(s.c_str());
}

void LoginController::onRegisterFailed() {
    TipView::showSimpleTipView("注册失败\n请重试");
}

