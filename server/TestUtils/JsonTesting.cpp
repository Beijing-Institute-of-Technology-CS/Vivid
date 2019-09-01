//
// Created by YichengChen on 8/29/19.
//
#include <iostream>
#include "JsonTesting.h"
#include "../JsonUtils/JsonUtils.h"
#include "../../Constants.h"

#include <vector>

void JsonTesting::json_parse_request_testing() {
//
//    /**
//     * json
//     */
//
//    std::cout << "json parsing" << std::endl;
//
//    cJSON *json_root = NULL;
//    char * json_requestType = "sendMessages";
//    cJSON *json_token = NULL;
//    cJSON *json_content = NULL;
//
//    char *s_json = NULL;
//
//    json_root = cJSON_CreateObject();
//    json_token = cJSON_CreateObject();
//    json_content = cJSON_CreateObject();
//
//    cJSON_AddStringToObject(json_root,"requestType",json_requestType);
//
//    cJSON_AddNumberToObject(json_token,"uId",1);
//    cJSON_AddStringToObject(json_token,"uPwd","pwd");
//    cJSON_AddItemToObject(json_root,"requestToken",json_token);
//
//    cJSON_AddStringToObject(json_content,"username","cyc");
//    cJSON_AddStringToObject(json_content,"password","password");
//    cJSON_AddItemToObject(json_root,"requestContent",json_content);
//
////    cJSON_AddNumberToObject(json_content,"lastCalledMessage",99);
////    cJSON_AddItemToObject(json_root,"requestContent",json_content);
//
////    cJSON_AddNumberToObject(json_content,"utoId",999);
////    cJSON_AddStringToObject(json_content,"content","connnt");
////    cJSON_AddItemToObject(json_root,"requestContent",json_content);
//
//    s_json = cJSON_Print(json_root);
//
//    cJSON_Delete(json_root);
//
//    std::cout << s_json << std::endl;


/**
 * testing parsing
 */
//    char * s_json
//
//    char * requestType;
//    JsonUtils::parse_request_type(s_json, requestType);
//    std::cout << requestType << std::endl;
//
//    int uId;
//    char * uPwd;
//
//    JsonUtils::parse_request_token(s_json, &uId, uPwd);
//    std::cout << (uId) << " " << uPwd << std::endl;
//
//    char *username;
//    char *password;
//
//    JsonUtils::parse_request_login_json(s_json,username,password);
//    std::cout << username << " " << password << std::endl;

    //////////

//    int lastCalledMessage;
//    JsonUtils::parse_request_getMessages_json(s_json,&lastCalledMessage);
//    std::cout << lastCalledMessage << std::endl;

//    int utoId;
//    char * content;
//
//    JsonUtils::parse_request_sendMessages_json(s_json, &utoId, content);
//    std::cout << utoId <<" " << content << std::endl;
}

void JsonTesting::json_make_response_testing() {
    std::cout << JsonUtils::make_response_register_json(TRUE_CONTENT,1) << std::endl;

    std::cout << JsonUtils::make_response_login_json(FALSE_CONTENT,"cyc") << std::endl;

    std::vector <User> v_users;

    v_users.emplace_back(User(1, "cyc", "password", 3));
    v_users.emplace_back(User(2, "zhc", "passwordddd", 5));

//    std::cout << JsonUtils::make_response_getInfo_json(FALSE_CONTENT, 9, v_users) << std::endl;
//
//    std::vector<Message> v_messages;

//    v_messages.emplace_back(Message(1,"connnnt",3,"1.22312"));
//    v_messages.emplace_back(Message(2,"connererer",4,"9.092301"));
//
//    std:: cout << JsonUtils::make_response_getMessages_json(FALSE_CONTENT,v_messages) << std::endl;
//
//    std::cout << JsonUtils::make_response_sendMessages_json(FALSE_CONTENT,88) <<std::endl;
}
