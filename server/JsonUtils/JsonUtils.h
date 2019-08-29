//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_JSONUTILS_H
#define SERVER_JSONUTILS_H

#include <vector>
#include "../Beans/User.h"
#include "../Beans/Message.h"

class JsonUtils {
public:
    static bool parse_request_token(char * s_json, int * uId, char *& uPwd);

    static bool parse_request_type(char *s_json, char *&requestType);

    static bool parse_request_register_json(char * s_json, char *&username, char *&password);

    static bool parse_request_login_json(char * s_json, char *&username, char *&password);

    static bool parse_request_getInfo_json(char * s_json);

    static bool parse_request_getMessages_json(char * s_json, int * lastCalledMessage);

    static bool parse_request_sendMessages_json(char *s_json, int *uToId, char *&content);

    static char * make_response_register_json(char *result, int uId);

    static char * make_response_login_json(char *result, int uId);

    static char * make_response_getInfo_json(char *result, int fIcon, std::vector<User> contactsArray);

    static char * make_response_getMessages_json(char *result, std::vector<Message> messagesArray);

    static char * make_response_sendMessages_json(char *result, int mId);
};


#endif //SERVER_JSONUTILS_H


