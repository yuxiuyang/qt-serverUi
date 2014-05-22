#include "co2mgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
Co2Mgr::Co2Mgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,CO2_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    if(State::getInstance()->getStateData(CO2_TEST)){
        startTest();
    }else{
        stopTest();
    }
    setShowDataSign(State::getInstance()->getStateData(CO2_SHOWDATA));
    startSendData(State::getInstance()->getStateData(CO2_SENDDATA));

    gettimeofday(&m_tStartTimer,NULL);
    assert(openFile("datafile/CO2/data.txt"));
}
Co2Mgr::~Co2Mgr()
{
    if(isOpenFile())
        assert(closeFile());

}

void Co2Mgr::onTimer(){
    if(!getSendDataState()) return;

    if(m_pLinkMgr->findClientSocket(CO2_CLIENT)==-1) return;

    int readnum = read();

    int time = test(readnum);
    display();
}

void Co2Mgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(CO2_CLIENT,getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((MainWindow*)m_ui)->showData(CO2_CLIENT,m_readBuf);

}
bool Co2Mgr::anal_DataPag(const BYTE* buf,const int len){
    if(State::getInstance()->getStateData(COLLECT_DATA)){
        if(State::getInstance()->getStateData(COLLECT_START)){//start collect data
            if(!m_collectDataFile){
                m_collectDataFile = fopen("datafile/NIBP/~tmp_nibp.txt","w");
                if(!m_collectDataFile){
                    cout<<"NibpMgr  open collect data file failure"<<endl;
                }
            }
            fwrite(buf, 1,len, m_collectDataFile);
        }else{
            if(m_collectDataFile)
                fclose(m_collectDataFile);
            m_collectDataFile = NULL;
        }
    }
    if(!isTestRunning()){
        startTest();
        setShowDataSign(true);
    }

    int count = test(len);

    string strBuf="";
    char tmp[10]={0};
    for(int i=0;i<len;i++){
        sprintf(tmp,"%02x ",buf[i]);
        strBuf += tmp;
    }
    memset(m_readBuf,0,sizeof(m_readBuf));
    strcpy(m_readBuf,strBuf.c_str());
    display();
    return true;
}
void Co2Mgr::analyseCmd(BYTE cmd,BYTE param){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool Co2Mgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
char* Co2Mgr::getCollectDataTmpFile(){
    return "datafile/CO2/~tmp_co2.txt";
}
