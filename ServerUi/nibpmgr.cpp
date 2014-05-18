#include "nibpmgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
NibpMgr::NibpMgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,NIBP_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    if(State::getInstance()->getStateData(NIBP_TEST)){
        startTest();
    }else{
        stopTest();
    }
    setShowDataSign(State::getInstance()->getStateData(NIBP_SHOWDATA));
    startSendData(State::getInstance()->getStateData(NIBP_SENDDATA));
    
    gettimeofday(&m_tStartTimer,NULL);
    m_start = false;
    assert(openFile("datafile/NIBP/nibp_adult.txt"));
}
NibpMgr::~NibpMgr()
{
    if(isOpenFile())
        assert(closeFile());

}
void NibpMgr::sendData(const BYTE* buf,int len){
    //cout<<"nibpmgr  senddata"<<endl;
    BasicMgr::sendData(Data_Msg,buf,len);
}

void NibpMgr::onTimer(){
    if(!getSendDataState()) return;
    if(!m_start) return;

    int readnum = read();

    int count = test(readnum);
//    if(count!=0){ // have not start test
//        printf("NibpMgr::onTimer   interval=%dms  readnum=%d  times=%d",time,readnum,m_testMsg.times);
//        display();
//    }
    display();
}

void NibpMgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(NIBP_CLIENT,getTestMsg());
         clearTestData();
     }
    if(isShowData()){
        ((MainWindow*)m_ui)->showData(NIBP_CLIENT,m_readBuf);
    }
}
bool NibpMgr::anal_DataPag(const BYTE* buf,const int len){
    switch(buf[3]){
    case ECG_CLIENT:
        break;
    case SPO2_CLIENT:
        break;
    case CO2_CLIENT:
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
void NibpMgr::analyseCmd(BYTE cmd){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
    switch(cmd){
    case NIBP_ADULT:
        closeFile();
        assert(openFile("datafile/NIBP/nibp_adult.txt"));
        break;
    case NIBP_ENFANT:
        closeFile();
        assert(openFile("datafile/NIBP/nibp_enfant.txt"));
        break;
    case NIBP_BABY:
        closeFile();
        assert(openFile("datafile/NIBP/nibp_baby.txt"));
        break;
    case NIBP_START:
        m_start = true;
        printf("nibp_start......\n");
        break;
    case NIBP_STOP:
        m_start = false;
        printf("nibp_stop......\n");
        break;
    default:
        break;
    }
}

bool NibpMgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
}
