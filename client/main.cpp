#include <iostream>
#include <gtk/gtk.h>
#include "Controller/MainController.h"

int main(int argc , char* argv[]) {
    gtk_init(&argc, &argv);
    init_db();
    MainController::getInstance().start();
    gtk_main();
    close_db();
    return 0;
}
