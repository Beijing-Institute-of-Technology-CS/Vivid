//
// Created by YichengChen on 8/29/19.
//

#include "JsonUtils.h"
//#include "../Utils/cJSON.h"
//#include "../Utils/cJSON.c"

/**
 * make request json
 */

// *
// * @param uId
// * @param uPwd
// * @return
// */
//char* JsonUtils::make_request_token_json(int uId, char *uPwd) {
//    cJSON *pJsonRoot = NULL;
//    char *p = NULL;
//
//    pJsonRoot = cJSON_CreateObject();
//    if (NULL == pJsonRoot) {
//        printf("%s line=%d NULL\n", __func__, __LINE__);
//        return NULL;
//    }
//
//    cJSON_AddNumberToObject(pJsonRoot, "uId", uId);
//    cJSON_AddStringToObject(pJsonRoot, "uPwd", uPwd);
//
//    p = cJSON_Print(pJsonRoot);
//    if(NULL == p)
//    {
//        printf("%s line=%d NULL\n", __func__, __LINE__);
//        cJSON_Delete(pJsonRoot);
//        return NULL;
//    }
//    cJSON_Delete(pJsonRoot);
//    return p;
//}

/**
 *
 * @param username
 * @param password
 * @return
 */
char* JsonUtils::make_request_reqister_json(char *username, char *password, char *uId, char *uPwd) {
    cJSON *pJsonRoot = NULL;
    cJSON *pSubJson = NULL;
    char *p = NULL;

    pJsonRoot = cJSON_CreateObject();
    if (NULL == pJsonRoot) {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        return NULL;
    }

    cJSON_AddStringToObject(pJsonRoot, "requestType", "register");

    pSubJson = cJSON_CreateObject();
    cJSON_AddStringToObject(pSubJson, "uId", "null");
    cJSON_AddStringToObject(pSubJson, "uPwd", "null");
    cJSON_AddItemToObject(pJsonRoot, "requestToken", pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddStringToObject(pSubJson, "username", username);
    cJSON_AddStringToObject(pSubJson, "password", password);
    cJSON_AddItemToObject(pJsonRoot, "requestContent", pSubJson);

    p = cJSON_Print(pJsonRoot);
    if(NULL == p)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return p;
}

/**
 *
 * @param username
 * @param password
 * @return
 */
char* JsonUtils::make_request_login_json(char *username, char *password, char *uId, char*uPwd) {
    cJSON *pJsonRoot = NULL;
    cJSON *pSubJson = NULL;
    char *p = NULL;

    pJsonRoot = cJSON_CreateObject();
    if (NULL == pJsonRoot) {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        return NULL;
    }

    cJSON_AddStringToObject(pJsonRoot, "requestType", "login");

    pSubJson = cJSON_CreateObject();
    cJSON_AddStringToObject(pSubJson, "uId", "null");
    cJSON_AddStringToObject(pSubJson, "uPwd", "null");
    cJSON_AddItemToObject(pJsonRoot, "requestToken", pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddStringToObject(pSubJson, "username", username);
    cJSON_AddStringToObject(pSubJson, "password", password);
    cJSON_AddItemToObject(pJsonRoot, "requestContent", pSubJson);

    p = cJSON_Print(pJsonRoot);
    if(NULL == p)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return p;
}

/**
 *
 * @return
 */
char* JsonUtils::make_request_getInfo_json(int uId, char *uPwd) {
    cJSON *pJsonRoot = NULL;
    cJSON *pSubJson = NULL;
    char *p = NULL;

    pJsonRoot = cJSON_CreateObject();
    if (NULL == pJsonRoot) {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        return NULL;
    }

    cJSON_AddStringToObject(pJsonRoot, "requestType", "getInfo");

    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, "uId", uId);
    cJSON_AddStringToObject(pSubJson, "uPwd", uPwd);
    cJSON_AddItemToObject(pJsonRoot, "requestToken", pSubJson);

    p = cJSON_Print(pJsonRoot);
    if(NULL == p)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return p;
}

/**
 *
 * @param lastCalledMessage
 * @return
 */
char* JsonUtils::make_request_getMessages_json(int lastCalledMessage, int uId, char *uPwd) {
    cJSON *pJsonRoot = NULL;
    cJSON *pSubJson = NULL;
    char *p = NULL;

    pJsonRoot = cJSON_CreateObject();
    if (NULL == pJsonRoot) {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        return NULL;
    }

    cJSON_AddStringToObject(pJsonRoot, "requestType", "getMessages");

    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, "uId", uId);
    cJSON_AddStringToObject(pSubJson, "uPwd", uPwd);
    cJSON_AddItemToObject(pJsonRoot, "requestToken", pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddNumberToObject(pSubJson, "lastCalledMessage", lastCalledMessage);
    cJSON_AddItemToObject(pJsonRoot, "requestContent", pSubJson);

    p = cJSON_Print(pJsonRoot);
    if(NULL == p)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return p;
}

/**
 *
 * @param uToId
 * @param content
 * @return
 */
char* JsonUtils::make_request_sendMessages_json(int uToId, char *content, int uId, char *uPwd) {
    cJSON *pJsonRoot = NULL;
    cJSON *pSubJson = NULL;
    char *p = NULL;

    pJsonRoot = cJSON_CreateObject();
    if (NULL == pJsonRoot) {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        return NULL;
    }

    cJSON_AddStringToObject(pJsonRoot, "requestType", "sendMessages");

    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, "uId", uId);
    cJSON_AddStringToObject(pSubJson, "uPwd", uPwd);
    cJSON_AddItemToObject(pJsonRoot, "requestToken", pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddNumberToObject(pSubJson, "utoId", uToId);
    cJSON_AddStringToObject(pSubJson, "content", content);
    cJSON_AddItemToObject(pJsonRoot, "requestContent", pSubJson);

    p = cJSON_Print(pJsonRoot);
    if(NULL == p)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
//    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return p;
}

/**
 * parse json
 */

/**
 *
 * @param s_json
 * @param responseType
 * @return
 */
bool JsonUtils::parse_response_type_json(char *s_json, char *&responseType) {
    cJSON *pJsonRoot = NULL;
    if(NULL == s_json){
        return false;
    }

    pJsonRoot = cJSON_Parse(s_json);
    if(NULL == pJsonRoot){
        return false;
    }

    char *temp_responseType = cJSON_GetObjectItem(pJsonRoot, "responseType")->valuestring;
    responseType = (char *)malloc((strlen(temp_responseType)+1)*sizeof(char));
    strcpy(responseType, temp_responseType);
    cJSON_Delete(pJsonRoot);
    return true;
}

/**
 *
 * @param s_json
 * @param result
 * @return
 */
bool JsonUtils::parse_response_result_json(char *s_json, char *&result) {
    cJSON *pJsonRoot = NULL;
    if(NULL == s_json){
        return false;
    }

    pJsonRoot = cJSON_Parse(s_json);
    if(NULL == pJsonRoot){
        return false;
    }

    char *temp_result = cJSON_GetObjectItem(pJsonRoot, "result")->valuestring;
    result = (char *)malloc((strlen(temp_result)+1)*sizeof(char));
    strcpy(result, temp_result);
    cJSON_Delete(pJsonRoot);
    return true;
}

/**
 *
 * @param s_json
 * @param uId
 * @param publicKey
 * @return
 */
bool JsonUtils::parse_response_register_json(char *s_json, int *uId, char *&publicKey) {
    cJSON *pJsonRoot = NULL;
    cJSON * pSubJson = NULL;
    if(NULL == s_json){
        return false;
    }

    pJsonRoot = cJSON_Parse(s_json);
    if(NULL == pJsonRoot){
        return false;
    }

    pSubJson = cJSON_GetObjectItem(pJsonRoot, "responseContent");
    *uId = cJSON_GetObjectItem(pSubJson, "uId")->valueint;
    char *temp_publicKey = cJSON_GetObjectItem(pSubJson, "publicKey")->valuestring;
    publicKey = (char *)malloc((strlen(temp_publicKey)+1)*sizeof(char));
    strcpy(publicKey, temp_publicKey);

//    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return true;
}

/**
 *
 * @param s_json
 * @return
 */
bool JsonUtils::parse_response_login_json(char *s_json, int *uId, char *&publicKey) {
    cJSON *pJsonRoot = NULL;
    cJSON * pSubJson = NULL;
    if(NULL == s_json){
        return false;
    }

    pJsonRoot = cJSON_Parse(s_json);
    if(NULL == pJsonRoot){
        return false;
    }

    pSubJson = cJSON_GetObjectItem(pJsonRoot, "responseContent");
    *uId = cJSON_GetObjectItem(pSubJson, "uId")->valueint;
    char *temp_publicKey = cJSON_GetObjectItem(pSubJson, "publicKey")->valuestring;
    publicKey = (char *)malloc((strlen(temp_publicKey)+1)*sizeof(char));
    strcpy(publicKey, temp_publicKey);

//    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return true;
}

/**
 *
 * @param s_json
 * @param fIcon
 * @param contactsNumber
 * @param contactsArray
 * @return
 */
bool JsonUtils::parse_response_getInfo_json(char *s_json, int *fIcon, int *contactsNumber, std::vector<User> *contactsArray) {
    cJSON *pJsonRoot = NULL;
    if(NULL == s_json){
        return false;
    }

    pJsonRoot = cJSON_Parse(s_json);
    if(NULL == pJsonRoot){
        return false;
    }

    cJSON *json_responseContent = cJSON_GetObjectItem(pJsonRoot, "responseContent");
    *fIcon = cJSON_GetObjectItem(json_responseContent, "fIcon")->valueint;
    cJSON *json_contacts = cJSON_GetObjectItem(json_responseContent, "contacts");
    *contactsNumber = cJSON_GetObjectItem(json_contacts, "contactsNumber")->valueint;
    cJSON *json_contactsArray = cJSON_GetObjectItem(json_contacts, "contactsArray")->child;
//    int contactsArraySize = cJSON_GetArraySize(json_contactsArray);
//    cJSON *pContactsArray = json_contactsArray->child;
//    for(int i=0; i<contactsArraySize; i++, pContactsArray = pContactsArray->next){
//        contactsArray[i].uId = cJSON_GetObjectItem(pContactsArray, "uId")->valueint;
//        contactsArray[i].uName = cJSON_GetObjectItem(pContactsArray, "uName")->valuestring;
//        contactsArray[i].fIcon = cJSON_GetObjectItem(pContactsArray, "fIcon")->valueint;
//    }

    while(json_contactsArray != NULL){
        User user;
        user.setUId(cJSON_GetObjectItem(json_contactsArray, "uId")->valueint);
        user.setUName(cJSON_GetObjectItem(json_contactsArray, "uName")->valuestring);
        user.setFIconFile(cJSON_GetObjectItem(json_contactsArray, "fIcon")->valueint);
        contactsArray->push_back(user);
        json_contactsArray = json_contactsArray->next;
    }

//    cJSON_Delete(pJsonRoot);
    return true;
}

/**
 *
 * @param s_json
 * @param messagesNumber
 * @param messagesArray
 * @return
 */
bool JsonUtils::parse_response_getMessages_json(char *s_json, int *messagesNumber, std::vector<Message> *messagesArray) {
    cJSON *pJsonRoot = NULL;
    if(NULL == s_json){
        return false;
    }

    pJsonRoot = cJSON_Parse(s_json);
    if(NULL == pJsonRoot){
        return false;
    }

    cJSON *json_responseContent = cJSON_GetObjectItem(pJsonRoot, "responseContent");
    cJSON *json_messages = cJSON_GetObjectItem(json_responseContent, "messages");
    *messagesNumber = cJSON_GetObjectItem(json_messages, "messagesNumber")->valueint;
    cJSON *json_messagesArray = cJSON_GetObjectItem(json_messages, "messagesArray")->child;
//    int messagesArraySize = cJSON_GetArraySize(json_messagesArray);
//    cJSON *pMessagesArray = json_messagesArray->child;
//    for(int i=0; i<messagesArraySize; i++, pMessagesArray = pMessagesArray->next){
//        messagesArray[i].mId = cJSON_GetObjectItem(pMessagesArray, "mId")->valueint;
//        messagesArray[i].mContent = cJSON_GetObjectItem(pMessagesArray, "mContent")->valuestring;
//        messagesArray[i].fId = cJSON_GetObjectItem(pMessagesArray, "fId")->valueint;
//        messagesArray[i].mTime = cJSON_GetObjectItem(pMessagesArray, "mTime")->valuestring;
//    }

    while(json_messagesArray !=NULL){
        Message message;
        message.setMId(cJSON_GetObjectItem(json_messagesArray, "mId")->valueint);
        message.setMContent(cJSON_GetObjectItem(json_messagesArray, "mContent")->valuestring);
        message.setFId(cJSON_GetObjectItem(json_messagesArray, "fId")->valueint);
        message.setMTime(cJSON_GetObjectItem(json_messagesArray, "mTime")->valuestring);
        messagesArray->push_back(message);
        json_messagesArray = json_messagesArray->next;
    }

//    cJSON_Delete(pJsonRoot);
    return true;
}

/**
 *
 * @param s_json
 * @param mId
 * @return
 */
bool JsonUtils::parse_response_sendMessages_json(char *s_json, int *mId) {
    cJSON *pJsonRoot = NULL;
    cJSON * pSubJson = NULL;
    if(NULL == s_json){
        return false;
    }

    pJsonRoot = cJSON_Parse(s_json);
    if(NULL == pJsonRoot){
        return false;
    }

    pSubJson = cJSON_GetObjectItem(pJsonRoot, "responseContent");
    *mId = cJSON_GetObjectItem(pSubJson, "mId")->valueint;

    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return true;
}