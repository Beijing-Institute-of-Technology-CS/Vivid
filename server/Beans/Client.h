//
// Created by YichengChen on 8/30/19.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H


class Client {
public:
    Client();

    int getFd() const;

    void setFd(int fd);

    int getUId() const;

    void setUId(int uId);

private:
    int fd;
    int uId;
};


#endif //SERVER_CLIENT_H
