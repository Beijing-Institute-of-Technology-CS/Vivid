//
// Created by William Zhang on 2019-08-29.
//

#include "LoginView.h"

void LoginView::get_input_login_content(const char *&id, const char *&password) {
    id = gtk_entry_get_text(GTK_ENTRY(id_entry));
    password = gtk_entry_get_text(GTK_ENTRY(psw_entry));
}

void LoginView::show() {
    if (isShow) {
        return;
    }

    //构造控件
    GtkWidget *login_button;
    GtkWidget *reg_button;
    GtkWidget *close_button;
    GtkWidget *logo_img;
    GtkWidget *font_id;
    GtkWidget *font_password;

    //GTK BUILDER
    GtkBuilder * builder;
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "login.xml", nullptr);


    login_window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    login_button = GTK_WIDGET(gtk_builder_get_object(builder, "login_btn"));
    reg_button = GTK_WIDGET(gtk_builder_get_object(builder, "reg_btn"));
    id_entry = GTK_WIDGET(gtk_builder_get_object(builder, "id_entry"));
    psw_entry = GTK_WIDGET(gtk_builder_get_object(builder, "psw_entry"));
    close_button = GTK_WIDGET(gtk_builder_get_object(builder, "close_btn"));
    logo_img = GTK_WIDGET(gtk_builder_get_object(builder, "login_view_logo"));
    font_id = GTK_WIDGET(gtk_builder_get_object(builder, "font_id"));
    font_password = GTK_WIDGET(gtk_builder_get_object(builder, "font_password"));

    gtk_widget_set_name(close_button, "login_view_close_btn");
    gtk_widget_set_name(login_button, "login_view_login_btn");
    gtk_widget_set_name(reg_button, "login_view_reg_btn");
    gtk_widget_set_name(id_entry, "login_view_id_entry");
    gtk_widget_set_name(psw_entry, "login_view_psw_entry");
    gtk_widget_set_name(logo_img, "login_view_logo");
    gtk_widget_set_name(login_window, "login_view_window");
    gtk_widget_set_name(font_id, "login_view_font_id");
    gtk_widget_set_name(font_password, "login_view_font_password");

    //连接
    g_signal_connect(G_OBJECT(login_window),"destroy", G_CALLBACK(on_destroy), this);
    g_signal_connect(G_OBJECT(login_button),"clicked", G_CALLBACK(on_button_login_clicked), this);
    g_signal_connect(G_OBJECT(reg_button), "clicked", G_CALLBACK(on_button_register_clicked), this);
    g_signal_connect(G_OBJECT(close_button), "clicked", G_CALLBACK(on_button_close_clicked), this);

    //设置参数
    gtk_entry_set_visibility(GTK_ENTRY(psw_entry),FALSE);
    gtk_widget_show_all(login_window);
    isShow = true;
}

void LoginView::destroy() {
    if (!isShow) {
        return;
    }
    isShow = false;
    gtk_widget_destroy(login_window);
}

void LoginView::on_button_login_clicked(GtkWidget *button, gpointer data) {
    if (((LoginView *) data)->callback == nullptr) {
        return;
    }
    ((LoginView *) data)->callback->onButtonLoginClicked();
}

void LoginView::setCallback(LoginViewCallback *loginCallback) {
    LoginView::callback = loginCallback;
}


void LoginView::on_button_register_clicked(GtkWidget *button, gpointer data) {
    if (((LoginView *) data)->callback == nullptr) {
        return;
    }
    ((LoginView *) data)->callback->onButtonRegisterClicked();
}

void LoginView::on_destroy(GtkWidget *widget, gpointer data) {
    ((LoginView *) data)->isShow = false;
    if (((LoginView *) data)->callback == nullptr) {
        return;
    }
    ((LoginView *) data)->callback->onLoginViewDestroy();
}

void LoginView::on_button_close_clicked(GtkWidget *button, gpointer data) {
    gtk_widget_destroy(((LoginView *) data)->login_window);
}
