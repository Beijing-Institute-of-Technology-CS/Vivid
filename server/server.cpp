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
//#include <mysql.h>

//#include "TestUtils/JsonTesting.h"
//#include "Utils/ThreadPool.h"
#include "Beans/User.h"
#include "Beans/Message.h"
#include "Beans/Message.cpp"
#include "Database/Database.h"
#include "Database/Database.cpp"
//#include "Network/NetworkUtils.h"

#include "../Constants.h"

int main() {
//    Database::mql_connect();
//    int id = Database::doRegister("hello", "psd");
//    std::cout << id << std::endl;
//    std::cout << Database::checkId(1) << std::endl;
//    std::cout << Database::checkPassword(1, "psd") << std::endl;
//    Message message(NULL, "another content", NULL, "18:15");
//    std::cout << Database::saveMessage(message) << std::endl;
//    Message message;
//    std::cout << Database::getMessage(1, message) << std::endl;
//    std::cout << message.getMId() << " " << message.getMContent() << " " << message.getFId() << " " << message.getFromId() << " " << message.getToId() << " " << message.getMTime() << std::endl;
//    std::vector<Message> messages;
//    Database::getMessage(1, 1, messages);
//    for(auto message :messages){
//        std::cout << message.getMId() << " " << message.getMContent() << " " << message.getFId() << " " << message.getFromId() << " " << message.getToId() << " " << message.getMTime() << std::endl;
//    }

//    JsonTesting::json_parse_request_testing();
//    JsonTesting::json_make_response_testing();

//    NetworkUtils::start_server();

    return 0;
}
