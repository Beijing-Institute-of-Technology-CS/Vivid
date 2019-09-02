//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_MAINVIEW_H
#define CLIENT_MAINVIEW_H


#include <gtk/gtk.h>
#include <string>
#include "List/MessageList/MessageList.h"
#include "List/FriendList/FriendList.h"
#include "List/GroupList/GroupList.h"

class MainViewCallback;

enum MainViewShowMode {
    MSG, CONTACTS, GROUP
};

class MainView {
public:
    MainView();
    /**
     * 展示主界面
     */
    void create();
    void show();
    void destroy();

    void setCallback(MainViewCallback *callback);

    message_list mlist;
    friend_list  flist;
    GroupList gList;

private:
    MainViewShowMode mode = MSG;

    GtkWidget *main_window = nullptr;

    MainViewCallback * callback;

    static void ChangeToMessage(GtkWidget *widget,  gpointer data);
    static void ChangeToFriend(GtkWidget *widget,  gpointer data);
    static void ChangeToGroup(GtkWidget *widget, gpointer data);
    static void tree_selection_message_changed(GtkTreeSelection *selection,  gpointer data);
    static void tree_selection_friend_changed(GtkTreeSelection *selection,gpointer data);
    static void buttonClickedCallback(GtkWidget * button, gpointer data) {
        printf("Hey!\n");
    }
};

class MainViewCallback {
public:
    virtual void selectUser(int uId, std::string uName) = 0;
    virtual void selectGroup(int gId) = 0;
};


#endif //CLIENT_MAINVIEW_H
