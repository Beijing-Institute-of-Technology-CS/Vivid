//
// Created by YichengChen on 8/29/19.
//

#include "JsonUtils.h"
#include "../Utils/cJSON.c"
#include "../Utils/cJSON.h"

//todo:free memory

bool JsonUtils::parse_requset_token(char *s_json, char *& uId, char *&uPwd) {
    cJSON * json_root;
    cJSON * json_requestToken;

    json_root = cJSON_Parse(s_json);
    json_requestToken = cJSON_GetObjectItem(json_root,"requestToken");

    uId = cJSON_Print(cJSON_GetObjectItem(json_requestToken,"uId"));
    uPwd = cJSON_Print(cJSON_GetObjectItem(json_requestToken,"uPWd"));

    return true;
}

bool JsonUtils::parse_requset_register_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    json_root = cJSON_Parse(s_json);

    return true;
}
