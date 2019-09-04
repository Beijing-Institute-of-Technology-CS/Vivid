//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H


class User {
public:
    User();

    User(int uId, char *uName, char *uPassword, int fIconFile);

    int getUId() const;

    void setUId(int uId);

    const char *getUName() const;

    const char *getUPassword() const;

    int getFIconFile() const;

    void setFIconFile(int fIconFile);

    bool isInUse() const;

    void setInUse(bool inUse);

    int getClientIndex() const;

    void setClientIndex(int clientIndex);

    void setUName(char *uName);

    void setUPassword(char *uPassword);

    void setLatestMessage(int mid);

    int getLatestMessage();


private:
    int uId;

    int fIconFile;

    /**
     * for server use only
     */
    int client_index;
    bool inUse;
    /**
     *
     */

    char * uName=nullptr;
    char * uPassword=nullptr;
    int latestMessageID;

};


#endif //SERVER_USER_H
