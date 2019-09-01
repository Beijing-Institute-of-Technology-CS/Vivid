//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_MAINCONTROLLER_H
#define CLIENT_MAINCONTROLLER_H


#include "LoginController/LoginController.h"
#include "ApplicationExitCallback.h"
#include "../View/MainView/MainView.h"

class MainController : OnLoginSuccessCallback, ApplicationExitCallback {
public:
    /**
     * 初始构造函数
     */
    MainController();

    /**
     * 程序开始
     */
    void start();

    /**
     * 设置程序退出方法
     * @param exitApplication
     */
    void setExitApplicationFunc(void (*exitApplication)());

    //登录成功回调
    void onLoginSuccessCallback() override;

    //程序退出回调
    void exitApplication() override;

private:
    //Controller
    LoginController loginController;

    //View
    MainView mainView;

    //退出函数指针
    void (* exit_application)() = nullptr;

    //设置主界面
    void startMainView();
};

#endif //CLIENT_MAINCONTROLLER_H
