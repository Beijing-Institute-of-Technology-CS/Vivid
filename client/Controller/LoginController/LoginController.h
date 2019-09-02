//
// Created by William Zhang on 2019-08-30.
//

#ifndef CLIENT_LOGINCONTROLLER_H
#define CLIENT_LOGINCONTROLLER_H

#include <string>
#include "../../View/LoginView/LoginView.h"
#include "../../View/RegisterView/RegisterView.h"

class LoginController : public LoginViewCallback, RegisterViewCallback {
public:
    LoginController();

    static LoginController & getInstance () {
        static LoginController instance;
        return instance;
    }

    //userInfo
    int userId = -1;
    std::string username;
    std::string userPassword;

    /**
     * 创建并启动LoginView
     */
    void startLoginView();

    /**
     * 登录相关
     */
     void loginSuccess(std::string username);
     void loginFailed();

    /*=======================callback========================*/

    /**
     * login view callback
     */
    void onButtonLoginClicked() override;
    void onButtonRegisterClicked() override;
    void onLoginViewDestroy() override;

    /**
     * register view callback
     */
    void onRegisterSubmit(const char * username, const char * password) override;

private:
    //status
    bool isLoggedIn = false;

    //View
    LoginView loginView;
    RegisterView registerView;

    /*=======================StaticThreadFunc========================*/

    static gboolean login_success(gpointer id);
    static gboolean login_failed(gpointer data);
    static gboolean register_success(gpointer id);
};

#endif //CLIENT_LOGINCONTROLLER_H
