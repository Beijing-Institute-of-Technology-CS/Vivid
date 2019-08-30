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
#include "../Constants.h"
#include "../Beans/User.h"
#include "../Utils/ThreadPool.h"

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

    User user[USERS_SIZE];

    int client_sockets[USERS_SIZE];

    for(int i=0;i<USERS_SIZE;i++){
        client_sockets[i]=0;
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
            fd = client_sockets[i];

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
//

            /**
             * adding new_socket to client_sockets
             */
            for(int i=0;i<USERS_SIZE;i++){

                if(client_sockets[i]==0){
                    client_sockets[i] = new_socket;
                    std::cout << "adding to list of sockets as "<< i <<std::endl;

                    break;
                }
            }
        }

        /**
         * else handling some IO operation on other socket
         */
        for(int i=0;i<USERS_SIZE;i++){
            fd = client_sockets[i];

            if(FD_ISSET(fd,&read_fds)){
                int val_read = read(fd,buffer,BUFFER_SIZE);
                if(val_read == 0){

                    /**
                     * close this socket
                     */

                    getpeername(fd,(sockaddr *)&address,(socklen_t *)&addrlen);
                    std::cout << "host disconnected " << " ip " << inet_ntoa(address.sin_addr) << " port " << ntohs(address.sin_port) << std::endl;
                    close(fd);
                    client_sockets[i]=0;
                }
                else{
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
