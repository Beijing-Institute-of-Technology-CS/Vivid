//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_MAINVIEW_H
#define CLIENT_MAINVIEW_H


#include <gtk/gtk.h>

class MainView {
public:
    /**
     * 展示主界面
     */
    void show_main_view();

private:
    static void buttonClickedCallback(GtkWidget * button, gpointer data) {
        printf("Hey!\n");
    }
};


#endif //CLIENT_MAINVIEW_H
