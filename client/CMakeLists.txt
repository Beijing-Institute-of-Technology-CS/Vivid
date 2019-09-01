cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

link_libraries(pthread)
link_libraries(dl)

add_executable(client main.cpp View/TestView/TestView.cpp View/TestView/TestView.h View/LoginView/LoginView.cpp
        View/LoginView/LoginView.h Controller/LoginController/LoginController.cpp
        Controller/LoginController/LoginController.h Controller/MainController.cpp Controller/MainController.h
        ../Constants.h JsonUtils/JsonUtils.h JsonUtils/JsonUtils.cpp Utils/cJSON.c Utils/cJSON.h
        Beans/Message.cpp Beans/Message.h Beans/User.cpp Beans/User.h View/TipView/TipView.cpp View/TipView/TipView.h View/RegisterView/RegisterView.cpp View/RegisterView/RegisterView.h Controller/ApplicationExitCallback.h
        View/MainView/MainView.cpp View/MainView/MainView.h View/MainView/List/MessageList/MessageList.cpp View/MainView/List/MessageList/MessageList.h View/MainView/List/FriendList/FriendList.cpp View/MainView/List/FriendList/FriendList.h
        Database/database.cpp Database/database.h Database/sqlite3ext.h Database/sqlite3.h Database/sqlite3.c)

target_link_libraries(client ${GTK3_LIBRARIES})