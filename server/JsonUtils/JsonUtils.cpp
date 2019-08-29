//
// Created by YichengChen on 8/29/19.
//

#include <iostream>
#include "JsonUtils.h"
#include "../Utils/cJSON.h"

//todo free memory

//checked
//checked
bool JsonUtils::parse_request_token(char *s_json, int *uId, char *&uPwd) {
    cJSON * json_root;
    cJSON * json_requestToken;

    json_root = cJSON_Parse(s_json);
    json_requestToken = cJSON_GetObjectItem(json_root,"requestToken");

    (*uId) = cJSON_GetObjectItem(json_requestToken,"uId")->valueint;

    char * char_temp = cJSON_GetObjectItem(json_requestToken,"uPwd")->valuestring;
    uPwd = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(uPwd,char_temp);

    cJSON_Delete(json_root);
    return true;
}

//checked
//checked
bool JsonUtils::parse_request_type(char *s_json, char *&requestType) {
    cJSON * json_root;

    json_root = cJSON_Parse(s_json);

    char * char_temp = cJSON_GetObjectItem(json_root,"requestType")->valuestring;
    requestType = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(requestType,char_temp);

    cJSON_Delete(json_root);
    return true;
}

//checked
bool JsonUtils::parse_request_register_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    char * char_temp = cJSON_GetObjectItem(json_requestContent, "username")->valuestring;
    username = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(username,char_temp);

    char_temp = cJSON_GetObjectItem(json_requestContent, "password")->valuestring;
    password = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(password,char_temp);

    cJSON_Delete(json_root);
    return true;
}
//checked
//checked
bool JsonUtils::parse_request_login_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    char * char_temp = cJSON_GetObjectItem(json_requestContent, "username")->valuestring;
    username = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(username,char_temp);

    char_temp = cJSON_GetObjectItem(json_requestContent, "password")->valuestring;
    password = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(password,char_temp);

    cJSON_Delete(json_root);
    return true;
}

bool JsonUtils::parse_request_getInfo_json(char *s_json) {

    return true;
}

//checked
//checked
bool JsonUtils::parse_request_getMessages_json(char *s_json, int *lastCalledMessage) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    (*lastCalledMessage) = cJSON_GetObjectItem(json_requestContent, "lastCalledMessage")->valueint;

    cJSON_Delete(json_root);
    return true;
}

//checked
//checked
bool JsonUtils::parse_request_sendMessages_json(char *s_json, int *uToId, char *&content) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    (*uToId) = cJSON_GetObjectItem(json_requestContent, "uToId")->valueint;

    char * char_temp = cJSON_GetObjectItem(json_requestContent, "content")->valuestring;
    content = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(content,char_temp);

    cJSON_Delete(json_root);
    return true;
}

/**
 * response json
 */
//check
char *JsonUtils::make_response_register_json(char *result, int uId) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char *json_responseType = "register";
    char *json_result = result;
    cJSON *json_responseContent =  cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,"responseType",json_responseType);
    cJSON_AddStringToObject(json_root,"result",json_result);

    cJSON_AddNumberToObject(json_responseContent,"uId",uId);
    cJSON_AddStringToObject(json_responseContent,"publicKey","null");
    cJSON_AddItemToObject(json_root,"responseContent",json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

//check
char *JsonUtils::make_response_login_json(char *result, int uId) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char *json_responseType = "login";
    char *json_result = result;
    cJSON *json_responseContent =  cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,"responseType",json_responseType);
    cJSON_AddStringToObject(json_root,"result",json_result);

    cJSON_AddNumberToObject(json_responseContent,"uId",uId);
    cJSON_AddStringToObject(json_responseContent,"publicKey","null");
    cJSON_AddItemToObject(json_root,"responseContent",json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *
JsonUtils::make_response_getInfo_json(char *result, int fIcon, std::vector<User> contactsArray) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char *json_responseType = "getInfo";
    char *json_result = result;
    cJSON *json_responseContent = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_responseContent,"fIcon",9);

    cJSON *json_contacts = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_contacts,"contactsNumber",contactsArray.size());

    cJSON *json_contactsArray = cJSON_CreateArray();

    for(int i=0;i<contactsArray.size();i++){
        cJSON *json_contactsItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_contactsItem, "uId", contactsArray.at(i).getUId());
        cJSON_AddStringToObject(json_contactsItem, "uName", contactsArray.at(i).getUName());
        cJSON_AddNumberToObject(json_contactsItem, "fIcon", contactsArray.at(i).getFIconFile());

        cJSON_AddItemToArray(json_contactsArray, json_contactsItem);
    }

    cJSON_AddItemToObject(json_contacts,"contactsArray",json_contactsArray);

    cJSON_AddItemToObject(json_responseContent,"contacts",json_contacts);

    cJSON_AddStringToObject(json_root,"responseType",json_responseType);
    cJSON_AddStringToObject(json_root,"result",json_result);
    cJSON_AddItemToObject(json_root,"responseContent",json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *JsonUtils::make_response_getMessages_json(char *result, std::vector<Message> messagesArray) {
    char * s_json;

    cJSON *json_root = cJSON_CreateObject();
    char * json_responseType = "getMessages";
    char * json_result = result;
    cJSON * json_responseContent = cJSON_CreateObject();

    cJSON * json_messages = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_messages,"messagesNumber",messagesArray.size());

    cJSON * json_messagesArray = cJSON_CreateArray();

    for(int i=0;i<messagesArray.size();i++){
        cJSON *json_messagesItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_messagesItem,"mId",messagesArray.at(i).getMId());
        cJSON_AddStringToObject(json_messagesItem,"mContent",messagesArray.at(i).getMContent());
        cJSON_AddNumberToObject(json_messagesItem,"fId",messagesArray.at(i).getFId());
        cJSON_AddStringToObject(json_messagesItem,"mTime",messagesArray.at(i).getMTime());

        cJSON_AddItemToArray(json_messagesArray,json_messagesItem);
    }

    cJSON_AddItemToObject(json_messages,"messagesArray",json_messagesArray);

    cJSON_AddItemToObject(json_responseContent,"messages",json_messages);

    cJSON_AddStringToObject(json_root,"responseType",json_responseType);
    cJSON_AddStringToObject(json_root,"result",json_result);
    cJSON_AddItemToObject(json_root,"responseContent",json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *JsonUtils::make_response_sendMessages_json(char *result, int mId) {
    char * s_json;

    cJSON * json_root = cJSON_CreateObject();
    char * json_responseType = "sendMessages";
    char * json_result = result;
    cJSON * json_responseContent = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_responseContent,"mId",90);

    cJSON_AddStringToObject(json_root,"responseContent",json_responseType);
    cJSON_AddStringToObject(json_root,"result",json_result);
    cJSON_AddItemToObject(json_root,"responseContent",json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}




