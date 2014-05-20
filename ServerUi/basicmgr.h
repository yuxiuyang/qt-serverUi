#ifndef BASICMGR_H
#define BASICMGR_H
#include <assert.h>
#include "../include/define.h"
#include "queue.h"
#include <sys/time.h>
#include "file.h"
#include "../common/datadev.h"
#include "linkmgr.h"
#include "state.h"
#define MAX_READ_TXT 3*300+1
#define MAX_BUF 1024
#define READ_WRITE_INTEVAL 30//the interval beweent read and write  to arrived a blance.
struct TESTMSG{
    unsigned long int usedtimeSum;//the totally of interval to call timer
    unsigned long int readSum;//read txt data totally
    int times;//count

    bool isStart;//start to test
    bool isShowData;//weather show the txt data.
    bool isFrist;//just first to call
    TESTMSG(){
        usedtimeSum = 0;
        readSum = 0;
        times = 0;
        isStart = false;
        isShowData = false;
        isFrist = true;
    }
};

class BasicMgr
{
public:
    BasicMgr(LinkMgr* pMgr,ClientType_ clientId);

    virtual void onTimer()=0;
    virtual void display()=0;//display
    virtual void sendData(const BYTE* buf,int len)=0;
    virtual char* getCollectDataTmpFile()=0;
    void setFrequency(int fre);
    void setReadNum(int num);
    int getFrequency(){
        return m_iFrequency;
    }
    int getReadNum(){
        return m_iReadNum/3;
    }
    int getTimeout(){
        return m_iTimeout;
    }
    TESTMSG* getTestMsg(){
        return &m_testMsg;
    }
    void startTest(){
        m_testMsg.isStart = true;
        m_testMsg.isFrist = true;
    }
    bool isTestRunning(){
        return m_testMsg.isStart;
    }

    void clearTestData();
    void setShowDataSign(bool show){
        m_testMsg.isShowData = show;
    }
    bool isShowData(){
        return m_testMsg.isShowData;
    }
    void startSendData(bool b=true){
        m_isStartSendData = b;
    }
    bool getSendDataState(){
        return m_isStartSendData;
    }
    void stopTest(){
        m_testMsg.isStart = false;
        m_testMsg.isFrist = false;
    }

    int m_iCurTime;//ms use in timer.record cur time

public:
    //fellowing is test info
    struct timeval m_tStartTimer;//used to save cur calling onTimer fun's time.
    TESTMSG m_testMsg;
    int test(int num);

    virtual void generateTestFile();//
    virtual void append(const char* data);

    void sendData(MsgType_ msgType,const BYTE* buf,const int len);
    void sendRequestIdData();
    void setWindow(void* ww){
        m_ui = ww;
    }
    void addBuf(const BYTE* buf,int len);
    int open_block();
    bool anal_pag(const BYTE* buf,const int len);
    virtual bool anal_DataPag(const BYTE* buf,const int len)=0;
    virtual bool anal_ConnectPag(const BYTE* buf,const int len)=0;
    virtual void analyseCmd(BYTE cmd)=0;


    ClientType_ getCurClientId(){
        return m_clientId;
    }

    void setReadFileStartPos(long startPos){
        if(m_file){
            m_file->setStartPos(startPos);

        }
    }
    void setReadFileEndPos(long endPos){
        if(m_file){
            m_file->setEndPos(endPos);
        }
    }
    long getFileSize(){
        if(m_file){
            return m_file->getFileSize();
        }else{
            return 0;
        }
    }
    bool updateFileFromStartPosToEndPos();
    bool copyFile(const char* destFileName,const char* strFileName);
    bool openFile(const char* filename);
    bool openFile();
    bool isOpenFile();
    bool closeFile();
    char* getFileName(){
        return m_strFileName;
    }

protected:

    virtual int read();//return the read count
    char m_readBuf[MAX_READ_TXT];//just tmp
    BYTE m_recieveBuf[MAX_READ_TXT];//just tmp
    Queue m_dataQueue;
    void resolveProtocol(const char* buf,int size,BYTE* recieveBuf,int& recieveBuf_len);

    LinkMgr* m_pLinkMgr;
    void* m_ui;//used to display msg on the window
    char m_strFileName[256];

    FILE* m_collectDataFile;
private:
    File* m_file;
    int m_iFrequency;//how many times call the fun-onTimer in 1 sec.
    int m_iReadNum;//how many datas will read just onece calling fun-onTimer.
    int m_iTimeout;//ms  time out to call fun-onTimer.calculate it by m_iFrequency.


    BYTE m_dataBuf[MAX_DATA_BUF];
    int m_curPos;

    ClientType_ m_clientId;
    bool m_isStartSendData;
    QMutex m_readWriteMutex;
};

#endif // BASICMGR_H
