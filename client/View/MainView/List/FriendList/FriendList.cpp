//
// Created by dd on 8/31/19.
//

#include "FriendList.h"

friend_list::friend_list() {
    view =gtk_tree_view_new_with_model(list_model_create());

    renderer=gtk_cell_renderer_text_new();

    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                FRIEND_ID,
                                                "id",renderer,
                                                "text",FRIEND_ID,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                FRIEND_NAME,
                                                "name",renderer,
                                                "text",FRIEND_NAME,
                                                NULL);
}

GtkWidget *friend_list::getView() {
    return view;
}

GtkTreeModel *friend_list::list_model_create() {
    GtkListStore *store;
    store = gtk_list_store_new(FRIEND_COLUMNS,G_TYPE_STRING, G_TYPE_STRING);
    return GTK_TREE_MODEL(store);
}

void friend_list::append(GtkWidget *list, const gchar *id, const gchar *name) {
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,FRIEND_ID,id,FRIEND_NAME,name, -1);
}
