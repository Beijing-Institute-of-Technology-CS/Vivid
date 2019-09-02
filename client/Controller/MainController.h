//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_MAINCONTROLLER_H
#define CLIENT_MAINCONTROLLER_H


#include "LoginController/LoginController.h"
#include "../View/MainView/MainView.h"
#include "NetworkController/NetworkController.h"

class MainController : public NetworkCallback {
public:
    MainController();

    /**
     * MainController 单例
     * @return
     */
    static MainController & getInstance() {
        static MainController mainController;
        return mainController;
    }

    void start();

    /*=========================callback===========================*/
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
    //view
    MainView mainView;

    void startMainView();

    //friends
    friend class LoginController;
};

#endif //CLIENT_MAINCONTROLLER_H
