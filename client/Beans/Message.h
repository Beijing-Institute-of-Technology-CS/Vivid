//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H


class Message {
public:
    char *uFromUsername;

    char *mContent;

    //todo: bool getMType()   (strcmp)
    char *mType;

    char *mTime;

    Message();

    //mType must be initialed
    Message(int mId, char *mContent, int fId, char *mTime);

    int getMId() const;

    void setMId(int mId);

    char *getMContent() const;

    char *getMType() const;

    int getGFromId() const;

    void setGFromId(int gFromId);

    int getUFromId() const;

    void setUFromId(int uFromId);

    char *getUFromusername() const;

    int getFId() const;

    void setFId(int fId);

    char *getMTime() const;

private:
    int mId;
    int gFromId;
    int uFromId;
    int fId;
};//todo: toId...


#endif //SERVER_MESSAGE_H
