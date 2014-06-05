/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jun 5 15:00:19 2014
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pStartServerBtn;
    QLabel *pServerStateLaber;
    QPushButton *pStopServerBtn;
    QCheckBox *pCollectDataCheckBox;
    QTextBrowser *pConnectMsgBrowser;
    QPushButton *pClearConnectMsgBtn;
    QComboBox *pGlobalPathCb;
    QPushButton *pAddGlobalPathBtn;
    QPushButton *pDelGlobalPathBtn;
    QLabel *pGlobalLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(967, 483);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pStartServerBtn = new QPushButton(centralWidget);
        pStartServerBtn->setObjectName(QString::fromUtf8("pStartServerBtn"));
        pStartServerBtn->setGeometry(QRect(30, 10, 99, 32));
        pServerStateLaber = new QLabel(centralWidget);
        pServerStateLaber->setObjectName(QString::fromUtf8("pServerStateLaber"));
        pServerStateLaber->setGeometry(QRect(140, 10, 171, 31));
        pStopServerBtn = new QPushButton(centralWidget);
        pStopServerBtn->setObjectName(QString::fromUtf8("pStopServerBtn"));
        pStopServerBtn->setGeometry(QRect(300, 10, 99, 32));
        pCollectDataCheckBox = new QCheckBox(centralWidget);
        pCollectDataCheckBox->setObjectName(QString::fromUtf8("pCollectDataCheckBox"));
        pCollectDataCheckBox->setGeometry(QRect(430, 10, 131, 27));
        pConnectMsgBrowser = new QTextBrowser(centralWidget);
        pConnectMsgBrowser->setObjectName(QString::fromUtf8("pConnectMsgBrowser"));
        pConnectMsgBrowser->setGeometry(QRect(30, 50, 231, 391));
        pClearConnectMsgBtn = new QPushButton(centralWidget);
        pClearConnectMsgBtn->setObjectName(QString::fromUtf8("pClearConnectMsgBtn"));
        pClearConnectMsgBtn->setGeometry(QRect(30, 460, 99, 32));
        pGlobalPathCb = new QComboBox(centralWidget);
        pGlobalPathCb->setObjectName(QString::fromUtf8("pGlobalPathCb"));
        pGlobalPathCb->setGeometry(QRect(660, 40, 171, 31));
        pAddGlobalPathBtn = new QPushButton(centralWidget);
        pAddGlobalPathBtn->setObjectName(QString::fromUtf8("pAddGlobalPathBtn"));
        pAddGlobalPathBtn->setGeometry(QRect(840, 40, 41, 27));
        pDelGlobalPathBtn = new QPushButton(centralWidget);
        pDelGlobalPathBtn->setObjectName(QString::fromUtf8("pDelGlobalPathBtn"));
        pDelGlobalPathBtn->setGeometry(QRect(890, 40, 41, 27));
        pGlobalLabel = new QLabel(centralWidget);
        pGlobalLabel->setObjectName(QString::fromUtf8("pGlobalLabel"));
        pGlobalLabel->setGeometry(QRect(580, 40, 71, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 967, 23));
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
        pStartServerBtn->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
        pServerStateLaber->setText(QApplication::translate("MainWindow", "server is running", 0, QApplication::UnicodeUTF8));
        pStopServerBtn->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        pCollectDataCheckBox->setText(QApplication::translate("MainWindow", "Collect datas", 0, QApplication::UnicodeUTF8));
        pClearConnectMsgBtn->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pAddGlobalPathBtn->setText(QApplication::translate("MainWindow", "add", 0, QApplication::UnicodeUTF8));
        pDelGlobalPathBtn->setText(QApplication::translate("MainWindow", "del", 0, QApplication::UnicodeUTF8));
        pGlobalLabel->setText(QApplication::translate("MainWindow", "data path", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
