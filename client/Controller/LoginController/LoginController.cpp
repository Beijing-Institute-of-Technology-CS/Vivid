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
    insert_userinfo(userId, username.c_str(), userPassword.c_str(), 0);
    gdk_threads_add_idle(login_success, &username);
}

gboolean LoginController::login_success(gpointer username) {
    LoginController::getInstance().username = *(std::string *)username;
    LoginController::getInstance().isLoggedIn = true;
    LoginController::getInstance().loginView.destroy();
    MainController::getInstance().startMainView();
    return FALSE;
}

gboolean LoginController::login_failed(gpointer data) {
    TipView::showSimpleTipView("登录失败");
    return FALSE;
}

void LoginController::registerSuccess(int id) {
    int * data = (int *)malloc(sizeof(int));
    *data = id;
    gdk_threads_add_idle(register_success, data);
}

void LoginController::registerFailed() {
    gdk_threads_add_idle(register_failed, nullptr);
}

gboolean LoginController::register_success(gpointer data) {
    int * id = (int *)data;
    std::string idString = "您的id是: " + std::to_string(*id);
    free(id);
    TipView::showSimpleTipView(idString.c_str());
    LoginController::getInstance().registerView.destroy();
    return FALSE;
}

gboolean LoginController::register_failed(gpointer data) {
    TipView::showSimpleTipView("注册失败，请重试");
    return FALSE;
}

