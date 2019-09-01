//
// Created by YichengChen on 8/29/19.
//

#include "Message.h"

Message::Message() {}
//todo: initialize mType uFromUsername?
Message::Message(int mId, char *mContent, int fId, char *mTime) : mId(mId), mContent(mContent), fId(fId),
                                                                  mTime(mTime) {}

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
