#include "spo2mgr.h"
#include "mainwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
Spo2Mgr::Spo2Mgr(LinkMgr* pLinkMgr):BasicMgr(pLinkMgr,SPO2_CLIENT)
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));

    if(State::getInstance()->getStateData(SPO2_TEST)){
        startTest();
    }else{
        stopTest();
    }
    setShowDataSign(State::getInstance()->getStateData(SPO2_SHOWDATA));
    startSendData(State::getInstance()->getStateData(SPO2_SENDDATA));

    gettimeofday(&m_tStartTimer,NULL);
    //assert(openFile("datafile/SPO2/data_100.txt"));
}
Spo2Mgr::~Spo2Mgr()
{
    if(isOpenFile())
        assert(closeFile());

}

void Spo2Mgr::onTimer(){
    if(!getSendDataState()) return;
    if(m_pLinkMgr->findClientSocket(SPO2_CLIENT)==-1) return;
    int readnum = read();

    int time = test(readnum);
    display();
}

void Spo2Mgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((MainWindow*)m_ui)->displayStatisicsResult(SPO2_CLIENT,getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((MainWindow*)m_ui)->showData(SPO2_CLIENT,m_readBuf);

}
bool Spo2Mgr::anal_DataPag(const BYTE* buf,const int len){
    if(State::getInstance()->getStateData(COLLECT_DATA)){
        if(State::getInstance()->getStateData(COLLECT_START)){//start collect data
            if(!m_collectDataFile.isOpen()){
                m_collectDataFile.setFileName("datafile/SPO2/~tmp_spo2.txt");
                if(!m_collectDataFile.open("w")){
                    cout<<"Spo2Mgr  open collect data file failure"<<endl;
                    return false;
                }
            }
            m_collectDataFile.write(buf,len);

        }else{
            m_collectDataFile.close();
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
void Spo2Mgr::analyseCmd(BYTE cmd,BYTE param){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool Spo2Mgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
char* Spo2Mgr::getCollectDataTmpFile(){
    return "datafile/SPO2/~tmp_spo2.txt";
}

void Spo2Mgr::setTxtValue(const char* val){
    char buf[300]={0};
    sprintf(buf,"./datafile/SPO2/data_%s.txt",val);

    closeFile();
    if(!openFile(buf)){
        printf("open file %s failure\n",buf);
    }
}

