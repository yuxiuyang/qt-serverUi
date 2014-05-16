#ifndef RECVOBJECT_H
#define RECVOBJECT_H

class RecvObject
{
public:
    RecvObject();
    virtual ~RecvObject();

    virtual int data_Arrived(int fd)=0;

    bool addFd(int fd);
    bool removeFd(int fd);
};

#endif // RECVOBJECT_H
