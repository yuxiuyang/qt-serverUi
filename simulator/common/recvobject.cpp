#include "recvobject.h"
#include "datadev.h"

RecvObject::RecvObject()
{
}

RecvObject::~RecvObject()
{
    DataDev::getInstance()->removeAll(this);
}
bool RecvObject::addFd(int fd){
    DataDev::getInstance()->addFd(this,fd);
}

bool RecvObject::removeFd(int fd){
    DataDev::getInstance()->removeFd(fd);
}

