#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "groupwindow.h"
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
    void clearConnectMsg_click();
    void sendTimer();
    void collectDatasCheckStateChanged(int state);
    void tabChange(int index);

    void addGlobalPathToCb_click();
    void delGlobalPathToCb_click();
    void globalPathChanged(int index);

public:
    void appendConnectMsg(const char* msg);
protected:
    void changeEvent(QEvent *e);


    GroupBasicWindow* getCurGroupWinodw(ClientType_ id);


private:
    Ui::MainWindow *ui;
    QTimer *m_pTimer;
    QMutex  m_pMutex;


    queue<string> m_queConnectMsgLine;

    QTabWidget* m_tabWidget;
    DataMgr* m_pDataMgr;
    GroupEcgWindow* m_groupEcg;
    GroupSpo2Window* m_groupSpo2;
    GroupNibpWindow* m_groupNibp;
    GroupIbpWindow* m_groupIbp;
    GroupCo2Window* m_groupCo2;
    GroupNarcoWindow* m_groupNarco;
    ClientType_ m_dataType;
};

#endif // MAINWINDOW_H
