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

    char* getCollectDataTmpFile();
protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd);

private:
    bool m_start;
};

#endif // NIBPMGR_H
