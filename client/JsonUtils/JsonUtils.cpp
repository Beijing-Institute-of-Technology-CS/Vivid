//
// Created by YichengChen on 8/29/19.
//

#include <stdio.h>
#include "JsonUtils.h"
#include "../../Constants.h"
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
char* JsonUtils::make_request_reqister_json(char *username, char *password) {
    cJSON *pJsonRoot = NULL;
    cJSON *pSubJson = NULL;
    char *p = NULL;

    pJsonRoot = cJSON_CreateObject();
    if (NULL == pJsonRoot) {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        return NULL;
    }

    cJSON_AddStringToObject(pJsonRoot, KEY_REQUEST_TYPE, TYPE_REGISTER);

    pSubJson = cJSON_CreateObject();
    cJSON_AddStringToObject(pSubJson, KEY_UID, NULL_CONTENT);
    cJSON_AddStringToObject(pSubJson, KEY_UPWD, NULL_CONTENT);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_TOKEN, pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddStringToObject(pSubJson, KEY_USERNAME, username);
    cJSON_AddStringToObject(pSubJson, KEY_PASSWORD, password);
    cJSON_AddItemToObject(pJsonRoot, KEY_RESPONSE_CONTENT, pSubJson);

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
char* JsonUtils::make_request_login_json(int uId, char *password) {
    cJSON *pJsonRoot = NULL;
    cJSON *pSubJson = NULL;
    char *p = NULL;

    pJsonRoot = cJSON_CreateObject();
    if (NULL == pJsonRoot) {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        return NULL;
    }

    cJSON_AddStringToObject(pJsonRoot, KEY_REQUEST_TYPE, TYPE_LOGIN);

    pSubJson = cJSON_CreateObject();
    cJSON_AddStringToObject(pSubJson, KEY_UID, NULL_CONTENT);
    cJSON_AddStringToObject(pSubJson, KEY_PASSWORD, NULL_CONTENT);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_TOKEN, pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddNumberToObject(pSubJson, KEY_UID,uId);
    cJSON_AddStringToObject(pSubJson, KEY_PASSWORD, password);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_CONTENT, pSubJson);

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

    cJSON_AddStringToObject(pJsonRoot, KEY_REQUEST_TYPE, TYPE_GET_INFO);

    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, KEY_UID, uId);
    cJSON_AddStringToObject(pSubJson, KEY_UPWD, uPwd);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_TOKEN, pSubJson);

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

    cJSON_AddStringToObject(pJsonRoot, KEY_REQUEST_TYPE, TYPE_GET_MESSAGES);

    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, KEY_UID, uId);
    cJSON_AddStringToObject(pSubJson, KEY_UPWD, uPwd);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_TOKEN, pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddNumberToObject(pSubJson, KEY_LAST_CALLED_MESSAGE, lastCalledMessage);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_CONTENT, pSubJson);

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

    cJSON_AddStringToObject(pJsonRoot, KEY_REQUEST_TYPE, TYPE_SEND_MESSAGES);

    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, KEY_UID, uId);
    cJSON_AddStringToObject(pSubJson, KEY_UPWD, uPwd);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_TOKEN, pSubJson);

    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        printf("%s line=%d NULL\n", __func__, __LINE__);
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddNumberToObject(pSubJson, KEY_UTOID, uToId);
    cJSON_AddStringToObject(pSubJson, KEY_CONTENT, content);
    cJSON_AddItemToObject(pJsonRoot, KEY_REQUEST_CONTENT, pSubJson);

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

    char *temp_responseType = cJSON_GetObjectItem(pJsonRoot, KEY_RESPONSE_TYPE)->valuestring;
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

    char *temp_result = cJSON_GetObjectItem(pJsonRoot,KEY_RESULT)->valuestring;
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

    pSubJson = cJSON_GetObjectItem(pJsonRoot, KEY_RESPONSE_CONTENT);
    *uId = cJSON_GetObjectItem(pSubJson, KEY_UID)->valueint;
    char *temp_publicKey = cJSON_GetObjectItem(pSubJson, KEY_PUBLIC_KEY)->valuestring;
    publicKey = (char *)malloc((strlen(temp_publicKey)+1)*sizeof(char));
    strcpy(publicKey, temp_publicKey);

    cJSON_Delete(pJsonRoot);
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

    pSubJson = cJSON_GetObjectItem(pJsonRoot, KEY_RESPONSE_CONTENT);
    *uId = cJSON_GetObjectItem(pSubJson, KEY_UID)->valueint;
    char *temp_publicKey = cJSON_GetObjectItem(pSubJson, KEY_PUBLIC_KEY)->valuestring;
    publicKey = (char *)malloc((strlen(temp_publicKey)+1)*sizeof(char));
    strcpy(publicKey, temp_publicKey);

    cJSON_Delete(pJsonRoot);
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

    cJSON *json_responseContent = cJSON_GetObjectItem(pJsonRoot,KEY_RESPONSE_CONTENT);
    *fIcon = cJSON_GetObjectItem(json_responseContent, KEY_FICON)->valueint;
    cJSON *json_contacts = cJSON_GetObjectItem(json_responseContent,KEY_CONTACTS);
    *contactsNumber = cJSON_GetObjectItem(json_contacts, KEY_CONTACTS_NUMBER)->valueint;
    cJSON *json_contactsArray = cJSON_GetObjectItem(json_contacts, KEY_CONTACTS_ARRAY)->child;
//    int contactsArraySize = cJSON_GetArraySize(json_contactsArray);
//    cJSON *pContactsArray = json_contactsArray->child;
//    for(int i=0; i<contactsArraySize; i++, pContactsArray = pContactsArray->next){
//        contactsArray[i].uId = cJSON_GetObjectItem(pContactsArray, "uId")->valueint;
//        contactsArray[i].uName = cJSON_GetObjectItem(pContactsArray, "uName")->valuestring;
//        contactsArray[i].fIcon = cJSON_GetObjectItem(pContactsArray, "fIcon")->valueint;
//    }

    while(json_contactsArray != NULL){
        User user;
        user.setUId(cJSON_GetObjectItem(json_contactsArray, KEY_UID)->valueint);
        char *temp_uName = cJSON_GetObjectItem(json_contactsArray, KEY_UNAME)->valuestring;
        char *uName = (char *)malloc((strlen(temp_uName)+1)*sizeof(char));
        strcpy(uName, temp_uName);
        user.setUName(uName);
        user.setFIconFile(cJSON_GetObjectItem(json_contactsArray,KEY_FICON)->valueint);
        contactsArray->push_back(user);
        json_contactsArray = json_contactsArray->next;
    }

    cJSON_Delete(pJsonRoot);
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

    cJSON *json_responseContent = cJSON_GetObjectItem(pJsonRoot, KEY_RESPONSE_CONTENT);
    cJSON *json_messages = cJSON_GetObjectItem(json_responseContent, KEY_MESSAGES);
    *messagesNumber = cJSON_GetObjectItem(json_messages, KEY_MESSAGES_NUMBER)->valueint;
    cJSON *json_messagesArray = cJSON_GetObjectItem(json_messages, KEY_MESSAGES_ARRAY)->child;
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
        message.setMId(cJSON_GetObjectItem(json_messagesArray, KEY_MID)->valueint);
        char *temp_mContent = cJSON_GetObjectItem(json_messagesArray, KEY_MCONTENT)->valuestring;
        char *mContent = (char *)malloc((strlen(temp_mContent)+1)*sizeof(char));
        strcpy(mContent, temp_mContent);
        message.setMContent(mContent);
        message.setFId(cJSON_GetObjectItem(json_messagesArray, KEY_FID)->valueint);
        char *temp_mTime = cJSON_GetObjectItem(json_messagesArray, KEY_MTIME)->valuestring;
        char *mTime = (char *)malloc((strlen(temp_mTime)+1)*sizeof(char));
        strcpy(mTime, temp_mTime);
        message.setMTime(mTime);
        messagesArray->push_back(message);
        json_messagesArray = json_messagesArray->next;
    }

    cJSON_Delete(pJsonRoot);
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

    pSubJson = cJSON_GetObjectItem(pJsonRoot, KEY_RESPONSE_CONTENT);
    *mId = cJSON_GetObjectItem(pSubJson, KEY_MID)->valueint;

    cJSON_Delete(pJsonRoot);
//    cJSON_Delete(pSubJson);
    return true;
}

bool JsonUtils::parse_response_receiveMessages_json(char *s_json, char *&mId, char *&mContent, int *uFromId) {
    cJSON *json_root = cJSON_Parse(s_json);
    cJSON *json_responseContent = cJSON_GetObjectItem(json_root,KEY_RESPONSE_CONTENT);

    *mId = cJSON_GetObjectItem(json_responseContent,KEY_MID)->valueint;

    char * char_temp = cJSON_GetObjectItem(json_responseContent,KEY_MCONTENT)->valuestring;
    mContent = (char *)malloc((strlen(char_temp)+1)*sizeof(char));
    strcpy(mContent,char_temp);

    *uFromId = cJSON_GetObjectItem(json_responseContent,KEY_UFROMID)->valueint;

    cJSON_Delete(json_root);
    return true;
}


