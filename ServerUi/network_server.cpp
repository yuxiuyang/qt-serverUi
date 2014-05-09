#include "network_server.h"
#include <assert.h>
#include <iostream>
#include <signal.h>
using namespace std;

Network_Server::Network_Server(int port)
{
    m_serverSockFd = -1;
    m_serverPort = port;
}
Network_Server::~Network_Server()
{
    stop();
}
bool Network_Server::init(){
    //return true;
    printf("Hello,welcome to my server !\r\n");
    m_serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == m_serverSockFd)
    {
        printf("socket fail ! \r\n");
        return false;
    }
    printf("socket ok !\r\n");


    bzero(&m_serverAddress,sizeof(struct sockaddr_in));
    m_serverAddress.sin_family=AF_INET;
    m_serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    m_serverAddress.sin_port=htons(m_serverPort);

    if(-1 == bind(m_serverSockFd,(struct sockaddr *)(&m_serverAddress), sizeof(struct sockaddr)))
    {
        printf("bind fail !\r\n");
        return false;
    }
    printf("bind ok !\r\n");

    if(-1 == listen(m_serverSockFd,5))
    {
        printf("listen fail !\r\n");
        return false;
    }
    //忽略SIGPIPE 信号
    signal(SIGPIPE,SIG_IGN);
    printf("listen ok\r\n");
    return true;
}
int Network_Server::waitAccept(){
    if(m_serverSockFd==-1){
        cout<<"please init server first"<<endl;
        return -1;
    }
    struct sockaddr_in client_addr;
    socklen_t addrLen=sizeof(struct sockaddr_in);
    return accept(m_serverSockFd, (struct sockaddr *)(&client_addr), &addrLen);
}
void Network_Server::stop(){
    if(m_serverSockFd != -1){
        cout<<"close server socket="<<m_serverSockFd<<endl;
        close(m_serverSockFd);
    }

    m_serverSockFd = -1;
}
