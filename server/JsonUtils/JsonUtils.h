//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_JSONUTILS_H
#define SERVER_JSONUTILS_H


class JsonUtils {
public:
    static void parse_register_json(char * s_json);
    static void parse_login_json(char * s_json);
    static void parse_getInfo_json(char * s_json);
    static void parse_getMessages_json(char * s_json);

    static void make_re
};


#endif //SERVER_JSONUTILS_H
