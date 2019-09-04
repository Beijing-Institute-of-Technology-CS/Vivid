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

add_executable(client main.cpp View/LoginView/LoginView.cpp
        View/LoginView/LoginView.h Controller/LoginController/LoginController.cpp
        Controller/LoginController/LoginController.h Controller/MainController.cpp Controller/MainController.h
        ../Constants.h JsonUtils/JsonUtils.h JsonUtils/JsonUtils.cpp Utils/cJSON.c Utils/cJSON.h
        Beans/Message.cpp Beans/Message.h Beans/User.cpp Beans/User.h View/TipView/TipView.cpp View/TipView/TipView.h View/RegisterView/RegisterView.cpp View/RegisterView/RegisterView.h
        View/MainView/MainView.cpp View/MainView/MainView.h View/MainView/List/FriendList/FriendList.cpp View/MainView/List/FriendList/FriendList.h View/MainView/List/GroupList/GroupList.cpp View/MainView/List/GroupList/GroupList.h
        Database/database.cpp Database/database.h Database/sqlite3ext.h Database/sqlite3.h Database/sqlite3.c Beans/Group.cpp Beans/Group.h TestUtils/JsonTesting.cpp TestUtils/JsonTesting.h
        Network/NetworkUtils.cpp Network/NetworkUtils.h Controller/NetworkController/NetworkController.cpp Controller/NetworkController/NetworkController.h TestUtils/NetworkCallbackTesting.cpp TestUtils/NetworkCallbackTesting.h
        View/MainView/ChatView/ChatView.cpp View/MainView/ChatView/ChatView.h View/MainView/List/GroupList/GroupList.cpp View/MainView/List/GroupList/GroupList.h Utils/CSSUtils.cpp Utils/CSSUtils.h)

#set(ENV{PKG_CONFIG_PATH} /usr/local/Cellar/libffi/3.2.1/lib/pkgconfig)

target_link_libraries(client ${GTK3_LIBRARIES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/View/LoginView/login.xml
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/View/ViewStyle.css
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/View/Assets/close_btn_icon.png
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/View/Assets/next_btn_icon.png
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/View/Assets/logo.png
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)