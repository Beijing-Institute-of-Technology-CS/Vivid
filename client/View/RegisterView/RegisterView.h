//
// Created by William Zhang on 2019-08-31.
//

#ifndef CLIENT_REGISTERVIEW_H
#define CLIENT_REGISTERVIEW_H

#include <gtk/gtk.h>
#include "../TipView/TipView.h"

class OnRegisterSubmitClickCallback;

class RegisterView {
public:

    /**
     * 初始构造函数
     */
    RegisterView();

    /**
     * 展示与销毁
     */
    void show();
    void destroy();

    void setSubmitCallback(OnRegisterSubmitClickCallback *submitCallback);

private:
    //GTK Widget
    GtkWidget* regi_window;
    GtkWidget* entry_name;
    GtkWidget* entry_pwd;
    GtkWidget* entry_check;

    //submit callback
    OnRegisterSubmitClickCallback * submitCallback = nullptr;

    //GTK callback
    static void onSubmitClickCallback(GtkWidget * button, gpointer data);
    static void onCancelClickCallback(GtkWidget * widget, gpointer data);

};

//注册点击回调
class OnRegisterSubmitClickCallback {
public:
    virtual void onRegisterSubmit(const char * username, const char * password) = 0;
};

#endif //CLIENT_REGISTERVIEW_H
