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

#include "NetworkUtils/NetworkUtils.h"
#include "TestUtils/JsonTesting.h"

int main() {
//    DatabaseUtils::mql_connect();
//    int id = DatabaseUtils::doRegister("hello", "psd");
//    std::cout << id << std::endl;
//    std::cout << DatabaseUtils::checkId(1) << std::endl;
//    std::cout << DatabaseUtils::checkPassword(1, "psd") << std::endl;
//    Message message(NULL, "another content", NULL, "18:15");
//    std::cout << DatabaseUtils::saveMessage(message) << std::endl;
//    Message message;
//    std::cout << DatabaseUtils::getMessages(1, message) << std::endl;
//    std::cout << message.getMId() << " " << message.getMContent() << " " << message.getFId() << " " << message.getFromId() << " " << message.getToId() << " " << message.getMTime() << std::endl;
//    std::vector<Message> messages;
//    DatabaseUtils::getMessages(1, 1, messages);
//    for(auto message :messages){
//        std::cout << message.getMId() << " " << message.getMContent() << " " << message.getFId() << " " << message.getFromId() << " " << message.getToId() << " " << message.getMTime() << std::endl;
//    }
//    User user;
//    DatabaseUtils::getUser(3, user);
//    std::cout << user.getUId() << " " << user.getUName() << " " << user.getUPassword() << " " << user.getFIconFile() << std::endl;
//    std::vector<User> users;
//    DatabaseUtils::getUsers(3, users);
//    for(auto user: users){
//        std::cout << user.getUId() << " " << user.getUName() << " " << user.getUPassword() << " " << user.getFIconFile() << std::endl;
//    }

//    JsonTesting::json_parse_request_testing();
//    JsonTesting::json_make_response_testing();

    NetworkUtils::start_server();

    return 0;
}
