#include "narcomgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
NarcoMgr::NarcoMgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,NARCO_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    if(State::getInstance()->getStateData(NARCO_TEST)){
        startTest();
    }else{
        stopTest();
    }
    setShowDataSign(State::getInstance()->getStateData(NARCO_SHOWDATA));
    startSendData(State::getInstance()->getStateData(NARCO_SENDDATA));
    gettimeofday(&m_tStartTimer,NULL);
    assert(openFile("datafile/NARCO/data.txt"));
}
NarcoMgr::~NarcoMgr()
{
    if(isOpenFile())
        assert(closeFile());

}
void NarcoMgr::sendData(const BYTE* buf,int len){
    //cout<<"nibpmgr  senddata"<<endl;
    BasicMgr::sendData(Data_Msg,buf,len);
}

void NarcoMgr::onTimer(){
    if(!getSendDataState()) return;

    int readnum = read();

    int time = test(readnum);
    display();
}

void NarcoMgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(NARCO_CLIENT,getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((MainWindow*)m_ui)->showData(NARCO_CLIENT,m_readBuf);

}
bool NarcoMgr::anal_DataPag(const BYTE* buf,const int len){
    return true;
}
void NarcoMgr::analyseCmd(BYTE cmd){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool NarcoMgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
