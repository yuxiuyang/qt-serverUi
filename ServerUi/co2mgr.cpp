#include "co2mgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
Co2Mgr::Co2Mgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,CO2_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    gettimeofday(&m_tStartTimer,NULL);
    assert(openFile("datafile/CO2/data.txt"));
}
Co2Mgr::~Co2Mgr()
{
    if(isOpenFile())
        assert(closeFile());

}
void Co2Mgr::sendData(const BYTE* buf,int len){
    //cout<<"nibpmgr  senddata"<<endl;
    BasicMgr::sendData(Data_Msg,buf,len);
}

void Co2Mgr::onTimer(){
    if(!getSendDataState()) return;

    int readnum = read();

    int time = test(readnum);
    if(time!=0){ // have not start test
        printf("Co2Mgr::onTimer   interval=%dms  readnum=%d  times=%d",time,readnum,m_testMsg.times);
        display();
    }
}

void Co2Mgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((MainWindow*)m_ui)->showData(m_readBuf);

}
bool Co2Mgr::anal_DataPag(const BYTE* buf,const int len){
    return true;
}
void Co2Mgr::analyseCmd(BYTE cmd){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool Co2Mgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
