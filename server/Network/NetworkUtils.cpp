//
// Created by YichengChen on 8/29/19.
//

#include <cstdio>
#include <fcntl.h>
#include <sys/socket.h>
#include <ctime>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <arpa/inet.h>

#include "NetworkUtils.h"
#include "../../Constants.h"
#include "../Beans/User.h"
#include "../Beans/Client.h"
#include "../Beans/Message.h"
#include "../Utils/ThreadPool.h"
#include "../JsonUtils/JsonUtils.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void NetworkUtils::start_server() {
    /**
     * server socket starting
     */
    std::cout << "server starting" << std::endl;

    int master_socket;

    sockaddr_in address;

    int addrlen = sizeof(address);

//    /**
//     * dk what these are for
//     */
//    lags = fcntl(master_socket,F_GETFL);
//    fcntl(master_socket,F_SETFL,lags&~O_NDELAY);

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
        close(master_socket);
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

    fd_set read_fds;

    User users[USERS_SIZE];
    Client clients[USERS_SIZE];

    for(int i=0;i<USERS_SIZE;i++){
        clients[i].setFd(0);
    }

    int max_fd = master_socket;

    int activity;

    char buffer[BUFFER_SIZE+1];

    while(true){
        FD_ZERO(&read_fds);
        FD_SET(master_socket,&read_fds);

        max_fd = master_socket;

        /**
         * adding client_socket
         */

        int fd;

        for(int i=0;i<USERS_SIZE;i++) {
            fd = clients[i].getFd();

            if (fd > 0) {
                FD_SET(fd, &read_fds);
            }

            if (fd > max_fd) {
                max_fd = fd;
            }
        }


        activity = select(max_fd+1,&read_fds,NULL,NULL,NULL);

        if(activity<0){
            perror("select error!");
        }

        /**
         * incoming connection
         */

        if(FD_ISSET(master_socket,&read_fds)){
            int new_socket = accept(master_socket, (sockaddr *)&address,(socklen_t *)&addrlen);
            if((new_socket <0)){
                perror("accept failed");
            }

            std::cout << "New connection! " << "socket fd is " << new_socket << " ip is "
                      << inet_ntoa(address.sin_addr) << " port is " << ntohs(address.sin_port) <<std::endl;

            /**
             * sending or reading
             */

//            char * welcome = "welcome!\n";
//
//            if(send(new_socket,welcome,strlen(welcome),0)<=0){
//                perror("send failed");
//            }

            /**
             * adding new_socket to client_sockets
             */
            for(int i=0;i<USERS_SIZE;i++){

                if(clients[i].getFd() == 0){
                    clients[i].setFd(new_socket);

                    /**
                     * fist time add to users, set fd
                     */
                    std::cout << "adding to list of sockets as "<< i <<std::endl;

                    break;
                }
            }
        }

        /**
         * read from client
         * else handling some IO operation on other socket
         */
        for(int i=0;i<USERS_SIZE;i++){
            fd = clients[i].getFd();

            if(FD_ISSET(fd,&read_fds)){

                /**
                 * buffer is json
                 */
                int val_read = read(fd,buffer,BUFFER_SIZE);

                if(val_read == 0){

                    /**
                     * close this socket
                     */

                    /**
                    * disconnected
                    */

                    getpeername(fd,(sockaddr *)&address,(socklen_t *)&addrlen);
                    std::cout << "host disconnected " << " ip " << inet_ntoa(address.sin_addr) << " port " << ntohs(address.sin_port) << std::endl;
                    close(fd);
                    clients[i].setFd(0);
                }
                else{
                    /**
                     * json parsing
                     */

                    /**
                     * login or register
                     */

                    char * requestType;
                    JsonUtils::parse_request_type(buffer,requestType);

                    if(strcmp(requestType,TYPE_REGISTER)==0){
                        //todo save username,password to db,
                        //todo send uId,publicKey,

                        char *username;
                        char *password;

                        JsonUtils::parse_request_register_json(buffer,username,password);


                    }else if(strcmp(requestType,TYPE_LOGIN)==0){
                        /**
                         * online
                         */
                        int uId;
                        char *password;

                        JsonUtils::parse_request_login_json(buffer,&uId,password);

                        //todo db_check
                        if(1){
                            users[uId].setInUse(true);
                            users[uId].uPassword = (char *)malloc((strlen(password)+1)*sizeof(char));
                            strcpy(users[uId].uPassword,password);

                            //todo read username from db;
                            char *username = "cyc";
                            char *s_json = JsonUtils::make_response_login_json(TRUE_CONTENT,username);
                        }else{

                            char *s_json = JsonUtils::make_response_login_json(FALSE_CONTENT,NULL_CONTENT);
                            send(fd,s_json,strlen(s_json),0);
                        }
                    }

                    int uId;
                    char * uPwd;
                    JsonUtils::parse_request_token(buffer,&uId,uPwd);

                    //todo check from database
                    if(1){
                        if(strcmp(requestType,TYPE_GET_INFO)==0){

                        }else if(strcmp(requestType,TYPE_GET_MESSAGES)==0){

                        }else if(strcmp(requestType,TYPE_SEND_MESSAGES)==0){
                            int uToId;
                            char * mContent;

                            JsonUtils::parse_request_sendMessages_json(buffer,&uToId,mContent);

                            std::cout << "send to " << uToId;
                        }
                    }else{
                        perror("wrong token!");
                    }
                     char * json_requestType;
                     JsonUtils::parse_request_type(buffer,json_requestType);



                    buffer[val_read]='\0';
                    if(send(fd,buffer,strlen(buffer),0)<=0){
                        perror("send failed!");
                    }
                }
            }
        }
    }

    close(master_socket);
}
#pragma clang diagnostic pop
