//
// Created by dd on 9/1/19.
//

#ifndef CLIENT_CHATVIEW_H
#define CLIENT_CHATVIEW_H

#include <gtk/gtk.h>
#include <vector>

class ChatViewCallback;


class ChatView
{
public:
    void create(GtkBuilder * builder);
    void setName(const char *name=NULL);
    void show();
    bool isGroup;
    int currentId;
    GtkWidget *message_box= nullptr;
    void receive_message(const char *message);
    void send_message(std::string message);
    void setCallback(ChatViewCallback *callback);
    bool isShow = false;
private:
    //std::vector <GtkWidget *> msg;
    GtkWidget *vbox= nullptr;
    GtkWidget *textView = nullptr;
    GtkWidget * name_label=nullptr;


    ChatViewCallback * callback;
    static void on_send_clicked(GtkButton *button,gpointer data);
    static void clear_input_area(GtkWidget *textView);
    static void on_destroy(GtkWidget * widget, gpointer data);

};

class ChatViewCallback {
public:
    virtual void chatViewSend(std::string msg) = 0;
};
#endif //CLIENT_CHATVIEW_H
