//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_LOGINCONTROLLER_H
#define CLIENT_LOGINCONTROLLER_H


#include "../../View/LoginView/LoginView.h"

class OnLoginSuccessCallback;

class LoginController : OnButtonLoginClickedCallback, OnLoginWindowCloseCallback {
public:
    LoginController();

    void showLoginView();
    void dismissLoginView();

    void onButtonLoginClicked() override;
    void onLoginWindowClose() override;

    void setLoginSuccessCallback(OnLoginSuccessCallback *loginSuccessCallback);
    void setLoginWindowCloseCallback(OnLoginWindowCloseCallback *loginWindowCloseCallback);

private:
    bool isLoginSuccess = false;
    LoginView loginView;

    bool checkLogin(const char * username, const char * password);

    void onLoginSuccess();
    void onLoginFailed();

    OnLoginSuccessCallback * loginSuccessCallback = nullptr;
    OnLoginWindowCloseCallback * loginWindowCloseCallback;
};

class OnLoginSuccessCallback {
public:
    virtual void onLoginSuccessCallback() = 0;
};

#endif //CLIENT_LOGINCONTROLLER_H
