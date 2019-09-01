//
// Created by William Zhang on 2019-08-29.
//

#include "MainView.h"
#include <gtk/gtk.h>



MainView::MainView():mlist(),flist() {
}


void MainView::show()
{
    gtk_widget_show_all(main_window);
    gtk_widget_hide(flist.getView());
}

void MainView::destroy() {
    gtk_widget_destroy(main_window);

}

void MainView::message_add(gchar* name,gchar *message) {
    mlist.append(mlist.getView(),name,message);
}

void MainView::friend_add(gchar *id, gchar *name) {
    flist.append(flist.getView(),id,name);
}

void MainView::ChangeToMessage(GtkWidget *widget, gpointer data) {
    MainView * mainView = (MainView *) data;
    gtk_widget_show(mainView->mlist.getView());
    gtk_widget_hide(mainView->flist.getView());
}


void MainView::ChangeToFriend(GtkWidget *widget, gpointer data) {
    MainView * mainView = (MainView *) data;
    gtk_widget_show(mainView->flist.getView());
    gtk_widget_hide(mainView->mlist.getView());
}

void MainView::create() {
    GtkWidget *scolled;
    GtkWidget *info_box;
    GtkWidget *button_box;
    GtkWidget *image_avatar;
    GtkWidget *label_name;
    GtkWidget *message_button;
    GtkWidget *friend_button;

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
    message_button = gtk_button_new_with_label("message");
    friend_button=gtk_button_new_with_label("friend");


    /**
     * 信号连接
     */
    g_signal_connect(G_OBJECT(main_window), "delete_event",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(message_button),"clicked",
                     G_CALLBACK(ChangeToMessage), this);
    g_signal_connect(G_OBJECT(friend_button),"clicked",
                     G_CALLBACK(ChangeToFriend), this);

    /**
     * 设定属性
     */
    gtk_window_set_title(GTK_WINDOW(main_window),"Vivid");
    gtk_window_set_default_size(GTK_WINDOW(main_window),300,600);
    gtk_window_set_position(GTK_WINDOW(main_window),GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(info_box,300,100);
    gtk_widget_set_size_request(mlist.getView(),300,500);
    gtk_button_set_relief(GTK_BUTTON(message_button),GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(friend_button),GTK_RELIEF_NONE);

    /**
     * 添加构件
     */

    gtk_container_add(GTK_CONTAINER(main_window),scolled);

    gtk_box_pack_start(GTK_BOX(info_box),image_avatar,FALSE,FALSE,50);
    gtk_box_pack_start(GTK_BOX(info_box),label_name,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(vbox),info_box,FALSE,FALSE,0);

    message_add("dd","vegetable");
    message_add("大哥","tql");
    message_add("大哥","这个掌是为您鼓的");
    message_add("cyc","nb");
    message_add("dd","vegetable");
    message_add("大哥","tql");
    message_add("大哥","这个掌是为您鼓的");
    message_add("cyc","nb");

    friend_add("1", "大哥");
    friend_add("2", "还是大哥");

    gtk_box_pack_start(GTK_BOX(button_box),message_button,FALSE,FALSE,50);
    gtk_box_pack_start(GTK_BOX(button_box),friend_button,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(vbox),button_box,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),mlist.getView(),FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(vbox),flist.getView(),FALSE,FALSE,5);
    gtk_container_add(GTK_CONTAINER(scolled),vbox);
}





