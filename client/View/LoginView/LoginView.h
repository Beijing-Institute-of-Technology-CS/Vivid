//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_LOGINVIEW_H
#define CLIENT_LOGINVIEW_H

#include <gtk/gtk.h>

class LoginViewCallback;

class LoginView {
public:
    /**
     * 展示、销毁
     */
    void show();
    void destroy();

    /**
     * 设置登录点击回调
     * @param loginClickedCallback
     */
    void setCallback(LoginViewCallback *loginCallback);

    /**
     * 获取输入的用户名、密码
     * @param id
     * @param password
     */
    void get_input_login_content(const char * & id, const char * & password);

private:
    //isShow
    bool isShow = false;

    //GTK控件
    GtkWidget *login_window = nullptr;
    GtkWidget *id_entry = nullptr;
    GtkWidget *psw_entry = nullptr;

    //登录点击回调
    LoginViewCallback * callback = nullptr;

    //GTK回调
    static void on_button_login_clicked(GtkWidget *button, gpointer data);
    static void on_button_register_clicked(GtkWidget *button, gpointer data);
    static void on_destroy(GtkWidget *widget, gpointer data);
    static void on_button_close_clicked(GtkWidget *button, gpointer data);
};

//登录点击回调
class LoginViewCallback {
public:
    virtual void onButtonLoginClicked() = 0;
    virtual void onButtonRegisterClicked() = 0;
    virtual void onLoginViewDestroy() = 0;
};


#endif //CLIENT_LOGINVIEW_H
