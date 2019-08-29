cmake_minimum_required(VERSION 3.13)
project(server)

set(CMAKE_CXX_STANDARD 11)

add_executable(server server.cpp Database/Database.cpp Database/Database.h JsonUtils/JsonUtils.cpp
        JsonUtils/JsonUtils.h JsonUtils/JsonUtils.cpp JsonUtils/JsonUtils.h Network/NetworkUtils.cpp Network/NetworkUtils.h User.cpp User.h)

INCLUDE_DIRECTORIES(/usr/local/mysql/include)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")