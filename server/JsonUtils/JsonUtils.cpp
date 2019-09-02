//
// Created by YichengChen on 8/29/19.
//

#include <cstdlib>
#include <cstring>

#include "JsonUtils.h"
#include "../Utils/cJSON.h"
#include "../../Constants.h"

//todo free memory

//checked
//checked
bool JsonUtils::parse_request_token(char *s_json, int *uId, char *&uPwd) {
    cJSON * json_root;
    cJSON * json_requestToken;

    json_root = cJSON_Parse(s_json);
    json_requestToken = cJSON_GetObjectItem(json_root,KEY_REQUEST_TOKEN);

    (*uId) = cJSON_GetObjectItem(json_requestToken,KEY_UID)->valueint;

    char * char_temp = cJSON_GetObjectItem(json_requestToken,KEY_UPWD)->valuestring;
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

    char * char_temp = cJSON_GetObjectItem(json_root,KEY_REQUEST_TYPE)->valuestring;
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
    json_requestContent = cJSON_GetObjectItem(json_root, KEY_REQUEST_CONTENT);

    char * char_temp = cJSON_GetObjectItem(json_requestContent, KEY_USERNAME)->valuestring;
    username = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(username,char_temp);

    char_temp = cJSON_GetObjectItem(json_requestContent, KEY_PASSWORD)->valuestring;
    password = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(password,char_temp);

    cJSON_Delete(json_root);
    return true;
}
//checked
//checked
bool JsonUtils::parse_request_login_json(char *s_json, int *uId, char *&password) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, KEY_REQUEST_CONTENT);

    (*uId) = cJSON_GetObjectItem(json_requestContent, KEY_UID)->valueint;

    char * char_temp = cJSON_GetObjectItem(json_requestContent, KEY_PASSWORD)->valuestring;
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
    json_requestContent = cJSON_GetObjectItem(json_root, KEY_REQUEST_CONTENT);

    (*lastCalledMessage) = cJSON_GetObjectItem(json_requestContent, KEY_LAST_CALLED_MESSAGE)->valueint;

    cJSON_Delete(json_root);
    return true;
}

//checked
//checked
bool JsonUtils::parse_request_sendMessages_json(char *s_json, int *uToId, int *gToId, char *& mType, char *&mContent) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, KEY_REQUEST_CONTENT);

    (*uToId) = cJSON_GetObjectItem(json_requestContent, KEY_UTOID)->valueint;

    (*gToId) = cJSON_GetObjectItem(json_requestContent, KEY_GTOID)->valueint;

    char * char_temp = cJSON_GetObjectItem(json_requestContent, KEY_MCONTENT)->valuestring;
    mContent = (char *)malloc((strlen(char_temp) + 1) * sizeof(char));
    strcpy(mContent, char_temp);

    char_temp = cJSON_GetObjectItem(json_requestContent,KEY_MTYPE)->valuestring;
    mType = (char *)malloc((strlen(char_temp) + 1) * sizeof(char));
    strcpy(mType, char_temp);

    cJSON_Delete(json_root);
    return true;
}

bool JsonUtils::parse_request_adduIdToGroup_json(char *s_json, int *uId, int *gId) {
    cJSON *json_root;
    cJSON *json_requestContent;

    json_root = cJSON_Parse(s_json);
    json_requestContent = cJSON_GetObjectItem(json_root, KEY_REQUEST_CONTENT);

    *uId = cJSON_GetObjectItem(json_requestContent,KEY_UID)->valueint;
    *gId = cJSON_GetObjectItem(json_requestContent,KEY_GID)->valueint;

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
    char *json_responseType = TYPE_REGISTER;
    char *json_result = result;
    cJSON *json_responseContent =  cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,KEY_RESPONSE_TYPE,json_responseType);
    cJSON_AddStringToObject(json_root,KEY_RESULT,json_result);

    cJSON_AddNumberToObject(json_responseContent,KEY_UID,uId);
    cJSON_AddStringToObject(json_responseContent,KEY_PUBLIC_KEY,NULL_CONTENT);
    cJSON_AddItemToObject(json_root,KEY_RESPONSE_CONTENT,json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

//check
char *JsonUtils::make_response_login_json(char *result, char *username) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char *json_responseType = TYPE_LOGIN;
    char *json_result = result;
    cJSON *json_responseContent =  cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,KEY_RESPONSE_TYPE,json_responseType);
    cJSON_AddStringToObject(json_root,KEY_RESULT,json_result);

    cJSON_AddStringToObject(json_responseContent,KEY_USERNAME,username);
    cJSON_AddStringToObject(json_responseContent,KEY_PUBLIC_KEY,NULL_CONTENT);
    cJSON_AddItemToObject(json_root,KEY_RESPONSE_CONTENT,json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *
JsonUtils::make_response_getInfo_json(char *result, int fIcon, std::vector<User> & contactsArray, std::vector<Group> &groupsArray) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char *json_responseType = TYPE_GET_INFO;
    char *json_result = result;
    cJSON *json_responseContent = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_responseContent,KEY_FICON,fIcon);

    /**
     *
     */

    cJSON *json_contacts = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_contacts,KEY_CONTACTS_NUMBER,contactsArray.size());

    cJSON *json_contactsArray = cJSON_CreateArray();

    for(int i=0;i<contactsArray.size();i++){
        cJSON *json_contactsItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_contactsItem, KEY_UID, contactsArray.at(i).getUId());
        cJSON_AddStringToObject(json_contactsItem, KEY_UNAME, contactsArray.at(i).getUName());
        cJSON_AddNumberToObject(json_contactsItem, KEY_FICON, contactsArray.at(i).getFIconFile());

        cJSON_AddItemToArray(json_contactsArray, json_contactsItem);
    }

    cJSON_AddItemToObject(json_contacts,KEY_CONTACTS_ARRAY,json_contactsArray);
    cJSON_AddItemToObject(json_responseContent,KEY_CONTACTS,json_contacts);

    /**
     *
     */

    cJSON * json_groups = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_groups, KEY_GROUPS_NUMBER, groupsArray.size());

    cJSON * json_groupsArray = cJSON_CreateArray();

    for(int i=0;i<groupsArray.size();i++){
        cJSON *json_groupsItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_groupsItem,KEY_GID,groupsArray.at(i).getGId());

        cJSON_AddItemToArray(json_groupsArray,json_groupsItem);
    }

    cJSON_AddItemToObject(json_groups,KEY_GROUPS_ARRAY,json_groupsArray);
    cJSON_AddItemToObject(json_responseContent,KEY_GROUPS,json_groups);

    /**
     *
     */

    cJSON_AddStringToObject(json_root,KEY_RESPONSE_TYPE,json_responseType);
    cJSON_AddStringToObject(json_root,KEY_RESULT,json_result);

    cJSON_AddItemToObject(json_root,KEY_RESPONSE_CONTENT,json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *JsonUtils::make_response_getMessages_json(char *result, std::vector<Message> & messagesArray) {
    char * s_json;

    cJSON *json_root = cJSON_CreateObject();
    char * json_responseType = TYPE_GET_MESSAGES;
    char * json_result = result;
    cJSON * json_responseContent = cJSON_CreateObject();

    cJSON * json_messages = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_messages,KEY_MESSAGES_NUMBER,messagesArray.size());

    cJSON * json_messagesArray = cJSON_CreateArray();

    for(int i=0;i<messagesArray.size();i++){
        cJSON *json_messagesItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_messagesItem,KEY_MID,messagesArray.at(i).getMId());
        cJSON_AddStringToObject(json_messagesItem,KEY_MCONTENT,messagesArray.at(i).getMContent());

        if(messagesArray.at(i).isGroupMessage()){
            cJSON_AddStringToObject(json_messagesItem,KEY_MTYPE,TYPE_GROUP_MESSAGE);
        }else{
            cJSON_AddStringToObject(json_messagesItem,KEY_MTYPE,TYPE_USER_MESSAGE);
        }

        cJSON_AddNumberToObject(json_messagesItem,KEY_GFROMID,messagesArray.at(i).getGId());
        cJSON_AddNumberToObject(json_messagesItem,KEY_UFROMID,messagesArray.at(i).getUFromId());
        cJSON_AddStringToObject(json_messagesItem,KEY_UFROMUSERNAME,messagesArray.at(i).uFromUsername);
        cJSON_AddNumberToObject(json_messagesItem,KEY_FID,messagesArray.at(i).getFId());
        cJSON_AddStringToObject(json_messagesItem,KEY_MTIME,messagesArray.at(i).getMTime());

        cJSON_AddItemToArray(json_messagesArray,json_messagesItem);
    }

    cJSON_AddItemToObject(json_messages,KEY_MESSAGES_ARRAY,json_messagesArray);

    cJSON_AddItemToObject(json_responseContent,KEY_MESSAGES,json_messages);

    cJSON_AddStringToObject(json_root,KEY_RESPONSE_TYPE,json_responseType);
    cJSON_AddStringToObject(json_root,KEY_RESULT,json_result);
    cJSON_AddItemToObject(json_root,KEY_RESPONSE_CONTENT,json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *JsonUtils::make_response_sendMessages_json(char *result, Message & message) {
    char * s_json;

    cJSON * json_root = cJSON_CreateObject();
    char * json_responseType =TYPE_SEND_MESSAGES;
    char * json_result = result;
    cJSON * json_responseContent = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_responseContent,KEY_MID,message.getMId());
    cJSON_AddStringToObject(json_responseContent,KEY_MCONTENT,message.getMContent());
    if(message.isGroupMessage()){
        cJSON_AddStringToObject(json_responseContent,KEY_MTYPE,TYPE_GROUP_MESSAGE);
    }else{
        cJSON_AddStringToObject(json_responseContent,KEY_MTYPE,TYPE_USER_MESSAGE);
    }
    cJSON_AddNumberToObject(json_responseContent,KEY_GFROMID,message.getGId());
    cJSON_AddNumberToObject(json_responseContent,KEY_UFROMID,message.getUFromId());

    cJSON_AddStringToObject(json_root,KEY_RESPONSE_TYPE,json_responseType);
    cJSON_AddStringToObject(json_root,KEY_RESULT,json_result);
    cJSON_AddItemToObject(json_root,KEY_RESPONSE_CONTENT,json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *JsonUtils::make_response_receiveMessages_json(char *result, Message & message) {
    char *s_json;

    cJSON * json_root = cJSON_CreateObject();
    char * json_responseType = TYPE_RECEIVE_MESSAGES;
    char * json_result = result;
    cJSON * json_responseContent = cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,KEY_RESPONSE_TYPE,json_responseType);
    cJSON_AddStringToObject(json_root,KEY_RESULT,json_result);

    cJSON_AddNumberToObject(json_responseContent,KEY_MID,message.getMId());
    cJSON_AddStringToObject(json_responseContent,KEY_MCONTENT,message.getMContent());
    if(message.isGroupMessage()){
        cJSON_AddStringToObject(json_responseContent,KEY_MTYPE,TYPE_GROUP_MESSAGE);
    }else{
        cJSON_AddStringToObject(json_responseContent,KEY_MTYPE,TYPE_USER_MESSAGE);
    }
    cJSON_AddNumberToObject(json_responseContent,KEY_GFROMID,message.getGId());
    cJSON_AddNumberToObject(json_responseContent,KEY_UFROMID,message.getUFromId());

    cJSON_AddNumberToObject(json_responseContent,KEY_FID,message.getFId());
    cJSON_AddStringToObject(json_responseContent,KEY_MTIME,message.getMTime());

    cJSON_AddItemToObject(json_root,KEY_RESPONSE_CONTENT,json_responseContent);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    return s_json;
}

char *JsonUtils::make_response_adduIdToGroup_json(char *result) {
    char *s_json;

    cJSON *json_root = cJSON_CreateObject();
    char * json_responseType = TYPE_ADD_TO_GROUP;
    char * json_result = result;
    cJSON *json_responseContent = cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,KEY_RESPONSE_TYPE,TYPE_ADD_TO_GROUP);
    cJSON_AddStringToObject(json_root,KEY_RESULT,json_result);
    cJSON_AddItemToObject(json_root,KEY_RESPONSE_CONTENT,json_responseContent);

    s_json = cJSON_Print(json_root);


    cJSON_Delete(json_root);

    return s_json;
}




