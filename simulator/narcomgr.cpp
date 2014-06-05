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
    //assert(openFile("datafile/NARCO/data_20.txt"));
}
NarcoMgr::~NarcoMgr()
{
    if(isOpenFile())
        assert(closeFile());

}
void NarcoMgr::onTimer(){
    if(!getSendDataState()) return;
    if(m_pLinkMgr->findClientSocket(NARCO_CLIENT)==-1) return;
    int readnum = read();

    int time = test(readnum);
    display();
}

void NarcoMgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((GroupBasicWindow*)m_ui)->displayStatisicsResult(getTestMsg());
         clearTestData();
     }
    if(isShowData())
        ((GroupBasicWindow*)m_ui)->showData(m_readBuf);

}
bool NarcoMgr::anal_DataPag(const BYTE* buf,const int len){
    if(State::getInstance()->getStateData(COLLECT_DATA)){
        if(State::getInstance()->getStateData(COLLECT_START)){//start collect data
            if(!m_collectDataFile.isOpen()){
                m_collectDataFile.setFileName("datafile/NARCO/~tmp_narco.txt");
                if(!m_collectDataFile.open("w")){
                    cout<<"NarcoMgr  open collect data file failure"<<endl;
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
void NarcoMgr::analyseCmd(BYTE cmd,BYTE param){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(buf);
}

bool NarcoMgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
        return true;
}
char* NarcoMgr::getCollectDataTmpFile(){
    return "datafile/NARCO/~tmp_narco.txt";
}

void NarcoMgr::setTxtValue(const char* val){
//    char buf[300]={0};
//    sprintf(buf,"./datafile/NARCO/data_%s.txt",val);
//
//    closeFile();
//    if(!openFile(buf)){
//        printf("open file %s failure\n",buf);
//    }


    char buf[300]={0};
    sprintf(buf,"./datafile/NARCO/%s",Global::getInstance()->getGlobalPath(NARCO_CLIENT).c_str());

    Global::create_Folder(buf);

    memset(buf,0,sizeof(buf));

    sprintf(buf,"./datafile/NARCO/%s/data_%s.txt",Global::getInstance()->getGlobalPath(NARCO_CLIENT).c_str(),val);
    closeFile();
    if(!openFile(buf)){
        printf("open file %s failure\n",buf);
    }
}
