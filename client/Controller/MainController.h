//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_MAINCONTROLLER_H
#define CLIENT_MAINCONTROLLER_H


#include "LoginController/LoginController.h"
#include "../View/TestView/TestView.h"

class MainController : OnLoginSuccessCallback, TestViewExitCallback, OnLoginWindowCloseCallback {
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

    //登录窗口关闭回调
    void onLoginWindowClose() override;

    //TestView 退出回调
    void onTestViewExit() override;

private:
    //Controller
    LoginController loginController;

    //View
    TestView testView;

    //退出函数指针
    void (* exit_application)();
};


#endif //CLIENT_MAINCONTROLLER_H
