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

void EcgMgr::onTimer(){
    if(!getSendDataState()) return;
    if(m_pLinkMgr->findClientSocket(CO2_CLIENT)==-1) return;
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
void EcgMgr::analyseCmd(BYTE cmd,BYTE param){
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
