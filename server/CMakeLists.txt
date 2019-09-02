cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 14)

add_executable(server server.cpp Beans/User.cpp Beans/User.h Beans/Message.cpp Beans/Message.h NetworkUtils/NetworkUtils.cpp NetworkUtils/NetworkUtils.h
        JsonUtils/JsonUtils.cpp JsonUtils/JsonUtils.h DatabaseUtils/DatabaseUtils.cpp DatabaseUtils/DatabaseUtils.h
        TestUtils/JsonTesting.cpp TestUtils/JsonTesting.h Utils/cJSON.c Utils/cJSON.h  ../Constants.h
        Beans/Client.cpp Beans/Client.h NetworkUtils/NetworkUtils.cpp NetworkUtils/NetworkUtils.h Beans/Group.cpp Beans/Group.h
        TestUtils/DatabaseTesting.cpp TestUtils/DatabaseTesting.h
        )


#include_directories(/usr/local/mysql/include)
#link_directories(/usr/local/mysql/lib)
#target_link_libraries(server /usr/local/mysql/lib)

#include_directories(/usr/include/mysql)
#link_directories(/usr/lib64/mysql)
#target_link_libraries(server /usr/lib64/mysql pthread m rt dl)