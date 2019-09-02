//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_MAINCONTROLLER_H
#define CLIENT_MAINCONTROLLER_H


#include "LoginController/LoginController.h"
#include "ApplicationExitCallback.h"
#include "../View/MainView/MainView.h"
#include "NetworkController/NetworkController.h"

class MainController : OnLoginSuccessCallback, ApplicationExitCallback, NetworkCallback {
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
    void onLoginSuccessCallback(int id, char * password) override;

    //程序退出回调
    void exitApplication() override;

    //Network Callbacks
    void netRegisterSuccess(int id) override;
    void netRegisterFailed() override;
    void netLoginSuccess(char * username) override;
    void netLoginFailed() override;
    void netGetInfoSuccess(std::vector<User> contacts, std::vector<Group> groups) override;
    void netGetInfoFailed() override;
    void netGetMessageSuccess(std::vector<Message> messages) override;
    void netGetMessageFailed() override;
    void netSendMessageSuccess(Message message) override;
    void netSendMessageFailed() override;
    void netReceiveMessage(Message message) override;
    void connectFailed() override;

private:
    //Controller
    LoginController loginController;

    //View
    MainView mainView;

    //userInfo
    int userId;
    char * userPwd;

    //退出函数指针
    void (* exit_application)() = nullptr;

    //设置主界面
    void startMainView();
};

#endif //CLIENT_MAINCONTROLLER_H
