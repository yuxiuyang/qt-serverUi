/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu May 15 08:23:44 2014
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
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
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
    QPushButton *pStart_btn;
    QPushButton *pStop_btn;
    QRadioButton *pNibp_rb;
    QRadioButton *pEcg_rb;
    QRadioButton *pSpo2_rb;
    QGroupBox *pGloupBox;
    QLabel *pBox_Label;
    QTextBrowser *pMsg_Txt;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *pFre_edit;
    QLineEdit *pTm_edit;
    QLineEdit *pRc_edit;
    QPushButton *pFreOk_btn;
    QPushButton *pRcOk_btn;
    QPushButton *pFreCancel_btn;
    QPushButton *pRcCancel_btn;
    QCheckBox *pST_check;
    QCheckBox *pShowReadData_check;
    QPushButton *pClear_btn;
    QPushButton *pExit_btn_2;
    QPushButton *pSendIdCommand;
    QPushButton *pSendData;
    QPushButton *pStopSend;
    QPushButton *pGenerateData_btn;
    QTextBrowser *pStatistics_txt;
    QCheckBox *pSendData_check;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(931, 625);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pExit_btn = new QPushButton(centralWidget);
        pExit_btn->setObjectName(QString::fromUtf8("pExit_btn"));
        pExit_btn->setGeometry(QRect(420, 510, 99, 32));
        pConnectMsg_txt = new QTextBrowser(centralWidget);
        pConnectMsg_txt->setObjectName(QString::fromUtf8("pConnectMsg_txt"));
        pConnectMsg_txt->setGeometry(QRect(10, 40, 221, 441));
        pConnectMsg_txt->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        pClearCon_btn = new QPushButton(centralWidget);
        pClearCon_btn->setObjectName(QString::fromUtf8("pClearCon_btn"));
        pClearCon_btn->setGeometry(QRect(10, 500, 99, 32));
        pClearDisplay_btn = new QPushButton(centralWidget);
        pClearDisplay_btn->setObjectName(QString::fromUtf8("pClearDisplay_btn"));
        pClearDisplay_btn->setGeometry(QRect(270, 510, 99, 32));
        pStart_label = new QLabel(centralWidget);
        pStart_label->setObjectName(QString::fromUtf8("pStart_label"));
        pStart_label->setGeometry(QRect(160, 0, 151, 22));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        pStart_label->setFont(font);
        pStart_btn = new QPushButton(centralWidget);
        pStart_btn->setObjectName(QString::fromUtf8("pStart_btn"));
        pStart_btn->setGeometry(QRect(20, 0, 99, 32));
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
        pGloupBox->setGeometry(QRect(240, 30, 611, 461));
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
        pMsg_Txt->setGeometry(QRect(10, 40, 311, 211));
        QFont font3;
        font3.setPointSize(15);
        pMsg_Txt->setFont(font3);
        label_2 = new QLabel(pGloupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 340, 81, 20));
        label_3 = new QLabel(pGloupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 380, 62, 17));
        label = new QLabel(pGloupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 410, 71, 20));
        pFre_edit = new QLineEdit(pGloupBox);
        pFre_edit->setObjectName(QString::fromUtf8("pFre_edit"));
        pFre_edit->setGeometry(QRect(90, 340, 91, 27));
        pTm_edit = new QLineEdit(pGloupBox);
        pTm_edit->setObjectName(QString::fromUtf8("pTm_edit"));
        pTm_edit->setEnabled(false);
        pTm_edit->setGeometry(QRect(90, 370, 91, 27));
        pTm_edit->setReadOnly(true);
        pRc_edit = new QLineEdit(pGloupBox);
        pRc_edit->setObjectName(QString::fromUtf8("pRc_edit"));
        pRc_edit->setGeometry(QRect(90, 410, 91, 27));
        pFreOk_btn = new QPushButton(pGloupBox);
        pFreOk_btn->setObjectName(QString::fromUtf8("pFreOk_btn"));
        pFreOk_btn->setGeometry(QRect(190, 340, 31, 27));
        pRcOk_btn = new QPushButton(pGloupBox);
        pRcOk_btn->setObjectName(QString::fromUtf8("pRcOk_btn"));
        pRcOk_btn->setGeometry(QRect(190, 410, 31, 27));
        pFreCancel_btn = new QPushButton(pGloupBox);
        pFreCancel_btn->setObjectName(QString::fromUtf8("pFreCancel_btn"));
        pFreCancel_btn->setGeometry(QRect(230, 340, 61, 27));
        pRcCancel_btn = new QPushButton(pGloupBox);
        pRcCancel_btn->setObjectName(QString::fromUtf8("pRcCancel_btn"));
        pRcCancel_btn->setGeometry(QRect(230, 410, 61, 27));
        pST_check = new QCheckBox(pGloupBox);
        pST_check->setObjectName(QString::fromUtf8("pST_check"));
        pST_check->setGeometry(QRect(10, 270, 121, 22));
        pShowReadData_check = new QCheckBox(pGloupBox);
        pShowReadData_check->setObjectName(QString::fromUtf8("pShowReadData_check"));
        pShowReadData_check->setGeometry(QRect(160, 270, 111, 22));
        pClear_btn = new QPushButton(pGloupBox);
        pClear_btn->setObjectName(QString::fromUtf8("pClear_btn"));
        pClear_btn->setGeometry(QRect(340, 40, 93, 27));
        pExit_btn_2 = new QPushButton(pGloupBox);
        pExit_btn_2->setObjectName(QString::fromUtf8("pExit_btn_2"));
        pExit_btn_2->setGeometry(QRect(440, 40, 93, 27));
        pSendIdCommand = new QPushButton(pGloupBox);
        pSendIdCommand->setObjectName(QString::fromUtf8("pSendIdCommand"));
        pSendIdCommand->setGeometry(QRect(340, 100, 211, 27));
        pSendData = new QPushButton(pGloupBox);
        pSendData->setObjectName(QString::fromUtf8("pSendData"));
        pSendData->setGeometry(QRect(340, 140, 121, 27));
        pStopSend = new QPushButton(pGloupBox);
        pStopSend->setObjectName(QString::fromUtf8("pStopSend"));
        pStopSend->setGeometry(QRect(340, 170, 121, 27));
        pGenerateData_btn = new QPushButton(pGloupBox);
        pGenerateData_btn->setObjectName(QString::fromUtf8("pGenerateData_btn"));
        pGenerateData_btn->setGeometry(QRect(340, 200, 121, 27));
        pStatistics_txt = new QTextBrowser(pGloupBox);
        pStatistics_txt->setObjectName(QString::fromUtf8("pStatistics_txt"));
        pStatistics_txt->setGeometry(QRect(300, 270, 301, 181));
        pSendData_check = new QCheckBox(pGloupBox);
        pSendData_check->setObjectName(QString::fromUtf8("pSendData_check"));
        pSendData_check->setGeometry(QRect(10, 300, 121, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 931, 32));
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
        pStart_btn->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
        pStop_btn->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        pNibp_rb->setText(QApplication::translate("MainWindow", "NIBP", 0, QApplication::UnicodeUTF8));
        pEcg_rb->setText(QApplication::translate("MainWindow", "ECG", 0, QApplication::UnicodeUTF8));
        pSpo2_rb->setText(QApplication::translate("MainWindow", "SPO2", 0, QApplication::UnicodeUTF8));
        pGloupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        pBox_Label->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "frequence", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "timeout", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "readcount", 0, QApplication::UnicodeUTF8));
        pFreOk_btn->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        pRcOk_btn->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        pFreCancel_btn->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        pRcCancel_btn->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        pST_check->setText(QApplication::translate("MainWindow", "start to test", 0, QApplication::UnicodeUTF8));
        pShowReadData_check->setText(QApplication::translate("MainWindow", "show data", 0, QApplication::UnicodeUTF8));
        pClear_btn->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pExit_btn_2->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
        pSendIdCommand->setText(QApplication::translate("MainWindow", "send comfire id commond", 0, QApplication::UnicodeUTF8));
        pSendData->setText(QApplication::translate("MainWindow", "send data", 0, QApplication::UnicodeUTF8));
        pStopSend->setText(QApplication::translate("MainWindow", "stop send", 0, QApplication::UnicodeUTF8));
        pGenerateData_btn->setText(QApplication::translate("MainWindow", "generateData", 0, QApplication::UnicodeUTF8));
        pSendData_check->setText(QApplication::translate("MainWindow", "send data", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
