//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_MAINVIEW_H
#define CLIENT_MAINVIEW_H


#include <gtk/gtk.h>
#include "List/MessageList/MessageList.h"
#include "List/FriendList/FriendList.h"

class MainViewCallback;

class MainView {
public:
    MainView();
    /**
     * 展示主界面
     */
    void create();
    void show();
    void destroy();
    //给历史消息列表加入一行新消息，消息id号，姓名，最后一条消息
    void message_add(gchar*,gchar*);
    //给好友列表中添加一个新好友，id，姓名
    void friend_add(gchar*,gchar*);

    void setCallback(MainViewCallback *callback);

private:
    GtkWidget *main_window = nullptr;
    GtkWidget *vbox;
    message_list mlist;
    friend_list  flist;

    MainViewCallback * callback;

    static void ChangeToMessage(GtkWidget *widget,  gpointer data);
    static void ChangeToFriend(GtkWidget *widget,  gpointer data);
    static void tree_selection_message_changed(GtkTreeSelection *selection,  gpointer data);
    static void tree_selection_friend_changed(GtkTreeSelection *selection,gpointer data);
    static void buttonClickedCallback(GtkWidget * button, gpointer data) {
        printf("Hey!\n");
    }
};

class MainViewCallback {
public:
    virtual void selectUser(int uId) = 0;
    virtual void selectGroup(int gId) = 0;
};


#endif //CLIENT_MAINVIEW_H
