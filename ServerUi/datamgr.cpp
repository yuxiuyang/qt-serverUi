#include "datamgr.h"
#include "../common/datadev.h"
#include "mainwindow.h"

#include <string>
using namespace std;

DataMgr::DataMgr()
{
    //DataDev::getInstance()->setCallback(recvData);
    memset(&m_dataBuf,0,sizeof(m_dataBuf));
    m_curPos = 0;


    m_pTimer = new QTimer();
    connect( m_pTimer, SIGNAL(timeout()), this, SLOT(_onWriteTimeout()) );
    m_pTimer->start(2);//2mms
    m_pLinkMgr = new LinkMgr();
    m_pLinkMgr->m_pDataMgr = this;
    m_pNibpMgr = new NibpMgr(m_pLinkMgr);
    assert(m_pNibpMgr);
    m_pNibpMgr->setFrequency(1);
    m_pNibpMgr->setReadNum(4);

    m_vecObject.push_back(m_pNibpMgr);
}
DataMgr::~DataMgr()
{
    delete m_pLinkMgr;
    m_pLinkMgr = NULL;
    delete m_pNibpMgr;
    m_pNibpMgr = NULL;
}

void DataMgr::handle(ClientType_ id,const BYTE* buf,int len){
    BasicMgr* mgr = getMgrbyId(id);
    assert(mgr);
    mgr->addBuf(buf,len);
    mgr->open_block();
}

BasicMgr* DataMgr::getMgrbyId(ClientType_ id){
    switch(id){
    case ECG_CLIENT:
        break;
    case SPO2_CLIENT:
        break;
    case CO2_CLIENT:
        break;
    case NIBP_CLIENT:
        return m_pNibpMgr;
    case IBPCO_CLIENT:
        break;
    case CMD_CLIENT:
        break;
    case DISPLAY_CLIENT:
        break;
    default:
        break;
    }
    return NULL;
}

void DataMgr::setWindow(void* ww){
    m_pWindow = ww;

    m_pLinkMgr->setWindow(ww);
    m_pNibpMgr->setWindow(ww);
}
void DataMgr::generateTestFile(ClientType_ type){
    switch(type){
    case ECG_CLIENT:
        break;
    case SPO2_CLIENT:
        break;
    case CO2_CLIENT:
        break;
    case NIBP_CLIENT:
        m_pNibpMgr->generateTestFile();
        break;
    case IBPCO_CLIENT:
        break;
    default:
        break;
    }
}

void DataMgr::_onWriteTimeout(){
    if(m_vecObject.size()<=0) return;
    //cout<<"m_vecObject.size()="<<m_vecObject.size()<<endl;
    for(vector<void*>::iterator iter=m_vecObject.begin();iter!=m_vecObject.end();iter++){
        BasicMgr* mgr = (BasicMgr*)(*iter);
        mgr->m_iCurTime+=2;
        if(mgr->m_iCurTime >= mgr->getTimeout()){
            mgr->onTimer();
            mgr->m_iCurTime = 0;
        }
    }
}




