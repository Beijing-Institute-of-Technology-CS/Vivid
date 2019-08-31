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

    char *getUName() const;

    char *getUPassword() const;

    int getFIconFile() const;

    void setFIconFile(int fIconFile);

    int getFd() const;

    void setFd(int fd);

    bool isInUse() const;

    void setInUse(bool inUse);

    int getClientIndex() const;

    void setClientIndex(int clientIndex);

    char * uName;
    char * uPassword;

private:
    int uId;

    int fIconFile;
    int fd;

    int client_index;
    bool inUse;
};


#endif //SERVER_USER_H
