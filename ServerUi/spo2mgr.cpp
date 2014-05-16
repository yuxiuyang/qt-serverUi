#include "spo2mgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
Spo2Mgr::Spo2Mgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,SPO2_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    gettimeofday(&m_tStartTimer,NULL);
    assert(openFile("datafile/SPO2/data.txt"));
}
Spo2Mgr::~Spo2Mgr()
{
    if(isOpenFile())
        assert(closeFile());

}
void Spo2Mgr::sendData(const BYTE* buf,int len){
    //cout<<"nibpmgr  senddata"<<endl;
    BasicMgr::sendData(Data_Msg,buf,len);
}

void Spo2Mgr::onTimer(){
    if(!getSendDataState()) return;

    int readnum = read();

    int time = test(readnum);
    if(time!=0){ // have not start test
        printf("Spo2Mgr::onTimer   interval=%dms  readnum=%d  times=%d",time,readnum,m_testMsg.times);
        display();
    }
}

void Spo2Mgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((MainWindow*)m_ui)->showData(m_readBuf);

}
bool Spo2Mgr::anal_DataPag(const BYTE* buf,const int len){
    switch(buf[3]){
    case ECG_CLIENT:
        break;
    case SPO2_CLIENT:
        break;
    case CO2_CLIENT:
        break;
    case NARCO_CLIENT:
        break;
    case NIBP_CLIENT:
        break;
    case IBP_CLIENT:
        break;
    case CMD_CLIENT:
        break;
    case DISPLAY_CLIENT:
        break;
    default:
        break;
    }

    return true;
}
void Spo2Mgr::analyseCmd(BYTE cmd){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool Spo2Mgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
