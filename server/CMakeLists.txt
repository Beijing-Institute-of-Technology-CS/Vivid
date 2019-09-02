cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 14)

#find_package(MySQL REQUIRED)
#include_directories(${MYSQL_INCLUDE_DIR})

#execute_process(COMMAND mysql_config --cflags
#        OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#execute_process(COMMAND mysql_config --libs
#        OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

add_executable(server server.cpp Beans/User.cpp Beans/User.h Beans/Message.cpp Beans/Message.h NetworkUtils/NetworkUtils.cpp NetworkUtils/NetworkUtils.h
        JsonUtils/JsonUtils.cpp JsonUtils/JsonUtils.h DatabaseUtils/DatabaseUtils.cpp DatabaseUtils/DatabaseUtils.h
        TestUtils/JsonTesting.cpp TestUtils/JsonTesting.h Utils/cJSON.c Utils/cJSON.h Utils/ThreadPool.h ../Constants.h
        Beans/Client.cpp Beans/Client.h NetworkUtils/NetworkUtils.cpp NetworkUtils/NetworkUtils.h Beans/Group.cpp Beans/Group.h
        TestUtils/DatabaseTesting.cpp TestUtils/DatabaseTesting.h
        )

#include_directories(/usr/local/mysql/include)
#link_directories(/usr/local/mysql/lib)
#target_link_libraries(server /usr/local/mysql/lib)

#target_compile_options(server PUBLIC ${MYSQL_CFLAGS})
#target_link_libraries(server ${MYSQL_LIB})

include_directories(/usr/include/mysql)
#link_directories(/usr/local/mysql/lib)
target_link_libraries(server /usr/lib64/mysql mysqlclient pthread m rt dl)