//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_JSONUTILS_H
#define SERVER_JSONUTILS_H


/**
 * read token from database!
 */

class JsonUtils {
public:
    static char * make_request_reqister_json(char * username, char password);

    static char * make_request_login_json(char * username, char password);

    static char * make_request_getInfo_json();

    /**
     * read lastCalledMessage from db
     */
    static char * make_request_getMessages_json();

    static char * make_request_sendMessages_json(int uToId, char * content);


    /**
     * parsing
     * @param s_json
     * @return
     */

    static char * parse_response_register_json(char * s_json);

    static char * parse_response_login_json(char * s_json);

    static char * parse_response_getInfo_json(char * s_json);

    static char * parse_response_getMessages_json(char * s_json);

    static char * parse_response_getMessages_json(char * s_json);


};


#endif //SERVER_JSONUTILS_H
