#include <iostream>
#include <gtk/gtk.h>
#include "Controller/MainController.h"

void exit_application() {
    gtk_main_quit();
}

int main(int argc , char* argv[]) {
    gtk_init(&argc, &argv);

    MainController mainController;

    mainController.setExitApplicationFunc(exit_application);

    mainController.start();

    gtk_main();

    return 0;
}
