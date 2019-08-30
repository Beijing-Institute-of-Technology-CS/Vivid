//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_CONSTANTS_H
#define SERVER_CONSTANTS_H

#define PORT 8899
#define QUEUE_SIZE 5
#define POOL_SIZE 10
#define BUFFER_SIZE 1024
#define USERS_SIZE 3

#define LOCALHOST "127.0.0.1"
#define MYSQL_USERNAME "root"
#define MYSQL_PASSWORD "lp13688421885"
#define MYSQL_DATABASE_NAME "Vivid"
#define MYSQL_PORT 3306

/**
 * request
 */
#define KEY_REQUEST_TYPE "requestType"
#define KEY_REQUEST_TOKEN "requestToken"
#define KEY_REQUEST_CONTENT "requestContent"

#define TYPE_REGISTER "register"
#define TYPE_LOGIN "login"
#define TYPE_GET_INFO "getInfo"
#define TYPE_GET_MESSAGES "getMessages"
#define TYPE_SEND_MESSAGES "sendMessages"

#define KEY_UID "uId"
#define KEY_UNAME "uName"
#define KEY_UPWD "uPwd"
#define KEY_USERNAME "username"
#define KEY_PASSWORD "password"

#define KEY_MID "mId"
#define KEY_MCONTENT "mContent"
#define KEY_FID "fId"
#define KEY_MTIME "mTime"

#define KEY_LAST_CALLED_MESSAGE "lastCalledMessage"

#define KEY_UTOID "uToId"
#define KEY_CONTENT "content"

/**
 * response
 */
#define KEY_RESPONSE_TYPE "responseType"
#define KEY_RESULT "result"

#define TRUE_CONTENT "true"
#define FALSE_CONTENT "false"

#define NULL_CONTENT "null"

#define KEY_RESPONSE_CONTENT "responseContent"
#define KEY_PUBLIC_KEY "publicKey"

#define KEY_FICON "fIcon"
#define KEY_CONTACTS "contacts"
#define KEY_CONTACTS_NUMBER "contactsNumber"
#define KEY_CONTACTS_ARRAY "contactsArray"

#define KEY_MESSAGES "messages"
#define KEY_MESSAGES_NUMBER "messagesNumber"
#define KEY_MESSAGES_ARRAY "messagesArray"


#endif //SERVER_CONSTANTS_H
