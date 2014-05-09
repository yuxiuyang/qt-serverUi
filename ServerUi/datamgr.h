#ifndef DATAMGR_H
#define DATAMGR_H
#include "../include/define.h"
#include "linkmgr.h"
#include "nibpmgr.h"
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
    int open_block();
    bool anal_pag(const BYTE* buf,const int len);
    bool anal_DataPag(const BYTE* buf,const int len);
    bool anal_ConnectPag(const BYTE* buf,const int len);
    void setWindow(void*);
    void handle(const BYTE* buf,int len);
    void generateTestFile(ClientType_ type);
    BasicMgr* getMgrbyId(ClientType_ type);
    NibpMgr* m_pNibpMgr;
    LinkMgr* m_pLinkMgr;
protected:

    void addBuf(const BYTE* buf,int len);


private:
    BYTE m_dataBuf[MAX_DATA_BUF];
    int m_curPos;

    QTimer* m_pTimer;
    void* m_pWindow;


    vector<void*> m_vecObject;
};

#endif // DATAMGR_H
