#include "datamgr.h"
#include "../common/datadev.h"
#include "mainwindow.h"

#include <string>
using namespace std;

#include "state.h"

DataMgr::DataMgr()
{
    if(!State::getInstance()->isExistConf()){
        State::getInstance()->setDef();
    }else{
        State::getInstance()->loadConf();
    }
    //DataDev::getInstance()->setCallback(recvData);
    m_pTimer = new QTimer();
    connect( m_pTimer, SIGNAL(timeout()), this, SLOT(_onWriteTimeout()) );
    m_pTimer->start(2);//2mms
    m_pLinkMgr = new LinkMgr();
    m_pLinkMgr->m_pDataMgr = this;


    m_pNibpMgr = new NibpMgr(m_pLinkMgr);
    assert(m_pNibpMgr);
    m_pNibpMgr->setFrequency(State::getInstance()->getStateData(NIBP_FRE));
    m_pNibpMgr->setReadNum(State::getInstance()->getStateData(NIBP_READRUM));

    m_pSpo2Mgr = new Spo2Mgr(m_pLinkMgr);
    assert(m_pSpo2Mgr);
    m_pSpo2Mgr->setFrequency(State::getInstance()->getStateData(SPO2_FRE));
    m_pSpo2Mgr->setReadNum(State::getInstance()->getStateData(SPO2_READRUM));

    m_pEcgMgr = new EcgMgr(m_pLinkMgr);
    assert(m_pEcgMgr);
    m_pEcgMgr->setFrequency(State::getInstance()->getStateData(ECG_FRE));
    m_pEcgMgr->setReadNum(State::getInstance()->getStateData(ECG_READRUM));

    m_pIbpMgr = new IbpMgr(m_pLinkMgr);
    assert(m_pEcgMgr);
    m_pIbpMgr->setFrequency(State::getInstance()->getStateData(IBP_FRE));
    m_pIbpMgr->setReadNum(State::getInstance()->getStateData(IBP_READRUM));

    m_pCo2Mgr = new Co2Mgr(m_pLinkMgr);
    assert(m_pCo2Mgr);
    m_pCo2Mgr->setFrequency(State::getInstance()->getStateData(CO2_FRE));
    m_pCo2Mgr->setReadNum(State::getInstance()->getStateData(CO2_READRUM));

    m_pNarcoMgr = new NarcoMgr(m_pLinkMgr);
    assert(m_pNarcoMgr);
    m_pNarcoMgr->setFrequency(State::getInstance()->getStateData(NARCO_FRE));
    m_pNarcoMgr->setReadNum(State::getInstance()->getStateData(NARCO_READRUM));


    m_vecObject.push_back(m_pNibpMgr);
    m_vecObject.push_back(m_pSpo2Mgr);
    m_vecObject.push_back(m_pEcgMgr);
    m_vecObject.push_back(m_pIbpMgr);
    m_vecObject.push_back(m_pCo2Mgr);
    m_vecObject.push_back(m_pNarcoMgr);
}
DataMgr::~DataMgr()
{
    delete m_pLinkMgr;
    m_pLinkMgr = NULL;
    delete m_pNibpMgr;
    m_pNibpMgr = NULL;
    delete m_pSpo2Mgr;
    m_pSpo2Mgr = NULL;

    delete m_pEcgMgr;
    m_pEcgMgr = NULL;
    delete m_pIbpMgr;
    m_pIbpMgr = NULL;
    delete m_pCo2Mgr;
    m_pCo2Mgr = NULL;
    delete m_pNarcoMgr;
    m_pNarcoMgr = NULL;
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
        return m_pEcgMgr;
        break;
    case SPO2_CLIENT:
        return m_pSpo2Mgr;
        break;
    case CO2_CLIENT:
        return m_pCo2Mgr;
        break;
    case NARCO_CLIENT:
        return m_pNarcoMgr;
        break;
    case NIBP_CLIENT:
        return m_pNibpMgr;
    case IBP_CLIENT:
        return m_pIbpMgr;
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
    m_pSpo2Mgr->setWindow(ww);
    m_pEcgMgr->setWindow(ww);
    m_pIbpMgr->setWindow(ww);
    m_pCo2Mgr->setWindow(ww);
    m_pNarcoMgr->setWindow(ww);
}
void DataMgr::generateTestFile(ClientType_ type){
    switch(type){
    case ECG_CLIENT:
        m_pEcgMgr->generateTestFile();
        break;
    case SPO2_CLIENT:
        m_pSpo2Mgr->generateTestFile();
        break;
    case CO2_CLIENT:
        m_pCo2Mgr->generateTestFile();
        break;
    case NARCO_CLIENT:
        m_pNarcoMgr->generateTestFile();
        break;
    case NIBP_CLIENT:
        m_pNibpMgr->generateTestFile();
        break;
    case IBP_CLIENT:
        m_pIbpMgr->generateTestFile();
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




