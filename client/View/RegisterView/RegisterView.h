//
// Created by William Zhang on 2019-08-31.
//

#ifndef CLIENT_REGISTERVIEW_H
#define CLIENT_REGISTERVIEW_H

#include <gtk/gtk.h>
#include "../TipView/TipView.h"

class RegisterViewCallback;

class RegisterView {
public:

    /**
     * 展示与销毁
     */
    void show();
    void destroy();

    void setCallback(RegisterViewCallback *submitCallback);

private:
    //is show
    bool isShow = false;

    //GTK Widget
    GtkWidget* regi_window;
    GtkWidget* entry_name;
    GtkWidget* entry_pwd;
    GtkWidget* entry_check;

    //submit callback
    RegisterViewCallback * submitCallback = nullptr;

    //GTK callback
    static void onSubmitClickCallback(GtkWidget * button, gpointer data);
    static void onCancelClickCallback(GtkWidget * widget, gpointer data);
    static void onDestroy(GtkWidget * widget, gpointer data);
    static void on_close_btn_callback(GtkWidget * widget, gpointer data);
};

//注册点击回调
class RegisterViewCallback {
public:
    virtual void onRegisterSubmit(const char * username, const char * password) = 0;
};

#endif //CLIENT_REGISTERVIEW_H
