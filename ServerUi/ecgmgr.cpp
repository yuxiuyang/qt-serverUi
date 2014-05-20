#include "ecgmgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
EcgMgr::EcgMgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,ECG_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    if(State::getInstance()->getStateData(ECG_TEST)){
        startTest();
    }else{
        stopTest();
    }
    setShowDataSign(State::getInstance()->getStateData(ECG_SHOWDATA));
    startSendData(State::getInstance()->getStateData(ECG_SENDDATA));

    gettimeofday(&m_tStartTimer,NULL);
    assert(openFile("datafile/ECG/data.txt"));
}
EcgMgr::~EcgMgr()
{
    if(isOpenFile())
        assert(closeFile());

}
void EcgMgr::sendData(const BYTE* buf,int len){
    //cout<<"nibpmgr  senddata"<<endl;
    BasicMgr::sendData(Data_Msg,buf,len);
}

void EcgMgr::onTimer(){
    if(!getSendDataState()) return;

    int readnum = read();

    int time = test(readnum);
    display();
}

void EcgMgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(ECG_CLIENT,getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((MainWindow*)m_ui)->showData(ECG_CLIENT,m_readBuf);

}
bool EcgMgr::anal_DataPag(const BYTE* buf,const int len){
    return true;
}
void EcgMgr::analyseCmd(BYTE cmd){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool EcgMgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
char* EcgMgr::getCollectDataTmpFile(){
    return "datafile/ECG/~tmp_ecg.txt";
}
