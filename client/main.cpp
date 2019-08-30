#include <iostream>
#include <gtk/gtk.h>
#include "View/LoginView/LoginView.h"
#include "Controller/LoginController/LoginController.h"
#include "Controller/MainController.h"

int main(int argc , char* argv[]) {
    gtk_init(&argc, &argv);

    MainController mainController;
    mainController.start();

    gtk_main();

    return 0;
}
