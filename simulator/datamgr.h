#ifndef DATAMGR_H
#define DATAMGR_H
#include "../include/define.h"
#include "linkmgr.h"
#include "nibpmgr.h"
#include "spo2mgr.h"
#include "ecgmgr.h"
#include "ibpmgr.h"
#include "co2mgr.h"
#include "narcomgr.h"
#include <QTimer>
#include <QObject>
class DataMgr:public QObject
{
    Q_OBJECT
public:
    DataMgr();
    ~DataMgr();
public Q_SLOTS:
    void _onWriteTimeout();
public:
    void setWindow(void*);
    void handle(ClientType_ id,const BYTE* buf,int len);
    void generateTestFile(ClientType_ type);
    BasicMgr* getMgrbyId(ClientType_ type);
    NibpMgr* m_pNibpMgr;
    Spo2Mgr* m_pSpo2Mgr;
    EcgMgr*  m_pEcgMgr;
    IbpMgr*  m_pIbpMgr;
    Co2Mgr*  m_pCo2Mgr;
    NarcoMgr* m_pNarcoMgr;
    LinkMgr* m_pLinkMgr;

    int sendCmd(BYTE cmd,BYTE param);
protected:


private:
    QTimer* m_pTimer;
    void* m_pWindow;


    vector<void*> m_vecObject;
};

#endif // DATAMGR_H
