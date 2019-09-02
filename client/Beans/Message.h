//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H


class Message {
public:
    Message();

    Message(int mId, int fId, int uFromId, int uToId, int gId, bool groupMessage, char *mContent, char *mTime,
            char *uFromUsername);

    int getMId() const;

    void setMId(int mId);

    const char *getContent() const;

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

    void setMContent(char *mContent);

    void setMTime(char *mTime);

    void setUFromUsername(char *uFromUsername);

    char *getUFromUsername() const;

    void setContent(char *ms);

    const char *setMTime(char *time);
private:
    int mId;
    int fId;

    int uFromId;
    int uToId;

    int gId;

    bool groupMessage;

    char * mContent;

    char * mTime;

    char * uFromUsername;

};


#endif //SERVER_MESSAGE_H
