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
    static char * make_reqister_json(char * username, char password);

    static char * make_login_json(char * username, char password);

    static char * make_getInfo_json();

    /**
     * read lastCalledMessage from db
     */
    static char * make_getMessages_json();

    static char * make_sendMessages_json(int uToId, char * content);
};


#endif //SERVER_JSONUTILS_H
