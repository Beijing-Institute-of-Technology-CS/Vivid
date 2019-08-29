//
// Created by YichengChen on 8/29/19.
//

#include "Database.h"

void Database::mql_connect() {
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
}
