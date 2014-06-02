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

    void display();
    int data_Arrived(int fd);

    char* getCollectDataTmpFile();

    virtual void setTxtValue(const char* val);
protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd,BYTE param);

private:
    bool m_start;
};

#endif // NIBPMGR_H
