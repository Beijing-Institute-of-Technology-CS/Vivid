//
// Created by YichengChen on 8/28/19.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H

#define BUFFER_SIZE 1024

/**
 * When a new connection established, an instance of User will be created
 */
class User {
private:
    bool is_in_use;
    int sd;
    char name[64];
    char buffer[BUFFER_SIZE];
public:
    bool isInUse() const;

    void setIsInUse(bool isInUse);

    int getSd() const;

    void setSd(int sd);

    const char *getName() const;

    const char *getBuffer() const;

    User();
};


#endif //SERVER_USER_H
