//
// Created by dd on 8/30/19.
//

#ifndef CLIENT_FRIENDLIST_H
#define CLIENT_FRIENDLIST_H
#include <gtk/gtk.h>
#include <vector>
#include "../../../../Beans/User.h"

enum{
    USER_ID,
    USER_NAME,
    USER_MESSAGE,
    USER_COLUMNS
};

class FriendList {
public:
    FriendList();
    //void create();
    //void show();
    //void destroy();
    GtkWidget *getView();
    void append(const gchar *id, const gchar *name, const gchar *message);
    void setData(const std::vector<User>& User);
    //void get_input_login_content(const char * & username, const char * & password);

private:
    GtkWidget *view= nullptr;
    GtkCellRenderer *renderer= nullptr;
    GtkTreeModel  *list_model_create();
};


#endif //CLIENT_FRIENDLIST// _H
