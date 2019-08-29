//
// Created by William Zhang on 2019-08-29.
//

#include "LoginView.h"

void LoginView::show() {
    GtkWidget *login_window;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget* entry1;
    GtkWidget* entry2;


    GtkWidget *login_button;
    GtkWidget *reg_button;
    GtkWidget *image_logo;
    GtkWidget *sep;

    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    box = gtk_vbox_new(FALSE,0);
    box1 = gtk_hbox_new(FALSE,15);
    box2 = gtk_hbox_new(FALSE,15);
    image_logo = gtk_image_new_from_file("logo.png");
    sep = gtk_hseparator_new();
    label1 = gtk_label_new("                         用户名：");
    entry1 = gtk_entry_new();
    label2 = gtk_label_new("                              密码：");
    entry2 = gtk_entry_new();
    box3 = gtk_hbutton_box_new();
    reg_button = gtk_button_new_with_label("register");
    login_button = gtk_button_new_with_label("login");

    LoginInputContent inputContent;
    inputContent.usernameWidget = entry1;
    inputContent.passwordWidget = entry2;

    g_signal_connect(G_OBJECT(login_window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(login_button),"clicked", G_CALLBACK(button_login_clicked_callback), &inputContent);
//    g_signal_connect_swapped(G_OBJECT(login_button),"clicked", G_CALLBACK(gtk_widget_destroy),login_window);

    gtk_window_set_title(GTK_WINDOW(login_window),"login");
    gtk_window_set_default_size(GTK_WINDOW(login_window),500,400);
    gtk_window_set_position(GTK_WINDOW(login_window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(login_window),0);
    gtk_window_set_resizable(GTK_WINDOW(login_window),FALSE);


    gtk_container_add(GTK_CONTAINER(login_window),box);
    gtk_widget_set_size_request(image_logo,500,150);
    gtk_box_pack_start(GTK_BOX(box),image_logo,FALSE,FALSE,0);

    gtk_widget_set_size_request(box1,200,30);
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);

    gtk_widget_set_size_request(box2,200,30);
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);


    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(box1),entry1,FALSE,FALSE,5);

    gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),entry2,FALSE,FALSE,5);


    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(box3),reg_button,FALSE,FALSE,5);
    gtk_button_set_relief(GTK_BUTTON(reg_button),GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(box3),login_button,FALSE,FALSE,5);

    gtk_widget_show_all(login_window);
    gtk_main();
}

void LoginView::set_login_callback(void (* callback)(GtkWidget* button,gpointer data)) {
    this->button_login_clicked_callback = callback;
}
