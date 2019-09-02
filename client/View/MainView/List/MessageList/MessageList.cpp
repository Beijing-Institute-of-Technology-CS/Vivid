//
// Created by dd on 8/30/19.
//

#include "MessageList.h"

message_list::message_list() {

    view =gtk_tree_view_new_with_model(list_model_create());

    renderer=gtk_cell_renderer_text_new();

    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                COLUMN_ID,
                                                "id",renderer,
                                                "text",COLUMN_ID,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                COLUMN_NAME,
                                                "name",renderer,
                                                "text",COLUMN_NAME,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                COLUMN_MESSAGE,
                                                "message",renderer,
                                                "text",COLUMN_MESSAGE,
                                                NULL);
}

GtkTreeModel *message_list::list_model_create() {
    GtkListStore *store;
    store = gtk_list_store_new(MESSAGE_COLUMNS,G_TYPE_INT,G_TYPE_STRING, G_TYPE_STRING);
    return GTK_TREE_MODEL(store);
}

void message_list::append(const gchar *name, const gchar *message) {
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(view)));
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,COLUMN_ID,history_id++,COLUMN_NAME,name,COLUMN_MESSAGE, message, -1);
}

GtkWidget *message_list::getView() {
    return view;
}

