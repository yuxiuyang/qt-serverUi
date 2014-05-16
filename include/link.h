#ifndef LINK_H
#define LINK_H
#include "define.h"
class Link{
    int fd;
    LinkSource_ comeForm;
    ClientType_ type;
    bool isConnect;
    char clientIp[30];
    int clientId;
};

#endif // LINK_H
