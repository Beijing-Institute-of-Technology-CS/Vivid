//
// Created by dd on 9/1/19.
//

#include <iostream>
#include "ChatView.h"

void ChatView::on_send_clicked(GtkButton *button, gpointer data) {

    ChatView *chatView = (ChatView *)data;
    gchar *text;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    std::cout<<"ON_SEND_CLICK"<<std::endl;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatView->textView));

    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    text=gtk_text_buffer_get_text(buffer,&start,&end,TRUE);

    chatView->callback->chatViewSend(text);

    clear_input_area(chatView->textView);
}

void ChatView::clear_input_area(GtkWidget *textView) {
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    gtk_text_buffer_delete(buffer,&start,&end);
}

void ChatView::show() {

    if (isShow) {
        return;
    }
    /*添加构件*/
    isShow = true;
}

void ChatView::receive_message(const char *message) {

    GtkWidget *single_box;
    GtkWidget *message_label;
    single_box = gtk_hbox_new(FALSE,0);
    message_label = gtk_label_new(message);
    //msg.push_back(message_label);
    printf("%s\n",message);
    gtk_label_set_justify(GTK_LABEL(message_label),GTK_JUSTIFY_LEFT);
    gtk_box_pack_start(GTK_BOX(single_box),message_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(message_box),single_box,FALSE,FALSE,0);

    gtk_widget_set_name(single_box, "main_view_receive_box");

    gtk_widget_show(single_box);
    gtk_widget_show(message_label);
}

void ChatView::on_destroy(GtkWidget *widget, gpointer data) {
    ((ChatView *)data)->isShow = false;
}

void ChatView::send_message(std::string message) {
    GtkWidget *single_box;
    GtkWidget *message_label;
    single_box = gtk_hbox_new(FALSE,0);
    message_label = gtk_label_new(message.c_str());
    std::cout<<"nb"<<std::endl;

    gtk_label_set_justify(GTK_LABEL(message_label),GTK_JUSTIFY_RIGHT);
    gtk_box_pack_end(GTK_BOX(single_box),message_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(message_box),single_box,FALSE,FALSE,0);

    gtk_widget_set_name(single_box, "main_view_send_box");

    gtk_widget_show(single_box);
    gtk_widget_show(message_label);
}

void ChatView::setCallback(ChatViewCallback *callback) {
    ChatView::callback = callback;
}

void ChatView::create(GtkBuilder *builder) {
    std::cout<<"chat view create!"<<std::endl;

    GtkWidget *send_button;


    /*获取所创建对象*/

    name_label = GTK_WIDGET(gtk_builder_get_object(builder,"label_chat"));
    message_box = GTK_WIDGET(gtk_builder_get_object(builder,"box10"));

    textView = GTK_WIDGET(gtk_builder_get_object(builder,"textview_input"));
    send_button = GTK_WIDGET(gtk_builder_get_object(builder,"button_send"));


    /*连接响应*/
    g_signal_connect(G_OBJECT(send_button),"clicked",G_CALLBACK(on_send_clicked),this);

    gtk_button_set_label(GTK_BUTTON(send_button),"send");

    gtk_widget_set_name(name_label, "main_view_name_label");
    gtk_widget_set_name(textView, "main_view_input_text");
    gtk_widget_set_name(send_button, "main_view_send_btn");
}

void ChatView::setName(const char *name)
{
    std::cout<<name<<std::endl;
    gtk_label_set_text(GTK_LABEL(name_label),name);
}
