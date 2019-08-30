//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H


class Message {
public:
    Message();

    Message(int mId, char *mContent, int fId, char *mTime);

    int getMId() const;

    void setMId(int mId);

    char *getMContent() const;

    int getFId() const;

    void setFId(int fId);

    char *getMTime() const;

    int getFromId() const;

    void setFromId(int fromId);

    int getToId() const;

    void setToId(int toId);

    char * mContent;
    char * mTime;


private:
    int mId;
    int fId;

    int fromId;
    int toId;
};


#endif //SERVER_MESSAGE_H
