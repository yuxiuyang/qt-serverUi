#ifndef CO2MGR_H
#define CO2MGR_H
#include "basicmgr.h"
class Co2Mgr : public BasicMgr
{
public:
        Co2Mgr(LinkMgr* pMgr);
    virtual ~Co2Mgr();

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
