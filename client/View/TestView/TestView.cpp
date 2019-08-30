//
// Created by William Zhang on 2019-08-29.
//

#include "TestView.h"
#include <gtk/gtk.h>

void TestView::exit_callback(GtkWidget * button, gpointer data) {
    printf("TEST_CALLBACK");
    ((TestView *)data)->exitCallback->onTestViewExit();
}

void TestView::show_main_view() {
    /**
     * 创建构件
     */
    GtkWidget * window;
    GtkWidget * button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    button = gtk_button_new_with_label("button");

    /**
     * 信号连接
     */
     g_signal_connect(G_OBJECT(window), "delete_event",
             G_CALLBACK(exit_callback), this);

     g_signal_connect(G_OBJECT(button), "clicked",
             G_CALLBACK(buttonClickedCallback), NULL);

    /**
     * 设定属性
     */
    gtk_window_set_title(GTK_WINDOW(window),"Hello 功能实现");
    gtk_window_set_default_size(GTK_WINDOW(window),500,100);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    gtk_container_set_border_width(GTK_CONTAINER(window),40);


    /**
     * 添加构件
     */
    gtk_container_add(GTK_CONTAINER(window),button);

    /**
     * 显示构件
     */
     gtk_widget_show(button);
     gtk_widget_show(window);
     gtk_main();
}

void TestView::setExitCallback(TestViewExitCallback *exitCallback) {
    TestView::exitCallback = exitCallback;
}

