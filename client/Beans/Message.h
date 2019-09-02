//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <cstring>
#include "../../Constants.h"

class Message {
public:
    char *uFromUsername;

    char *mContent;

    char *mType;

    char *mTime;

    Message();

    //mType must be initialed
    Message(int mId, char *mContent, int uFromId, char *mType, char *mTime);

    int getMId() const;

    void setMId(int mId);

    char *getMContent() const;

    char *getMType() const;

    bool isGroup() const;

    int getGFromId() const;

    void setGFromId(int gFromId);

    int getUFromId() const;

    void setUFromId(int uFromId);

    int getUToId() const;

    void setUToId(int uToId);

    char *getUFromusername() const;

    int getFId() const;

    void setFId(int fId);

    char *getMTime() const;

private:
    int mId;
    int gFromId;
    int uFromId;
    int uToId;
    int fId;
};


#endif //SERVER_MESSAGE_H
