//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H


class User {
public:
    User();
    User(int uId, char *uName, char *uPassword, char *fIconFile);

private:
    int uId;
    char * uName;
    char * uPassword;
public:
    int getUId() const;

    void setUId(int uId);

    char *getUName() const;

    void setUName(char *uName);

    char *getUPassword() const;

    void setUPassword(char *uPassword);

    char *getFIconFile() const;

    void setFIconFile(char *fIconFile);

private:
    char * fIconFile;
};


#endif //SERVER_USER_H
