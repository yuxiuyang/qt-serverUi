#ifndef DATADEV_H
#define DATADEV_H

//device the data

#include <QThread>
#include <errno.h>
#include <vector>
 #include <QMutex>
#include "l_jn.h"
#include <algorithm>//使用泛型算法必须包含头文件algorithm
#include "../common/recvobject.h"
using namespace std;
class DataDev;
struct INFO_DATA{
    int fd;
    BYTE buf[1024];
    int len;
    DataDev* pThis;
};
enum THREAD_STATE{
    THREAD_NOTSTART,
    THREAD_RUNNING,
    THREAD_STOP,
    THREAD_SUSPEND,
};
struct CALLBACK_FD{
    int (*callBack_)(int);
    int         fd;
    RecvObject* object;
    bool isNeedToDelete;

    CALLBACK_FD(){
        reset();
    }
    void reset(){
        callBack_ = NULL;
        fd = -1;
        object = NULL;
        isNeedToDelete = false;
    }
};

class DataDev : public QThread
{
    Q_OBJECT
    private:
        explicit DataDev(QObject *parent = 0);
    public:
        virtual ~DataDev();
    signals:

    public slots:


    public:

        friend class RecvObject;
        static DataDev* getInstance();

        void sendTestData(int type);
        void sendData(int fd,const BYTE* buf,int len);
        //void sendData(int socketFd,MsgType_ msgType,ClientType_ clientType,DataSource_ dataSource,const BYTE* buf,const int len);
        bool checkData(const BYTE* buf,const int len,const BYTE value);

        bool removeFd(int fd);
        bool addFd(const int fd,int(*callback)(int));
        bool removeAll(RecvObject* object=NULL);
        CALLBACK_FD* findFd(int fd);

        bool displayRemoteClientSocketMsg(int sockeFd);
        bool isValidateFd(int Fd);
        bool checkRecvFd(int Fd);
        void start ( Priority priority = InheritPriority );
        void stop();
protected:
        static void sendData_(void* pv);
        void recvData();
        virtual void run();
        bool addFd(RecvObject* object,const int fd);

private:
        static DataDev* m_instance;

        vector<CALLBACK_FD*> m_callbackFdVec;//just

        QMutex m_sendMutex;//
        QMutex m_socketFdMutex;
        CJobNest *m_pDataJob;//send data task thread.

        THREAD_STATE m_pthreadState;

};

#endif // DATADEV_H
