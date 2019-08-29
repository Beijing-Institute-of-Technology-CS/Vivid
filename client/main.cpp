#include <iostream>
#include <gtk/gtk.h>
#include "View/LoginView/LoginView.h"


void login_callback(GtkWidget* button,gpointer data) {
    const LoginInputContent content = * (LoginInputContent*)data;
    const char* username = gtk_entry_get_text(GTK_ENTRY(content.usernameWidget));
    const char* password = gtk_entry_get_text(GTK_ENTRY(content.passwordWidget));
    std::cout << username << std::endl << password << std::endl;
}

int main(int argc , char* argv[]) {
    gtk_init(&argc, &argv);

    LoginView loginView;
    loginView.set_login_callback(login_callback);

    loginView.show();

    return 0;
}
