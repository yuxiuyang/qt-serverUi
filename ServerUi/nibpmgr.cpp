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
    //assert(openFile("datafile/NIBP/nibp_adult.txt"));
}
NibpMgr::~NibpMgr()
{
    if(isOpenFile())
        assert(closeFile());

}

void NibpMgr::onTimer(){
    if(!getSendDataState()) return;
    if(!m_start) return;
    if(m_pLinkMgr->findClientSocket(NIBP_CLIENT)==-1) return;
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

    if(State::getInstance()->getStateData(COLLECT_DATA)){
        printf("getStateData(COLLECT_START)=%d\n",State::getInstance()->getStateData(COLLECT_START));
        if(State::getInstance()->getStateData(COLLECT_START)){//start collect data
            if(!m_collectDataFile.isOpen()){
                m_collectDataFile.setFileName("datafile/NIBP/~tmp_nibp.txt");
                if(!m_collectDataFile.open("w")){
                    cout<<"NibpMgr  open collect data file failure"<<endl;
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
    //((MainWindow*)(m_pLinkMgr->m_window))->appendData(NIBP_CLIENT,buf,len);
    return true;
}
void NibpMgr::analyseCmd(BYTE cmd,BYTE param){
    char buf[100]={0};
    sprintf(buf,"cmd=%d",cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)(m_pLinkMgr->m_window))->showData(NIBP_CLIENT,buf);
    switch(cmd){
    case NIBP_TYPE:
        {
            switch(param){
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
            default:
                break;
            }

        }
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
char* NibpMgr::getCollectDataTmpFile(){
    return "datafile/NIBP/~tmp_nibp.txt";
}

void NibpMgr::setTxtValue(const char* val){
    char buf[300]={0};
    sprintf(buf,"./datafile/NIBP/data_%s.txt",val);

    closeFile();
    if(!openFile(buf)){
        printf("open file %s failure\n",buf);
    }
}
