#ifndef NIBPMGR_H
#define NIBPMGR_H
#include "basicmgr.h"
class NibpMgr : public BasicMgr
{
public:
    NibpMgr(LinkMgr* pMgr);
    virtual ~NibpMgr();

public:
    void onTimer();
    void sendData(const BYTE* msg,int len);

    void display();
    int data_Arrived(int fd);

protected:

private:

};

#endif // NIBPMGR_H
