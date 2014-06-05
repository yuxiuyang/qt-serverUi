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

    void setPatientType(const char* buf){
        m_patientType = buf;
    }
    const char* getPatientType(){
        return m_patientType.c_str();
    }

protected:
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void analyseCmd(BYTE cmd,BYTE param);

    string m_patientType;
private:

};

#endif // NIBPMGR_H
