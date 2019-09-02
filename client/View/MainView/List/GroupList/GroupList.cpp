//
// Created by William Zhang on 2019-09-02.
//

#include <string>
#include "GroupList.h"

GroupList::GroupList() {
    view =gtk_tree_view_new_with_model(list_model_create());

    renderer=gtk_cell_renderer_text_new();

    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                GROUP_ID,
                                                "id",renderer,
                                                "text",GROUP_ID,
                                                NULL);
}

GtkWidget *GroupList::getView() {
    return view;
}

void GroupList::append(const gchar *id) {
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(view)));
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,GROUP_ID,id, -1);
}

void GroupList::setData(const std::vector<Group>& groups) {
    GtkListStore *store;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(view)));
    gtk_list_store_clear(store);
    for (auto i : groups) {
        append(std::to_string(i.getGId()).c_str());
    }
}

GtkTreeModel *GroupList::list_model_create() {
    GtkListStore *store;
    store = gtk_list_store_new(GROUP_COLUMNS,G_TYPE_STRING);
    return GTK_TREE_MODEL(store);
}
