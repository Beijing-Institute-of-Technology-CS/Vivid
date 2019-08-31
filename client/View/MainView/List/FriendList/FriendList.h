//
// Created by dd on 8/31/19.
//

#ifndef CLIENT_FRIENDLIST_H
#define CLIENT_FRIENDLIST_H

#include <gtk/gtk.h>

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
    void append(GtkWidget *list, const gchar *name,const gchar *message);
private:
    GtkWidget *view= nullptr;
    GtkCellRenderer *renderer= nullptr;
    GtkTreeModel  *list_model_create();

};
#endif //CLIENT_FRIENDLIST_H
