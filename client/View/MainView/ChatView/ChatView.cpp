//
// Created by dd on 9/1/19.
//

#include <iostream>
#include "ChatView.h"


//char *ChatView::get_text(gpointer data) {
//    ChatView *chatView = (ChatView *)data;
//    GtkTextBuffer *buffer;
//    GtkTextIter start, end;
//    gchar *text;
//    std::cout<<"1"<<std::endl;
//    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatView->textView));
//    std::cout<<"1"<<std::endl;
//    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
//    text=gtk_text_buffer_get_text(buffer,&start,&end,TRUE);
//    return text;
//}

void ChatView::on_send_clicked(GtkButton *button, gpointer data) {

    ChatView *chatView = (ChatView *)data;
    gchar *text;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    std::cout<<"why"<<std::endl;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatView->textView));

    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    text=gtk_text_buffer_get_text(buffer,&start,&end,TRUE);

    GtkWidget *single_box;
    GtkWidget *message_label;
    single_box = gtk_hbox_new(FALSE,0);
    message_label = gtk_label_new(text);

    gtk_label_set_justify(GTK_LABEL(message_label),GTK_JUSTIFY_RIGHT);
    gtk_box_pack_end(GTK_BOX(single_box),message_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(chatView->message_box),single_box,FALSE,FALSE,0);

    gtk_widget_show(single_box);
    gtk_widget_show(message_label);
    //clear_input_area(chatView->textView);
}

void ChatView::clear_input_area(GtkWidget *textView) {
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    gtk_text_buffer_delete(buffer,&start,&end);
}

void ChatView::show(char *name) {

    if (isShow) {
        destroy();
    }

    GtkWidget *message_scroll;
    GtkWidget *input_scroll;
    GtkWidget *button_box;
    GtkWidget *emoji_button;
    GtkWidget *history_button;

    GtkWidget *send_button;


    /*获取所创建对象*/
    chat_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  //创建窗口
    vbox = gtk_vbox_new(FALSE,0);
    message_scroll = gtk_scrolled_window_new(NULL,NULL);
    input_scroll = gtk_scrolled_window_new(NULL,NULL);
    textView = gtk_text_view_new ();
    message_box = gtk_vbox_new(TRUE,5);
    button_box = gtk_hbox_new(FALSE,0);
    emoji_button = gtk_button_new_with_label("emoji");
    history_button = gtk_button_new_with_label("history");
    send_button = gtk_button_new_with_label("send");


    /*连接响应*/
    g_signal_connect(G_OBJECT(chat_window),"destroy",G_CALLBACK(on_destroy),this);
    g_signal_connect(G_OBJECT(send_button),"clicked",G_CALLBACK(on_send_clicked),this);

    /*设定属性*/
    gtk_window_set_default_size(GTK_WINDOW(chat_window),600,650);
    gtk_container_set_border_width(GTK_CONTAINER(chat_window),15);
    gtk_window_set_title(GTK_WINDOW(chat_window),name);
    gtk_widget_set_size_request(vbox,600,700);
    gtk_widget_set_size_request(message_scroll,600,370);
    gtk_widget_set_size_request(button_box,600,40);
    gtk_widget_set_size_request(input_scroll,600,180);

    /*添加构件*/

    gtk_container_add(GTK_CONTAINER(chat_window),vbox);

    gtk_box_pack_start(GTK_BOX(vbox),message_scroll,FALSE,FALSE,0);
    gtk_container_add(GTK_CONTAINER(message_scroll),message_box);

    gtk_box_pack_start(GTK_BOX(vbox),button_box,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(button_box),emoji_button,FALSE,FALSE,0);
    gtk_box_pack_end(GTK_BOX(button_box),history_button,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(vbox),input_scroll,FALSE,FALSE,5);
    gtk_container_add(GTK_CONTAINER(input_scroll),textView);
    gtk_box_pack_start(GTK_BOX(vbox),send_button,FALSE,FALSE,0);
    gtk_widget_show_all(chat_window);
    isShow = true;
}

void ChatView::receive_message(char *message) {

    GtkWidget *single_box;
    GtkWidget *message_label;
    single_box = gtk_hbox_new(FALSE,0);
    message_label = gtk_label_new(message);
    printf("%s\n",message);
    gtk_label_set_justify(GTK_LABEL(message_label),GTK_JUSTIFY_LEFT);
    gtk_box_pack_end(GTK_BOX(single_box),message_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(message_box),single_box,FALSE,FALSE,0);

    gtk_widget_show(single_box);
}

void ChatView::on_destroy(GtkWidget *widget, gpointer data) {
    ((ChatView *)data)->isShow = false;
}

void ChatView::destroy() {
    gtk_widget_destroy(chat_window);
}
