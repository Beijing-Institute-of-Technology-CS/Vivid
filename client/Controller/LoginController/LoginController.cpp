//
// Created by William Zhang on 2019-08-30.
//
#include <iostream>
#include "LoginController.h"
#include "../NetworkController/NetworkController.h"
#include "../MainController.h"

LoginController::LoginController() {
    loginView.setCallback(this);
    registerView.setCallback(this);
}

void LoginController::onButtonLoginClicked() {
    const char * id;
    const char * password;
    loginView.get_input_login_content(id, password);
    if (std::strlen(id) <= 0) {
        loginFailed();
        return;
    }
    for (int i = 0; i < std::strlen(id); ++i) {
        if (id[i] < '0' || id[i] > '9') {
            loginFailed();
            return;
        }
    }
    userId = std::stoi(id);
    userPassword = std::string(password);
    NetworkController::netLogin(userId, userPassword.c_str());
}

void LoginController::onButtonRegisterClicked() {
    registerView.show();
}

void LoginController::onLoginViewDestroy() {
    if (!isLoggedIn) {
        gtk_main_quit();
    }
}

void LoginController::onRegisterSubmit(const char *username, const char *password) {
    NetworkController::netRegister(username, password);
}

void LoginController::startLoginView() {
    loginView.show();
}

void LoginController::loginFailed() {
    gdk_threads_add_idle(login_failed, nullptr);
}

void LoginController::loginSuccess(std::string username) {
    gdk_threads_add_idle(login_success, &username);
}

gboolean LoginController::login_success(gpointer username) {
    LoginController::getInstance().username = *(std::string *)username;
    LoginController::getInstance().isLoggedIn = true;
    LoginController::getInstance().loginView.destroy();

    //todo: debug only
    std::cout<<LoginController::getInstance().username<<std::endl
        <<LoginController::getInstance().userId<<std::endl
        <<LoginController::getInstance().userPassword<<std::endl;

    MainController::getInstance().startMainView();
    return FALSE;
}

gboolean LoginController::login_failed(gpointer data) {
    TipView::showSimpleTipView("登录失败");
    return FALSE;
}

