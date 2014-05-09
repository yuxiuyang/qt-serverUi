#include "datamgr.h"
#include "../common/datadev.h"
#include "mainwindow.h"

#include <string>
using namespace std;

DataMgr::DataMgr()
{
    //DataDev::getInstance()->setCallback(recvData);
    memset(&m_dataBuf,0,sizeof(m_dataBuf));
    m_curPos = 0;


    m_pTimer = new QTimer();
    connect( m_pTimer, SIGNAL(timeout()), this, SLOT(_onWriteTimeout()) );
    m_pTimer->start(2);//2mms
    m_pLinkMgr = new LinkMgr();
    m_pLinkMgr->m_pDataMgr = this;
    m_pNibpMgr = new NibpMgr(m_pLinkMgr);
    assert(m_pNibpMgr);
    m_pNibpMgr->setFrequency(1);
    m_pNibpMgr->setReadNum(4);

    m_vecObject.push_back(m_pNibpMgr);
}
DataMgr::~DataMgr()
{
    delete m_pLinkMgr;
    m_pLinkMgr = NULL;
    delete m_pNibpMgr;
    m_pNibpMgr = NULL;
}

void DataMgr::handle(const BYTE* buf,int len){
    addBuf(buf,len);
    open_block();
}
int DataMgr::open_block(){
    int ix=0;
    while(ix<m_curPos&&m_dataBuf[ix]!=0x99){//找到 99 开头的包。找不到，则丢掉之前数据
        ix++;
    }
    if(ix!=0){//丢掉之前数据
        memmove(m_dataBuf,m_dataBuf+ix,m_curPos-ix);//这里需要用 m_curPos
        m_curPos=m_curPos-ix;
         //重新初始化
        ix = 0;
     }

     //0x99后的 第二位  即数据包长度
     if(m_curPos<2){
         return 0;//数据长度不够，下次再来解析
     }
     int len = m_dataBuf[1];
     if(m_curPos<len){//未达到完整包长度
          return 0;//数据长度不够，下次再来解析
     }
     //printf("len=%02x-%d\n",len,len);
     if(m_dataBuf[len-1]!=0xdd){//这个包有问题，应丢掉
          // throw a pag
          printf("miss a page\n");
          memcpy(m_dataBuf,m_dataBuf+1,m_curPos-1);//这里需要用 m_curPos
          m_curPos -= 1;
          return 0;
      }

      //收到了一个完整的包，校验 
     if(DataDev::getInstance()->checkData(m_dataBuf+1,len-3,m_dataBuf[len-2])){//check ok
         anal_pag(m_dataBuf,len);
     }

     //analyse finished, delete this page
     memcpy(m_dataBuf,m_dataBuf+len,m_curPos-len);
     m_curPos=m_curPos-len;

}

void DataMgr::addBuf(const BYTE* buf,int len){
    if(m_curPos+len<=MAX_DATA_BUF){
          memmove(m_dataBuf+m_curPos,buf,len);
          m_curPos+=len;
    }
    else{
        if(MAX_DATA_BUF-m_curPos>0){
             memmove(m_dataBuf+m_curPos,buf,MAX_DATA_BUF-m_curPos);
             m_curPos=MAX_DATA_BUF;
        }
    }
}
bool DataMgr::anal_pag(const BYTE* buf,const int len){
    printf("anal_pag....len=%d\n",len);
    for(int i=0;i<len;i++){
        printf("%02x ",buf[i]);
    }
    printf("\nend....\n");
    switch(buf[2]){
    case Data_Msg:
        anal_DataPag(buf,len);
        break;
    case Link_Msg:
        anal_ConnectPag(buf,len);
        break;
    default:
        break;
    }

    return true;
}
BasicMgr* DataMgr::getMgrbyId(ClientType_ id){
    switch(id){
    case ECG_CLIENT:
        break;
    case SPO2_CLIENT:
        break;
    case CO2_CLIENT:
        break;
    case NIBP_CLIENT:
        return m_pNibpMgr;
    case IBPCO_CLIENT:
        break;
    case CMD_CLIENT:
        break;
    case DISPLAY_CLIENT:
        break;
    default:
        break;
    }
    return NULL;
}
bool DataMgr::anal_DataPag(const BYTE* buf,const int len){
    switch(buf[3]){
    case ECG_CLIENT:
        break;
    case SPO2_CLIENT:
        break;
    case CO2_CLIENT:
        break;
    case NIBP_CLIENT:
        break;
    case IBPCO_CLIENT:
        break;
    case CMD_CLIENT:
        break;
    case DISPLAY_CLIENT:
        break;
    default:
        break;
    }

    if(buf[3] == ((MainWindow*)m_pWindow)->getClientType()){
        ((MainWindow*)m_pWindow)->appendData(buf+5,len-7);
    }
    return true;
}

bool DataMgr::anal_ConnectPag(const BYTE* buf,const int len){
    return m_pLinkMgr->analLinkPag(buf,len);
}

void DataMgr::setWindow(void* ww){
    m_pWindow = ww;

    m_pLinkMgr->setWindow(ww);
    m_pNibpMgr->setWindow(ww);
}
void DataMgr::generateTestFile(ClientType_ type){
    switch(type){
    case ECG_CLIENT:
        break;
    case SPO2_CLIENT:
        break;
    case CO2_CLIENT:
        break;
    case NIBP_CLIENT:
        m_pNibpMgr->generateTestFile();
        break;
    case IBPCO_CLIENT:
        break;
    default:
        break;
    }
}

void DataMgr::_onWriteTimeout(){
    if(m_vecObject.size()<=0) return;
    //cout<<"m_vecObject.size()="<<m_vecObject.size()<<endl;
    for(vector<void*>::iterator iter=m_vecObject.begin();iter!=m_vecObject.end();iter++){
        BasicMgr* mgr = (BasicMgr*)(*iter);
        mgr->m_iCurTime+=2;
        if(mgr->m_iCurTime >= mgr->getTimeout()){
            mgr->onTimer();
            mgr->m_iCurTime = 0;
        }
    }
}




