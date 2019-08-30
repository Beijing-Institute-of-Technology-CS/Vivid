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
#include "Network/NetworkUtils.h"

#include "../Constants.h"

int main() {
    Database::mql_connect();

//    JsonTesting::json_parse_request_testing();
    JsonTesting::json_make_response_testing();

//    NetworkUtils::start_server();

    return 0;
}
