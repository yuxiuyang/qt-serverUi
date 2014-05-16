#ifndef IBPMGR_H
#define IBPMGR_H
#include "basicmgr.h"
class IbpMgr : public BasicMgr
{
public:
        IbpMgr(LinkMgr* pMgr);
    virtual ~IbpMgr();

public:
    void onTimer();
    void sendData(const BYTE* msg,int len);

    void display();
    int data_Arrived(int fd);

protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd);
};

#endif // NIBPMGR_H