//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_LOGINVIEW_H
#define CLIENT_LOGINVIEW_H

#include <gtk/gtk.h>

class OnButtonLoginClickedCallback;
class OnLoginWindowCloseCallback;

class LoginView {
public:
    /**
     * 构造、展示、销毁
     */
    void create();
    void show();
    void destroy();

    /**
     * 设置登录点击回调
     * @param loginClickedCallback
     */
    void setLoginClickedCallback(OnButtonLoginClickedCallback *loginClickedCallback);
    /**
     * 设置窗口关闭回调
     * @param closeCallback
     */
    void setCloseCallback(OnLoginWindowCloseCallback *closeCallback);

    /**
     * 获取输入的用户名、密码
     * @param username
     * @param password
     */
    void get_input_login_content(const char * & username, const char * & password);

private:
    //GTK控件
    GtkWidget *login_window = nullptr;
    GtkWidget *name_entry = nullptr;
    GtkWidget *psw_entry = nullptr;

    //登录点击回调
    OnButtonLoginClickedCallback * loginClickedCallback = nullptr;
    //关闭窗口回调
    OnLoginWindowCloseCallback * closeCallback = nullptr;

    //GTK回调
    static void onButtonLoginClicked(GtkWidget* button, gpointer data);
    static void onButtonRegisterClicked(GtkWidget* button, gpointer data);
    static void onWindowClose(GtkWidget * widget, gpointer data);
};

//登录点击回调
class OnButtonLoginClickedCallback {
public:
    virtual void onButtonLoginClicked() = 0;
    virtual void onButtonRegisterClicked() = 0;
};

//窗口关闭回调
class OnLoginWindowCloseCallback {
public:
    virtual void onLoginWindowClose() = 0;
};


#endif //CLIENT_LOGINVIEW_H
