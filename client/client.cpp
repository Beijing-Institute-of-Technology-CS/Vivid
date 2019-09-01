//#include <arpa/inet.h>
//#include <sys/socket.h>
//#include <unistd.h>
//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
////#include "Utils/cJSON.h"
////#include "Utils/cJSON.c"
//
//#define PORT 8899
//#define LOCALHOST "127.0.0.1"
//#define BITCS "114.55.146.102"
//#define BITCS_INNER "172.16.239.178"
//
//
//int main() {
//    printf("client starting\n");
//    fflush(stdout);
//
//    int sock;
//
//    sockaddr_in serv_addr;
//
//    int val_read;
//
//    char buffer[1024] = {0};
//
//    char message[1024]={0};
//
//    /**
//     * creating socket
//     */
//    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//        perror("client socket failed");
//        exit(EXIT_FAILURE);
//    }
//
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_port = htons(PORT);
//
//    /**
//     * Convert IPv4 and IPv6 addresses from text to binary form
//     */
//    if (inet_pton(AF_INET, LOCALHOST, &(serv_addr.sin_addr)) <= 0) {
//        //    if(inet_pton(AF_INET,BITCS,&(serv_addr.sin_addr))<=0){
//        perror("Invalid address | address not supported");
//        exit(EXIT_FAILURE);
//    }
//
//    /**
//     * connecting to server socket using the serv_addr
//     */
//    if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
//        perror("connection failed");
//        exit(EXIT_FAILURE);
//    }
//
//    /**
//     * sending messages
//     */
//    char *hello_message = "hello";
//    printf("%s", "hello");
//    send(sock, hello_message, strlen(hello_message), 0);
//    printf("hello from client sent\n");
//
//    val_read = read(sock, buffer, 1024);
//    printf("%s\n", buffer);
//
//    return 0;
//}
#include "TestUtils/JsonTesting.h"
#include "JsonUtils/JsonUtils.h"
#include "Utils/cJSON.h"

int main()
{
//    JsonTesting jsonTest;
//    jsonTest.test_make_request_json();
//    jsonTest.test_parse_response_json();
}
