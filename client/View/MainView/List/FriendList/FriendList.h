//
// Created by dd on 8/31/19.
//

#ifndef CLIENT_FRIENDLIST_H
#define CLIENT_FRIENDLIST_H

#include <gtk/gtk.h>
#include <vector>
#include "../../../../Beans/User.h"

enum{
    FRIEND_ID,
    FRIEND_NAME,
    FRIEND_COLUMNS
};

class friend_list
{
public:
    friend_list();
    GtkWidget *getView();
    void append(const gchar *id,const gchar *name);
    void setData(const std::vector<User>& contacts);
private:
    GtkWidget *view= nullptr;
    GtkCellRenderer *renderer= nullptr;
    GtkTreeModel  *list_model_create();

};
#endif //CLIENT_FRIENDLIST_H
