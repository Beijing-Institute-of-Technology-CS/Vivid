//
// Created by YichengChen on 8/29/19.
//
#include <iostream>
#include "JsonTesting.h"
#include "../JsonUtils/JsonUtils.h"
#include "../../Constants.h"

#include <vector>

void JsonTesting::json_parse_request_testing() {

}

void JsonTesting::json_make_response_testing() {
    std::cout << JsonUtils::make_response_register_json(TRUE_CONTENT,1) << std::endl;

    std::cout << JsonUtils::make_response_login_json(FALSE_CONTENT,"cyc") << std::endl;

    std::vector <User> v_users;

    v_users.emplace_back(User(1, "cyc", "password", 3));
    v_users.emplace_back(User(2, "zhc", "passwordddd", 5));

    std::vector <Group> v_groups;

    v_groups.emplace_back(Group(1));
    v_groups.emplace_back(Group(2));

    std::cout << JsonUtils::make_response_getInfo_json(FALSE_CONTENT, 9, v_users,v_groups) << std::endl;

    std::vector<Message> v_messages;

    v_messages.emplace_back(Message(1,0,1,2,0, false,"???","sj","cyc"));
    v_messages.emplace_back(Message(2,0,2,3,0, false,"777","sj2","zhc"));

    std::cout << JsonUtils::make_response_getMessages_json(TRUE_CONTENT,v_messages);

    Message message(3,0,3,2,0, false,"no","sj3","jkjkjk");

    std::cout << JsonUtils::make_response_sendMessages_json(TRUE_CONTENT,message);
    std::cout << JsonUtils::make_response_receiveMessages_json(FALSE_CONTENT,message);

    std::cout << JsonUtils::make_response_adduIdToGroup_json(FALSE_CONTENT);
}
