//
// Created by William Zhang on 2019-08-29.
//

#include "LoginView.h"

void LoginView::create() {

    GtkWidget *main_box;
    GtkWidget *fixed;
    GtkWidget *button_box;
    GtkWidget *name_label;
    GtkWidget *psw_label;

    GtkWidget *login_button;
    GtkWidget *reg_button;
    GtkWidget *image_logo;
    GtkWidget *sep;

    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    main_box = gtk_vbox_new(FALSE,0);
    fixed=gtk_fixed_new();
    button_box = gtk_hbox_new(FALSE,15);
    image_logo = gtk_image_new_from_file("logo.png");
    sep = gtk_hseparator_new();
    name_label = gtk_label_new("用户名：");
    name_entry = gtk_entry_new();
    psw_label = gtk_label_new("密码：");
    psw_entry = gtk_entry_new();
    reg_button = gtk_button_new_with_label("register");
    login_button = gtk_button_new_with_label("login");

    g_signal_connect(G_OBJECT(login_window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(login_button),"clicked", G_CALLBACK(button_login_clicked_callback), this);

    gtk_window_set_title(GTK_WINDOW(login_window),"login");
    gtk_window_set_default_size(GTK_WINDOW(login_window),500,400);
    gtk_window_set_position(GTK_WINDOW(login_window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(login_window),0);
    gtk_window_set_resizable(GTK_WINDOW(login_window),FALSE);

    gtk_entry_set_visibility(GTK_ENTRY(psw_entry),FALSE);

    gtk_container_add(GTK_CONTAINER(login_window),main_box);
    gtk_widget_set_size_request(image_logo,500,150);
    gtk_box_pack_start(GTK_BOX(main_box),image_logo,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(main_box),fixed,FALSE,FALSE,0);

    gtk_fixed_put(GTK_FIXED(fixed),name_label,120,10);
    gtk_fixed_put(GTK_FIXED(fixed),name_entry,200,10);
    gtk_fixed_put(GTK_FIXED(fixed),psw_label,140,40);
    gtk_fixed_put(GTK_FIXED(fixed),psw_entry,200,40);

    gtk_box_pack_start(GTK_BOX(main_box),sep,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(main_box),button_box,FALSE,FALSE,5);    
    gtk_box_pack_start(GTK_BOX(button_box),reg_button,FALSE,FALSE,5);
    
    gtk_button_set_relief(GTK_BUTTON(reg_button),GTK_RELIEF_NONE);

    gtk_box_pack_end(GTK_BOX(button_box),login_button,FALSE,FALSE,5);
}

void LoginView::set_login_callback(void (* callback)(GtkWidget* button,gpointer data)) {
    this->button_login_clicked_callback = callback;
}

void LoginView::get_input_login_content(const char *&username, const char *&password) {
    username = gtk_entry_get_text(GTK_ENTRY(name_entry));
    password = gtk_entry_get_text(GTK_ENTRY(psw_entry));
}

void LoginView::show() {
    gtk_widget_show_all(login_window);
}
