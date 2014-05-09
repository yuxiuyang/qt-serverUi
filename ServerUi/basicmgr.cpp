#include "basicmgr.h"
#include <errno.h>
#include <iostream>
#include "../common/datadev.h"
using namespace std;
BasicMgr::BasicMgr(LinkMgr* pLinkMgr):m_dataQueue(MAX_BUF)
{
    m_iFrequency = 1;
    m_iTimeout = 1000;
    m_iReadNum = 0;
    m_iCurTime = 0;
    m_file = NULL;
    memset(m_readBuf,0,sizeof(m_readBuf));
    DataDev::getInstance()->start();
    m_pLinkMgr = pLinkMgr;

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
void BasicMgr::sendData(MsgType_ msgType,ClientType_ clientType,DataSource_ dataSource,const BYTE* buf,const int len){
    int sock = m_pLinkMgr->findClientSocket(clientType);
    if(sock==-1) return;

    assert(len+7<=100);

    BYTE tmpBuf[100];
    tmpBuf[0] = 0x99;//start
    tmpBuf[1] = len+7;//
    tmpBuf[2] = msgType;
    tmpBuf[3] = clientType;
    tmpBuf[4] = dataSource;

    BYTE calSum = 0x00;
    for(int i=0;i<len;i++){
        tmpBuf[5+i] = buf[i];
        calSum += buf[i];
    }
    tmpBuf[5+len] = tmpBuf[1] + tmpBuf[2] + tmpBuf[3] +tmpBuf[4] + calSum;

    tmpBuf[5+len+1] = 0xdd;//end


     DataDev::getInstance()->sendData(sock,tmpBuf,7+len);
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

void BasicMgr::analyseCmd(int cmd,void* wparam,void* lparam){

}

void BasicMgr::clearTestData(){
    m_testMsg.usedtimeSum = 0;
    m_testMsg.readSum = 0;
    m_testMsg.times = 0;
}

