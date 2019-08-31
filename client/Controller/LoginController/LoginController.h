//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_LOGINCONTROLLER_H
#define CLIENT_LOGINCONTROLLER_H


#include "../../View/LoginView/LoginView.h"
#include "../../View/TipView/TipView.h"
#include "../ApplicationExitCallback.h"
#include "../../View/RegisterView/RegisterView.h"

class OnLoginSuccessCallback;

class LoginController : OnButtonLoginClickedCallback, OnLoginWindowCloseCallback, OnRegisterSubmitClickCallback {
public:
    /**
     * 初始构造函数
     */
    LoginController();

    /**
     * 展示与销毁
     */
    void showLoginView();
    void dismissLoginView();

    /**
     * 设置登录成功回调
     * @param loginSuccessCallback
     */
    void setLoginSuccessCallback(OnLoginSuccessCallback *loginSuccessCallback);

    /**
     * 设置程序退出回调
     * @param applicationExitCallback
     */
    void setApplicationExitCallback(ApplicationExitCallback *applicationExitCallback);

    //登录相关回调
    void onButtonLoginClicked() override;
    void onButtonRegisterClicked() override;
    void onLoginWindowClose() override;
    void onRegisterSubmit(const char * username, const char * password) override;

private:
    //是否登录成功
    bool isLoginSuccess = false;

    //View
    LoginView loginView;
    RegisterView registerView;
    TipView loginFailedTip;

    /**
     * 检查登录信息
     * @param username
     * @param password
     * @return 是否成功
     */
    bool checkLogin(const char * username, const char * password);

    /**
     * 登录成功、失败操作
     */
    void onLoginSuccess();
    void onLoginFailed();

    /**
     * 注册
     * @param username
     * @param password
     * @return 是否成功
     */
    bool doRegister(const char * username, const char * password);

    /**
     * 登录成功、失败操作
     */
    void onRegisterSuccess(int id);
    void onRegisterFailed();

    //回调
    OnLoginSuccessCallback * loginSuccessCallback = nullptr;
    ApplicationExitCallback * applicationExitCallback = nullptr;
};

//登录成功回调
class OnLoginSuccessCallback {
public:
    virtual void onLoginSuccessCallback() = 0;
};

#endif //CLIENT_LOGINCONTROLLER_H
