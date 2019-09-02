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
#include <ctime>

#include "NetworkUtils.h"
#include "../../Constants.h"
#include "../Beans/User.h"
#include "../Beans/Client.h"
#include "../Beans/Message.h"
#include "../JsonUtils/JsonUtils.h"
#include "../DatabaseUtils/DatabaseUtils.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void NetworkUtils::start_server() {
    /**
     * server socket starting
     */
    std::cout << "server starting..." << std::endl;

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

    std::cout << "server started" << std::endl;

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

                    getpeername(fd,(sockaddr *)&address,(socklen_t *)&addrlen);
                    std::cout << "host disconnected " << " ip " << inet_ntoa(address.sin_addr) << " port " << ntohs(address.sin_port) << std::endl;
                    close(fd);

                    /**
                    * disconnected
                    */

                    users[clients[i].getUId()].setInUse(false);

                    clients[i].setFd(0);
                    clients[i].setUId(0);
                }
                else{
                    /**
                     * logging
                     */
                    std::cout << buffer << std::endl;

                    /**
                     * json parsing
                     */

                    /**
                     * login or register
                     */

                    char * requestType;
                    JsonUtils::parse_request_type(buffer,requestType);

                    if(strcmp(requestType,TYPE_REGISTER)==0){
                        char *username;
                        char *password;

                        JsonUtils::parse_request_register_json(buffer,username,password);

                        int uId = DatabaseUtils::doRegister(username,password);

                        char *s_json = JsonUtils::make_response_register_json(TRUE_CONTENT,uId);

                        send(fd,s_json,strlen(s_json),0);
                    }else if(strcmp(requestType,TYPE_LOGIN)==0){
                        /**
                         * online
                         */
                        int uId;
                        char *password;

                        JsonUtils::parse_request_login_json(buffer,&uId,password);

                        if(DatabaseUtils::checkPassword(uId,password)){
                            /**
                             * login online
                             */

                            /**
                             * users
                             */
                            users[uId].setInUse(true);

                            users[uId].uPassword = (char *)malloc((strlen(password)+1)*sizeof(char));
                            strcpy(users[uId].uPassword,password);

                            users[uId].setClientIndex(i);

                            /**
                             * clients
                             */
                            clients[i].setUId(uId);

                            User user_for_username;
                            DatabaseUtils::getUser(uId, user_for_username);
                            char *username = user_for_username.getUName();

                            char *s_json = JsonUtils::make_response_login_json(TRUE_CONTENT,username);
                            send(fd,s_json,strlen(s_json),0);

                        }else{
                            char *s_json = JsonUtils::make_response_login_json(FALSE_CONTENT,NULL_CONTENT);
                            send(fd,s_json,strlen(s_json),0);
                        }
                    }
                    /**
                     * verifying token
                     */
                     else{
                        int uId;
                        char * uPwd;
                        JsonUtils::parse_request_token(buffer,&uId,uPwd);

                        if(DatabaseUtils::checkPassword(uId,uPwd)){
                            if(strcmp(requestType,TYPE_GET_INFO)==0){

                                int fIcon = 0;

                                std::vector<User> contacts;
                                DatabaseUtils::getUsers(uId,contacts);

                                std::vector<Group> groups;
                                DatabaseUtils::getGroups(uId,groups);

                                char * s_json = JsonUtils::make_response_getInfo_json(TRUE_CONTENT, fIcon, contacts,groups);

                                send(fd, s_json, strlen(s_json), 0);

                            }else if(strcmp(requestType,TYPE_GET_MESSAGES)==0){
                                int lastCalledMessage;

                                JsonUtils::parse_request_getMessages_json(buffer,&lastCalledMessage);

                                std::vector<Message> messages;
                                DatabaseUtils::getMessages(uId,lastCalledMessage,messages);

                                char *s_json = JsonUtils::make_response_getMessages_json(TRUE_CONTENT,messages);

                                send(fd,s_json,strlen(s_json),0);

                            }else if(strcmp(requestType,TYPE_SEND_MESSAGES)==0){
                                int uToId;
                                int gToId;
                                char * mType;
                                char * mContent;

                                JsonUtils::parse_request_sendMessages_json(buffer,&uToId,&gToId,mType,mContent);

                                /**
                                 * uFromId should be equal to uId
                                 */
                                int uFromId = clients[i].getUId();

                                std::cout << uFromId << " send to " << uToId << " content: " << mContent <<std::endl;

                                Message message;
                                message.setUFromId(uFromId);
                                message.setUToId(uToId);
                                message.setGId(gToId);

                                message.mContent = (char *)malloc(sizeof(char)*(strlen(mContent)+1));
                                strcpy(message.mContent,mContent);

                                if(strcmp(mType,TYPE_GROUP_MESSAGE)==0){
                                    message.setGroupMessage(true);
                                }else{
                                    message.setGroupMessage(false);
                                }

                                /**
                                 * generate time
                                 */
                                time_t now = time(0);
                                tm *ltm = localtime(&now);

                                std::string time_s = std::to_string(ltm->tm_hour);
                                time_s += " ";
                                time_s += std::to_string(ltm->tm_min);
                                time_s += " ";
                                time_s += std::to_string(ltm->tm_sec);

                                message.mTime = (char *)malloc(sizeof(char)* (time_s.length()+1));
                                strcpy(message.mTime,time_s.c_str());

                                /**
                                 * to sender
                                 */
                                {
                                    char *s_json = JsonUtils::make_response_sendMessages_json(TRUE_CONTENT,message);
                                    send(fd,s_json,strlen(s_json),0);
                                }

                                /**
                                 * to receiver
                                 */
                                if(message.isGroupMessage()){
                                    std::vector<User> groupContacts;
                                    for(int j=0;j<groupContacts.size();j++){
                                        int uToId_groupMessage = groupContacts.at(j).getUId();
                                        if(users[uToId_groupMessage].isInUse()){

                                            int clientIndex = users[uToId_groupMessage].getClientIndex();
                                            int fd = clients[clientIndex].getFd();

                                            char *s_json = JsonUtils::make_response_sendMessages_json(TRUE_CONTENT,message);
                                            send(fd,s_json,strlen(s_json),0);

                                        }else{
                                            //todo do nothing
                                        }
                                    }
                                }
                                else{
                                    /**
                                     * receiver is online
                                     */
                                    if(users[uToId].isInUse()){

                                        int clientIndex = users[uToId].getClientIndex();

                                        char *s_json = JsonUtils::make_response_receiveMessages_json(TRUE_CONTENT,message);
                                        send(clients[clientIndex].getFd(),s_json,strlen(s_json),0);
                                    }
                                    /**
                                     * receiver is not online
                                     */
                                    else{
                                        //todo do nothing?
                                    }
                                }
                            }else if(strcmp(requestType,TYPE_ADD_TO_GROUP)==0){
                                    int uId;
                                    int gId;

                                    JsonUtils::parse_request_adduIdToGroup_json(buffer,&uId,&gId);

                                    DatabaseUtils::addUIdToGroup(uId,gId);

                                    char *s_json = JsonUtils::make_response_adduIdToGroup_json(TRUE_CONTENT);
                            }
                        }else{
                            perror("wrong token!");
                        }
                    }
                }
            }
        }
    }

    close(master_socket);
}
#pragma clang diagnostic pop
