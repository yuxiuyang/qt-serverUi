#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QTabWidget>
#include <QComboBox>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include "datamgr.h"
#include <QMutex>
#include <queue>
#include "datamgr.h"
#include <QInputDialog>
#include "global.h"
#include <QMessageBox>

class GroupBasicWindow:public QWidget
{
    Q_OBJECT
public:
    GroupBasicWindow(QWidget *parent,ClientType_ dataType,DataMgr* pMgr);

public Q_SLOTS:
    void clearTextBrowser_click();
    void sendRequestData_click();
    void generateTestData_click();

    void valueChanged(int);
    void alarmChanged(int);
    void addValueToCb_click();
    void delValueToCb_click();
    void addAlarmToCb_click();
    void delAlarmToCb_click();
    void updateFileFromStartToEndPos_click();
    void setValue_slider(int);

    void startTestCheckStateChanged (int state);
    void showReadDataCheckStateChanged(int state);
    void sendDataCheckStateChanged(int state);

    void startCollectDatas_click();
    void stopCollectDatas_click();
    void saveCollectDatas_click();
    void delCollectDatas_click();

    void freOk_click();
    void freCancel_click();
    void rcOk_click();
    void rcCancel_click();
public:
    virtual void init();
    virtual void sendTimer();
public:
    virtual void initLayout();
    virtual void updateWindow(MODE_TYPE mode);
    void appendStatisticsMsg(char* buf);
    void displayStatisicsResult(TESTMSG* msg);
    void checkLinkState();

    void handleCB();
    void handleSlider(bool isInit=false);

    void showData(const char* buf);
protected:
    QTextBrowser* m_pTextBrowser;


    QPushButton* m_clearBtn;
    QPushButton* m_sendComfireBtn;
    QComboBox* m_valueCb;
    QComboBox* m_alarmCb;
    QPushButton* m_addValueBtn;
    QPushButton* m_delValueBtn;
    QPushButton* m_addAlarmBtn;
    QPushButton* m_delAlarmBtn;
    QPushButton* m_generateTestDataBtn;
    QLabel*    m_posStartToEndLabel;
    QPushButton* m_saveCurPosBtn;
    QSlider* m_readStartPos_slider;
    QSlider* m_readEndPos_slider;
    QCheckBox* m_startTestCheckBox;
    QCheckBox* m_showDataCheckBox;
    QCheckBox* m_sendDataCheckBox;
    QTextBrowser* m_statisticsBrowser;

    QLineEdit*   m_freEdit;
    QLineEdit*   m_timeoutEdit;
    QLineEdit*   m_readcountEdit;
    QPushButton* m_freOkBtn;
    QPushButton* m_freCancelBtn;
    QPushButton* m_readcountOkBtn;
    QPushButton* m_readcountCancelBtn;

    QPushButton* m_startCollectData;
    QPushButton* m_stopCollectData;
    QPushButton* m_saveCollectData;
    QPushButton* m_delCollectData;
    QHBoxLayout* m_layoutData;

    QHBoxLayout *m_mainLayout1;
    QVBoxLayout *m_layout2;
    QHBoxLayout *m_layout12;
    QHBoxLayout *m_layout13;
    //QTimer *m_pTimer;
    QMutex  m_pMutex;
    queue<string> m_queDataLine;
    queue<string> m_queStasticMsgLine;

    ClientType_ m_dataType;
    DataMgr* m_pDataMgr;
};
class GroupEcgWindow : public GroupBasicWindow
{
public:
    GroupEcgWindow(QWidget *parent,DataMgr* pMgr);
    void initLayout();
    void updateWindow(MODE_TYPE mode);

private:

};



class GroupSpo2Window : public GroupBasicWindow
{
public:
    GroupSpo2Window(QWidget *parent,DataMgr* pMgr);
    void initLayout();
    void updateWindow(MODE_TYPE mode);

};

class GroupNibpWindow : public GroupBasicWindow
{
public:
    GroupNibpWindow(QWidget *parent,DataMgr* pMgr);
    void initLayout();

    void updateWindow(MODE_TYPE mode);

};

class GroupIbpWindow : public GroupBasicWindow
{
public:
    GroupIbpWindow(QWidget *parent,DataMgr* pMgr);
    void initLayout();
    void updateWindow(MODE_TYPE mode);

};

class GroupCo2Window : public GroupBasicWindow
{
public:
    GroupCo2Window(QWidget *parent,DataMgr* pMgr);
    void initLayout();
    void updateWindow(MODE_TYPE mode);

};
class GroupNarcoWindow : public GroupBasicWindow
{
public:
    GroupNarcoWindow(QWidget *parent,DataMgr* pMgr);
    void initLayout();
    void updateWindow(MODE_TYPE mode);

};
#endif // GROUPWINDOW_H
