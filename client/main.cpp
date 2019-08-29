#include <iostream>
#include <gtk/gtk.h>
#include "View/LoginView/LoginView.h"

LoginView loginView;

void login_callback(GtkWidget* widget,gpointer data) {
    const char * username, * password;
    ((LoginView *)data)->get_input_login_content(username, password);
    std::cout << username << std::endl << password << std::endl;
}

int main(int argc , char* argv[]) {
    gtk_init(&argc, &argv);

    loginView.set_login_callback(login_callback);

    loginView.create();

    loginView.show();

    gtk_main();

    return 0;
}
