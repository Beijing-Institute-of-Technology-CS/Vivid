//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_LOGINCONTROLLER_H
#define CLIENT_LOGINCONTROLLER_H


#include "../../View/LoginView/LoginView.h"

class OnLoginSuccessCallback;

class LoginController : OnButtonLoginClickedCallback {
public:
    LoginController();

    void showLoginView();
    void dismissLoginView();

    void onButtonLoginClicked() override;

    void setLoginSuccessCallback(OnLoginSuccessCallback *loginSuccessCallback);

private:
    LoginView loginView;

    bool checkLogin(const char * username, const char * password);

    void onLoginSuccess();
    void onLoginFailed();

    OnLoginSuccessCallback * loginSuccessCallback = nullptr;
};

class OnLoginSuccessCallback {
public:
    virtual void onLoginSuccessCallback() = 0;
};

#endif //CLIENT_LOGINCONTROLLER_H
