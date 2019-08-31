//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_TESTVIEW_H
#define CLIENT_TESTVIEW_H


#include <gtk/gtk.h>
#include "../../Controller/ApplicationExitCallback.h"

class TestView {
public:
    /**
     * 展示界面
     */
    void show_main_view();

    void setExitCallback(ApplicationExitCallback *exitCallback);

private:
    static void buttonClickedCallback(GtkWidget * button, gpointer data) {
        printf("Hey!\n");
    }

    static void exit_callback(GtkWidget * button, gpointer data);

    ApplicationExitCallback * exitCallback = nullptr;
};


#endif //CLIENT_TESTVIEW_H
