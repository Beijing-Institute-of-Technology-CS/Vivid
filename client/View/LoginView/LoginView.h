//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_LOGINVIEW_H
#define CLIENT_LOGINVIEW_H

#include <gtk/gtk.h>

class LoginView {
public:
    void set_login_callback(void (* callback)(GtkWidget* button,gpointer data));
    void show();

private:
    void (* button_login_clicked_callback)(GtkWidget* button,gpointer data);
};

typedef struct LoginInputContent {
    const GtkWidget* usernameWidget;
    const GtkWidget* passwordWidget;
} LoginInputContent;


#endif //CLIENT_LOGINVIEW_H
