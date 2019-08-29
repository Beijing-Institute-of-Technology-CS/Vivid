#include <iostream>
#include <gtk/gtk.h>
#include "View/TestView/MainView.h"

MainView mainView;

/**
 * 点击按钮回调
 */
void on_button_clicked();

/**
 * 初始化回调
 */
void init();

/**
 * 启动主界面
 */
void start_main_view();

int main(int argc , char* argv[]) {
    //初始化
    init();
    gtk_init(&argc, &argv);

    //启动主界面
    start_main_view();

    return 0;
}

void init() {
    mainView.set_button_callback(on_button_clicked);
}


void start_main_view() {
    mainView.show_main_view();
}

void on_button_clicked() {
    std::cout << "clicked!" << std::endl;
}