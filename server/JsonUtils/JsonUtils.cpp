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
bool JsonUtils::parse_request_sendMessages_json(char *s_json, int *uToId, char *&content) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, "requestContent");

    (*uToId) = cJSON_GetObjectItem(json_requestContent, "uToId")->valueint;
    content = cJSON_GetObjectItem(json_requestContent, "content")->valuestring;

    cJSON_Delete(json_root);
    return true;
}

/**
 * response json
 */

char *JsonUtils::make_response_register_json(char *result, int uId) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char *json_responseType = "register";
    char *json_result = result;
    cJSON *json_responseContent =  cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,"responseType",json_responseType);
    cJSON_AddStringToObject(json_root,"responseType",json_result);

    cJSON_AddNumberToObject(json_responseContent,"uId",uId);
    cJSON_AddStringToObject(json_responseContent,"publicKey","null");
    cJSON_AddItemToObject(json_root,"responseContent",json_responseContent);

    s_json = cJSON_Print(json_root);

    return s_json;
}

char *JsonUtils::make_response_login_json(char *result, int uId) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char *json_responseType = "login";
    char *json_result = result;
    cJSON *json_responseContent =  cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,"responseType",json_responseType);
    cJSON_AddStringToObject(json_root,"responseType",json_result);

    cJSON_AddNumberToObject(json_responseContent,"uId",uId);
    cJSON_AddStringToObject(json_responseContent,"publicKey","null");
    cJSON_AddItemToObject(json_root,"responseContent",json_responseContent);

    s_json = cJSON_Print(json_root);

    return s_json;
}




