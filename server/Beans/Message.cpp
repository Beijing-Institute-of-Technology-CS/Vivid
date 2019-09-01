//
// Created by YichengChen on 8/29/19.
//

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

int Message::getUUoId() const {
    return uUoId;
}

void Message::setUUoId(int uUoId) {
    Message::uUoId = uUoId;
}
