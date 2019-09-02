//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H


#include <vector>
//#include <mysql.h>
#include <iostream>

#include "../Beans/Message.h"
#include "../../Constants.h"
#include "../Beans/User.h"
#include "../Beans/Group.h"

class DatabaseUtils {
public:
//    static void mql_connect(MYSQL &mysql_sock);

    /**
     * 注册用户
     * @param username
     * @param password
     * @return 返回用户uId，为-1表示失败
     */
    static int doRegister(const char * username, const char * password);

    /**
     * 检查密码
     * @param uId
     * @param password
     * @return 密码是否正确
     */
    static bool checkPassword(int uId, const char * password);

    /**
     * 检查id是否存在
     * @param uId
     * @return 是否存在
     */
    static bool checkId(int uId);

    /**
     * 保存消息
     * @param message 消息无id
     * @return 消息保存后的消息id，-1为失败
     */
    static int saveMessage(const Message & message);

    /**
     * 获取消息
     * 根据指定消息id获取消息
     * @param mId
     * @param message 向该引用对象中插入查询到的消息相关信息
     * @return 是否成功
     */
    static bool getMessage(int mId, Message & message);

    /**
     * 获取消息
     * 获取指定接受者，指定消息ID之后的全部消息
     * @param uToId
     * @param lastCalledMessage
     * @param messages 返回数据添加至vector中
     */
    static void getMessages(int uToId, int lastCalledMessage, std::vector<Message> & messages);

    /**
     *
     * @param uId
     * @param user
     */
    static void getUser(int uId,User &user);

    /**
     *
     * @param uId
     * @param users
     */
    static void getUsers(int uId,std::vector<User> &users);

    /**
     * 根据uId获取其所在的所有Group
     * Group不用管vector<User> users(不用set)(其实管不管都无所谓)
     * @param uId
     * @param groups
     */
    static void getGroups(int uId,std::vector<Group>& groups);

    static void addUIdToGroup(int uId,int gId);

    /**
     * 根据gId获取该群的所有contacts
     * @param gId
     * @param groupContacts
     */
    static void getGroupContacts(int gId, std::vector<User> &groupContacts);
};


#endif //SERVER_DATABASE_H
