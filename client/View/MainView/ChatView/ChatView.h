//
// Created by dd on 9/1/19.
//

#ifndef CLIENT_CHATVIEW_H
#define CLIENT_CHATVIEW_H

#include <gtk/gtk.h>

class ChatViewCallback;

class ChatView
{
public:
    void show(const char *name);
    void destroy();
    bool isGroup;
    int currentId;
private:
    bool isShow = false;

    GtkWidget *chat_window = nullptr;
    GtkWidget *vbox= nullptr;
    GtkWidget *textView = nullptr;
    GtkWidget *message_box= nullptr;

    ChatViewCallback * callback;
public:
    void setCallback(ChatViewCallback *callback);

private:

    //static char *get_text(gpointer data);
    static void on_send_clicked(GtkButton *button,gpointer data);
    void receive_message(char *message);
    void send_message(std::string message);
    static void clear_input_area(GtkWidget *textView);
    static void on_destroy(GtkWidget * widget, gpointer data);

};

class ChatViewCallback {
public:
    virtual void chatViewSend(std::string msg) = 0;
};
#endif //CLIENT_CHATVIEW_H
