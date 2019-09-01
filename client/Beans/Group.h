//
// Created by 蓝雁 on 2019/9/1.
//

#ifndef CLIENT_GROUP_H
#define CLIENT_GROUP_H

class Group{
private:
    int gId;
public:
    Group();

    Group(int gId);

    int getGId() const;

    void setGId(int gId);
};

#endif //CLIENT_GROUP_H
