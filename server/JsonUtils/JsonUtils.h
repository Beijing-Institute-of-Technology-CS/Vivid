//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_JSONUTILS_H
#define SERVER_JSONUTILS_H


class JsonUtils {
public:
    static bool parse_request_token(char * s_json, char *& uId, char *& uPwd);

    static bool parse_request_type(char *s_json, char *&requestType);

    static bool parse_request_register_json(char * s_json, char *&username, char *&password);

    static bool parse_request_login_json(char * s_json, char *&username, char *&password);

    static bool parse_request_getInfo_json(char * s_json);

    static bool parse_request_getMessages_json(char * s_json, char *& lastCalledMessage);

    static bool parse_request_sendMessages_json(char *s_json, char *&utoId, char *&content);

    static bool make_response_register_json();
};


#endif //SERVER_JSONUTILS_H


