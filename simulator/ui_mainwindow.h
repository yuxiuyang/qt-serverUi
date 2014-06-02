/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Sat May 31 18:12:34 2014
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(802, 568);
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
    pCollectDataCheckBox->setGeometry(QRect(520, 10, 131, 27));
    pConnectMsgBrowser = new QTextBrowser(centralWidget);
    pConnectMsgBrowser->setObjectName(QString::fromUtf8("pConnectMsgBrowser"));
    pConnectMsgBrowser->setGeometry(QRect(30, 50, 231, 391));
    pClearConnectMsgBtn = new QPushButton(centralWidget);
    pClearConnectMsgBtn->setObjectName(QString::fromUtf8("pClearConnectMsgBtn"));
    pClearConnectMsgBtn->setGeometry(QRect(30, 460, 99, 32));
    MainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 802, 32));
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
    Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_MAINWINDOW_H
