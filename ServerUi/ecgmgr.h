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
protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd,BYTE param);

    QString m_ecgValues;
    QString m_ecgAlarms;
};

#endif // NIBPMGR_H
