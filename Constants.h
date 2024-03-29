//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_CONSTANTS_H
#define SERVER_CONSTANTS_H

#define PORT 8899
#define QUEUE_SIZE 5
#define POOL_SIZE 10
#define BUFFER_SIZE 1048576
#define USERS_SIZE 300



#define LOCALHOST "127.0.0.1"
#define BITCS "114.55.146.102"

#define MYSQL_USERNAME "root"
//#define MYSQL_PASSWORD "lp13688421885"
//#define MYSQL_PASSWORD "bluebirds"
#define MYSQL_PASSWORD "@BITCSpwd123"
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
#define TYPE_RECEIVE_MESSAGES "receiveMessages"

#define KEY_UID "uId"
#define KEY_UID1 "uId1"
#define KEY_UID2 "uId2"
#define KEY_UNAME "uName"
#define KEY_UPWD "uPwd"
#define KEY_UPASSWORD  "uPassword"
#define KEY_USERNAME "username"
#define KEY_PASSWORD "password"

#define KEY_MID "mId"
#define KEY_MCONTENT "mContent"
#define KEY_FID "fId"
#define KEY_FFILE "fFile"
#define KEY_MTIME "mTime"

#define KEY_LAST_CALLED_MESSAGE "lastCalledMessage"

#define KEY_UFROMID "uFromId"
#define KEY_UFROMUSERNAME "uFromUsername"
#define KEY_UTOID "uToId"

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

#define KEY_MTYPE "mType"
#define KEY_GID "gId"
#define KEY_GTOID "gToId"
#define KEY_GFROMID "gFromId"

#define KEY_GROUPS "groups"
#define KEY_GROUPS_NUMBER "groupsNumber"
#define KEY_GROUPS_ARRAY "groupsArray"

#define TYPE_USER_MESSAGE "userMessage"
#define TYPE_GROUP_MESSAGE "groupMessage"

#define TYPE_ADD_TO_GROUP "addToGroup"




#endif //SERVER_CONSTANTS_H
