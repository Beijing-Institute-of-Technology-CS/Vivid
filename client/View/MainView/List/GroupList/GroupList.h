//
// Created by William Zhang on 2019-09-02.
//

#ifndef CLIENT_GROUPLIST_H
#define CLIENT_GROUPLIST_H

#include <gtk/gtk.h>
#include <vector>
#include "../../../../Beans/Group.h"

enum{
    GROUP_ID,
    GROUP_COLUMNS
};

class GroupList {
public:
    GroupList();
    GtkWidget *getView();
    void append(const gchar *id);
    void setData(const std::vector<Group>& groups);
private:
    GtkWidget *view= nullptr;
    GtkCellRenderer *renderer= nullptr;
    GtkTreeModel  *list_model_create();
};


#endif //CLIENT_GROUPLIST_H
