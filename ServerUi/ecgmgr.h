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

    void display();
    int data_Arrived(int fd);

    char* getCollectDataTmpFile();

    virtual void setTxtValue(const char* val);
    virtual void setTxtAlarm(const char* val);
protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd,BYTE param);
};

#endif // NIBPMGR_H
