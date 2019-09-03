//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_MAINCONTROLLER_H
#define CLIENT_MAINCONTROLLER_H

#define TIP_GET_INFO_FAILED 1001
#define TIP_GETMESSAGE_FAILED 1002
#define TIP_SEND_MSG_FAILED 1003
#define TIP_CONNECT_FAILED 1004


#include "LoginController/LoginController.h"
#include "../View/MainView/MainView.h"
#include "NetworkController/NetworkController.h"
#include "../Database/database.h"
#include "../View/MainView/ChatView/ChatView.h"

class MainController : public NetworkCallback, MainViewCallback {
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

    void selectUser(int uId, std::string uName) override;
    void selectGroup(int gId) override;

private:
    //view
    MainView mainView;
    ChatView chatView;

    static void startNetworkConnect();
    void startMainView();

    void addMsgToDB(Message message);

    static gboolean refreshMessage(gpointer data);
    static gboolean refreshContacts(gpointer data);
    static gboolean refreshGroups(gpointer data);
    static gboolean showTip(gpointer string);

    //friends
    friend class LoginController;
};

#endif //CLIENT_MAINCONTROLLER_H
