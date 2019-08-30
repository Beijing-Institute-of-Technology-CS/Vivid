cmake_minimum_required(VERSION 3.14)
project(Vivid)

set(CMAKE_CXX_STANDARD 14)

include_directories(client/JsonUtils)
include_directories(client/Utils)
include_directories(client/beans)
include_directories(server)
include_directories(server/Database)
include_directories(server/JsonUtils)
include_directories(server/Network)
include_directories(server/Utils)

add_executable(Vivid
        client/JsonUtils/JsonUtils.cpp
        client/JsonUtils/JsonUtils.h
        client/Utils/cJSON.c
        client/Utils/cJSON.h
        client/client.cpp
        client/CMakeLists.txt
        server/Database/Database.cpp
        server/Database/Database.h
        server/JsonUtils/JsonUtils.cpp
        server/JsonUtils/JsonUtils.h
        server/Network/NetworkUtils.cpp
        server/Network/NetworkUtils.h
        server/Utils/cJSON.c
        server/Utils/cJSON.h
        server/Utils/ThreadPool.h
        server/CMakeLists.txt
        server/server.cpp
        server/User.cpp
        server/User.h)
