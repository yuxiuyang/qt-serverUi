#ifndef ECGMGR_H
#define ECGMGR_H
#include "basicmgr.h"
class EcgMgr : public BasicMgr
{
public:
    EcgMgr(LinkMgr* pMgr);
    virtual ~EcgMgr();

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
