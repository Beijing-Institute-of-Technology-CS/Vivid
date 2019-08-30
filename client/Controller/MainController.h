//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_MAINCONTROLLER_H
#define CLIENT_MAINCONTROLLER_H


#include "LoginController/LoginController.h"

class MainController : OnLoginSuccessCallback {
public:
    MainController();
    void start();

    void onLoginSuccessCallback() override;
private:
    LoginController loginController;
};


#endif //CLIENT_MAINCONTROLLER_H
