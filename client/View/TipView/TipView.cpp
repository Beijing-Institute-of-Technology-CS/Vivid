//
// Created by William Zhang on 2019-08-31.
//

#include "TipView.h"
#include <gtk/gtk.h>

TipView::TipView(const char *msg) : msg(msg) {}

void TipView::show() {
    /**
     * 创建构件
     */
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *bbox;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *image;
    GtkWidget *sep;

    /**
     * 设定window属性
     */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy", G_CALLBACK(onNegClickCallback), this);
    gtk_window_set_title(GTK_WINDOW(window),"Tip");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);

    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    hbox = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
    //image = gtk_image_new_from_stock (GTK_STOCK_DIALOG_WARNING,GTK_ICON_SIZE_DIALOG);
    //gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,5);
    label = gtk_label_new(msg);
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5);
    bbox = gtk_hbutton_box_new();
    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),GTK_BUTTONBOX_SPREAD);
    gtk_box_pack_start(GTK_BOX(vbox),bbox,FALSE,FALSE,5);

    /**
     * 信号连接
     */
    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(onPosClickCallback),this);
    g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    g_signal_connect_swapped(G_OBJECT(button),"clicked", G_CALLBACK(gtk_widget_destroy),window);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);

    /**
     * 显示构件
     */
    gtk_widget_show_all(window);
}

void TipView::setTipViewCallback(TipViewCallback *tipViewCallback) {
    TipView::tipViewCallback = tipViewCallback;
}

void TipView::onPosClickCallback(GtkWidget *button, gpointer data) {
    if (((TipView *)data)->tipViewCallback == nullptr) {
        return;
    }
    ((TipView *)data)->tipViewCallback->onPosClick();
}

void TipView::onNegClickCallback(GtkWidget *button, gpointer data) {
    if (((TipView *)data)->tipViewCallback == nullptr) {
        return;
    }
    ((TipView *)data)->tipViewCallback->onNegClick();
}

void TipView::destroy() {
    gtk_widget_destroy(window);
}

void TipView::showSimpleTipView(const char *msg) {
    /**
     * 创建构件
     */
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *bbox;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *sep;

    /**
     * 设定window属性
     */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Tip");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);

    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    hbox = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
    label = gtk_label_new(msg);
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5);
    bbox = gtk_hbutton_box_new();
    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),GTK_BUTTONBOX_SPREAD);
    gtk_box_pack_start(GTK_BOX(vbox),bbox,FALSE,FALSE,5);

    /**
     * 信号连接
     */
    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);

    /**
     * 显示构件
     */
    gtk_widget_show_all(window);
}
