//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_MAINVIEW_H
#define CLIENT_MAINVIEW_H


#include <gtk/gtk.h>
#include <string>
#include <cstring>
#include "List/FriendList/FriendList.h"
#include "List/GroupList/GroupList.h"

class MainViewCallback;

enum MainViewShowMode {
    MSG, CONTACTS, GROUP
};

class MainView {
public:
    /**
     * 展示主界面
     */
    GtkBuilder* create();
    void show();
    void destroy();

    void setCallback(MainViewCallback *callback);

    FriendList flist;
    GroupList glist;

private:
    MainViewShowMode mode = MSG;
    GtkWidget *main_window = nullptr;
    GtkWidget *inputEntry;

    MainViewCallback * callback;

    std::string getInput();

    static void ChangeToFriend(GtkWidget *widget,  gpointer data);
    static void ChangeToGroup(GtkWidget *widget, gpointer data);
    static void tree_selection_friend_changed(GtkTreeSelection *selection,gpointer data);
    static void tree_selection_group_changed(GtkTreeSelection *selection,gpointer data);
    static void goButtonClickedCallback(GtkWidget * button, gpointer data);
};

class MainViewCallback {
public:
    virtual void selectUser(int uId, std::string uName) = 0;
    virtual void selectGroup(int gId) = 0;
};


#endif //CLIENT_MAINVIEW_H
