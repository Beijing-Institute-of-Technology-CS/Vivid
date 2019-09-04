//
// Created by William Zhang on 2019-08-30.
//

#include <thread>
#include "MainController.h"
#include "../TestUtils/NetworkCallbackTesting.h"
#include "../Network/NetworkUtils.h"
#include "../../Constants.h"
#include <map>
#include <vector>
#include <utility>
#include <iostream>

MainController::MainController() {
    NetworkController::setCallback(this);
    NetworkCallbackTesting::setCallback(this);
    NetworkCallbackTesting::startTestingThread();
    chatView.setCallback(this);
    mainView.setCallback(this);
}

void MainController::startMainView() {

    chatView.create(mainView.create());
    mainView.show();
    NetworkController::netGetInfo(LoginController::getInstance().userId, LoginController::getInstance().userPassword.c_str());
}


/*====================NetworkCallback========================*/

void MainController::netRegisterSuccess(int id) {
    LoginController::getInstance().registerSuccess(id);
}

void MainController::netRegisterFailed() {
    LoginController::getInstance().registerFailed();
}

void MainController::netLoginSuccess(char *username) {
    LoginController::getInstance().loginSuccess(username);
}

void MainController::netLoginFailed() {
    LoginController::getInstance().loginFailed();
}

void MainController::netGetInfoSuccess(std::vector<User> contacts, std::vector<Group> groups) {
    //更新数据库contacts信息
    for (auto i : contacts) {
        insert_friend(i.getUId(), i.getUName(), 0);
    }
    //更新数据库groups信息
    for (auto i : groups) {
        insert_Group(i.getGId(), LoginController::getInstance().userId);
    }
    //通知刷新联系人界面
    gdk_threads_add_idle(refreshContacts, nullptr);
    //通知刷新群聊界面
    gdk_threads_add_idle(refreshGroups, nullptr);
    std::vector<User> users;
    show_user(LoginController::getInstance().userId, &users);
    int lastCalledMsg = 0;
    if (!users.empty()) {
        lastCalledMsg = users[0].getLatestMessage();
    }

    NetworkController::netGetMessages(LoginController::getInstance().userId,
            LoginController::getInstance().userPassword.c_str(), lastCalledMsg);
}

void MainController::netGetInfoFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_GET_INFO_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}

void MainController::netGetMessageSuccess(std::vector<Message> messages) {
    //更新数据库messages信息
    for (auto i : messages) {
        i.setUToId(LoginController::getInstance().userId);
        addMsgToDB(i);
    }
    //通知刷新消息界面
    refreshMsgs();
}

void MainController::netGetMessageFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_GETMESSAGE_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}

void MainController::netSendMessageSuccess(Message message) {
    //将信息插入数据库
    addMsgToDB(message);
    //通知刷新消息界面
    auto * data = new ChatViewRefreshData();
    data->message = message;
    data->isReceive = false;
    gdk_threads_add_idle(refreshChatView, data);
    refreshMsgs();
}

void MainController::netSendMessageFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_SEND_MSG_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}

void MainController::netReceiveMessage(Message message) {
    //将消息插入数据库
    message.setUToId(LoginController::getInstance().userId);
    addMsgToDB(message);
    //通知刷新消息界面
    auto * data = new ChatViewRefreshData();
    data->message = message;
    data->isReceive = true;
    gdk_threads_add_idle(refreshChatView, data);
    refreshMsgs();
}

void MainController::connectFailed() {
    //tip
    int * cmd = (int *)malloc(sizeof(int));
    *cmd = TIP_CONNECT_FAILED;
    gdk_threads_add_idle(showTip, cmd);
}
/*====================End===NetworkCallback========================*/

void MainController::start() {
    LoginController::getInstance().startLoginView();
    std::thread thread(startNetworkConnect);
    thread.detach();
}

void MainController::startNetworkConnect() {
    NetworkUtils::start_client(BITCS);
}

void MainController::selectUser(int uId, std::string uName) {
    GList *list=gtk_container_get_children(GTK_CONTAINER(chatView.message_box));
    GList *head = list;
//    for(int i=0;i<g_list_length(list);i++)
//    {
//        gtk_widget_destroy(GTK_WIDGET(head->data));
//        head=head->next;
//    }
    chatView.setName(uName.c_str());
    chatView.show();
    chatView.currentId = uId;
    chatView.isGroup = false;
}

void MainController::selectGroup(int gId) {
    std::string title = "Group: " + std::to_string(gId);
    NetworkController::netAddUIdToGroup(LoginController::getInstance().userId, LoginController::getInstance().userPassword.c_str(), gId);
    GList *list=gtk_container_get_children(GTK_CONTAINER(chatView.message_box));
    GList *head = list;
    for(int i=0;i<g_list_length(list);i++)
        {
            gtk_widget_destroy(GTK_WIDGET(head->data));
            head=head->next;
        }
    chatView.setName(std::to_string(gId).c_str());
    chatView.show();
    chatView.currentId = gId;
    chatView.isGroup = true;
}

void MainController::addMsgToDB(Message message) {
    if (!message.isGroupMessage()) {
        insert_Usermessage(message.getMId(), message.getUFromId(), message.getUToId(), message.getMContent(), message.getMTime());
    } else {
        insert_Groupmessage(message.getMId(), message.getUFromId(), LoginController::getInstance().userId, message.getMContent(), message.getMTime(), message.getGId());
    }
}

gboolean MainController::refreshMessage(gpointer data) {
    //todo:
    auto * p = (std::pair<std::map<int, std::string>, std::map<int, std::string>> *) data;
    auto userMsgMap = p->first;
    auto groupMsgMap = p->second;
    free(data);
    for (auto & v : userMsgMap) {
        std::cout<<v.first<<": ";
        std::cout<<v.second<<std::endl;
        if (v.first == LoginController::getInstance().userId) continue;
        MainController::getInstance().mainView.flist.setFriend(v.first, v.second.c_str());
    }
    for (auto & v : groupMsgMap) {
        std::cout<<v.first<<": ";
        std::cout<<v.second<<std::endl;
        MainController::getInstance().mainView.glist.setGroup(v.first, v.second.c_str());
    }
    return 0;
}

gboolean MainController::refreshContacts(gpointer data) {
    std::vector<User> contacts;
    show_friend(LoginController::getInstance().userId, &contacts);
    MainController::getInstance().mainView.flist.setData(contacts);
    return 0;
}

gboolean MainController::refreshGroups(gpointer data) {
    std::vector<Group> groups;
    show_Groupinfo(LoginController::getInstance().userId, &groups);
    MainController::getInstance().mainView.glist.setData(groups);
    return 0;
}

gboolean MainController::showTip(gpointer commandPtr) {
    std::string msg;
    int command = *(int*)commandPtr;
    free(commandPtr);
    switch (command) {
        case TIP_GET_INFO_FAILED:
            msg = "获取网络数据失败";
            break;
        case TIP_GETMESSAGE_FAILED:
            msg = "获取最新信息失败";
            break;
        case TIP_SEND_MSG_FAILED:
            msg = "信息发送失败";
            break;
        case TIP_CONNECT_FAILED:
            msg = "网络连接失败";
            break;
        default:
            break;
    }
    TipView::showSimpleTipView(msg.c_str());
    return 0;
}

void MainController::chatViewSend(std::string msg) {
    if (msg.empty()) {
        return;
    }
    NetworkController::netSendMessage(
            LoginController::getInstance().userId,
            LoginController::getInstance().userPassword.c_str(),
            chatView.isGroup,
            chatView.currentId,
            chatView.currentId,
            msg.c_str()
            );
}

gboolean MainController::refreshChatView(gpointer data) {
    Message message = ((ChatViewRefreshData * )data)->message;
    bool isReceive = ((ChatViewRefreshData * )data)->isReceive;
    free(data);
    if (!MainController::getInstance().chatView.isShow) {
        return 0;
    }
    std::string msg;
    if (!isReceive) {
        msg = message.getMContent();
        if (MainController::getInstance().chatView.isGroup && message.isGroupMessage() &&
            message.getGId() == MainController::getInstance().chatView.currentId) {
            MainController::getInstance().chatView.send_message(msg);
        } else if (!MainController::getInstance().chatView.isGroup && !message.isGroupMessage() &&
            message.getUToId() == MainController::getInstance().chatView.currentId) {
            MainController::getInstance().chatView.send_message(msg);
        }
        return 0;
    }
    if (MainController::getInstance().chatView.isGroup && message.isGroupMessage()) {
        if (MainController::getInstance().chatView.currentId == message.getGId()) {
            msg = "(" + std::to_string(message.getUFromId()) + ")"
                    + message.getUFromUsername() + ": " + message.getMContent();
        }
    } else if (!MainController::getInstance().chatView.isGroup && !message.isGroupMessage()) {
        if (MainController::getInstance().chatView.currentId == message.getUFromId() ||
            MainController::getInstance().chatView.currentId == message.getUToId()) {
            msg = message.getMContent();
        }
    }
    if (isReceive) {
        MainController::getInstance().chatView.receive_message(msg.c_str());
    }
    return 0;
}

void MainController::refreshMsgs() {
    std::vector<Group> groups;
    std::vector<Message> userMsgs;
    std::map<int, std::string> userMsgMap;
    std::map<int, std::string> groupMsgMap;
    show_Usermessage(LoginController::getInstance().userId, &userMsgs);
    show_Groupinfo(LoginController::getInstance().userId, &groups);
    for (auto i : userMsgs) {
        userMsgMap[i.getUToId()] = std::string(i.getMContent());
        userMsgMap[i.getUFromId()] = std::string(i.getMContent());
    }
    for (auto i : groups) {
        int gId = i.getGId();
        std::vector<Message> groupMsgs;
        show_Groupmessage(gId, &groupMsgs);
        if (groupMsgs.empty()) continue;
        groupMsgMap[gId] = groupMsgs[groupMsgs.size() - 1].getMContent();
    }

    auto * p = new std::pair<std::map<int, std::string>, std::map<int, std::string>>();
    p->first = userMsgMap;
    p->second = groupMsgMap;

    gdk_threads_add_idle(refreshMessage, p);
}
