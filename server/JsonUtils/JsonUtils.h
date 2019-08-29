//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_JSONUTILS_H
#define SERVER_JSONUTILS_H


class JsonUtils {
public:
    static bool parse_requset_token(char * s_json, char *& username, char *& password);

    static bool parse_requset_register_json(char * s_json, char *&username,char *&password);

    static bool parse_requset_login_json(char * s_json);

    static bool parse_requset_getInfo_json(char * s_json, int *lastCalledMessage);

    static bool parse_requset_getMessages_json(char * s_json, int *utoId , char *content);

    static bool parse_requset_sendMessages_json(char *s_json);

    static bool make_response_register_json();
};


#endif //SERVER_JSONUTILS_H


