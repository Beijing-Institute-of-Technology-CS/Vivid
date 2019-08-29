//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_LOGINVIEW_H
#define CLIENT_LOGINVIEW_H

#include <gtk/gtk.h>

class LoginView {
public:
    void set_login_callback(void (* callback)(GtkWidget* button,gpointer data));
    void create();
    void show();

    void get_input_login_content(const char * & username, const char * & password);

private:
    void (* button_login_clicked_callback)(GtkWidget* button,gpointer data);

    GtkWidget *login_window;
    GtkWidget *name_entry;
    GtkWidget *psw_entry;

};


#endif //CLIENT_LOGINVIEW_H
