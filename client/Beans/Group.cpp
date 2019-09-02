//
// Created by 蓝雁 on 2019/9/1.
//

#include "Group.h"

Group::Group() { }

Group::Group(int gId) : gId(gId){ }

int Group::getGId() const{
    return gId;
}

void Group::setGId(int gId) {
    Group::gId = gId;
}

int Group::getUId(){
    return uId;
}

void Group::setUId(int uId){
    Group::uId=uId;
}