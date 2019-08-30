//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H


#include <vector>
#include "../Beans/Message.h"

class Database {
public:
    static void mql_connect();

    /**
     * 注册用户
     * @param username
     * @param password
     * @return 返回用户id，为-1表示失败
     */
    static int doRegister(const char * username, const char * password);

    /**
     * 检查密码
     * @param id
     * @param password
     * @return 密码是否正确
     */
    static bool checkPassword(int id, const char * password);

    /**
     * 检查id是否存在
     * @param id
     * @return 是否存在
     */
    static bool checkId(int id);

    /**
     * 保存消息
     * @param message 消息无id
     * @return 消息保存后的消息id，-1为失败
     */
    static int saveMessage(const Message & message);

    /**
     * 获取消息
     * 根据指定消息id获取消息
     * @param msgId
     * @param message 向该引用对象中插入查询到的消息相关信息
     * @return 是否成功
     */
    static bool getMessage(int msgId, Message & message);

    /**
     * 获取消息
     * 获取指定接受者，指定消息ID之后的全部消息
     * @param receiverId
     * @param msgId
     * @param messages 返回数据添加至vector中
     */
    static void getMessage(int receiverId, int msgId, std::vector<Message> & messages);
};


#endif //SERVER_DATABASE_H
