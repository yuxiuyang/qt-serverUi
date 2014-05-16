#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "state.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pTestTimer = new QTimer(this);
    connect(ui->pStart_btn, SIGNAL(clicked()), this, SLOT(start_click()));
    connect(ui->pStop_btn, SIGNAL(clicked()), this, SLOT(stop_click()));
    connect(ui->pClearCon_btn, SIGNAL(clicked()), this, SLOT(clearConnectMsg_click()));
    connect(ui->pClear_btn, SIGNAL(clicked()), this, SLOT(clearDisplayMsg_click()));
    connect(ui->pSendIdCommand,SIGNAL(clicked()), this, SLOT(sendRequestData_click()));
    connect(ui->pGenerateData_btn,SIGNAL(clicked()),this,SLOT(generateData_click()));
    connect(ui->pExit_btn,SIGNAL(clicked()),this,SLOT(exit_click()));
    connect( m_pTestTimer, SIGNAL(timeout()), this, SLOT(sendTimer()) );
    connect(ui->pST_check, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(ui->pShowReadData_check,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(ui->pSendData_check,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));

    connect(ui->pNibp_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pSpo2_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pEcg_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));


    connect(ui->pFreOk_btn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(ui->pFreCancel_btn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(ui->pRcOk_btn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(ui->pRcCancel_btn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));


    ui->pStart_btn->setEnabled(true);
    ui->pStop_btn->setEnabled(false);


    setWindowTitle("Server....");
    m_pDataMgr = new DataMgr();
    m_pDataMgr->setWindow((void*)this);

    m_dataType = NIBP_CLIENT;
    ui->pNibp_rb->setChecked(true);
    ui->pFre_edit->setText(QString::number(m_pDataMgr->m_pNibpMgr->getFrequency()));
    ui->pTm_edit->setText(QString::number(m_pDataMgr->m_pNibpMgr->getTimeout()));
    ui->pTm_edit->setReadOnly(true);
    ui->pTm_edit->setEnabled(false);
    ui->pRc_edit->setText(QString::number(m_pDataMgr->m_pNibpMgr->getReadNum()));

    ui->pFreOk_btn->setEnabled(false);
    ui->pRcOk_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(false);
    ui->pFre_edit->setEnabled(false);
    ui->pStart_btn->setEnabled(false);
    ui->pStop_btn->setEnabled(false);

    ui->pGloupBox->setTitle("NIBP Setup");
    ui->pBox_Label->setText("NIBP");


    m_pTestTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::radioChange(){
    if(ui->pNibp_rb==sender()){
        m_dataType = NIBP_CLIENT;
        ui->pGloupBox->setTitle("NIBP Setup");
        ui->pBox_Label->setText("NIBP");
    }else if(ui->pSpo2_rb==sender()){
        ui->pGloupBox->setTitle("SPO2 Setup");
        ui->pBox_Label->setText("SPO2");
        m_dataType = SPO2_CLIENT;
    }else if(ui->pEcg_rb==sender()){
        ui->pGloupBox->setTitle("ECG Setup");
        ui->pBox_Label->setText("ECG");
        m_dataType = ECG_CLIENT;
    }else{

    }

    if(!m_pDataMgr->getMgrbyId(m_dataType)){
        cout<<"has not displayment"<<endl;
        return ;
    }
    ui->pFre_edit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getFrequency()));
    ui->pTm_edit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));
    ui->pTm_edit->setReadOnly(true);
    ui->pTm_edit->setEnabled(false);
    ui->pRc_edit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getReadNum()));

    ui->pFreOk_btn->setEnabled(false);
    ui->pRcOk_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(false);
    ui->pFre_edit->setEnabled(false);
    ui->pFreCancel_btn->setEnabled(true);
    ui->pRcCancel_btn->setEnabled(true);


    ui->pMsg_Txt->clear();
}

void MainWindow::start_click(){
    ui->pStart_label->setText("server running");
    ui->pStart_btn->setEnabled(false);
    ui->pStop_btn->setEnabled(true);

    DataDev::getInstance()->start();
//    ui->pStart_btn->setEnabled(true);
//    ui->pStop_btn->setEnabled(false);
//    ui->pStart_label->setText("server stop");
}

void MainWindow::stop_click(){
    ui->pStart_btn->setEnabled(true);
    ui->pStop_btn->setEnabled(false);
    ui->pStart_label->setText("server stop");
    DataDev::getInstance()->stop();
}

void MainWindow::clearConnectMsg_click(){
    ui->pConnectMsg_txt->clear();
}

void MainWindow::clearDisplayMsg_click(){
    //ui->pDisplay_txt->clear();
    ui->pMsg_Txt->clear();
}
void MainWindow::generateData_click(){
    m_pDataMgr->generateTestFile(m_dataType);
}
void MainWindow::sendRequestData_click(){
    m_pDataMgr->m_pLinkMgr->requestLinkMsg();
}

void MainWindow::freOk_click(){
    ui->pFreOk_btn->setEnabled(false);
    ui->pFreCancel_btn->setEnabled(true);
    ui->pFre_edit->setEnabled(false);
    ui->pFreCancel_btn->setFocus();

    QString str = ui->pFre_edit->text();
//printf("freOk_click str = %s\n",str.toStdString().c_str());
    bool toIntOk = false;
    int val = str.toInt(&toIntOk,10);
    if(!toIntOk){
        ui->pFre_edit->insert("error");
        return;
    }
    m_pDataMgr->m_pNibpMgr->setFrequency(val);
    State::getInstance()->setStateData(NIBP_FRE,val);
cout<<"freOk_click src="<<str.toStdString().c_str()<<"val="<<val<<endl;
    ui->pTm_edit->clear();
    ui->pTm_edit->insert(QString::number(m_pDataMgr->m_pNibpMgr->getTimeout()));
}

void MainWindow::freCancel_click(){
    ui->pFreOk_btn->setEnabled(true);
    ui->pFreCancel_btn->setEnabled(false);
    ui->pFre_edit->setEnabled(true);
    ui->pFreOk_btn->setFocus();

}

void MainWindow::rcOk_click(){
    ui->pRcOk_btn->setEnabled(false);
    ui->pRcCancel_btn->setEnabled(true);
    ui->pRc_edit->setEnabled(false);
    ui->pRcCancel_btn->setFocus();

    QString str = ui->pRc_edit->text();


    bool toIntOk = false;
    int val = str.toInt(&toIntOk,10);
    if(!toIntOk){
        ui->pFre_edit->insert("error");
        return;
    }
    m_pDataMgr->m_pNibpMgr->setReadNum(val);
    State::getInstance()->setStateData(NIBP_READRUM,val);
cout<<"rcOk_click src="<<str.toStdString().c_str()<<"val="<<val<<endl;
    //ui->pMsg_Txt->clear();
    //ui->pStatistics_txt->clear();
}

void MainWindow::rcCancel_click(){
    ui->pRcOk_btn->setEnabled(true);
    ui->pRcCancel_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(true);
    ui->pRcOk_btn->setFocus();
}

void MainWindow::appendMsg(const char* msg){
    m_pMutex.lock();
    //ui->pConnectMsg_txt->append(msg);
    m_queConnectMsgLine.push(msg);
    m_pMutex.unlock();
}
void MainWindow::exit_click(){
    close();
}
void MainWindow::appendData(const char* msg){
    m_pMutex.lock();
    m_queDataLine.push(msg);
    m_pMutex.unlock();
}
void MainWindow::appendData(const BYTE* msg,const int len){
    m_pMutex.lock();
    string strBuf="";
    char tmp[10]={0};
    for(int i=0;i<len;i++){
        sprintf(tmp,"%02x ",msg[i]);
        strBuf += tmp;
    }
    m_queDataLine.push(strBuf.c_str());
    m_pMutex.unlock();
}

void MainWindow::sendTimer(){
    //cout<<"helllooo"<<endl;
//    while(!m_queDataLine.empty()){
//         QTextCursor cursor =  ui->pDisplay_txt->textCursor();
//         cursor.movePosition(QTextCursor::End);
//         ui->pDisplay_txt->setTextCursor(cursor);
//         ui->pDisplay_txt->insertPlainText(m_queDataLine.front().c_str());
//         m_pMutex.lock();
//         m_queDataLine.pop();
//         m_pMutex.unlock();
//    }

    while(!m_queConnectMsgLine.empty()){
//         QTextCursor cursor =  ui->pConnectMsg_txt->textCursor();
//         cursor.movePosition(QTextCursor::End);
//         ui->pConnectMsg_txt->setTextCursor(cursor);
//         ui->pConnectMsg_txt->insertPlainText(m_queConnectMsgLine.front().c_str());
         ui->pConnectMsg_txt->append(m_queConnectMsgLine.front().c_str());
         m_pMutex.lock();
         m_queConnectMsgLine.pop();
         m_pMutex.unlock();
    }
//    while(!m_queStasticMsgLine.empty()){
//         QTextCursor cursor =  ui->pStatistics_txt->textCursor();
//         cursor.movePosition(QTextCursor::End);
//         ui->pStatistics_txt->setTextCursor(cursor);
//         ui->pStatistics_txt->insertPlainText(m_queStasticMsgLine.front().c_str());
//         m_pMutex.lock();
//         m_queStasticMsgLine.pop();
//         m_pMutex.unlock();
//    }

        checkLinkState();
}
void MainWindow::startTestCheckStateChanged(int state){
    if(ui->pST_check->isChecked()){
        m_pDataMgr->m_pNibpMgr->startTest();
        showData("");
    }else{
        m_pDataMgr->m_pNibpMgr->stopTest();
    }
}
void MainWindow::showReadDataCheckStateChanged(int state){
        m_pDataMgr->m_pNibpMgr->setShowDataSign(ui->pShowReadData_check->isChecked());
}
void MainWindow::sendDataCheckStateChanged(int state){
    m_pDataMgr->getMgrbyId(m_dataType)->startSendData(ui->pSendData_check->isChecked());
}

void MainWindow::showData(const char* buf){
    QTextCursor cursor =  ui->pMsg_Txt->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->pMsg_Txt->setTextCursor(cursor);
    ui->pMsg_Txt->insertPlainText(buf);
    ui->pMsg_Txt->append(buf);
}
void MainWindow::appendStatisticsMsg(char* buf){
    QTextCursor cursor =  ui->pStatistics_txt->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->pStatistics_txt->setTextCursor(cursor);
    ui->pStatistics_txt->append(buf);
}
void MainWindow::displayStatisicsResult(TESTMSG* msg){
    appendStatisticsMsg("------------caculator  start ------------");
    static char buf[100]={0};
    sprintf(buf,"used time=%ld",msg->usedtimeSum);
    appendStatisticsMsg(buf);
    sprintf(buf,"readSum=%ld",msg->readSum);
    appendStatisticsMsg(buf);
    sprintf(buf,"times=%ld",msg->times);
    appendStatisticsMsg(buf);

    sprintf(buf,"arg_time1=%4.1f (ms)",(float)msg->usedtimeSum/(float)msg->times);
    appendStatisticsMsg(buf);

//    sprintf(buf,"arg_time2=%4.1f (ts/s)",((float)msg->times/(float)msg->timeSum)*1000.);
//    appendStatisticsMsg(buf);

    sprintf(buf,"arg_read1=%4.1f (one each)",(float)msg->readSum/(float)msg->times);
    appendStatisticsMsg(buf);
    sprintf(buf,"arg_read2=%4.1f (n/s)",(float)msg->readSum/((float)msg->usedtimeSum/1000));
    appendStatisticsMsg(buf);

    appendStatisticsMsg("------------caculator  end ------------");
    /*QTextCursor cs=ui.chat_edit->textCursor();
                cs.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
                cs.movePosition(QTextCursor::NextBlock,QTextCursor::KeepAnchor, iLines);
                cs.removeSelectedText();
          qt qtextbrowser 添加字符
*/
}
void MainWindow::checkLinkState(){
    LinkState state = m_pDataMgr->m_pLinkMgr->getLinkState(m_dataType);
    switch(state){
    case link_not_comfirmId:
        ui->pSendIdCommand->setText("send comfire id commond");
        ui->pSendIdCommand->setEnabled(true);
        break;
    case link_and_comfirmId:
        ui->pSendIdCommand->setText("had comfirem id");
        ui->pSendIdCommand->setEnabled(false);
        break;
    case dis_link:
        ui->pSendIdCommand->setText("send comfire id commond");
        ui->pSendIdCommand->setEnabled(true);
        break;
    default:
        break;
    }

}
