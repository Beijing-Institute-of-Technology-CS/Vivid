//
// Created by YichengChen on 8/29/19.
//

#include "Database.h"

//void Database::mql_connect() {
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
void Database::mql_connect(MYSQL &mysql_sock) {
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

int Database::doRegister(const char *username, const char *password) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
//    std::cout << mysql_sock << std::endl;
    char query_sql[2048];
    int uId = -1;

    sprintf(query_sql, "INSERT INTO User(%s, %s) VALUES(\'%s\', \'%s\')", KEY_UNAME, KEY_UPASSWORD, username, password);
//    printf("%s\n",query_sql);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
    }else{
        uId = mysql_insert_id(&mysql_sock);
    }

    mysql_close(&mysql_sock);
    return uId;
}

bool Database::checkPassword(int uId, const char *password) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
    char query_sql[2048];
    bool flag = false;

    sprintf(query_sql, "SELECT %s FROM User WHERE %s = %d", KEY_UPASSWORD, KEY_UID, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
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

    mysql_close(&mysql_sock);
    return flag;
}

bool Database::checkId(int uId) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
    char query_sql[2048];
    bool flag = false;

    sprintf(query_sql, "SELECT * FROM User WHERE %s = %d", KEY_UID, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
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

    mysql_close(&mysql_sock);
    return flag;
}

int Database::saveMessage(const Message &message) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
    char query_sql[2048];
    int mId = -1;

    sprintf(query_sql, "INSERT INTO Message(%s, %s, %s, %s, %s) VALUES(\'%s\', %d, %d, %d, \'%s\')", KEY_MCONTENT, KEY_FFILE, KEY_UFROMID, KEY_UTOID, KEY_MTIME, message.getMContent(), message.getFId(), message.getFromId(), message.getToId(), message.getMTime());
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
    }else{
        mId = mysql_insert_id(&mysql_sock);
    }

    mysql_close(&mysql_sock);
    return mId;
}

bool Database::getMessage(int mId, Message &message) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
    char query_sql[2048];
    bool flag = false;


    sprintf(query_sql, "SELECT * FROM Message WHERE %s = %d", KEY_MID, mId);
//    printf("%s\n",query_sql);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
            flag = false;
        }
        else{
            MYSQL_ROW row;
            if((row = mysql_fetch_row(mysql_results))) {
                message.setMId(mId);
                message.mContent = (char *)malloc((strlen(row[1])+1)*sizeof(char));
                strcpy(message.mContent, row[1]);
                message.setFId(atoi(row[2]));
                message.setFromId(atoi(row[3]));
                message.setToId(atoi(row[4]));
                message.mTime = (char *)malloc((strlen(row[5])+1)*sizeof(char));
                strcpy(message.mTime, row[5]);
                flag = true;
            }
            else{
                flag = false;
            }
        }
        mysql_free_result(mysql_results);
    }

    mysql_close(&mysql_sock);
    return flag;
}

void Database::getMessages(int uToId, int lastCalledMessage, std::vector<Message> &messages) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "SELECT * FROM Message WHERE %s = %d AND %s > %d", KEY_UTOID, uToId, KEY_MID, lastCalledMessage);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        if(mysql_results == NULL){
            ;
        }
        else{
            MYSQL_ROW row;
            while((row = mysql_fetch_row(mysql_results)) != NULL) {
                Message temp_message;
                temp_message.setMId(atoi(row[0]));
                temp_message.mContent = (char *)malloc((strlen(row[1])+1)*sizeof(char));
                strcpy(temp_message.mContent, row[1]);
                temp_message.setFId(atoi(row[2]));
                temp_message.setFromId(atoi(row[3]));
                temp_message.setToId(atoi(row[4]));
                temp_message.mContent = (char *)malloc((strlen(row[5])+1)*sizeof(char));
                strcpy(temp_message.mContent, row[5]);
                messages.push_back(temp_message);
            }
        }
        mysql_free_result(mysql_results);
    }

    mysql_close(&mysql_sock);
}

//todo: error: atoi(NULL)
void Database::getUser(int uId, User &user) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "SELECT * FROM User WHERE %s = %d", KEY_UID, uId);
    std::cout << query_sql << std::endl;
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
    }else{
        MYSQL_RES *mysql_results = mysql_store_result(&mysql_sock);
        MYSQL_ROW row = mysql_fetch_row(mysql_results);
        user.setUId(atoi(row[0]));
        user.uName = (char *)malloc(strlen(row[1]+1)*sizeof(char));
        strcpy(user.uName, row[1]);
        user.uPassword = (char *)malloc((strlen(row[2]+1)*sizeof(char)));
        strcpy(user.uPassword, row[2]);
//        user.setFIconFile(atoi(row[3]));
    }

    mysql_close(&mysql_sock);
}

void Database::getUsers(int uId, std::vector<User> &users) {
    MYSQL mysql_sock ;
    mql_connect(mysql_sock);
    char query_sql[2048];

    sprintf(query_sql, "SELECT * FROM User WHERE %s = (SELECT %s FROM Befriend WHERE %s = %d)", KEY_UID, KEY_UID2, KEY_UID1, uId);
    if(mysql_query(&mysql_sock, query_sql)!=0){
        perror("query failed");
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
                temp_user.uName = (char *)malloc(strlen(row[1]+1)*sizeof(char));
                strcpy(temp_user.uName, row[1]);
                temp_user.uPassword = (char *)malloc((strlen(row[2]+1)*sizeof(char)));
                strcpy(temp_user.uPassword, row[2]);
//                temp_user.setFIconFile(atoi(row[3]));
                users.push_back(temp_user);
            }
        }
        mysql_free_result(mysql_results);
    }

    mysql_close(&mysql_sock);
}
