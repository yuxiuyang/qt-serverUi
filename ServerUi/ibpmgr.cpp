#include "ibpmgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
IbpMgr::IbpMgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,IBP_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    if(State::getInstance()->getStateData(IBP_TEST)){
        startTest();
    }else{
        stopTest();
    }
    setShowDataSign(State::getInstance()->getStateData(IBP_SHOWDATA));
    startSendData(State::getInstance()->getStateData(IBP_SENDDATA));

    gettimeofday(&m_tStartTimer,NULL);
    assert(openFile("datafile/IBP/data.txt"));
}
IbpMgr::~IbpMgr()
{
    if(isOpenFile())
        assert(closeFile());

}
void IbpMgr::sendData(const BYTE* buf,int len){
    //cout<<"nibpmgr  senddata"<<endl;
    BasicMgr::sendData(Data_Msg,buf,len);
}

void IbpMgr::onTimer(){
    if(!getSendDataState()) return;

    int readnum = read();

    int time = test(readnum);
    display();
}

void IbpMgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(IBP_CLIENT,getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((MainWindow*)m_ui)->showData(IBP_CLIENT,m_readBuf);

}
bool IbpMgr::anal_DataPag(const BYTE* buf,const int len){
    return true;
}
void IbpMgr::analyseCmd(BYTE cmd){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool IbpMgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
