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
     * 设置登录窗口关闭回调
     * @param loginWindowCloseCallback
     */
    void setLoginWindowCloseCallback(OnLoginWindowCloseCallback *loginWindowCloseCallback);

    //登录相关回调
    void onButtonLoginClicked() override;
    void onLoginWindowClose() override;

private:
    //是否登录成功
    bool isLoginSuccess = false;

    //View
    LoginView loginView;
    TipView loginFailedTip;

    /**
     * 检查登录信息
     * @param username
     * @param password
     * @return
     */
    bool checkLogin(const char * username, const char * password);

    /**
     * 登录成功、失败操作
     */
    void onLoginSuccess();
    void onLoginFailed();

    //回调
    OnLoginSuccessCallback * loginSuccessCallback = nullptr;
    OnLoginWindowCloseCallback * loginWindowCloseCallback = nullptr;

};

//登录成功回调
class OnLoginSuccessCallback {
public:
    virtual void onLoginSuccessCallback() = 0;
};

#endif //CLIENT_LOGINCONTROLLER_H
