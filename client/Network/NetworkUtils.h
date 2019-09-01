//
// Created by YichengChen on 8/31/19.
//

#ifndef CLIENT1_NETWORKUTILS_H
#define CLIENT1_NETWORKUTILS_H

#include <netinet/in.h>
#include <thread>


class NetworkUtils {
public:
    static void start_client(char *ip);
    static void send_json_to_server(char *s_json);

    static bool client_ready;
    static bool sending_messages;
private:
    static void init_client(char *ip);
    static void listen_from_server();
    static void sending_json(char *s_json);
    static int master_socket;
    static sockaddr_in serv_addr;
    static char * buffer;
};


#endif //CLIENT1_NETWORKUTILS_H
