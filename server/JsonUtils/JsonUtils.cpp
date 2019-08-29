//
// Created by YichengChen on 8/29/19.
//

#include "JsonUtils.h"
#include "../Utils/cJSON.c"
#include "../Utils/cJSON.h"

//todo:free memory


//checked
bool JsonUtils::parse_request_token(char *s_json, int *uId, char *&uPwd) {
    cJSON * json_root;
    cJSON * json_requestToken;

    json_root = cJSON_Parse(s_json);
    json_requestToken = cJSON_GetObjectItem(json_root,"requestToken");

    (*uId) = cJSON_GetObjectItem(json_requestToken,"uId")->valueint;
    uPwd = cJSON_GetObjectItem(json_requestToken,"uPWd")->valuestring;

    cJSON_Delete(json_root);
    return true;
}

//checked
bool JsonUtils::parse_request_type(char *s_json, char *&requestType) {
    cJSON * json_root;

    json_root = cJSON_Parse(s_json);
    requestType = cJSON_GetObjectItem(json_root,"requestType")->valuestring;

    cJSON_Delete(json_root);
    return true;
}

//checked
bool JsonUtils::parse_request_register_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    username = cJSON_GetObjectItem(json_requestContent, "username")->valuestring;
    password = cJSON_GetObjectItem(json_requestContent, "password")->valuestring;

    cJSON_Delete(json_root);
    return true;
}
//checked
bool JsonUtils::parse_request_login_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    username = cJSON_GetObjectItem(json_requestContent, "username")->valuestring;
    password = cJSON_GetObjectItem(json_requestContent, "password")->valuestring;

    cJSON_Delete(json_root);
    return true;
}

bool JsonUtils::parse_request_getInfo_json(char *s_json) {

    return true;
}

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
bool JsonUtils::parse_request_sendMessages_json(char *s_json, int *utoId, char *&content) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    (*utoId) = cJSON_GetObjectItem(json_requestContent, "utoId")->valueint;
    content = cJSON_GetObjectItem(json_requestContent, "content")->valuestring;

    cJSON_Delete(json_root);
    return true;
}


