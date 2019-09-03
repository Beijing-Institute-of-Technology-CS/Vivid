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
    GtkWidget *main_box;
    GtkWidget *fixed;
    GtkWidget *button_box;
    GtkWidget *button_box_left;
    GtkWidget *button_box_right;
    GtkWidget *id_label;
    GtkWidget *psw_label;

    GtkWidget *login_button;
    GtkWidget *reg_button;
    GtkWidget *image_logo;
    GtkWidget *sep;

    //static GdkColor b_color = {0, 0, 0, 0};

    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    main_box = gtk_vbox_new(FALSE,0);
    fixed=gtk_fixed_new();
    button_box= gtk_hbox_new(FALSE,15);
    button_box_left = gtk_hbox_new(FALSE,15);
    button_box_right = gtk_hbox_new(FALSE,15);
    image_logo = gtk_image_new_from_file("logo.png");
    sep = gtk_hseparator_new();
    id_label = gtk_label_new("          ID：");
    id_entry = gtk_entry_new();
    psw_label = gtk_label_new("密码：");
    psw_entry = gtk_entry_new();
    reg_button = gtk_button_new_with_label("      register      ");
    login_button = gtk_button_new_with_label("          login          ");

    //连接
    g_signal_connect(G_OBJECT(login_window),"destroy", G_CALLBACK(on_destroy), this);
    g_signal_connect(G_OBJECT(login_button),"clicked", G_CALLBACK(on_button_login_clicked), this);
    g_signal_connect(G_OBJECT(reg_button), "clicked", G_CALLBACK(on_button_register_clicked), this);

    //设置参数
    gtk_window_set_title(GTK_WINDOW(login_window),"login");
    gtk_window_set_default_size(GTK_WINDOW(login_window),500,300);
    gtk_window_set_position(GTK_WINDOW(login_window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(login_window),0);
    gtk_window_set_resizable(GTK_WINDOW(login_window),FALSE);

    gtk_entry_set_visibility(GTK_ENTRY(psw_entry),FALSE);

    gtk_container_add(GTK_CONTAINER(login_window),main_box);
    gtk_widget_set_size_request(image_logo,500,150);
    gtk_box_pack_start(GTK_BOX(main_box),image_logo,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(main_box),fixed,FALSE,FALSE,0);

    gtk_fixed_put(GTK_FIXED(fixed),id_label,120,20);
    gtk_fixed_put(GTK_FIXED(fixed),id_entry,200,20);
    gtk_fixed_put(GTK_FIXED(fixed),psw_label,140,60);
    gtk_fixed_put(GTK_FIXED(fixed),psw_entry,200,60);

    gtk_box_pack_start(GTK_BOX(main_box),sep,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(main_box),button_box,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(button_box),button_box_left,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(button_box),button_box_right,TRUE,TRUE,5);

    gtk_box_pack_end(GTK_BOX(button_box_left),reg_button,FALSE,FALSE,5);

    gtk_button_set_relief(GTK_BUTTON(reg_button),GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(button_box_right),login_button,FALSE,FALSE,5);
    gtk_button_set_relief(GTK_BUTTON(login_button),GTK_RELIEF_NONE);

    //gtk_widget_modify_bg(reg_button, GTK_STATE_NORMAL, &b_color);
    //gtk_widget_modify_bg(login_button, GTK_STATE_NORMAL, &b_color);

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
