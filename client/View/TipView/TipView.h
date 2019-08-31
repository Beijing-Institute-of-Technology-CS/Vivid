//
// Created by William Zhang on 2019-08-31.
//

#ifndef CLIENT_TIPVIEW_H
#define CLIENT_TIPVIEW_H

#include <gtk/gtk.h>

class TipViewCallback;

class TipView {
public:
    TipView(const char *msg);
    void show();
    void destroy();

    void setTipViewCallback(TipViewCallback *tipViewCallback);

private:
    const char * msg;
    TipViewCallback * tipViewCallback = nullptr;
    GtkWidget *window;
    static void onPosClickCallback(GtkWidget * button, gpointer data);
    static void onNegClickCallback(GtkWidget * button, gpointer data);
};

class TipViewCallback {
public:
    virtual void onPosClick() = 0;
    virtual void onNegClick() = 0;
};


#endif //CLIENT_TIPVIEW_H
