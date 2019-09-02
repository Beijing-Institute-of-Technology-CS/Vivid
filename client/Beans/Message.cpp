//
// Created by YichengChen on 8/29/19.
//

#include "Message.h"

Message::Message() {}

Message::Message(int mId, char *mContent, int uFromId, char *mType, char *mTime) : mId(mId), mContent(mContent),
                                                                uFromId(uFromId), mType(mType), mTime(mTime) {this->uFromUsername = NULL;}

int Message::getMId() const {
    return mId;
}

void Message::setMId(int mId) {
    Message::mId = mId;
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

char *Message::getMType() const {
    return mType;
}

int Message::getGFromId() const {
    return gFromId;
}

void Message::setGFromId(int gId) {
    Message::gFromId = gId;
}

char *Message::getUFromusername() const {
    return uFromUsername;
}

int Message::getUFromId() const {
    return uFromId;
}

void Message::setUFromId(int uFromId) {
    Message::uFromId = uFromId;
}

bool Message::isGroup() const {
    if(Message::mType != NULL){
        if (std::strcmp(Message::mType, TYPE_GROUP_MESSAGE) == 0)
            return true;
        else
            return false;
    }
    else
        return false;
}

int Message::getUToId() const {
    return Message::uToId;
}

void Message::setUToId(int uToId) {
    Message::uToId = uToId;
}

void Message::setContent(char * ms)
{
    Message::mContent=ms;
}

const char * Message::getMContent() const{
    return Message::mContent;
}

const char * Message::setMTime(char * time)
{
    Message::mTime=time;
}
