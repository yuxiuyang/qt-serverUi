#include "basicmgr.h"
#include <errno.h>
#include <iostream>
#include "../common/datadev.h"
using namespace std;
BasicMgr::BasicMgr(LinkMgr* pLinkMgr,ClientType_ clientId):m_dataQueue(MAX_BUF)
{
    m_iFrequency = 1;
    m_iTimeout = 1000;
    m_iReadNum = 0;
    m_iCurTime = 0;
    m_file = NULL;
    memset(m_readBuf,0,sizeof(m_readBuf));
    DataDev::getInstance()->start();
    m_pLinkMgr = pLinkMgr;

    m_clientId = clientId;
    m_ui = NULL;
}

void BasicMgr::setFrequency(int fre){
    assert(fre<=500);//the basic timer'interval is 2mms. must not more then 500
    m_iFrequency = fre;
    //1s = 1000ms
    m_iTimeout = 1000/m_iFrequency;
    if(m_iTimeout%2)//if not 2's Integer multiples
        m_iTimeout+=1;//m_iTimeout have to >=2 ms
}
void BasicMgr::setReadNum(int num){
    m_iReadNum = num*3;
    assert(m_file);
    m_file->reset();
    clearTestData();
}
void BasicMgr::sendData(MsgType_ msgType,const BYTE* buf,const int len){
    int sock = m_pLinkMgr->findClientSocket(getCurClientId());
    assert(sock);
    assert(len+5<=100);

    BYTE tmpBuf[100];
    tmpBuf[0] = 0x99;//start
    tmpBuf[1] = len+5;//
    tmpBuf[2] = msgType;


    BYTE calSum = 0x00;
    for(int i=0;i<len;i++){
        tmpBuf[3+i] = buf[i];
        calSum += buf[i];
    }
    tmpBuf[3+len] = tmpBuf[1] + tmpBuf[2] + calSum;

    tmpBuf[3+len+1] = 0xdd;//end


     DataDev::getInstance()->sendData(sock,tmpBuf,5+len);
}
void BasicMgr::sendRequestIdData(){
    m_pLinkMgr->requestLinkMsg();//send request id msg
}

int BasicMgr::test(int num){
    if(m_testMsg.isStart){
        if(m_testMsg.isFrist){
            m_testMsg.isFrist =false;
            gettimeofday(&m_tStartTimer,NULL);
            return 0;
        }

        struct timeval curTime;
        gettimeofday(&curTime,NULL);
        int timeuse = (1000*1000*(curTime.tv_sec-m_tStartTimer.tv_sec)+(curTime.tv_usec-m_tStartTimer.tv_usec))/1000;

        m_testMsg.usedtimeSum += timeuse;
        m_testMsg.times += 1;
        m_testMsg.readSum += num;
        char buf[100]={0};
        cout<<buf<<endl;

        m_tStartTimer = curTime;
        return timeuse;
    }
    return 0;
}
void BasicMgr::generateTestFile(){//
    m_file->clear();//clear file
    if(!isOpenFile()){
        cout<<"read failure  please call openFile to create a file"<<endl;
        return;
    }
    for(int i=0;i<256;i++){
        m_file->write("%02x ",i);
    }
    m_file->flush();
}
void BasicMgr::append(const char* data){//
    if(!isOpenFile()){
        cout<<"read failure  please call openFile to create a file"<<endl;
        return;
    }
    m_file->write(data);
    m_file->flush();
}

int BasicMgr::read(){
    if(!isOpenFile()){
        cout<<"read failure  please call openFile to create a file"<<endl;
        return 0;
    }
    memset(m_readBuf,0,sizeof(m_readBuf));
    assert(m_iReadNum<MAX_BUF);
    int len = m_file->read(m_readBuf,m_iReadNum);//read 3*300 datas per time.
    if(len<=0){
        cout<<"len="<<len<<" read error"<<endl;
        return 0;
    }
    int recieveBuf_len=0;
    resolveProtocol(m_readBuf,len,m_recieveBuf,recieveBuf_len);
    if(recieveBuf_len){
        //m_dataQueue.push(m_recieveBuf,recieveBuf_len);
        //printf("m_iReadNum=%d,len=%d,recieveBuf_len=%d,thread=%lu\n",m_iReadNum,len,recieveBuf_len,pthread_self());
        sendData(m_recieveBuf,recieveBuf_len);
    }else{
        cout<<"resolveProtocol error happen"<<endl;
    }

    return recieveBuf_len;
    //cout<<"read   m_readBuf="<<m_readBuf<<endl;
}
bool BasicMgr::openFile(const char* filename){
    if(isOpenFile()){
        cout<<"had create a file"<<endl;
        return false;
    }
    m_file = new File();
    assert(m_file);
    m_file->setFileName(filename);
    m_file->setReadFileProperty(true);
    return m_file->open("a+");

}

bool BasicMgr::isOpenFile(){
    return m_file==NULL?false:true;
}

bool BasicMgr::closeFile(){
    if(!m_file){
        cout<<"closefile m_file=null may be not created"<<endl;
        return false;
    }
    assert(m_file->close());
    delete m_file;
    m_file = NULL;
    return true;
}
void BasicMgr::resolveProtocol(const char* buf,int size,BYTE* recieveBuf,int& recieveBuf_len){//
    //cout<<"buf=%s"<<buf<<endl;
    char tmp[3]={0};
    int index=0;
    recieveBuf_len = 0;
        for(int i=0;i<size;){
            while(buf[i]==' '&&i<size) i++;//Filter space
            if(i==size) return;

            bool sign = true;
            while(buf[i]!=' '&&i<size){
                    if(index<2){//get the data.
                            tmp[index++] = buf[i];
                            //printf("tmp[%d]=%d\n",index-1,tmp[index-1]);
                    }else{
                            cout<<"may be error"<<endl;
                            sign = false;
                            i++;
                            break;
                    }
                    i++;
            }

            if(sign&&index == 2){//hex to dec.
                    recieveBuf[recieveBuf_len++] = twoBYTEConverToHex(charConvertToHex(tmp[0]),charConvertToHex(tmp[1]));
                    //printf("%02x ",rel);
            }else if(sign&&index!=2){
                    cout<<endl<<"may be error  tmp[0]="<<tmp[0]<<endl;
            }
            memset(tmp,0,sizeof(tmp));
            index = 0;
        }
}

void BasicMgr::clearTestData(){
    m_testMsg.usedtimeSum = 0;
    m_testMsg.readSum = 0;
    m_testMsg.times = 0;
}

int BasicMgr::open_block(){
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
          memcpy(m_dataBuf,m_dataBuf+len,m_curPos-len);//这里需要用 m_curPos
          m_curPos -= len;
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

void BasicMgr::addBuf(const BYTE* buf,int len){
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
bool BasicMgr::anal_pag(const BYTE* buf,const int len){
    switch(buf[2]){
    case Data_Msg:
        anal_DataPag(buf,len);
        break;
    case Link_Msg:
        anal_ConnectPag(buf,len);
        break;
    case Cmd_Msg:
        analyseCmd(buf[3],buf[4]);
        break;
    default:
        break;
    }

    return true;
}
bool BasicMgr::anal_DataPag(const BYTE* buf,const int len){
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

//    if(buf[3] == ((MainWindow*)m_pWindow)->getClientType()){
//        ((MainWindow*)m_pWindow)->appendData(buf+5,len-7);
//    }
    return true;
}
void BasicMgr::analyseCmd(BYTE clientId,BYTE cmd){
    char buf[100]={0};
    sprintf(buf,"clientid=%02x  cmd=%d",clientId,cmd);
    cout<<"buf="<<buf<<endl;
    //((MainWindow*)m_pWindow)->appendData(buf);
}

bool BasicMgr::anal_ConnectPag(const BYTE* buf,const int len){
    //return m_pLinkMgr->analLinkPag(buf,len);
}
