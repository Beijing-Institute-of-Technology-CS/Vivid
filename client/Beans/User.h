//
// Created by YichengChen on 8/29/19.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H


class User {
public:
    char *uName;
    char *uPassword;

    User();
    User(int uId, char *uName, char *uPassword, int fIconFile);

    int getUId() const;

    void setUId(int uId);

    char *getUName() const;

    char *getUPassword() const;

    int getFIconFile() const;

    void setFIconFile(int fIconFile);

private:
    int uId;
    int fIconFile;
};


#endif //SERVER_USER_H
