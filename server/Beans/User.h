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

    void setUName(char *uName);

    char *getUPassword() const;

    void setUPassword(char *uPassword);

    int getFIconFile() const;

    void setFIconFile(int fIconFile);

    int getFd() const;

    void setFd(int fd);

private:
    int uId;
    char * uName;
    char * uPassword;
    int fIconFile;
    int fd;
};


#endif //SERVER_USER_H
