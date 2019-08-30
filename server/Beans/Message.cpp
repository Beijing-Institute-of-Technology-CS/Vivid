//
// Created by YichengChen on 8/29/19.
//

#include "Message.h"

Message::Message() {}

Message::Message(int mId, char *mContent, int fId, char *mTime) : mId(mId), mContent(mContent), fId(fId),
                                                                  mTime(mTime) {}

int Message::getMId() const {

}

void Message::setMId(int mId) {
    Message::mId = mId;
}

char *Message::getMContent() const {
    return mContent;
}

void Message::setMContent(char *mContent) {
    Message::mContent = mContent;
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

void Message::setMTime(char *mTime) {
    Message::mTime = mTime;
}

int Message::getFromId() const {
    return fromId;
}

void Message::setFromId(int fromId) {
    Message::fromId = fromId;
}

int Message::getToId() const {
    return toId;
}

void Message::setToId(int toId) {
    Message::toId = toId;
}
