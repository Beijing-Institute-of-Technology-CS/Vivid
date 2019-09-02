//
// Created by dd on 8/30/19.
//

#ifndef CLIENT_MESSAGELIST_H
#define CLIENT_MESSAGELIST_H
#include <gtk/gtk.h>
#include <vector>
#include "../../../../Beans/Message.h"

enum{
    COLUMN_ID,
    COLUMN_NAME,
    COLUMN_MESSAGE,
    MESSAGE_COLUMNS
};

class message_list {
public:
    message_list();
    //void create();
    //void show();
    void destroy();
    GtkWidget *getView();
    void append(int mId, const gchar *message, const gchar *name);
    void setData(const std::vector<Message>& messages);
    //void get_input_login_content(const char * & username, const char * & password);

private:
    GtkWidget *view= nullptr;
    GtkCellRenderer *renderer= nullptr;
    GtkTreeModel  *list_model_create();
};


#endif //CLIENT_MESSAGELIST_H
