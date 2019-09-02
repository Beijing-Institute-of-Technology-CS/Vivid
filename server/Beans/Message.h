//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H


class Message {
public:
    Message();

    Message(int mId, char *mContent, int uFromId, bool groupMessage, char *mTime);

    int getMId() const;

    void setMId(int mId);

    char *getMContent() const;

    int getFId() const;

    void setFId(int fId);

    char *getMTime() const;

    int getUFromId() const;

    void setUFromId(int uFromId);

    int getUToId() const;

    void setUToId(int uToId);

    bool isGroupMessage() const;

    void setGroupMessage(bool groupMessage);

    int getGId() const;

    void setGId(int gId);

    char * mContent;

    char * mTime;

    char *uFromUsername;

private:
    int mId;
    int fId;

    int uFromId;
    int uToId;

    /**
     * should be the same
     */
    int gId;

    bool groupMessage;

};


#endif //SERVER_MESSAGE_H
