//
// Created by YichengChen on 8/29/19.
//

#include "JsonUtils.h"
#include "../Utils/cJSON.c"
#include "../Utils/cJSON.h"



bool JsonUtils::parse_requset_token(char *s_json, char *& username, char *& password) {
    cJSON *json_root;
    json_root = cJSON_Parse(s_json);

    username = cJSON_Print(cJSON_GetObjectItem(json_root,"uId"));
    password = cJSON_Print(cJSON_GetObjectItem(json_root,"uPwd"));

    return true;
}

bool JsonUtils::parse_requset_register_json(char *s_json, char *&username, char *&password) {
    cJSON *json_root;
    json_root = cJSON_Parse(s_json);

    return true;
}
