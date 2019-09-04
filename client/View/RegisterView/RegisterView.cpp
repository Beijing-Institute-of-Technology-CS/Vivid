//
// Created by William Zhang on 2019-08-31.
//

#include "RegisterView.h"

void RegisterView::show() {
    if (isShow) {
        return;
    }

    GtkWidget *box;
    GtkWidget *button_box;
    GtkWidget *button_box_left;
    GtkWidget *button_box_right;
    GtkWidget *fixed;

    GtkWidget *label_name;
    GtkWidget *label_pwd;
    GtkWidget *label_check;

    GtkWidget *submit_button;
    GtkWidget *cancel_button;
    GtkWidget *image_logo;
    GtkWidget *sep;


    regi_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*窗口设置*/
    gtk_window_set_title(GTK_WINDOW(regi_window),"register");
    gtk_window_set_default_size(GTK_WINDOW(regi_window),500,350);
    gtk_window_set_position(GTK_WINDOW(regi_window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(regi_window),0);
    gtk_window_set_resizable(GTK_WINDOW(regi_window),FALSE);

    /*按从上到下顺序布置*/
    box = gtk_vbox_new(FALSE,0);
    fixed=gtk_fixed_new();
    button_box = gtk_hbox_new(FALSE,15);
    button_box_left = gtk_hbox_new(FALSE,15);
    button_box_right = gtk_hbox_new(FALSE,15);

    image_logo = gtk_image_new_from_file("logoooooo.png");
    gtk_widget_set_size_request(image_logo,500,150);

    sep = gtk_hseparator_new();

    label_name = gtk_label_new("username:");
    entry_name = gtk_entry_new();

    label_pwd = gtk_label_new("password:");
    entry_pwd = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_pwd),FALSE);

    label_check = gtk_label_new("password:");
    entry_check = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_check),FALSE);

    submit_button = gtk_button_new_with_label("          submit          ");
    cancel_button = gtk_button_new_with_label("          cancel          ");

    gtk_container_add(GTK_CONTAINER(regi_window),box);
    gtk_box_pack_start(GTK_BOX(box),image_logo,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),fixed,FALSE,FALSE,0);

    gtk_fixed_put(GTK_FIXED(fixed),label_name,120,10);
    gtk_fixed_put(GTK_FIXED(fixed),entry_name,200,10);
    gtk_fixed_put(GTK_FIXED(fixed),label_pwd,120,60);
    gtk_fixed_put(GTK_FIXED(fixed),entry_pwd,200,60);
    gtk_fixed_put(GTK_FIXED(fixed),label_check,120,110);
    gtk_fixed_put(GTK_FIXED(fixed),entry_check,200,110);

    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(box),button_box,FALSE,FALSE,5);

    //gtk_box_pack_start(GTK_BOX(button_box),submit_button,FALSE,FALSE,5);
    //gtk_box_pack_end(GTK_BOX(button_box),cancel_button,FALSE,FALSE,5);

    gtk_box_pack_start(GTK_BOX(button_box),button_box_left,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(button_box),button_box_right,TRUE,TRUE,5);

    gtk_box_pack_end(GTK_BOX(button_box_left),submit_button,FALSE,FALSE,5);

    gtk_button_set_relief(GTK_BUTTON(submit_button),GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(button_box_right),cancel_button,FALSE,FALSE,5);
    gtk_button_set_relief(GTK_BUTTON(cancel_button),GTK_RELIEF_NONE);

    /*按钮触发*/
    g_signal_connect(G_OBJECT(submit_button),"clicked", G_CALLBACK(onSubmitClickCallback),this);
    g_signal_connect(G_OBJECT(cancel_button),"clicked", G_CALLBACK(onCancelClickCallback),this);
    g_signal_connect(G_OBJECT(regi_window),"destroy", G_CALLBACK(onDestroy), this);

    gtk_widget_show_all(regi_window);
    isShow = true;
}

void RegisterView::setCallback(RegisterViewCallback *submitCallback) {
    RegisterView::submitCallback = submitCallback;
}

void RegisterView::destroy() {
    if (isShow) {
        gtk_widget_destroy(regi_window);
    }
    isShow = false;
}

void RegisterView::onSubmitClickCallback(GtkWidget *button, gpointer data) {
    RegisterView * view = (RegisterView *)data;
    const char * username = gtk_entry_get_text(GTK_ENTRY(view->entry_name));
    const char * pass = gtk_entry_get_text(GTK_ENTRY(view->entry_pwd));
    const char * check = gtk_entry_get_text(GTK_ENTRY(view->entry_check));

    /*检查密码为空或密码不一致*/
    if(!strcmp(pass,"")){
        TipView::showSimpleTipView("密码不能为空");
        return;
    }
    if(strcmp(pass,check)){
        TipView::showSimpleTipView("密码与密码验证不一致");
        return;
    }

    if (view->submitCallback != nullptr) {
        view->submitCallback->onRegisterSubmit(username, pass);
    }
}

void RegisterView::onCancelClickCallback(GtkWidget *widget, gpointer data) {
    ((RegisterView *)data)->destroy();
}

void RegisterView::onDestroy(GtkWidget *widget, gpointer data) {
    ((RegisterView *)data)->isShow = false;
}
