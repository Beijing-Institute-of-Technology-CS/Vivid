//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_TESTVIEW_H
#define CLIENT_TESTVIEW_H


#include <gtk/gtk.h>

class TestViewExitCallback;

class TestView {
public:
    /**
     * 展示主界面
     */
    void show_main_view();

    void setExitCallback(TestViewExitCallback *exitCallback);

private:
    static void buttonClickedCallback(GtkWidget * button, gpointer data) {
        printf("Hey!\n");
    }

    static void exit_callback(GtkWidget * button, gpointer data);

    TestViewExitCallback * exitCallback = nullptr;
};

class TestViewExitCallback {
public:
    virtual void onTestViewExit() = 0;
};


#endif //CLIENT_TESTVIEW_H
