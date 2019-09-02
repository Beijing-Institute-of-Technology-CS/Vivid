#include <iostream>
#include <gtk/gtk.h>
#include "Controller/MainController.h"

int main(int argc , char* argv[]) {
    gtk_init(&argc, &argv);

//    MainController mainController = MainController::getInstance();
//
//    mainController.start();

    MainController::getInstance().start();

    gtk_main();

    return 0;
}
