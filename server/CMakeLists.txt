cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 14)

add_executable(server server.cpp Beans/User.cpp Beans/User.h Beans/Message.cpp Beans/Message.h NetworkUtils/NetworkUtils.cpp NetworkUtils/NetworkUtils.h
        JsonUtils/JsonUtils.cpp JsonUtils/JsonUtils.h Database/Database.cpp Database/Database.h
        TestUtils/JsonTesting.cpp TestUtils/JsonTesting.h Utils/cJSON.c Utils/cJSON.h Utils/ThreadPool.h ../Constants.h
        Beans/Client.cpp Beans/Client.h NetworkUtils/NetworkUtils.cpp NetworkUtils/NetworkUtils.h Beans/Group.cpp Beans/Group.h
        )