//
// Created by William Zhang on 2019-08-31.
//

#ifndef CLIENT_TIPVIEW_H
#define CLIENT_TIPVIEW_H

#include <gtk/gtk.h>

class TipViewCallback;

class TipView {
public:
    /**
     * 展示简单Tip
     * 仅含有信息及一个确定按钮
     * @param msg
     */
    static void showSimpleTipView(const char * msg);

    /**
     * 构造函数
     * @param msg 展示消息
     */
    explicit TipView(const char *msg);

    /**
     * 展示与销毁
     */
    void show();
    void destroy();

    /**
     * 设置回调
     * @param tipViewCallback
     */
    void setTipViewCallback(TipViewCallback *tipViewCallback);

private:
    //消息信息
    const char * msg;

    //回调
    TipViewCallback * tipViewCallback = nullptr;

    //主窗口
    GtkWidget *window;

    //GTK回调
    static void onPosClickCallback(GtkWidget * button, gpointer data);
    static void onNegClickCallback(GtkWidget * button, gpointer data);
};

//回调
class TipViewCallback {
public:
    virtual void onPosClick() = 0;
    virtual void onNegClick() = 0;
};


#endif //CLIENT_TIPVIEW_H
