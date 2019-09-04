//
// Created by William Zhang on 2019-08-29.
//

#include "MainView.h"
#include "List/FriendList/FriendList.h"
#include <gtk/gtk.h>
#include <string>
#include <iostream>


void MainView::show()
{
    gtk_widget_show_all(main_window);
    ChangeToFriend(nullptr, this);
}

void MainView::destroy() {
    gtk_widget_destroy(main_window);

}

void MainView::ChangeToFriend(GtkWidget *widget, gpointer data) {
    MainView * mainView = (MainView *) data;
    gtk_entry_set_text(GTK_ENTRY(mainView->inputEntry), "");
    gtk_widget_show(mainView->flist.getView());
    gtk_widget_hide(mainView->glist.getView());
    mainView->mode = CONTACTS;
}


void MainView::ChangeToGroup(GtkWidget *widget, gpointer data) {
    MainView * mainView = (MainView *) data;
    gtk_entry_set_text(GTK_ENTRY(mainView->inputEntry), "");
    gtk_widget_show(mainView->glist.getView());
    gtk_widget_hide(mainView->flist.getView());
    mainView->mode = GROUP;
}



GtkBuilder * MainView::create() {

    GtkWidget *exit_button;
    GtkWidget *button_go;
    GtkWidget *friend_button;
    GtkWidget * group_button;
    GtkTreeSelection *friend_selection;
    GtkTreeSelection *group_selection;
    GtkWidget *list_box;
    GtkBuilder *builder;
    /**
     * 创建构件
     */
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"MainView.xml",NULL);
    main_window = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));

    list_box = GTK_WIDGET(gtk_builder_get_object(builder,"box15"));
    exit_button = GTK_WIDGET(gtk_builder_get_object(builder,"button_close"));
    inputEntry = GTK_WIDGET(gtk_builder_get_object(builder,"input_entry"));
    button_go = GTK_WIDGET(gtk_builder_get_object(builder,"button_go"));
    friend_button = GTK_WIDGET(gtk_builder_get_object(builder,"button_friend"));
    group_button = GTK_WIDGET(gtk_builder_get_object(builder,"button_group"));

    gtk_button_set_label(GTK_BUTTON(friend_button),"Contacts");
    gtk_button_set_label(GTK_BUTTON(group_button),"Group");
    friend_selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder,"friend_selection"));
    group_selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder,"group_selection"));
    flist.create(GTK_WIDGET(gtk_builder_get_object(builder,"contact_list")));
    glist.create(GTK_WIDGET(gtk_builder_get_object(builder,"group_list")));
    /**
     * 信号连接
     */
    g_signal_connect(G_OBJECT(exit_button), "clicked",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(friend_button),"clicked",
                     G_CALLBACK(ChangeToFriend), this);
    g_signal_connect(G_OBJECT(group_button),"clicked",
                     G_CALLBACK(ChangeToGroup), this);
    g_signal_connect(G_OBJECT(button_go),"clicked",
                     G_CALLBACK(goButtonClickedCallback),this);

    g_signal_connect(G_OBJECT(friend_selection),"changed",
                    G_CALLBACK(tree_selection_friend_changed),this);
    g_signal_connect(G_OBJECT(group_selection),"changed",
                     G_CALLBACK(tree_selection_group_changed),this);
    /**
     * 设定属性
     */
     return builder;

}

void MainView::tree_selection_friend_changed(GtkTreeSelection *selection, gpointer data) {
    GtkTreeIter iter;
    GtkTreeModel *model;

    gchar *id;
    gchar *name;

    if(gtk_tree_selection_get_selected(selection,&model,&iter))
    {

        gtk_tree_model_get(model,&iter,USER_ID,&id,USER_NAME,&name,-1);
        g_print("id = %s\n",id);
        g_print("name = %s\n",name);
        int selectedId = std::stoi(id);
        std::string Name = name;
        gtk_tree_selection_unselect_all(selection);
        ((MainView *)data)->callback->selectUser(selectedId,Name);
        g_free(id);
        g_free(name);
    }
}

void MainView::tree_selection_group_changed(GtkTreeSelection *selection, gpointer data) {
    GtkTreeIter iter;
    GtkTreeModel *model;

    gchar *id;
    gchar *message;

    if(gtk_tree_selection_get_selected(selection,&model,&iter))
    {
        gtk_tree_model_get(model,&iter,GROUP_ID,&id,GROUP_MESSAGE,&message,-1);
        g_print("id = %s\n",id);
        g_print("name = %s\n",message);
        int selectedId = std::stoi(id);
        gtk_tree_selection_unselect_all(selection);
        ((MainView *)data)->callback->selectGroup(selectedId);
        g_free(id);
        g_free(message);
    }
}

void MainView::setCallback(MainViewCallback *callback) {
    MainView::callback = callback;
}

void MainView::goButtonClickedCallback(GtkWidget *button, gpointer data) {
    auto * mainView = (MainView *)data;
    std::string idString = mainView->getInput();
    if (idString.empty()) {
        return;
    }
    const char * tmp = idString.c_str();
    for (int i = 0; i < std::strlen(tmp); ++i) {
        if (tmp[i] < '0' || tmp[i] > '9') {
            return;
        }
    }
    int idInt = std::stoi(idString);
    if (mainView->mode == GROUP) {
        mainView->callback->selectGroup(idInt);
    } else if (mainView->mode == CONTACTS) {
        mainView->callback->selectUser(idInt, "User: " + idString);
    }
}

std::string MainView::getInput() {
    std::string content = gtk_entry_get_text(GTK_ENTRY(inputEntry));
    return content;
}





