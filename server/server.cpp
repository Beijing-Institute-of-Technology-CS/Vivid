#include <cstdio>
#include <fcntl.h>
#include <csignal>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctime>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <vector>
//#include <mysql/mysql.h>

#include "Utils/ThreadPool.h"
#include "Utils/cJSON.h"
//#include "Utils/cJSON.c"


#include "User.h"

#include "Database/Database.h"

#include "JsonUtils/JsonUtils.h"

#define PORT 8899
#define QUEUE_SIZE 5
#define POOL_SIZE 10
#define BUFFER_SIZE 1024
#define USERS_SIZE 100

#define LOCALHOST "127.0.0.1"
#define MYSQL_USERNAME "root"
#define MYSQL_PASSWORD "lp13688421885"
#define MYSQL_DATABASE_NAME "Vivid"
#define MYSQL_PORT 3306

void do_services(int new_socket){
    char buffer [BUFFER_SIZE] = {0};

    while(read(new_socket,buffer,BUFFER_SIZE)!=-1){
        /**
         * echoing
         */
        send(new_socket,buffer,strlen(buffer),0);
    }
}



int main() {
    Database::mql_connect();

    /**
     * json
     */

    std::cout << "json parsing" << std::endl;

    cJSON *json_root = NULL;
    char * json_requestType = "sendMessages";
    cJSON *json_token = NULL;
    cJSON *json_content = NULL;

    char *s_json = NULL;

    json_root = cJSON_CreateObject();
    json_token = cJSON_CreateObject();
    json_content = cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,"requestType",json_requestType);

    cJSON_AddNumberToObject(json_token,"uId",1);
    cJSON_AddStringToObject(json_token,"uPwd","pwd");
    cJSON_AddItemToObject(json_root,"requestToken",json_token);

    cJSON_AddStringToObject(json_content,"username","cyc");
    cJSON_AddStringToObject(json_content,"password","password");
    cJSON_AddItemToObject(json_root,"requestContent",json_content);

//    cJSON_AddNumberToObject(json_content,"lastCalledMessage",99);
//    cJSON_AddItemToObject(json_root,"requestContent",json_content);

//    cJSON_AddNumberToObject(json_content,"utoId",999);
//    cJSON_AddStringToObject(json_content,"content","connnt");
//    cJSON_AddItemToObject(json_root,"requestContent",json_content);

    s_json = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    std::cout << s_json << std::endl;

    char * requestType;
    JsonUtils::parse_request_type(s_json, requestType);
    std::cout << requestType << std::endl;

    int uId;
    char * uPwd;

    JsonUtils::parse_request_token(s_json, &uId, uPwd);
    std::cout << (uId) << " " << uPwd << std::endl;

    char *username;
    char *password;

    JsonUtils::parse_request_login_json(s_json,username,password);
    std::cout << username << " " << password << std::endl;

//    int lastCalledMessage;
//    JsonUtils::parse_request_getMessages_json(s_json,&lastCalledMessage);
//    std::cout << lastCalledMessage << std::endl;

//    int utoId;
//    char * content;
//
//    JsonUtils::parse_request_sendMessages_json(s_json, &utoId, content);
//    std::cout << utoId <<" " << content << std::endl;

    /**
     * server socket starting
     */
    std::cout << "server starting" << std::endl;

    int master_socket;

    sockaddr_in address;

    int addrlen = sizeof(address);

    User user[USERS_SIZE];

    int lags;

    int user_count=0;

    /**
     * dk what these are for
     */
    lags = fcntl(master_socket,F_GETFL);
    fcntl(master_socket,F_SETFL,lags&~O_NDELAY);

    /**
     * creating socket
     */
    if((master_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("server socket failed");
        exit(EXIT_FAILURE);
    }

    /**
     * config address?
     */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    /**
     * porting address
     */
    address.sin_port = htons(PORT);

    /**
     * binding
     */
    if(bind(master_socket, (sockaddr *)&address, addrlen) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    /**
     * listening
     */
    if(listen(master_socket, QUEUE_SIZE) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    /**
     * accepting
     * new_socket refer to the new file descriptor that connects to the client socket
     */

    int new_socket;

    /**
     * thread pool initializing
     */

    ThreadPool pool(POOL_SIZE);
    std::vector< std::future<int> > threadpool_results;

    while(true){

        if((new_socket = accept(master_socket, (sockaddr*)&address, (socklen_t *)&addrlen)) < 0){
            perror("client accept failed");
            exit(EXIT_FAILURE);
        }else{
            if(user_count>=USERS_SIZE){
                perror("too many users!");
                close(new_socket);
            }else{
                /**
                * threading
               */
                pool.enqueue(do_services,new_socket);
                user_count++;
            }
        }

    }
    close(master_socket);
    return 0;
}