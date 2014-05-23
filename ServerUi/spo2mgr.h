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
