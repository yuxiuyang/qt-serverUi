#include "linkmgr.h"
#include <errno.h>
#include "datamgr.h"
#include "mainwindow.h"
LinkMgr::LinkMgr(){
    m_window = NULL;
    m_pDataMgr = NULL;
    m_initServerOk = m_serverNetwork.init();

    //start listen server
    assert(m_initServerOk);
    addFd(getServerFd());
}
LinkMgr::~LinkMgr(){
    for(vector<LinkSocketId*>::iterator iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.begin();){
        delete (*iter);
        m_clientConnectMsgVec.erase(iter);
    }

    m_registerClientSocketFdVec.clear();
}
int LinkMgr::getServerFd(){
    return m_serverNetwork.getServerSocketFd();
}
int LinkMgr::waitAcceptConnect(){
    int clientFd = m_serverNetwork.waitAccept();
    if(-1 == clientFd){
        cout<<"clientFd=-1 accept failure errno="<<errno<<endl;
        recvLinkMsg(Connect_Failure,-1,errno);
        if(EAGAIN == errno){

        }
        return -10;
    }
    recvLinkMsg(Connect_Success,clientFd);

    return 0;
}

bool LinkMgr::registerSocketFd(int socketFd){
    if(isRegister(socketFd))
        return false;
    m_registerClientSocketFdVec.push_back(socketFd);
    return true;
}

bool LinkMgr::unregisterSocketFd(int socketFd){
    vector<int>::iterator iter=find(m_registerClientSocketFdVec.begin(),m_registerClientSocketFdVec.end(),socketFd);
    if(iter == m_registerClientSocketFdVec.end()){
        cout<<"has not register sockFd="<<socketFd<<endl;
        return false;
    }

    m_registerClientSocketFdVec.erase(iter);
    return true;
}
bool LinkMgr::isRegister(int socketFd){//check weather has register
    vector<int>::iterator iter=find(m_registerClientSocketFdVec.begin(),m_registerClientSocketFdVec.end(),socketFd);
    if(iter==m_registerClientSocketFdVec.end()){
        cout<<"this socketFd="<<socketFd<<"has exist"<<endl;
        return true;
    }
    return false;
}
bool LinkMgr::sendToClient(int clientSocket){//send connect or disconnect to client
    return true;
}

LinkSocketId* LinkMgr::findClient(int clientSocket){
    std::vector <LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        if(clientSocket == (*iter)->fd)
            return (*iter);
    }

    return NULL;
}
int LinkMgr::findIdbysocket(int socket){
    std::vector <LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        if(clientSocket == (*iter)->fd)
            return (*iter)->id;
    }
    return -1;
}

int LinkMgr::findClientSocket(ClientType_ type){
    std::vector <LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        if(type == (*iter)->clientId)
            return (*iter)->fd;
    }
    return -1;
}
LinkSocketId* LinkMgr::findClientMsgbyId(ClientType_ clientId){
    std::vector <LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        if(clientId == (*iter)->clientId)
            return (*iter);
    }

    return NULL;
}

bool LinkMgr::removeClientSocket(int clientSocket){
    std::vector <LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        if(clientSocket == (*iter)->fd)
            break;
    }

    if(iter != m_clientConnectMsgVec.end()){
        DataDev::getInstance()->removeFd(clientSocket);
        delete *iter;
        m_clientConnectMsgVec.erase(iter);

        unregisterSocketFd(clientSocket);
        removeFd(clientSocket);
        return true;
    }

    printf("has not exist\n");
    return false;

}

bool LinkMgr::removeLinkMsg(ClientType_ id){
    int fd = findClientSocket(id);
    return removeClientSocket(fd);
}

bool LinkMgr::addClientSocketFd(int clientFd){
    assert(clientFd>0);
    //char msgBuf[100]={0};
    //manage client FD
    if(NULL == findClient(clientFd)){// not exsit
        LinkSocketId* socketId = new LinkSocketId;
        socketId->fd = clientFd;
        socketId->clientId = NONE_CLIENT;
       m_clientConnectMsgVec.push_back(socketId);
       //sprintf(msgBuf,"accept client =%d success",clientFd);
       //((MainWindow*)m_window)->appendMsg(msgBuf);
       addFd(clientFd);
    }else{
        cout<<"this client="<<clientFd<<"has exist"<<endl;
        return true;
    }
    cout<<"accept socket success socket="<<clientFd<<endl;
     return true;
}
void LinkMgr::setWindow(void* win){
    m_window = win;
}
void LinkMgr::getClientSocketFd(int clientFd[],int& len){
    // add active connection to fd set
    len = 0;
    std::vector<LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        //FD_SET(iter->first, &fdSet);
        clientFd[len++] = (*iter)->fd;
    }
}
void LinkMgr::getClientSocketFd(vector<int>* vec){
    assert(vec);
    std::vector<LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        //FD_SET(iter->first, &fdSet);
        //clientFd[len++] = iter->first;
        vec->push_back((*iter)->fd);
    }
}

int LinkMgr::analLinkData(const BYTE* buf,int len){//return fd
    ClientType_ clientId = (ClientType_)buf[3];
    assert(clientId>0);

    return clientId;
}
void LinkMgr::requestLinkMsg(){
    std::vector<LinkSocketId*>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        if((*iter)->clientId==-1){
            sendRequestLink((*iter)->fd);
        }
    }
}
void LinkMgr::sendRequestLink(int fd){
    BYTE tmpBuf[5];
    tmpBuf[0] = 0x99;//start
    tmpBuf[1] = 0x05;//
    tmpBuf[2] = Link_Request;
    tmpBuf[3] = tmpBuf[1]+tmpBuf[2];
    tmpBuf[4] = 0xdd;

    DataDev::getInstance()->sendData(fd,tmpBuf,5);
}

int LinkMgr::data_Arrived(int Fd){
    if(Fd == getServerFd()){
        return waitAcceptConnect();
    }
    BYTE tmpbuf[200]={0};
    int len = recv(Fd,&tmpbuf,sizeof(tmpbuf),0);
    if (len <= 0) {        // client close
          recvLinkMsg(Connect_Close,Fd);
          return -1;
     } else {        // receive data
           //cout<<"server   success rec data from client     fd="<<socket<<endl;

            LinkSocketId* sockId = findClient(fd);
            asset(sockId);
            if(sockId->clientId>0){
                if(m_pDataMgr)
                     ((DataMgr*)m_pDataMgr)->handle(clientId,tmpbuf,len);
            }else{//has not register
                sockId->clientId = analLinkData(tmpbuf,len);

                char msgBuf[100]={0};
                sprintf(msgBuf,"comfirm client id =%d success",sockId->clientId);
                ((MainWindow*)m_window)->appendMsg(msgBuf);
            }

    }
     return 0;

}
void LinkMgr::recvLinkMsg(CONNECT_MSG_TYPE type,int clientFd,int error){
    char msgBuf[100]={0};
    switch(type){
        case Connect_Close:
            assert(clientFd>0);
            removeClientSocket(clientFd);
            close(clientFd);
            sprintf(msgBuf,"close,clientfd=%d",clientFd);
            break;
        case Connect_Failure:
            sprintf(msgBuf,"connect ,error=%d",error);
            break;
        case Connect_Success:
            assert(clientFd>0);
            assert(addClientSocketFd(clientFd));
            sprintf(msgBuf,"accept clientfd=%d",clientFd);
            break;
        case Connect_Error:
            sprintf(msgBuf,"connect error");
            break;
        case Connect_Timeout:
            sprintf(msgBuf,"connect timeout");
            break;
        default:
            sprintf(msgBuf,"connect sernior error");
            break;
    }
    ((MainWindow*)m_window)->appendMsg(msgBuf);
}
LinkState LinkMgr::getLinkState(ClientType_ id){
    if(findClientMsgbyId(id))
        return link_and_comfirmId;

    return dis_link;
}






