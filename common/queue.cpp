#include "queue.h"
#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;
Queue::Queue(int size)
{
    m_maxSize = size;
    m_readPos = 0;
    m_writePos = 0;

    m_readSum = 0;
    m_writeSum = 0;
    m_dataBuf = new BYTE[size];
    assert(m_dataBuf);
    //memset(m_dataBuf,0,sizeof(m_dataBuf)*sizeof(BYTE));
    for(int i=0;i<size;i++){
        m_dataBuf[i]=0;
    }
}
Queue::~Queue(){
    delete m_dataBuf;
    m_dataBuf = NULL;
}
int Queue::push(const BYTE* data,int len){
    assert(len>0&&len<m_maxSize);
    if(getunReadCount()+len>m_maxSize){//too many datas but unread. so miss half
        if(m_readPos+m_maxSize/2<m_maxSize){
            m_readPos += m_maxSize/2;
        }else{
            m_readPos = m_maxSize/2+m_readPos-m_maxSize;
        }
        m_readSum += m_maxSize/2;
    }
    if(m_writePos+len<m_maxSize){
        memcpy(m_dataBuf+m_writePos,data,len);
        m_writePos += len;
    }else{
        memcpy(m_dataBuf+m_writePos,data,m_maxSize-m_writePos);
        memcpy(m_dataBuf,data,len-(m_maxSize-m_writePos));
        m_writePos = len-(m_maxSize-m_writePos);
    }
    m_writeSum += len;
    //cout<<"push len="<<len<<"  m_writePos="<<m_writePos<<"  m_readPos="<<m_readPos<<endl;
    //cout<<"m_dataBuf= "<<m_dataBuf<<endl;
//    char tmp[20]={0};
//
//    for(int i=0;i<m_maxSize;i++){
//        sprintf(tmp,"%d ",m_dataBuf[i]);
//        cout<<tmp;
//    }
    //cout<<endl<<"........."<<endl;
    //cout<<"push  m_writePos="<<m_writePos<<" m_readPos="<<m_readPos<<" m_writeSum="<<m_writeSum<<" m_readSum="<<m_readSum<<" getunReadCount()="<<getunReadCount()<<endl;
    return len;
}

int Queue::getDatas(BYTE* data,int len){
    assert(data&&len>0&&len<m_maxSize);

    len = (getunReadCount()>len)?len:getunReadCount();
    if(len==0){
        cout<<"m_readPos="<<m_readPos<<"m_writePos="<<m_writePos<<endl;
        assert(m_readPos==m_writePos);
        return 0;
    }
    if(m_readPos+len<m_maxSize){
        memcpy(data,m_dataBuf+m_readPos,len);
        m_readPos += len;
    }else{
        memcpy(data,m_dataBuf+m_readPos,m_maxSize-m_readPos);
        memcpy(data+m_maxSize-m_readPos,m_dataBuf,len-(m_maxSize-m_readPos));
        m_readPos = len-(m_maxSize-m_readPos);
    }
    m_readSum += len;
    //cout<<"getDatas len="<<len<<"  m_writePos="<<m_writePos<<"  m_readPos="<<m_readPos<<endl;
    //cout<<"m_dataBuf= "<<m_dataBuf<<endl;
    //cout<<"getDatas  m_writePos="<<m_writePos<<" m_readPos="<<m_readPos<<" m_writeSum="<<m_writeSum<<" m_readSum="<<m_readSum<<" getunReadCount()="<<getunReadCount()<<endl;
    return len;
}

int Queue::getunReadCount(){//get the data of unreading datas size.
    if(m_writeSum>0x0fffff){
        m_writeSum = m_writeSum-m_readSum;
        m_readSum = 0;
    }
    return m_writeSum-m_readSum;
}
