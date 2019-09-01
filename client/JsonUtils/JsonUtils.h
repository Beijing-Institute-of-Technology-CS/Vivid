//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_JSONUTILS_H
#define SERVER_JSONUTILS_H


#include <vector>
#include "../Utils/cJSON.h"
#include "../Beans/User.h"
#include "../Beans/Message.h"



/**
 * read token from database!
 */

class JsonUtils {
public:
//    static char * make_request_token_json(int uId, char *uPwd);

    static char * make_request_reqister_json(char * username, char *password);

    static char * make_request_login_json(int uId, char *password);

    static char * make_request_getInfo_json(int uId, char *uPwd);

    /**
     * read lastCalledMessage from db
     */
    static char * make_request_getMessages_json(int lastCalledMessage, int uId, char *uPwd);

    static char * make_request_sendMessages_json(int uToId, char * content, int uId, char *uPwd);


    /**
     * parsing
     * @param s_json
     * @return
     */

    static bool parse_response_type_json(char *s_json, char *&responseType);

    static bool parse_response_result_json(char *s_json, char *&result);

    static bool parse_response_register_json(char * s_json, int *uId, char *&publicKey);

    static bool parse_response_login_json(char * s_json, int *uId, char *&publicKey);

    static bool parse_response_getInfo_json(char * s_json, int *fIcon, int *contactsNumber, std::vector<User> *contactsArray);

    static bool parse_response_getMessages_json(char * s_json, int *messagesNumber, std::vector<Message> *messagesArray);

    static bool parse_response_sendMessages_json(char * s_json, int *mId);

    static bool parse_response_receiveMessages_json(char *s_json, char *&mId, char *&mContent, int *uFromId);

};


#endif //SERVER_JSONUTILS_H
