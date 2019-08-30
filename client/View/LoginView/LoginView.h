//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_LOGINVIEW_H
#define CLIENT_LOGINVIEW_H

#include <gtk/gtk.h>

class OnButtonLoginClickedCallback;

class LoginView {
public:
    void create();
    void show();
    void destroy();

    void setLoginClickedCallback(OnButtonLoginClickedCallback *loginClickedCallback);
    void get_input_login_content(const char * & username, const char * & password);

private:
    GtkWidget *login_window = nullptr;
    GtkWidget *name_entry = nullptr;
    GtkWidget *psw_entry = nullptr;

    OnButtonLoginClickedCallback * loginClickedCallback = nullptr;

    //login click callback
    static void onButtonLoginClicked(GtkWidget* button, gpointer data);

};

class OnButtonLoginClickedCallback {
public:
    virtual void onButtonLoginClicked() = 0;
};


#endif //CLIENT_LOGINVIEW_H
