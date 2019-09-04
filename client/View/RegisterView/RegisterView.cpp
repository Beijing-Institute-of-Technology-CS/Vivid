//
// Created by William Zhang on 2019-08-31.
//

#include "RegisterView.h"

void RegisterView::show() {
    if (isShow) {
        return;
    }

    GtkBuilder *builder;

    GtkWidget *submit_button;
    GtkWidget *cancel_button;

    builder = gtk_builder_new ();//指针分配空间
    gtk_builder_add_from_file (builder, "RegisterView.xml", NULL);//读取xml文件

    regi_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    regi_window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
    entry_name = GTK_WIDGET (gtk_builder_get_object (builder, "entry_name"));
    entry_pwd = GTK_WIDGET (gtk_builder_get_object (builder, "entry_pass"));
    entry_check = GTK_WIDGET (gtk_builder_get_object (builder, "entry_check"));
    submit_button= GTK_WIDGET (gtk_builder_get_object (builder, "button_submit"));
    cancel_button= GTK_WIDGET (gtk_builder_get_object (builder, "button_cancel"));

    gtk_widget_set_name(regi_window, "register_view_window");
    gtk_widget_set_name(entry_name, "register_view_entry_view");
    gtk_widget_set_name(entry_pwd, "register_view_entry_pwd");
    gtk_widget_set_name(entry_check, "register_view_entry_check");
    gtk_widget_set_name(submit_button, "register_view_submit_btn");
    gtk_widget_set_name(cancel_button, "register_view_cancel_btn");

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
