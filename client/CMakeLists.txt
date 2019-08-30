cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(client main.cpp View/TestView/MainView.cpp View/TestView/MainView.h View/LoginView/LoginView.cpp
        View/LoginView/LoginView.h Controller/LoginController/LoginController.cpp
        Controller/LoginController/LoginController.h Controller/MainController.cpp Controller/MainController.h
        ../Constants.h JsonUtils/JsonUtils.h JsonUtils/JsonUtils.cpp)

target_link_libraries(client ${GTK3_LIBRARIES})