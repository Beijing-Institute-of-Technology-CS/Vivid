//
// Created by YichengChen on 8/31/19.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "NetworkUtils.h"
#include "../../Constants.h"
#include "../JsonUtils/JsonUtils.h"
#include "../Controller/NetworkController/NetworkController.h"


int NetworkUtils::master_socket;
sockaddr_in NetworkUtils::serv_addr;
bool NetworkUtils::client_ready = false;
bool NetworkUtils::sending_messages = false;
char * NetworkUtils::buffer = (char *)malloc(sizeof(char)*1024);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void NetworkUtils::listen_from_server() {
    std::cout << "listening from server " <<std::endl;
    int val_read;

    while(true){
        val_read = read(master_socket,buffer,BUFFER_SIZE);

        /**
         * logging
         */
        std::cout << buffer << std::endl;

        char *responseType;
        char *result;

        JsonUtils::parse_response_type_json(buffer, responseType);
        JsonUtils::parse_response_result_json(buffer,result);

        /**
         * parsing json
         */
        if(strcmp(responseType, TYPE_REGISTER) == 0){
            sending_messages = false;
            if(strcmp(result,TRUE_CONTENT)==0){
                NetworkController::netRegisterSuccess(buffer);
            }else if(strcmp(result,FALSE_CONTENT)==0){
                NetworkController::netRegisterFailed();
            }
        }else if(strcmp(responseType, TYPE_LOGIN) == 0){
            sending_messages = false;
            if(strcmp(result,TRUE_CONTENT)==0){
                NetworkController::netLoginSuccess(buffer);
            }else if(strcmp(result,FALSE_CONTENT)==0){
                NetworkController::netLoginFailed();
            }
        }else if(strcmp(responseType, TYPE_GET_INFO)==0){
            sending_messages = false;
            if(strcmp(result,TRUE_CONTENT)==0){
                NetworkController::netGetInfoSuccess(buffer);
            }else if(strcmp(result,FALSE_CONTENT)==0){
                NetworkController::netGetInfoFailed();
            }
        }else if(strcmp(responseType, TYPE_GET_MESSAGES)==0){
            sending_messages = false;
            if(strcmp(result,TRUE_CONTENT)==0){
                NetworkController::netGetMessageSuccess(buffer);
            }else if(strcmp(result,FALSE_CONTENT)==0){
                NetworkController::netGetMessageFailed();
            }
        }else if(strcmp(responseType,TYPE_SEND_MESSAGES)==0){
            sending_messages = false;
            if(strcmp(result,TRUE_CONTENT)==0){
                NetworkController::netSendMessageSuccess(buffer);
            }else if(strcmp(result,FALSE_CONTENT)==0){
                NetworkController::netSendMessageFailed();
            }
        }else if(strcmp(responseType,TYPE_RECEIVE_MESSAGES)==0){
            if(strcmp(result,TRUE_CONTENT)==0){
                NetworkController::netReceiveMessage(buffer);
            }else if(strcmp(result,FALSE_CONTENT)==0){

            }
        }else if(strcmp(responseType,TYPE_ADD_TO_GROUP)==0){
            sending_messages = false;
            if(strcmp(result,TRUE_CONTENT)==0){
            }else if(strcmp(result,FALSE_CONTENT)==0){

            }
        }
}
#pragma clang diagnostic pop


void NetworkUtils::init_client(char *ip) {
    client_ready = false;
    sending_messages = false;

    std::cout << "client starting..." << std::endl;

    /**
     * creating socket
     */
    if((master_socket=socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("client master_socket failed");
//        exit(EXIT_FAILURE);
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    /**
     * Convert IPv4 and IPv6 addresses from text to binary form
     */
    if(inet_pton(AF_INET,ip,&(serv_addr.sin_addr))<=0){
        perror("Invalid address | address not supported");
//        exit(EXIT_FAILURE);
        return;
    }

    /**
     * connecting to server socket using the serv_addr
     */

    if(connect(master_socket, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("connection failed");
//        exit(EXIT_FAILURE);
        return;
    }

    std::thread t_listen_from_server(NetworkUtils::listen_from_server);
    t_listen_from_server.detach();

    std::cout << "client started " << std::endl;
    client_ready = true;
}

void NetworkUtils::start_client(char *ip) {
//    std::thread t_init_client(NetworkUtils::init_client, ip);
    NetworkUtils::init_client(ip);
}

void NetworkUtils::send_json_to_server(char *s_json) {
    std::thread t_sending_json(NetworkUtils::sending_json,s_json);
    t_sending_json.detach();

}

void NetworkUtils::sending_json(char *s_json) {
    //todo: debug only
    std::cout<<std::endl<<std::endl<<"====================================="<<std::endl;
    std::cout<<"sending_json:"<<std::endl;
    std::cout<<s_json<<std::endl;
    std::cout<<"====================================="<<std::endl;
    while(!client_ready||sending_messages);
    sending_messages = true;
    if (send(master_socket,s_json,strlen(s_json),0) <= 0) {
        NetworkController::connectFailed();
    } else {
        std::cout<<"Send Success"<<std::endl;
    }
}

