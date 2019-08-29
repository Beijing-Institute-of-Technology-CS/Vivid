//
// Created by YichengChen on 8/29/19.
//

#include "JsonUtils.h"
#include "../Utils/cJSON.c"
#include "../Utils/cJSON.h"

//todo:free memory


//checked
bool JsonUtils::parse_request_token(char *s_json, char *&uId, char *&uPwd) {
    cJSON * json_root;
    cJSON * json_requestToken;

    json_root = cJSON_Parse(s_json);
    json_requestToken = cJSON_GetObjectItem(json_root,"requestToken");

    uId = cJSON_Print(cJSON_GetObjectItem(json_requestToken,"uId"));
    uPwd = cJSON_Print(cJSON_GetObjectItem(json_requestToken,"uPWd"));

    cJSON_Delete(json_root);
    return true;
}

//checked
bool JsonUtils::parse_request_type(char *s_json, char *&requestType) {
    cJSON * json_root;

    json_root = cJSON_Parse(s_json);
    requestType = cJSON_Print(cJSON_GetObjectItem(json_root,"requestType"));

    cJSON_Delete(json_root);
    return true;
}

//checked
bool JsonUtils::parse_request_register_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    username = cJSON_Print(cJSON_GetObjectItem(json_requestContent, "username"));
    password = cJSON_Print(cJSON_GetObjectItem(json_requestContent, "password"));

    cJSON_Delete(json_root);
    return true;
}
//checked
bool JsonUtils::parse_request_login_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    username = cJSON_Print(cJSON_GetObjectItem(json_requestContent, "username"));
    password = cJSON_Print(cJSON_GetObjectItem(json_requestContent, "password"));

    cJSON_Delete(json_root);
    return true;
}

bool JsonUtils::parse_request_getInfo_json(char *s_json) {

    return true;
}

//checked
bool JsonUtils::parse_request_getMessages_json(char *s_json, char *&lastCalledMessage) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    lastCalledMessage = cJSON_Print(cJSON_GetObjectItem(json_requestContent, "lastCalledMessage"));

    cJSON_Delete(json_root);
    return true;
}

//checked
bool JsonUtils::parse_request_sendMessages_json(char *s_json, char *&utoId, char *&content) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    utoId = cJSON_Print(cJSON_GetObjectItem(json_requestContent, "utoId"));
    content = cJSON_Print(cJSON_GetObjectItem(json_requestContent, "content"));

    cJSON_Delete(json_root);
    return true;
}


