#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network_server.h"
#include "../common/datadev.h"
#include "datamgr.h"
#include <QMutex>
#include <queue>
using namespace std;
namespace Ui {
    class MainWindow;
}
enum SAVE_TYPE{
        SAVE_FRE,
        SAVE_READNUM,
        SAVE_FILE_START_POS,
        SAVE_FILE_END_POS,
        SAVE_TEST,
        SAVE_SHOWDATA,
        SAVE_SENDDATA,
};
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void start_click();
    void stop_click();
    void exit_click();
    void clearConnectMsg_click();
    void clearDisplayMsg_click();
    void generateData_click();
    void sendRequestData_click();
    void startCollectDatas_click();
    void stopCollectDatas_click();
    void saveCollectDatas_click();
    void delCollectDatas_click();
    void startTestCheckStateChanged (int state);
    void showReadDataCheckStateChanged(int state);
    void appendStatisticsMsg(char* buf);
    void showData(ClientType_ id,const char* buf);
    void displayStatisicsResult(ClientType_ id,TESTMSG* msg);
    void updateFileFromStartToEndPos_click();

    void valueChanged(int);
    void alarmChanged(int);

    void setValue_slider(int);

    void sendDataCheckStateChanged(int state);
    void collectDatasCheckStateChanged(int state);
    void appendMsg(const char* msg);
    void appendData(const char* msg);
    void appendData(ClientType_ id,const BYTE* msg,const int len);
    void radioChange();

    void freOk_click();
    void freCancel_click();
    void rcOk_click();
    void rcCancel_click();


    void sendTimer();

public:
    ClientType_ getClientType(){
        return m_dataType;
    }
    void checkLinkState();

    void setSave(ClientType_ id, SAVE_TYPE saveType,int val);
    int  getSaveValue(ClientType_ id,SAVE_TYPE saveType);

    void handleCB();
    void handleSlider();

    void initClient();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;


    DataMgr* m_pDataMgr;


    ClientType_ m_dataType;

    QTimer *m_pTestTimer;
    QMutex  m_pMutex;
    queue<string> m_queDataLine;
    queue<string> m_queConnectMsgLine;
    //queue<string> m_queStasticMsgLine;

};

#endif // MAINWINDOW_H
