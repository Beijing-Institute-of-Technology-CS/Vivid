//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_LOGINCONTROLLER_H
#define CLIENT_LOGINCONTROLLER_H


#include "../../View/LoginView/LoginView.h"
#include "../../View/TipView/TipView.h"

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

    //inner
    class LoginFailedTipViewCallback : public TipViewCallback {
    public:
        void onPosClick() override;
        void onNegClick() override;
        explicit LoginFailedTipViewCallback(LoginController *controller) : controller(controller) {}

    private:
        LoginController * controller;
    };

    friend class LoginFailedTipViewCallback;

    bool isLoginSuccess = false;
    LoginView loginView;
    TipView loginFailedTip;

    bool checkLogin(const char * username, const char * password);

    void onLoginSuccess();
    void onLoginFailed();

    OnLoginSuccessCallback * loginSuccessCallback = nullptr;
    OnLoginWindowCloseCallback * loginWindowCloseCallback = nullptr;

    LoginFailedTipViewCallback * loginFailedTipViewCallback = new LoginFailedTipViewCallback(this);


};

class OnLoginSuccessCallback {
public:
    virtual void onLoginSuccessCallback() = 0;
};

#endif //CLIENT_LOGINCONTROLLER_H
