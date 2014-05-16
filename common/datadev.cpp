#include "datadev.h"

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "fltkLog.h"
#include <iostream>
using namespace std;
fltkLog log;

DataDev* DataDev::m_instance = new DataDev();
DataDev::DataDev(QObject *parent) :
        QThread(parent)
{
    m_pDataJob = GetJobNest();
    assert(m_pDataJob);


    m_pthreadState = THREAD_NOTSTART;

    printf("this = %lu\n",this);
}
DataDev::~DataDev(){
    for(vector<CALLBACK_FD*>::iterator iter=m_callbackFdVec.begin();iter!=m_callbackFdVec.end();){
        close((*iter)->fd);
        delete (*iter);
        m_callbackFdVec.erase(iter);
    }
}
void DataDev::start ( Priority priority ){
    if(!m_callbackFdVec.empty()){
        log.Write("start......");
        QThread::start(priority);
    }
    m_pthreadState = THREAD_RUNNING;
}
void DataDev::stop(){
    m_pthreadState = THREAD_NOTSTART;
    terminate();
}

DataDev* DataDev::getInstance(){
    return m_instance;
}
void DataDev::run(){//device recv data
    log.Write("thread run start thread=%lu",pthread_self());
    recvData();
    log.Write("thread run end thread=%lu",pthread_self());
}


void DataDev::recvData(){
    fd_set fdSet;
    int ret = -1;
    struct timeval tv;
    int maxFd = -1;
    while(THREAD_RUNNING == m_pthreadState){
        // initialize file descriptor set
        FD_ZERO(&fdSet);
        // timeout setting
       tv.tv_sec = 10000;
       tv.tv_usec = 0;

       maxFd = -1;
        // add active connection to fd set
       for(vector<CALLBACK_FD*>::iterator iter=m_callbackFdVec.begin();iter!=m_callbackFdVec.end();){
           if((*iter)->isNeedToDelete || !isValidateFd((*iter)->fd)){//has remove,so should delete it
               close((*iter)->fd);
               delete (*iter);
               m_callbackFdVec.erase(iter);
               log.Write("removeFd fd=%d",(*iter)->fd);
               continue;
           }
           sockaddr_in addrMy;
            memset(&addrMy,0,sizeof(addrMy));
            socklen_t len = sizeof(addrMy);

            if(-1 == getsockname((*iter)->fd,(sockaddr*)&addrMy,&len)){
                log.Write("start listen a closed socket fd=%d",(*iter)->fd);
            }

           //add active connection to fd set
           FD_SET((*iter)->fd, &fdSet);
           if(maxFd<(*iter)->fd){
                maxFd = (*iter)->fd;
            }
           //log.Write("start listen fd=%d",(*iter)->fd);
           iter++;
       }

       ret = select(maxFd + 1, &fdSet, NULL, NULL, &tv);
        if (ret < 0) {
            printf("select error,ret=%d\n",ret);
            sleep(1);
            continue;
        } else if (ret == 0) {
            //cout<<"time out"<<endl;
            continue;
        }

        // check every active client fd in the set
        for(int i=0;i<m_callbackFdVec.size();i++){
            if (FD_ISSET(m_callbackFdVec[i]->fd, &fdSet)) {
                //cout<<"select success m_callbackFdVec[i]="<<m_callbackFdVec[i]<<endl;
                log.Write("select success m_callbackFdVec[i].fd=%d",m_callbackFdVec[i]->fd);
                if(m_callbackFdVec[i]->object){
                    m_callbackFdVec[i]->object->data_Arrived(m_callbackFdVec[i]->fd);
                }else if(m_callbackFdVec[i]->callBack_)
                m_callbackFdVec[i]->callBack_(m_callbackFdVec[i]->fd);

                if(!checkRecvFd(m_callbackFdVec[i]->fd))  removeFd(m_callbackFdVec[i]->fd);

            }
        }
    }
}

void DataDev::sendData(int fd,const BYTE* buf,int len){
    if(fd<=0)return;
    //cout<<"sendData fd="<<fd<<endl;
    if(!isValidateFd(fd)) return;
    m_sendMutex.lock();

    //驱动任务巢
    CJobPkg* pkg=m_pDataJob->GetJobPkg(0);
    assert(pkg);


    INFO_DATA* pci=(INFO_DATA*)pkg->Alloc(sizeof(INFO_DATA));
    assert(pci);
    pci->buf = new BYTE[len];
    pci->fd = fd;
    pci->len = len;
    pci->pThis = this;
    memcpy(pci->buf,buf,sizeof(BYTE)*len);


    pkg->SetExecFunction(sendData_);
    pkg->SetExecParam(pci);
    pkg->SetID(1);//different thread have different source. as to this ID ,can delete the soucre.

    m_pDataJob->SubmitJobPkg(pkg);

    m_sendMutex.unlock();
}

bool DataDev::checkData(const BYTE* buf,const int len,const BYTE value){
    BYTE sum=0x00;
    for(int i=0;i<len;i++){
        sum += buf[i];
    }

    return sum==value?true:false;
}

void DataDev::sendData_(void* pv){
    INFO_DATA* dataMsg = (INFO_DATA*)pv;
    assert(dataMsg);


    int total = 0;
    int len = dataMsg->len;
    while(1){
        int size = send(dataMsg->fd,dataMsg->buf+total,len,0);
        if(size<=0){
            cout<<"maybe a error  send failure,and close fd="<<dataMsg->fd<<endl;
            close(dataMsg->fd);
        }
        total += size;
        if(size<len){
            len -= size;
            continue;
        }else{
            break;
        }
    }
}
void DataDev::sendTestData(int type){
    BYTE tmp[3];
    tmp[0] = 0x99;
    tmp[1] = 0x88;
    tmp[2] = 0x77;
    int socket = 23;
    int size = send(m_callbackFdVec[type]->fd,tmp,3,0);
    log.Write("fd=%d,size=%d   send success",m_callbackFdVec[type]->fd,size);
    if(size<=0){
        cout<<"main window send failure\n";
    }
    return;
}

bool DataDev::addFd(const int fd,int(*callback)(int)){
    m_socketFdMutex.lock();
    CALLBACK_FD* iter = findFd(fd);
    if(iter){
        //cout<<"addClientFd has exist fd="<<fd<<endl;
        iter->reset();
        iter->callBack_ = callback;
        m_socketFdMutex.unlock();
        return true;
    }

    CALLBACK_FD *p = new CALLBACK_FD;
    p->callBack_ = callback;
    p->fd = fd;

    m_callbackFdVec.push_back(p);
    if(m_pthreadState!=THREAD_NOTSTART && m_pthreadState!=THREAD_RUNNING){
        m_pthreadState = THREAD_RUNNING;
        start();
    }
    m_socketFdMutex.unlock();
}

bool DataDev::addFd(RecvObject* object,const int fd){
    m_socketFdMutex.lock();
    CALLBACK_FD* iter = findFd(fd);
    if(iter){
        //cout<<"33  addClientFd has exist fd="<<fd<<endl;
        iter->reset();//first reset
        iter->object = object;
        m_socketFdMutex.unlock();
        return true;
    }

    CALLBACK_FD *p = new CALLBACK_FD;
    p->object = object;
    p->fd = fd;

    m_callbackFdVec.push_back(p);
    if(m_pthreadState!=THREAD_NOTSTART){
        m_pthreadState = THREAD_RUNNING;
        start();
    }
    m_socketFdMutex.unlock();
}
bool DataDev::removeFd(int fd){
    return true;
    m_socketFdMutex.lock();

    for(vector<CALLBACK_FD*>::iterator iter=m_callbackFdVec.begin();iter!=m_callbackFdVec.end();iter++){
        if((*iter)->fd == fd){
            (*iter)->isNeedToDelete = true;
//            delete *iter;
//            m_callbackFdVec.erase(iter);
        }
    }
    if(m_callbackFdVec.empty()){//stop thread
        m_pthreadState = THREAD_STOP;
    }
    m_socketFdMutex.unlock();
    return true;
}
bool DataDev::removeAll(RecvObject* object){//when object is null,and delete all.
    return true;
    m_socketFdMutex.lock();
    if(!object){//remove all fd
        for(vector<CALLBACK_FD*>::iterator iter=m_callbackFdVec.begin();iter!=m_callbackFdVec.end();){
//            delete *iter;
//            m_callbackFdVec.erase(iter);
            (*iter)->isNeedToDelete = true;
        }
    }else{
        for(vector<CALLBACK_FD*>::iterator iter=m_callbackFdVec.begin();iter!=m_callbackFdVec.end();){
            if((*iter)->object == object){
//                delete *iter;
//                m_callbackFdVec.erase(iter);
                (*iter)->isNeedToDelete = true;
            }
        }
    }

    if(m_callbackFdVec.empty())//no client fd needed to listen
        m_pthreadState = THREAD_STOP;


    m_socketFdMutex.unlock();
    return true;
}
CALLBACK_FD* DataDev::findFd(int fd){
    for(int i=0;i<m_callbackFdVec.size();i++){
        if(fd == m_callbackFdVec[i]->fd){
            return m_callbackFdVec[i];
        }
    }
    return NULL;
}
bool DataDev::displayRemoteClientSocketMsg(int socketFd){
    char bufTmp[200]={0};
    sockaddr_in addrMy;
     memset(&addrMy,0,sizeof(addrMy));
     socklen_t len = sizeof(addrMy);

     int ret = getsockname(socketFd,(sockaddr*)&addrMy,&len);
     //int ret = getpeername(socketFd,(sockaddr*)&addrMy,&len);
     if (ret != 0)
     {
       cout<<"Getsockname Error!"<<endl;
       log.Write("Get Sockname error,sockFd=%d,errno=%d",socketFd,errno);
       return -1;
     }

     if(addrMy.sin_family != AF_INET)
     {
        sprintf(bufTmp, "Not an Internet socket.");
        log.Write(bufTmp);
        return -1;
     }
     sprintf(bufTmp, "socket=%d ==> address is: %s : %d", socketFd, inet_ntoa(addrMy.sin_addr), ntohs(addrMy.sin_port));
     log.Write(bufTmp);
     return 0;

}

bool DataDev::isValidateFd(int Fd){
    if(Fd<=0) return false;
    sockaddr_in addrMy;
    memset(&addrMy,0,sizeof(addrMy));
    socklen_t socklen = sizeof(addrMy);

    if(-1 == getsockname(Fd,(sockaddr*)&addrMy,&socklen)){
        cout<<"has listen the close has closed fd="<<Fd<<endl;
        return false;
    }
    return true;
}
bool DataDev::checkRecvFd(int Fd){
    if(Fd<=0) return false;

    //displayRemoteClientSocketMsg(Fd);

    BYTE buf[100];
    int len = recv(Fd,buf,sizeof(buf),MSG_PEEK);
    if(len==0){//this client socket has closed
        log.Write("isValidatefd listen success and close fd=%d",Fd);
        return false;
    }
    return true;
}
