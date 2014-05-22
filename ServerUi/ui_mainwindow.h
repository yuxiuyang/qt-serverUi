/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu May 22 08:41:27 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pExit_btn;
    QTextBrowser *pConnectMsg_txt;
    QPushButton *pClearCon_btn;
    QPushButton *pClearDisplay_btn;
    QLabel *pStart_label;
    QPushButton *pStop_btn;
    QRadioButton *pNibp_rb;
    QRadioButton *pEcg_rb;
    QRadioButton *pSpo2_rb;
    QGroupBox *pGloupBox;
    QLabel *pBox_Label;
    QTextBrowser *pMsg_Txt;
    QTextBrowser *pStatistics_txt;
    QGroupBox *pBtnGroup;
    QComboBox *pAlarm_cb;
    QComboBox *pValue_cb;
    QPushButton *pGenerateData_btn;
    QPushButton *pClear_btn;
    QPushButton *pSendIdCommand;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *pFre_edit;
    QLineEdit *pTm_edit;
    QLineEdit *pRc_edit;
    QPushButton *pFreOk_btn;
    QPushButton *pFreCancel_btn;
    QPushButton *pRcOk_btn;
    QPushButton *pRcCancel_btn;
    QGroupBox *pChecksGroup;
    QCheckBox *pST_check;
    QCheckBox *pSendData_check;
    QCheckBox *pShowReadData_check;
    QGroupBox *pCollectDatasBtnGroup;
    QPushButton *pSaveCollectDatas;
    QPushButton *pStartCollectDatas;
    QPushButton *pStopCollectDatas;
    QPushButton *pDelCollectDatas;
    QGroupBox *pCheckCollectDatasGroup;
    QLabel *pCollectDatas_label;
    QSlider *pReadStartPos_slider;
    QLabel *pReadPos_label;
    QSlider *pReadEndPos_slider;
    QPushButton *pUpdateFile;
    QRadioButton *pIbp_rb;
    QRadioButton *pCo2_rb;
    QRadioButton *pNarco_rb;
    QCheckBox *pCollectDatas_check;
    QPushButton *pStart_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(945, 689);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pExit_btn = new QPushButton(centralWidget);
        pExit_btn->setObjectName(QString::fromUtf8("pExit_btn"));
        pExit_btn->setGeometry(QRect(350, 560, 99, 32));
        pConnectMsg_txt = new QTextBrowser(centralWidget);
        pConnectMsg_txt->setObjectName(QString::fromUtf8("pConnectMsg_txt"));
        pConnectMsg_txt->setGeometry(QRect(10, 40, 221, 501));
        pConnectMsg_txt->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        pClearCon_btn = new QPushButton(centralWidget);
        pClearCon_btn->setObjectName(QString::fromUtf8("pClearCon_btn"));
        pClearCon_btn->setGeometry(QRect(10, 570, 99, 32));
        pClearDisplay_btn = new QPushButton(centralWidget);
        pClearDisplay_btn->setObjectName(QString::fromUtf8("pClearDisplay_btn"));
        pClearDisplay_btn->setGeometry(QRect(240, 560, 99, 32));
        pStart_label = new QLabel(centralWidget);
        pStart_label->setObjectName(QString::fromUtf8("pStart_label"));
        pStart_label->setGeometry(QRect(160, 0, 151, 22));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        pStart_label->setFont(font);
        pStop_btn = new QPushButton(centralWidget);
        pStop_btn->setObjectName(QString::fromUtf8("pStop_btn"));
        pStop_btn->setGeometry(QRect(340, 0, 99, 32));
        pNibp_rb = new QRadioButton(centralWidget);
        pNibp_rb->setObjectName(QString::fromUtf8("pNibp_rb"));
        pNibp_rb->setGeometry(QRect(860, 50, 71, 22));
        pEcg_rb = new QRadioButton(centralWidget);
        pEcg_rb->setObjectName(QString::fromUtf8("pEcg_rb"));
        pEcg_rb->setGeometry(QRect(860, 110, 61, 22));
        pSpo2_rb = new QRadioButton(centralWidget);
        pSpo2_rb->setObjectName(QString::fromUtf8("pSpo2_rb"));
        pSpo2_rb->setGeometry(QRect(860, 80, 71, 22));
        pGloupBox = new QGroupBox(centralWidget);
        pGloupBox->setObjectName(QString::fromUtf8("pGloupBox"));
        pGloupBox->setGeometry(QRect(240, 30, 611, 511));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        pGloupBox->setFont(font1);
        pGloupBox->setLayoutDirection(Qt::LeftToRight);
        pGloupBox->setAutoFillBackground(true);
        pGloupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pGloupBox->setFlat(false);
        pGloupBox->setCheckable(false);
        pBox_Label = new QLabel(pGloupBox);
        pBox_Label->setObjectName(QString::fromUtf8("pBox_Label"));
        pBox_Label->setGeometry(QRect(230, 0, 131, 31));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setWeight(75);
        pBox_Label->setFont(font2);
        pBox_Label->setLineWidth(1);
        pMsg_Txt = new QTextBrowser(pGloupBox);
        pMsg_Txt->setObjectName(QString::fromUtf8("pMsg_Txt"));
        pMsg_Txt->setGeometry(QRect(10, 30, 371, 201));
        QFont font3;
        font3.setPointSize(15);
        pMsg_Txt->setFont(font3);
        pStatistics_txt = new QTextBrowser(pGloupBox);
        pStatistics_txt->setObjectName(QString::fromUtf8("pStatistics_txt"));
        pStatistics_txt->setGeometry(QRect(320, 320, 291, 181));
        pBtnGroup = new QGroupBox(pGloupBox);
        pBtnGroup->setObjectName(QString::fromUtf8("pBtnGroup"));
        pBtnGroup->setGeometry(QRect(380, 90, 221, 141));
        pAlarm_cb = new QComboBox(pBtnGroup);
        pAlarm_cb->setObjectName(QString::fromUtf8("pAlarm_cb"));
        pAlarm_cb->setGeometry(QRect(0, 50, 211, 28));
        pValue_cb = new QComboBox(pBtnGroup);
        pValue_cb->setObjectName(QString::fromUtf8("pValue_cb"));
        pValue_cb->setGeometry(QRect(0, 10, 211, 28));
        pGenerateData_btn = new QPushButton(pBtnGroup);
        pGenerateData_btn->setObjectName(QString::fromUtf8("pGenerateData_btn"));
        pGenerateData_btn->setGeometry(QRect(10, 90, 121, 27));
        pClear_btn = new QPushButton(pGloupBox);
        pClear_btn->setObjectName(QString::fromUtf8("pClear_btn"));
        pClear_btn->setGeometry(QRect(382, 30, 101, 27));
        pSendIdCommand = new QPushButton(pGloupBox);
        pSendIdCommand->setObjectName(QString::fromUtf8("pSendIdCommand"));
        pSendIdCommand->setGeometry(QRect(380, 60, 221, 27));
        groupBox = new QGroupBox(pGloupBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 410, 301, 101));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 81, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 62, 17));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 71, 16));
        pFre_edit = new QLineEdit(groupBox);
        pFre_edit->setObjectName(QString::fromUtf8("pFre_edit"));
        pFre_edit->setGeometry(QRect(90, 10, 91, 27));
        pTm_edit = new QLineEdit(groupBox);
        pTm_edit->setObjectName(QString::fromUtf8("pTm_edit"));
        pTm_edit->setEnabled(false);
        pTm_edit->setGeometry(QRect(90, 40, 91, 27));
        pTm_edit->setReadOnly(true);
        pRc_edit = new QLineEdit(groupBox);
        pRc_edit->setObjectName(QString::fromUtf8("pRc_edit"));
        pRc_edit->setGeometry(QRect(90, 70, 91, 27));
        pFreOk_btn = new QPushButton(groupBox);
        pFreOk_btn->setObjectName(QString::fromUtf8("pFreOk_btn"));
        pFreOk_btn->setGeometry(QRect(190, 10, 31, 27));
        pFreCancel_btn = new QPushButton(groupBox);
        pFreCancel_btn->setObjectName(QString::fromUtf8("pFreCancel_btn"));
        pFreCancel_btn->setGeometry(QRect(230, 10, 61, 27));
        pRcOk_btn = new QPushButton(groupBox);
        pRcOk_btn->setObjectName(QString::fromUtf8("pRcOk_btn"));
        pRcOk_btn->setGeometry(QRect(190, 60, 31, 27));
        pRcCancel_btn = new QPushButton(groupBox);
        pRcCancel_btn->setObjectName(QString::fromUtf8("pRcCancel_btn"));
        pRcCancel_btn->setGeometry(QRect(230, 60, 61, 27));
        pChecksGroup = new QGroupBox(pGloupBox);
        pChecksGroup->setObjectName(QString::fromUtf8("pChecksGroup"));
        pChecksGroup->setGeometry(QRect(0, 300, 301, 111));
        pST_check = new QCheckBox(pChecksGroup);
        pST_check->setObjectName(QString::fromUtf8("pST_check"));
        pST_check->setGeometry(QRect(10, 20, 121, 22));
        pSendData_check = new QCheckBox(pChecksGroup);
        pSendData_check->setObjectName(QString::fromUtf8("pSendData_check"));
        pSendData_check->setGeometry(QRect(10, 50, 121, 22));
        pShowReadData_check = new QCheckBox(pChecksGroup);
        pShowReadData_check->setObjectName(QString::fromUtf8("pShowReadData_check"));
        pShowReadData_check->setGeometry(QRect(160, 20, 111, 22));
        pCollectDatasBtnGroup = new QGroupBox(pGloupBox);
        pCollectDatasBtnGroup->setObjectName(QString::fromUtf8("pCollectDatasBtnGroup"));
        pCollectDatasBtnGroup->setGeometry(QRect(320, 340, 291, 131));
        pSaveCollectDatas = new QPushButton(pCollectDatasBtnGroup);
        pSaveCollectDatas->setObjectName(QString::fromUtf8("pSaveCollectDatas"));
        pSaveCollectDatas->setGeometry(QRect(10, 90, 111, 32));
        pStartCollectDatas = new QPushButton(pCollectDatasBtnGroup);
        pStartCollectDatas->setObjectName(QString::fromUtf8("pStartCollectDatas"));
        pStartCollectDatas->setGeometry(QRect(10, 10, 231, 32));
        pStopCollectDatas = new QPushButton(pCollectDatasBtnGroup);
        pStopCollectDatas->setObjectName(QString::fromUtf8("pStopCollectDatas"));
        pStopCollectDatas->setGeometry(QRect(10, 50, 231, 32));
        pDelCollectDatas = new QPushButton(pCollectDatasBtnGroup);
        pDelCollectDatas->setObjectName(QString::fromUtf8("pDelCollectDatas"));
        pDelCollectDatas->setGeometry(QRect(130, 90, 111, 32));
        pCheckCollectDatasGroup = new QGroupBox(pGloupBox);
        pCheckCollectDatasGroup->setObjectName(QString::fromUtf8("pCheckCollectDatasGroup"));
        pCheckCollectDatasGroup->setGeometry(QRect(10, 100, 301, 111));
        pCollectDatas_label = new QLabel(pCheckCollectDatasGroup);
        pCollectDatas_label->setObjectName(QString::fromUtf8("pCollectDatas_label"));
        pCollectDatas_label->setGeometry(QRect(10, 20, 281, 51));
        QFont font4;
        font4.setPointSize(26);
        font4.setBold(true);
        font4.setWeight(75);
        pCollectDatas_label->setFont(font4);
        pReadStartPos_slider = new QSlider(pGloupBox);
        pReadStartPos_slider->setObjectName(QString::fromUtf8("pReadStartPos_slider"));
        pReadStartPos_slider->setGeometry(QRect(10, 270, 251, 21));
        pReadStartPos_slider->setOrientation(Qt::Horizontal);
        pReadPos_label = new QLabel(pGloupBox);
        pReadPos_label->setObjectName(QString::fromUtf8("pReadPos_label"));
        pReadPos_label->setGeometry(QRect(10, 240, 371, 22));
        pReadEndPos_slider = new QSlider(pGloupBox);
        pReadEndPos_slider->setObjectName(QString::fromUtf8("pReadEndPos_slider"));
        pReadEndPos_slider->setGeometry(QRect(260, 270, 251, 21));
        pReadEndPos_slider->setOrientation(Qt::Horizontal);
        pUpdateFile = new QPushButton(pGloupBox);
        pUpdateFile->setObjectName(QString::fromUtf8("pUpdateFile"));
        pUpdateFile->setGeometry(QRect(370, 240, 221, 27));
        pIbp_rb = new QRadioButton(centralWidget);
        pIbp_rb->setObjectName(QString::fromUtf8("pIbp_rb"));
        pIbp_rb->setGeometry(QRect(860, 140, 61, 22));
        pCo2_rb = new QRadioButton(centralWidget);
        pCo2_rb->setObjectName(QString::fromUtf8("pCo2_rb"));
        pCo2_rb->setGeometry(QRect(860, 170, 61, 22));
        pNarco_rb = new QRadioButton(centralWidget);
        pNarco_rb->setObjectName(QString::fromUtf8("pNarco_rb"));
        pNarco_rb->setGeometry(QRect(860, 200, 81, 22));
        pCollectDatas_check = new QCheckBox(centralWidget);
        pCollectDatas_check->setObjectName(QString::fromUtf8("pCollectDatas_check"));
        pCollectDatas_check->setGeometry(QRect(610, 10, 201, 22));
        pStart_btn = new QPushButton(centralWidget);
        pStart_btn->setObjectName(QString::fromUtf8("pStart_btn"));
        pStart_btn->setGeometry(QRect(30, 0, 99, 32));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 945, 32));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pExit_btn->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
        pClearCon_btn->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pClearDisplay_btn->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pStart_label->setText(QApplication::translate("MainWindow", "server is not start", 0, QApplication::UnicodeUTF8));
        pStop_btn->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        pNibp_rb->setText(QApplication::translate("MainWindow", "NIBP", 0, QApplication::UnicodeUTF8));
        pEcg_rb->setText(QApplication::translate("MainWindow", "ECG", 0, QApplication::UnicodeUTF8));
        pSpo2_rb->setText(QApplication::translate("MainWindow", "SPO2", 0, QApplication::UnicodeUTF8));
        pGloupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        pBox_Label->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        pBtnGroup->setTitle(QString());
        pGenerateData_btn->setText(QApplication::translate("MainWindow", "generateData", 0, QApplication::UnicodeUTF8));
        pClear_btn->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pSendIdCommand->setText(QApplication::translate("MainWindow", "send comfire id commond", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("MainWindow", "frequence", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "timeout", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "readcount", 0, QApplication::UnicodeUTF8));
        pFreOk_btn->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        pFreCancel_btn->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        pRcOk_btn->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        pRcCancel_btn->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        pChecksGroup->setTitle(QString());
        pST_check->setText(QApplication::translate("MainWindow", "start to test", 0, QApplication::UnicodeUTF8));
        pSendData_check->setText(QApplication::translate("MainWindow", "send data", 0, QApplication::UnicodeUTF8));
        pShowReadData_check->setText(QApplication::translate("MainWindow", "show data", 0, QApplication::UnicodeUTF8));
        pCollectDatasBtnGroup->setTitle(QString());
        pSaveCollectDatas->setText(QApplication::translate("MainWindow", "save datas", 0, QApplication::UnicodeUTF8));
        pStartCollectDatas->setText(QApplication::translate("MainWindow", "start collecting datas", 0, QApplication::UnicodeUTF8));
        pStopCollectDatas->setText(QApplication::translate("MainWindow", "stop collecting datas", 0, QApplication::UnicodeUTF8));
        pDelCollectDatas->setText(QApplication::translate("MainWindow", "delete datas", 0, QApplication::UnicodeUTF8));
        pCheckCollectDatasGroup->setTitle(QString());
        pCollectDatas_label->setText(QApplication::translate("MainWindow", "collecting datas", 0, QApplication::UnicodeUTF8));
        pReadPos_label->setText(QApplication::translate("MainWindow", "read data from start pos:     to end pos:", 0, QApplication::UnicodeUTF8));
        pUpdateFile->setText(QApplication::translate("MainWindow", "update file from start to end pos", 0, QApplication::UnicodeUTF8));
        pIbp_rb->setText(QApplication::translate("MainWindow", "IBP", 0, QApplication::UnicodeUTF8));
        pCo2_rb->setText(QApplication::translate("MainWindow", "CO2", 0, QApplication::UnicodeUTF8));
        pNarco_rb->setText(QApplication::translate("MainWindow", "NARCO", 0, QApplication::UnicodeUTF8));
        pCollectDatas_check->setText(QApplication::translate("MainWindow", "Collect datas", 0, QApplication::UnicodeUTF8));
        pStart_btn->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
