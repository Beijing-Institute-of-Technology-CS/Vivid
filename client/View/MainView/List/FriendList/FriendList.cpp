//
// Created by dd on 8/30/19.
//

#include "FriendList.h"
#include <string>

FriendList::FriendList() {

    view =gtk_tree_view_new_with_model(list_model_create());

    renderer=gtk_cell_renderer_text_new();

    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                USER_ID,
                                                "id",renderer,
                                                "text",USER_ID,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                USER_NAME,
                                                "name",renderer,
                                                "text",USER_NAME,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                USER_MESSAGE,
                                                "last message",renderer,
                                                "text",USER_MESSAGE,
                                                NULL);
}

GtkTreeModel *FriendList::list_model_create() {
    GtkListStore *store;
    store = gtk_list_store_new(USER_COLUMNS,G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);
    return GTK_TREE_MODEL(store);
}

void FriendList::append(const gchar *id, const gchar *name,const char *message) {
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(view)));
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,USER_ID,id,USER_NAME,name, USER_MESSAGE,message,-1);
}

GtkWidget *FriendList::getView() {
    return view;
}

void FriendList::setData(const std::vector<User>& User) {
    GtkListStore *store;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(view)));
    gtk_list_store_clear(store);
    for (auto i : User) {
        append(std::to_string(i.getUId()).c_str(), i.getUName(),"");
    }
}

void FriendList::setFriend(const int id, const char *message) {
    GtkTreeModel *pmodel;
    pmodel = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    GtkListStore *store;
    GtkTreeIter iter;
    gtk_tree_model_get_iter_first(pmodel,&iter);

    char *idstr;
    char *name;
    do{
        gtk_tree_model_get(GTK_TREE_MODEL(pmodel),&iter,USER_ID,&idstr,USER_NAME,&name,-1);
        int ID;
        sscanf(idstr,"%d",&ID);
        if(ID == id)
        {
            store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(view)));
            gtk_list_store_set(store, &iter,USER_ID,idstr,USER_MESSAGE,message, -1);
            return;
        }
    }while(gtk_tree_model_iter_next(pmodel,&iter));

    append(std::to_string(id).c_str(),NULL,message);
}


