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
    void startTestCheckStateChanged (int state);
    void showReadDataCheckStateChanged(int state);
    void appendStatisticsMsg(char* buf);
    void showData(const char* buf);
    void displayStatisicsResult(TESTMSG* msg);

    void sendDataCheckStateChanged(int state);
    void appendMsg(const char* msg);
    void appendData(const char* msg);
    void appendData(const BYTE* msg,const int len);
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
