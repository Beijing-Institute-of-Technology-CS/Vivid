//
// Created by dd on 8/31/19.
//

#ifndef CLIENT_GROUPLIST_H
#define CLIENT_GROUPLIST_H

#include <gtk/gtk.h>
#include <vector>
#include "../../../../Beans/Group.h"

enum{
    GROUP_ID,
    GROUP_MESSAGE,
    GROUP_COLUMNS
};

class GroupList
{
public:
    GroupList();
    GtkWidget *getView();
    void append(const gchar *id,const gchar *message);
    void setData(const std::vector<Group>& contacts);
    void setGroup(const int id,const char *message);
private:
    GtkWidget *view= nullptr;
    GtkCellRenderer *renderer= nullptr;
    GtkTreeModel  *list_model_create();

};
#endif //CLIENT_GROUPLIST_H
