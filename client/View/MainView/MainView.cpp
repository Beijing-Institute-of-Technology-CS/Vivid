//
// Created by William Zhang on 2019-08-29.
//

#include "MainView.h"
#include "List/FriendList/FriendList.h"
#include <gtk/gtk.h>
#include <string>


MainView::MainView():flist(),glist(){
}


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



void MainView::create() {

    GtkWidget *scolled;
    GtkWidget *vbox;
    GtkWidget *info_box;
    GtkWidget *button_box;
    GtkWidget *list_box;
    GtkWidget *image_avatar;
    GtkWidget *label_name;

    GtkWidget *friend_button;
    GtkWidget * group_button;

    GtkWidget * inputConfirmButton;
    GtkTreeSelection *friend_selection;
    GtkTreeSelection *group_selection;

    /**
     * 创建构件
     */
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    scolled = gtk_scrolled_window_new(NULL,NULL);
    vbox = gtk_vbox_new(FALSE,0);
    info_box=gtk_hbox_new(FALSE,0);
    image_avatar = gtk_image_new_from_file("avatar.png");
    label_name=gtk_label_new("dd");
    button_box = gtk_hbox_new(FALSE,0);
    list_box = gtk_vbox_new(FALSE,0);
    friend_button=gtk_button_new_with_label("Contacts");
    group_button = gtk_button_new_with_label("Groups");
    friend_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(flist.getView()));
    group_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(glist.getView()));

    inputHBox = gtk_hbox_new(FALSE, 0);
    inputEntry = gtk_entry_new();
    inputConfirmButton = gtk_button_new_with_label("GO");
    /**
     * 信号连接
     */
    g_signal_connect(G_OBJECT(main_window), "delete_event",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(friend_button),"clicked",
                     G_CALLBACK(ChangeToFriend), this);
    g_signal_connect(G_OBJECT(group_button),"clicked",
                     G_CALLBACK(ChangeToGroup), this);
    g_signal_connect(G_OBJECT(inputConfirmButton),"clicked",
                     G_CALLBACK(goButtonClickedCallback),this);

    g_signal_connect(G_OBJECT(friend_selection),"changed",
                    G_CALLBACK(tree_selection_friend_changed),this);
    g_signal_connect(G_OBJECT(group_selection),"changed",
                     G_CALLBACK(tree_selection_group_changed),this);

    /**
     * 设定属性
     */
    gtk_window_set_title(GTK_WINDOW(main_window),"Vivid");
    gtk_window_set_default_size(GTK_WINDOW(main_window),300,600);
    gtk_window_set_position(GTK_WINDOW(main_window),GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(info_box,300,100);
    gtk_button_set_relief(GTK_BUTTON(friend_button),GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(group_button),GTK_RELIEF_NONE);

    /**
     * 添加构件
     */

    gtk_box_pack_start(GTK_BOX(info_box),image_avatar,FALSE,FALSE,50);
    gtk_box_pack_start(GTK_BOX(info_box),label_name,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(vbox),info_box,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(inputHBox), inputEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(inputHBox), inputConfirmButton, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(button_box),friend_button,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(button_box), group_button, TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(vbox),button_box,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),scolled,TRUE,TRUE,0);
    gtk_container_add(GTK_CONTAINER(scolled),list_box);


    gtk_box_pack_start(GTK_BOX(list_box), inputHBox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(list_box),flist.getView(),TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(list_box),glist.getView(),TRUE,TRUE,5);

    gtk_container_add(GTK_CONTAINER(main_window),vbox);
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





