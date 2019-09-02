//
// Created by 蓝雁 on 2019/9/1.
//

#include "JsonTesting.h"

void JsonTesting::test_make_request_json() {
    int uId = 1;
    char *uPwd = "psd";
    char *username = "jack";
    char *password = "password";
    char *requestType = "login";
    int lastCalledMessage = 2;
    int uToId = 1;
    int gToId = 2;
    char *mType = "userMessage";
    char *mContent = "contentttt";
    int gId = 2;

    char *s_json;
    s_json = JsonUtils::make_request_login_json(uId, password);
//    s_json = JsonUtils::make_request_reqister_json(username, password);
//    s_json = JsonUtils::make_request_getInfo_json(uId, uPwd);
//    s_json = JsonUtils::make_request_getMessages_json(lastCalledMessage, uId, uPwd);
//    s_json = JsonUtils::make_request_sendMessages_json(uToId, gToId, mType, mContent, uId, uPwd);
//    s_json = JsonUtils::make_request_adduIdToGroup_json(uId, gId, uPwd);
    std::cout << s_json << std::endl;
}

void JsonTesting::test_parse_response_json() {
    int uId = 1;
    char *uPwd = "psd";
    char *username = "jack";
    char *password = "password";
    char *requestType = "login";
    int lastCalledMessage = 2;
    int uToId = 1;
    int gToId = 2;
    char *mType = "userMessage";
    char *mContent = "contentttt";
    int gId = 2;
    int fIcon = 1;
    int contactsNumber = 10;
    int groupsNumber = 15;
    char *responseType = "register";
    char *result = "true";
    int mId = 1;
    int gFromId = 1;
    int uFromId = 3;
    int fId = 1;
    char *mTime = "12:00";
    char *publicKey = "null";
    Message message;

    std::vector<User> contactsArray;
    contactsArray.push_back(User(1,"Mike", "mmm", 1));
    contactsArray.push_back(User(2,"Jennie", "jjj", 2));
    std::vector<Group> groupsArray;
    groupsArray.push_back(Group(1));
    groupsArray.push_back(Group(2));
    int messagesNumber = 20;
    std::vector<Message> messagesArray;
    messagesArray.push_back(Message(1, "contentttt", 2, "18:00"));
    messagesArray.push_back(Message(2, "ttt", 3, "18:15"));

    cJSON *pJsonRoot = cJSON_CreateObject();
    cJSON_AddStringToObject(pJsonRoot, KEY_RESPONSE_TYPE, responseType);
    cJSON_AddStringToObject(pJsonRoot, KEY_RESULT, result);

    cJSON *json_responseContent = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_responseContent, KEY_UID, uId);
    cJSON_AddStringToObject(json_responseContent, KEY_PUBLIC_KEY, NULL_CONTENT);
    cJSON_AddStringToObject(json_responseContent, KEY_USERNAME, username);
    cJSON_AddNumberToObject(json_responseContent, KEY_FICON, fIcon);
    cJSON_AddNumberToObject(json_responseContent, KEY_MID, mId);
    cJSON_AddStringToObject(json_responseContent, KEY_MCONTENT, mContent);
    cJSON_AddStringToObject(json_responseContent, KEY_MTYPE, mType);
    cJSON_AddNumberToObject(json_responseContent, KEY_GFROMID, gFromId);
    cJSON_AddNumberToObject(json_responseContent, KEY_UFROMID, uFromId);
    cJSON_AddNumberToObject(json_responseContent, KEY_FID, fId);
    cJSON_AddStringToObject(json_responseContent, KEY_MTIME, mTime);



    cJSON *pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, KEY_CONTACTS_NUMBER, contactsNumber);
    cJSON *json_contactsArray = cJSON_CreateArray();
    for(int i=0;i<contactsArray.size();i++){
        cJSON *json_contactsItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_contactsItem, KEY_UID, contactsArray.at(i).getUId());
        cJSON_AddStringToObject(json_contactsItem, KEY_UNAME, contactsArray.at(i).getUName());
        cJSON_AddNumberToObject(json_contactsItem, KEY_FICON, contactsArray.at(i).getFIconFile());
        cJSON_AddItemToArray(json_contactsArray, json_contactsItem);
    }
    cJSON_AddItemToObject(pSubJson,KEY_CONTACTS_ARRAY,json_contactsArray);
    cJSON_AddItemToObject(json_responseContent, KEY_CONTACTS, pSubJson);


    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, KEY_GROUPS_NUMBER, groupsNumber);
    cJSON *json_groupsArray = cJSON_CreateArray();
    for(int i=0;i<groupsArray.size();i++){
        cJSON *json_groupsItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_groupsItem, KEY_GID, groupsArray.at(i).getGId());
        cJSON_AddItemToArray(json_groupsArray, json_groupsItem);
    }
    cJSON_AddItemToObject(pSubJson,KEY_GROUPS_ARRAY,json_groupsArray);
    cJSON_AddItemToObject(json_responseContent, KEY_GROUPS, pSubJson);


    pSubJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(pSubJson, KEY_MESSAGES_NUMBER, messagesNumber);
    cJSON *json_messagesArray = cJSON_CreateArray();
    for(int i=0;i<messagesArray.size();i++){
        cJSON *json_messagesItem = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_messagesItem, KEY_MID, messagesArray.at(i).getMId());
        cJSON_AddStringToObject(json_messagesItem, KEY_MCONTENT, messagesArray.at(i).getMContent());
//        cJSON_AddStringToObject(json_messagesItem, KEY_MTYPE, messagesArray.at(i).getMType());
        cJSON_AddNumberToObject(json_messagesItem, KEY_GFROMID, messagesArray.at(i).getGFromId());
        cJSON_AddNumberToObject(json_messagesItem, KEY_UFROMID, messagesArray.at(i).getUFromId());
//        cJSON_AddStringToObject(json_messagesItem, KEY_UFROMUSERNAME, messagesArray.at(i).getUFromusername());
        cJSON_AddNumberToObject(json_messagesItem, KEY_FID, messagesArray.at(i).getFId());
        cJSON_AddStringToObject(json_messagesItem, KEY_MTIME, messagesArray.at(i).getMTime());
        cJSON_AddItemToArray(json_messagesArray, json_messagesItem);
    }
    cJSON_AddItemToObject(pSubJson,KEY_MESSAGES_ARRAY,json_messagesArray);
    cJSON_AddItemToObject(json_responseContent, KEY_MESSAGES, pSubJson);


    cJSON_AddItemToObject(pJsonRoot, KEY_RESPONSE_CONTENT, json_responseContent);

    char *s_json = cJSON_Print(pJsonRoot);
//    std::cout << s_json << std::endl;

    JsonUtils::parse_response_type_json(s_json, responseType);
    std::cout << responseType << std::endl;
//
//    JsonUtils::parse_response_result_json(s_json, result);
//    std::cout << result << std::endl;
//
//    JsonUtils::parse_response_register_json(s_json, &uId, publicKey);
//    std::cout << uId << "  " << publicKey << std::endl;
//
//    JsonUtils::parse_response_login_json(s_json, &uId, publicKey);
//    std::cout << uId << "  " << publicKey << std::endl;

//    JsonUtils::parse_response_getInfo_json(s_json, &fIcon, &contactsNumber, &contactsArray, &groupsNumber, &groupsArray);
//    std::cout << fIcon << " " << contactsNumber << " ";
//    for(auto user: contactsArray){
//        std::cout << user.getUName()  << " " << user.getUId() << " " << user.getFIconFile() << " ";
//    }
//    std::cout << groupsNumber << " ";
//    for(auto group: groupsArray){
//        std::cout << group.getGId() << " ";
//    }
//    std::cout << std::endl;
//
//    JsonUtils::parse_response_getMessages_json(s_json, &messagesNumber, &messagesArray);
//    std::cout << messagesNumber << " ";
//    for(auto message: messagesArray){
//        std::cout << message.getMId() << " " << message.getMTime() << " " << message.getFId()  << " " << message.getUFromId() << " " << message.getGFromId()  << " " << message.getMContent() << " ";
//    }
//    std::cout << std::endl;

//    JsonUtils::parse_response_receiveMessages_json(s_json, message);
//    for(auto message: messagesArray){
//        std::cout << message.getMId() << " " << message.getMTime() << " " << message.getFId()  << " " << message.getUFromId() << " " << message.getGFromId()  << " " << message.getMContent() << " ";
//    }
//    std::cout << std::endl;

//    JsonUtils::parse_response_sendMessages_json(s_json, message);
//    for(auto message: messagesArray){
//        std::cout << message.getMId() << " " << message.getMTime() << " " << message.getFId() << " " << message.getUFromId() << " " << message.getGFromId()  << " " << message.getMContent() << " ";
//    }
//    std::cout << std::endl;
//
//    JsonUtils::parse_response_adduIdToGroup(s_json);

//    cJSON_Delete(pJsonRoot);
}
