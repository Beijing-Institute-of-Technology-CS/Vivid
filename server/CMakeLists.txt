cmake_minimum_required(VERSION 3.14)
project(server)

set(CMAKE_CXX_STANDARD 14)

add_executable(server server.cpp Beans/User.cpp Beans/User.h Beans/Message.cpp Beans/Message.h Network/NetworkUtils.cpp Network/NetworkUtils.h
        JsonUtils/JsonUtils.cpp JsonUtils/JsonUtils.h Database/Database.cpp Database/Database.h
        TestUtils/JsonTesting.cpp TestUtils/JsonTesting.h Utils/cJSON.c Utils/cJSON.h Utils/ThreadPool.h Constants.h)