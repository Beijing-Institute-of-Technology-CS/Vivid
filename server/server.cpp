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

#include "Utils/cJSON.h"
#include "Utils/cJSON.c"
#include "User.h"
#include "Utils/ThreadPool.h"
#include "Database/Database.h"

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
    cJSON *json_sub = NULL;

    char *p = NULL;

    json_root = cJSON_CreateObject();

    cJSON_AddStringToObject(json_root,"key0","value");
    cJSON_AddNumberToObject(json_root,"key1",111);
    json_sub = cJSON_CreateObject();

    cJSON_AddStringToObject(json_sub,"key0","subJson");
    cJSON_AddItemToObject(json_root,"key2",json_sub);

    p = cJSON_Print(json_root);

    cJSON_Delete(json_root);

    std::cout << p << std::endl;

    cJSON *pjson_root = cJSON_Parse(p);

    cJSON *pjson_sub = cJSON_GetObjectItem(pjson_root,"key2");

    char * val = cJSON_Print(cJSON_GetObjectItem(pjson_root,"key0"));
    char *subjson = cJSON_Print(cJSON_GetObjectItem(pjson_sub,"key0"));

    std::cout << val << std::endl;
    std::cout << subjson << std::endl;

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