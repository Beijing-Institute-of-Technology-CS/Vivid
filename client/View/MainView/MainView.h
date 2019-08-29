//
// Created by William Zhang on 2019-08-29.
//

#ifndef CLIENT_MAINVIEW_H
#define CLIENT_MAINVIEW_H


class MainView {
public:
    /**
     * 展示主界面
     */
    void show_main_view();

    /**
     * 设置回调
     * @param callback
     */
    void set_button_callback(void (* callback)());

private:
    void (* button_clicked_callback)();
};


#endif //CLIENT_MAINVIEW_H
