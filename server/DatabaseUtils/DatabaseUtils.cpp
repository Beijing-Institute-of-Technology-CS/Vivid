//
// Created by YichengChen on 8/29/19.
//

#include "DatabaseUtils.h"

//void Database::mysql_connect() {
//    /**
//     * mysql initiating
//     */
//    MYSQL mysql, *mysql_sock;
//    MYSQL_RES * mysql_results;
//    MYSQL_ROW row;
//
//    char * query_sql = "select * from User";
//
//    mysql_init(&mysql);
//
//    if((mysql_sock=mysql_real_connect(&mysql,LOCALHOST,MYSQL_USERNAME,MYSQL_PASSWORD,MYSQL_DATABASE_NAME,MYSQL_PORT,NULL,0))==NULL){
//        perror("mysql connection failed");
//        exit(EXIT_FAILURE);
//    }else{
//        std::cout << "mysql connected" << std::endl;
//    }
//
//    /**
//     * querying...
//     */
//
//    if(mysql_query(&mysql,query_sql)!=0){
//        perror("query failed");
//        exit(EXIT_FAILURE);
//    }else{
//        if((mysql_results = mysql_store_result(&mysql))==NULL){
//            perror("store failed");
//            exit(EXIT_FAILURE);
//        }else{
//            while((row=mysql_fetch_row(mysql_results))!=NULL) {
//                printf("%s %s %s %s", row[0], row[1], row[2], row[3]);
//            }
//        }
//    }
//
//    mysql_free_result(mysql_results);
//    mysql_close(mysql_sock);
//}
//

MYSQL DatabaseUtils::mysql_sock;

void DatabaseUtils::mysql_connect(MYSQL &mysql_sock) {
//    MYSQL mysql, *mysql_sock;
//    mysql_init(&mysql);
    mysql_init(&mysql_sock);
    if((mysql_real_connect(&mysql_sock,LOCALHOST,MYSQL_USERNAME,MYSQL_PASSWORD,MYSQL_DATABASE_NAME,MYSQL_PORT,NULL,0))==NULL){
        perror("mysql connection failed");
        exit(EXIT_FAILURE);
    }else{
        std::cout << "mysql connected" << std::endl;
    }
//    return mysql_sock;
//    return &mysql;
}


void DatabaseUtils::database_start() {
    std::cout << "database starting" << std::endl;
    mysql_connect(mysql_sock);
    std::cout << "database started" << std::endl;
}

int DatabaseUtils::doRegister(const char *username, const char *password) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
//    std::cout << mysql_sock << std::endl;
    char query_sql[2048];
    int uId = -1;

    sprintf(query_sql, "INSERT INTO User(%s, %s) VALUES(\'%s\', \'%s\')", KEY_UNAME, KEY_UPASSWORD, username, password);
//    printf("%s\n",query_sql);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("doRegister query failed");
    }else{
        uId = mysql_insert_id(&mysql_sock);
    }

//    mysql_close(&mysql_sock);
    return uId;
}


bool DatabaseUtils::checkPassword(int uId, const char *password) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];
    bool flag = false;

    sprintf(query_sql, "SELECT %s FROM User WHERE %s = %d", KEY_UPASSWORD, KEY_UID, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("checkPassword query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        MYSQL_ROW row = mysql_fetch_row(mysql_results);
        char *real_psd = row[0];
        if(strcmp(password, real_psd) == 0)
            flag = true;
        else
            flag = false;
        mysql_free_result(mysql_results);

    }

//    mysql_close(&mysql_sock);
    return flag;
}


bool DatabaseUtils::checkId(int uId) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];
    bool flag = false;

    sprintf(query_sql, "SELECT * FROM User WHERE %s = %d", KEY_UID, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("checkId query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
            flag = false;
        }
        else{
            MYSQL_ROW row;
            if((row = mysql_fetch_row(mysql_results)))
                flag = true;
            else
                flag = false;
        }
        mysql_free_result(mysql_results);
    }

//    mysql_close(&mysql_sock);
    return flag;
}


int DatabaseUtils::saveMessage(const Message &message) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];
    int mId = -1;

    sprintf(query_sql, "INSERT INTO Message(%s, %s, %s, %s, %s, %s, %s, %s) VALUES(\'%s\', %d, %d, %d, %d, \'%s\', \'%s\', \'%s\')",
            KEY_MCONTENT, KEY_FFILE, KEY_UFROMID, KEY_UTOID, KEY_GID, KEY_MTYPE, KEY_MTIME, KEY_UFROMUSERNAME,
            message.getMContent(), message.getFId(), message.getUFromId(), message.getUToId(),
            message.getGId(), message.isGroupMessage()?TYPE_GROUP_MESSAGE:TYPE_USER_MESSAGE, message.getMTime(),
            message.getUFromUsername());
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("saveMessage query failed");
    }else{
        mId = mysql_insert_id(&mysql_sock);
    }

//    mysql_close(&mysql_sock);
    return mId;
}


bool DatabaseUtils::getMessage(int mId, Message &message) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];
    bool flag = false;


    sprintf(query_sql, "SELECT * FROM Message WHERE %s = %d", KEY_MID, mId);
//    printf("%s\n",query_sql);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("getMessage query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
            flag = false;
        }
        else{
            MYSQL_ROW row;
            if((row = mysql_fetch_row(mysql_results))) {
                message.setMId(mId);
//                message.mContent = (char *)std::malloc((std::strlen(row[1])+1)*sizeof(char));
//                strcpy(message.mContent, row[1]);
                message.setMContent(row[1]);
                message.setFId(atoi(row[2]));
                message.setUFromId(atoi(row[3]));
                message.setUToId(atoi(row[4]));
                message.setGId(atoi(row[5]));
                message.setGroupMessage(std::strcmp(row[6], TYPE_GROUP_MESSAGE)?false:true);
//                message.mTime = (char *)std::malloc((std::strlen(row[7])+1)*sizeof(char));
//                strcpy(message.mTime, row[7]);
                message.setMTime(row[7]);
                message.setUFromUsername(row[8]);
                flag = true;
            }
            else{
                flag = false;
            }
        }
        mysql_free_result(mysql_results);
    }

//    mysql_close(&mysql_sock);
    return flag;
}


void DatabaseUtils::getMessages(int uToId, int lastCalledMessage, std::vector<Message> &messages) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "SELECT * FROM Message WHERE %s = %d AND %s > %d", KEY_UTOID, uToId, KEY_MID, lastCalledMessage);
//    std::cout << query_sql << std::endl;
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("getMessages query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
        }
        else{
            MYSQL_ROW row;
            while((row = mysql_fetch_row(mysql_results)) != NULL) {
                Message temp_message;
                temp_message.setMId(atoi(row[0]));
//                temp_message.mContent = (char *)std::malloc((std::strlen(row[1])+1)*sizeof(char));
//                strcpy(temp_message.mContent, row[1]);
                temp_message.setMContent(row[1]);
                temp_message.setFId(atoi(row[2]));
                temp_message.setUFromId(atoi(row[3]));
                temp_message.setUToId(atoi(row[4]));
                temp_message.setGId(atoi(row[5]));
                temp_message.setGroupMessage(std::strcmp(row[6], TYPE_GROUP_MESSAGE)?false:true);
//                temp_message.mTime = (char *)std::malloc((std::strlen(row[7])+1)*sizeof(char));
//                strcpy(temp_message.mTime, row[7]);
                temp_message.setMTime(row[7]);
                temp_message.setUFromUsername(row[8]);
                messages.push_back(temp_message);
            }
        }
        mysql_free_result(mysql_results);
    }

//    mysql_close(&mysql_sock);
}

//todo: error: atoi(NULL)

void DatabaseUtils::getUser(int uId, User &user) {


//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "SELECT * FROM User WHERE %s = %d", KEY_UID, uId);
//    std::cout << query_sql << std::endl;
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("getUser query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        MYSQL_ROW row = mysql_fetch_row(mysql_results);
        user.setUId(atoi(row[0]));
//        user.uName = (char *)std::malloc(std::strlen(row[1]+1)*sizeof(char));
//        strcpy(user.uName, row[1]);
        user.setUName(row[1]);
//        user.uPassword = (char *)std::malloc((std::strlen(row[2]+1)*sizeof(char)));
//        strcpy(user.uPassword, row[2]);
        user.setUPassword(row[2]);
//        user.setFIconFile(atoi(row[3]));
    }

//    mysql_close(&mysql_sock);
}

void DatabaseUtils::getUsers(int uId, std::vector<User> &users) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];

//    sprintf(query_sql, "SELECT * FROM User WHERE %s IN (SELECT %s FROM Befriend WHERE %s = %d)", KEY_UID, KEY_UID2, KEY_UID1, uId);
    sprintf(query_sql, "SELECT * FROM User WHERE %s != %d", KEY_UID, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("getUsers query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
            ;
        }
        else{
            MYSQL_ROW row;
            while((row = mysql_fetch_row(mysql_results)) != NULL) {
                User temp_user;
                temp_user.setUId(atoi(row[0]));
//                temp_user.uName = (char *)std::malloc(std::strlen(row[1]+1)*sizeof(char));
//                strcpy(temp_user.uName, row[1]);
                temp_user.setUName(row[1]);
//                temp_user.uPassword = (char *)std::malloc((std::strlen(row[2]+1)*sizeof(char)));
//                strcpy(temp_user.uPassword, row[2]);
                temp_user.setUPassword(row[2]);
//                temp_user.setFIconFile(atoi(row[3]));
                users.push_back(temp_user);
            }
        }
        mysql_free_result(mysql_results);
    }

//    mysql_close(&mysql_sock);
}


void DatabaseUtils::getGroups(int uId, std::vector<Group> &groups) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "SELECT %s FROM GroupVivid WHERE %s = %d", KEY_GID, KEY_UID, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("getGroups query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
            ;
        }
        else{
            MYSQL_ROW row;
            while((row = mysql_fetch_row(mysql_results)) != NULL) {
                Group temp_group(atoi(row[0]));
//                temp_group.setGId(atoi(row[0]));
                groups.push_back(temp_group);
            }
        }
        mysql_free_result(mysql_results);
    }

//    mysql_close(&mysql_sock);
}


void DatabaseUtils::addUIdToGroup(int uId, int gId) {

//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "INSERT INTO GroupVivid VALUES(%d, %d)", gId, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("addUIdToGroup query failed");
    }else{
        ;
    }

//    mysql_close(&mysql_sock);
}


void DatabaseUtils::getGroupContacts(int gId, std::vector<User> &groupContacts) {


//    MYSQL mysql_sock ;
//    mysql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "SELECT * FROM User WHERE %s IN (SELECT %s FROM GroupVivid WHERE %s = %d)", KEY_UID, KEY_UID, KEY_GID, gId);
//    std::cout << query_sql << std::endl;
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("getGroupContacts query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
            ;
        }
        else{
            MYSQL_ROW row;
            while((row = mysql_fetch_row(mysql_results)) != NULL) {
                User temp_user;
                temp_user.setUId(atoi(row[0]));
//                temp_user.uName = (char *)std::malloc(std::strlen(row[1]+1)*sizeof(char));
//                strcpy(temp_user.uName, row[1]);
                temp_user.setUName(row[1]);
//                temp_user.uPassword = (char *)std::malloc((std::strlen(row[2]+1)*sizeof(char)));
//                strcpy(temp_user.uPassword, row[2]);
                temp_user.setUPassword(row[2]);
//                temp_user.setFIconFile(atoi(row[3]));
                groupContacts.push_back(temp_user);
            }
        }
        mysql_free_result(mysql_results);
    }

//    mysql_close(&mysql_sock);
}
