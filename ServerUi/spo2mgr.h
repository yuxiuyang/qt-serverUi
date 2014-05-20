#ifndef SPO2MGR_H
#define SPO2MGR_H
#include "basicmgr.h"
class Spo2Mgr : public BasicMgr
{
public:
        Spo2Mgr(LinkMgr* pMgr);
    virtual ~Spo2Mgr();

public:
    void onTimer();
    void sendData(const BYTE* msg,int len);

    void display();
    int data_Arrived(int fd);

    char* getCollectDataTmpFile();
protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd);
};

#endif // NIBPMGR_H
