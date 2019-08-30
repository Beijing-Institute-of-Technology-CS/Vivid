//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_MAINCONTROLLER_H
#define CLIENT_MAINCONTROLLER_H


#include "LoginController/LoginController.h"
#include "../View/TestView/TestView.h"

class MainController : OnLoginSuccessCallback, TestViewExitCallback {
public:
    MainController();
    void start();

    void onLoginSuccessCallback() override;

    void setExitApplicationFunc(void (*exitApplication)());

    void onTestViewExit() override;

private:
    LoginController loginController;

    void (* exit_application)();
};


#endif //CLIENT_MAINCONTROLLER_H
