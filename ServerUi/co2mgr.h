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

    void display();
    int data_Arrived(int fd);

    char* getCollectDataTmpFile();
    virtual void setTxtValue(const char* val);

protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd,BYTE param);
};

#endif // NIBPMGR_H
