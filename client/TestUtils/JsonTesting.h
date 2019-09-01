//
// Created by 蓝雁 on 2019/9/1.
//

#ifndef CLIENT_JSONTESTING_H
#define CLIENT_JSONTESTING_H

#include "../JsonUtils/JsonUtils.h"
#include <iostream>
#include "../../Constants.h"
#include "../Utils/cJSON.h"

class JsonTesting{
public:
    static void test_make_request_json();

    static void test_parse_response_json();
};

#endif //CLIENT_JSONTESTING_H
