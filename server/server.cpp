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

#include "TestUtils/JsonTesting.h"
#include "Utils/ThreadPool.h"
#include "Beans/User.h"
#include "Database/Database.h"

#include "Constants.h"


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

//    JsonTesting::json_parse_request_testing();
    JsonTesting::json_make_response_testing();
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
