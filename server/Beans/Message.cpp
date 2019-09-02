//
// Created by YichengChen on 8/29/19.
//

#include <cstdlib>
#include <cstring>
#include "Message.h"

Message::Message() {}

int Message::getMId() const {
    return mId;
}

void Message::setMId(int mId) {
    Message::mId = mId;
}

char *Message::getMContent() const {
    return mContent;
}

int Message::getFId() const {
    return fId;
}

void Message::setFId(int fId) {
    Message::fId = fId;
}

char *Message::getMTime() const {
    return mTime;
}

bool Message::isGroupMessage() const {
    return groupMessage;
}

void Message::setGroupMessage(bool groupMessage) {
    Message::groupMessage = groupMessage;
}

int Message::getGId() const {
    return gId;
}

void Message::setGId(int gId) {
    Message::gId = gId;
}

int Message::getUFromId() const {
    return uFromId;
}

void Message::setUFromId(int uFromId) {
    Message::uFromId = uFromId;
}

int Message::getUToId() const {
    return uToId;
}

void Message::setUToId(int uToId) {
    Message::uToId = uToId;
}

void Message::setMContent(char *mContent) {
    this->mContent = (char *)malloc(sizeof(char)*(strlen(mContent)+1));
    strcpy(this->mContent,mContent);
}

void Message::setMTime(char *mTime) {
    this->mTime = (char *)malloc(sizeof(char)*(strlen(mTime)+1));
    strcpy(this->mTime,mTime);
}

void Message::setUFromUsername(char *uFromUsername) {
    this->uFromUsername = (char *)malloc(sizeof(char)*(strlen(uFromUsername)+1));
    strcpy(this->uFromUsername,uFromUsername);
}

char *Message::getUFromUsername() const {
    return uFromUsername;
}

