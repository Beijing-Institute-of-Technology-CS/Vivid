//
// Created by William Zhang on 2019-09-01.
//

#include <iostream>
#include "NetworkController.h"
#include "../../Network/NetworkUtils.h"
#include "../../../Constants.h"
#include "../../JsonUtils/JsonUtils.h"

NetworkCallback * NetworkController::callback = nullptr;

void NetworkController::setCallback(NetworkCallback *callback) {
    NetworkController::callback = callback;
}

void NetworkController::startServer() {
    NetworkUtils::start_client(BITCS);
}

void NetworkController::netRegisterSuccess(char *json) {
    int id;
    char * publicKey;
    JsonUtils::parse_response_register_json(json, &id, publicKey);
    free(publicKey);
    callback->netRegisterSuccess(id);
}

void NetworkController::netRegisterFailed() {
    callback->netRegisterFailed();
}

void NetworkController::netLoginSuccess(char *json) {
    char * username;
    char * publicKey;
    JsonUtils::parse_response_login_json(json, username, publicKey);
    free(publicKey);
    callback->netLoginSuccess(username);
}

void NetworkController::netLoginFailed() {
    callback->netLoginFailed();
}

void NetworkController::netGetInfoSuccess(char *json) {
    std::vector<User> contacts;
    std::vector<Group> groups;
    int fileIcon;
    int contactsNum;
    int groupNum;
    JsonUtils::parse_response_getInfo_json(json, &fileIcon,&contactsNum, &contacts, &groupNum, &groups);
    callback->netGetInfoSuccess(contacts, groups);
}

void NetworkController::netGetInfoFailed() {
    callback->netGetInfoFailed();
}

void NetworkController::netGetMessageSuccess(char *json) {
    int msgNum;
    std::vector<Message> messages;
    JsonUtils::parse_response_getMessages_json(json, &msgNum, &messages);
    callback->netGetMessageSuccess(messages);
}

void NetworkController::netGetMessageFailed() {
    callback->netGetMessageFailed();
}

void NetworkController::netSendMessageSuccess(char *json) {
    Message message;
    JsonUtils::parse_response_sendMessages_json(json, message);
    callback->netSendMessageSuccess(message);
}

void NetworkController::netSendMessageFailed() {
    callback->netSendMessageFailed();
}

void NetworkController::netReceiveMessage(char *json) {
    Message message;
    JsonUtils::parse_response_receiveMessages_json(json, message);
    callback->netReceiveMessage(message);
}

void NetworkController::netRegister(char *username, char *password) {
    char * json;
    json = JsonUtils::make_request_reqister_json(username, password);
    NetworkUtils::send_json_to_server(json);
}

void NetworkController::netLogin(int uId, char *password) {
    char * json;
    json = JsonUtils::make_request_login_json(uId, password);
    NetworkUtils::send_json_to_server(json);
}

void NetworkController::netGetInfo(int uId, char *password) {
    char * json;
    json = JsonUtils::make_request_getInfo_json(uId, password);
    NetworkUtils::send_json_to_server(json);
}

void NetworkController::netGetMessages(int uId, char *password, int lastCalledMsg) {
    char * json;
    json = JsonUtils::make_request_getMessages_json(lastCalledMsg, uId, password);
    NetworkUtils::send_json_to_server(json);
}

void NetworkController::netSendMessage(int uId, char * password, bool isGroup, int uToId, int gToId, char * content) {
    char * json;
    if (isGroup) {
        JsonUtils::make_request_sendMessages_json(0, gToId, TYPE_GROUP_MESSAGE, content, uId, password);
    } else {
        JsonUtils::make_request_sendMessages_json(uToId, 0, TYPE_USER_MESSAGE, content, uId, password);
    }
    NetworkUtils::send_json_to_server(json);
}

void NetworkController::connectFailed() {
    callback->connectFailed();
}

void NetworkController::netAddUIdToGroup(int uId, char *password, int gId) {
    char * json;
    JsonUtils::make_request_adduIdToGroup_json(uId, gId, password);
    NetworkUtils::send_json_to_server(json);
}

