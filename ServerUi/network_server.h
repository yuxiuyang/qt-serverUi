#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include "../include/define.h"
class Network_Server
{
public:
    Network_Server(int port=8090);
    ~Network_Server();


public:
    bool init();
    int waitAccept();
    void stop();
    int getServerSocketFd(){
        return m_serverSockFd;
    }
private:
    int m_serverSockFd;
    unsigned short m_serverPort;
    struct sockaddr_in m_serverAddress;


};

#endif // NETWORK_SERVER_H
