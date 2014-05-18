#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "state.h"
#include "../include/global.h"
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
    connect(ui->pSaveCollectDatas,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect( m_pTestTimer, SIGNAL(timeout()), this, SLOT(sendTimer()) );
    connect(ui->pST_check, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(ui->pShowReadData_check,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(ui->pSendData_check,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));
    connect(ui->pCollectDatas_check,SIGNAL(stateChanged(int)),this,SLOT(collectDatasCheckStateChanged(int)));

    connect(ui->pReadStartPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));
    connect(ui->pReadEndPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));

    connect(ui->pNibp_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pSpo2_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pEcg_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pIbp_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pCo2_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pNarco_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));


    connect(ui->pFreOk_btn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(ui->pFreCancel_btn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(ui->pRcOk_btn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(ui->pRcCancel_btn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));


    connect(ui->pValue_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(ui->pAlarm_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(alarmChanged(int)));

    ui->pStart_btn->setEnabled(true);
    ui->pStop_btn->hide();
    ui->pStart_label->setText("server running");


    setWindowTitle("Server....");
    m_pDataMgr = new DataMgr();
    m_pDataMgr->setWindow((void*)this);

    m_dataType = (ClientType_)State::getInstance()->getStateData(CUR_CLIENT);

    ui->pCollectDatasBtnGroup->hide();
    ui->pCheckCollectDatasGroup->hide();


    ui->pReadPos_label->setText("read data from start pos: 0  to end pos: 100");


    m_pTestTimer->start(1000);

    g_InitGlobalText();

    initClient();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initClient(){
    if(m_dataType==NIBP_CLIENT){
        ui->pGloupBox->setTitle("NIBP Setup");
        ui->pBox_Label->setText("NIBP");
        ui->pNibp_rb->setChecked(true);
    }else if(m_dataType==SPO2_CLIENT){
        ui->pGloupBox->setTitle("SPO2 Setup");
        ui->pBox_Label->setText("SPO2");
        ui->pSpo2_rb->setChecked(true);
    }else if(m_dataType==ECG_CLIENT){
        ui->pGloupBox->setTitle("ECG Setup");
        ui->pBox_Label->setText("ECG");
        ui->pEcg_rb->setChecked(true);
    }else if(m_dataType==IBP_CLIENT){
        ui->pGloupBox->setTitle("IBP Setup");
        ui->pBox_Label->setText("IBP");
        ui->pIbp_rb->setChecked(true);
    }else if(m_dataType==CO2_CLIENT){
        ui->pGloupBox->setTitle("CO2 Setup");
        ui->pBox_Label->setText("CO2");
        ui->pCo2_rb->setChecked(true);
    }else if(m_dataType==NARCO_CLIENT){
        ui->pGloupBox->setTitle("NARCO Setup");
        ui->pBox_Label->setText("NARCO");
        ui->pNarco_rb->setChecked(true);
    }
    handleCB();
    handleSlider();

    printf("radioChange  m_dataType=%d\n ",m_dataType);
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

    if(m_pDataMgr->getMgrbyId(m_dataType)->isTestRunning()){
        ui->pST_check->setChecked(true);
    }else{
        ui->pST_check->setChecked(false);
    }
    if(m_pDataMgr->getMgrbyId(m_dataType)->isShowData()){
        ui->pShowReadData_check->setChecked(true);
    }else{
        ui->pShowReadData_check->setChecked(false);
    }
    if(m_pDataMgr->getMgrbyId(m_dataType)->getSendDataState()){
        ui->pSendData_check->setChecked(true);
    }else{
        ui->pSendData_check->setChecked(false);
    }

    ui->pMsg_Txt->clear();
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
    }else if(ui->pSpo2_rb==sender()){
        m_dataType = SPO2_CLIENT;
    }else if(ui->pEcg_rb==sender()){
        m_dataType = ECG_CLIENT;
    }else if(ui->pIbp_rb==sender()){
        m_dataType = IBP_CLIENT;
    }else if(ui->pCo2_rb==sender()){
        m_dataType = CO2_CLIENT;
    }else if(ui->pNarco_rb==sender()){
        m_dataType = NARCO_CLIENT;
    }else{
        m_dataType = NIBP_CLIENT;
    }
    State::getInstance()->setStateData(CUR_CLIENT,m_dataType);
    initClient();
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
    m_pDataMgr->getMgrbyId(m_dataType)->setFrequency(val);

    cout<<"freOk_click src="<<str.toStdString().c_str()<<"val="<<val<<endl;
    ui->pTm_edit->clear();
    ui->pTm_edit->insert(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));

    setSave(m_dataType,SAVE_FRE,val);
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
    m_pDataMgr->getMgrbyId(m_dataType)->setReadNum(val);
    cout<<"rcOk_click src="<<str.toStdString().c_str()<<"val="<<val<<endl;
    setSave(m_dataType,SAVE_READNUM,val);
}

void MainWindow::rcCancel_click(){
    ui->pRcOk_btn->setEnabled(true);
    ui->pRcCancel_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(true);
    ui->pRcOk_btn->setFocus();

    ui->pGloupBox->hide();
}

void MainWindow::saveCollectDatas_click(){
    cout<<"save Collect datas success"<<endl;
}

void MainWindow::valueChanged(int index){
    cout<<"valuechanged index="<<index<<"   value="<<ui->pValue_cb->currentText().toStdString().c_str()<<endl;
}

void MainWindow::alarmChanged(int index){

}

void MainWindow::setValue_slider(int val){
    char buf[200]={0};
    sprintf(buf,"read data from start pos: %lu   to end pos: %lu",ui->pReadStartPos_slider->value(),ui->pReadEndPos_slider->value());

    ui->pReadPos_label->setText(buf);

    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileStartPos(ui->pReadStartPos_slider->value());
    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileEndPos(ui->pReadEndPos_slider->value());

    setSave(m_dataType,SAVE_FILE_START_POS,ui->pReadStartPos_slider->value());//save the datas
    setSave(m_dataType,SAVE_FILE_END_POS,ui->pReadEndPos_slider->value());
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
    setSave(m_dataType,SAVE_TEST,ui->pST_check->isChecked());
    if(ui->pST_check->isChecked()){
        m_pDataMgr->getMgrbyId(m_dataType)->startTest();
        showData(m_dataType,"");
    }else{
        m_pDataMgr->getMgrbyId(m_dataType)->stopTest();
    }
}
void MainWindow::showReadDataCheckStateChanged(int state){
    //cout<<"pShowReadData_check->isChecked()="<<ui->pShowReadData_check->isChecked()<<endl;
    setSave(m_dataType,SAVE_SHOWDATA,ui->pShowReadData_check->isChecked());
    m_pDataMgr->getMgrbyId(m_dataType)->setShowDataSign(ui->pShowReadData_check->isChecked());
}
void MainWindow::sendDataCheckStateChanged(int state){
    setSave(m_dataType,SAVE_SENDDATA,ui->pSendData_check->isChecked());
    m_pDataMgr->getMgrbyId(m_dataType)->startSendData(ui->pSendData_check->isChecked());
}

void MainWindow::collectDatasCheckStateChanged(int state){
    ui->pMsg_Txt->clear();
    if(ui->pCollectDatas_check->isChecked()){
        ui->pCollectDatas_check->setText("Collecting data");

        ui->pCollectDatasBtnGroup->move(ui->pBtnGroup->x(),ui->pBtnGroup->y());
        ui->pBtnGroup->hide();
        ui->pCollectDatasBtnGroup->show();

        ui->pCheckCollectDatasGroup->move(ui->pChecksGroup->x(),ui->pChecksGroup->y());
        ui->pChecksGroup->hide();
        ui->pCheckCollectDatasGroup->show();


        ui->pReadEndPos_slider->hide();
        ui->pReadStartPos_slider->hide();
        ui->pReadPos_label->hide();

    }else{
        ui->pCollectDatas_check->setText("Collect datas");


        ui->pBtnGroup->show();
        ui->pCollectDatasBtnGroup->hide();
        ui->pChecksGroup->show();
        ui->pCheckCollectDatasGroup->hide();

        ui->pReadEndPos_slider->show();
        ui->pReadStartPos_slider->show();
        ui->pReadPos_label->show();

    }
}

void MainWindow::showData(ClientType_ id,const char* buf){
    if(id != m_dataType) return ;

    QTextCursor cursor =  ui->pMsg_Txt->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->pMsg_Txt->setTextCursor(cursor);
    ui->pMsg_Txt->insertPlainText(buf);
    //ui->pMsg_Txt->append(buf);
}
void MainWindow::appendStatisticsMsg(char* buf){
    QTextCursor cursor =  ui->pStatistics_txt->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->pStatistics_txt->setTextCursor(cursor);
    ui->pStatistics_txt->append(buf);
}
void MainWindow::displayStatisicsResult(ClientType_ id,TESTMSG* msg){
    if(id != m_dataType) return;
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
void MainWindow::handleSlider(){
    long max = m_pDataMgr->getMgrbyId(m_dataType)->getFileSize();

    long mid = max/2-10;

    cout<<"start slider   range  0 ~ "<<mid<<"  val="<<getSaveValue(m_dataType,SAVE_FILE_START_POS)<<endl;
    cout<<"end slider     range  "<<mid+1<<"~ "<<max<<"  val="<<getSaveValue(m_dataType,SAVE_FILE_END_POS)<<endl;
    ui->pReadStartPos_slider->setRange(0,mid);
    ui->pReadStartPos_slider->setValue(getSaveValue(m_dataType,SAVE_FILE_START_POS));
    ui->pReadEndPos_slider->setRange(mid+1,max);
    ui->pReadEndPos_slider->setValue(getSaveValue(m_dataType,SAVE_FILE_END_POS));


    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileStartPos(ui->pReadStartPos_slider->value());
    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileEndPos(ui->pReadEndPos_slider->value());
}

void MainWindow::handleCB(){
    ui->pAlarm_cb->hide();
    ui->pValue_cb->clear();
    switch(m_dataType){
    case ECG_CLIENT:
        {
            ui->pValue_cb->insertItems(0,g_ecgValues);
            ui->pValue_cb->setCurrentIndex(1);

            ui->pAlarm_cb->show();
            ui->pAlarm_cb->insertItems(0,g_ecgAlarms);
            ui->pAlarm_cb->setCurrentIndex(0);

        }
        break;
    case SPO2_CLIENT:
        {
            ui->pValue_cb->insertItems(0,g_spo2Values);
            ui->pValue_cb->setCurrentIndex(0);
        }
        break;
    case NIBP_CLIENT:
        {
            ui->pValue_cb->insertItems(0,g_nibpValues);
            ui->pValue_cb->setCurrentIndex(0);
        }
        break;
    case IBP_CLIENT:
        ui->pValue_cb->insertItems(0,g_ibpValues);
        ui->pValue_cb->setCurrentIndex(0);
        break;
    case CO2_CLIENT:
        ui->pValue_cb->insertItems(0,g_co2Values);
        ui->pValue_cb->setCurrentIndex(0);
        break;
    case NARCO_CLIENT:
        ui->pValue_cb->insertItems(0,g_narcoValues);
        ui->pValue_cb->setCurrentIndex(0);
        break;
    default:
        break;
    }
}

void MainWindow::setSave(ClientType_ id, SAVE_TYPE saveType,int val) {
        switch (id) {
        case ECG_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                State::getInstance()->setStateData(ECG_FRE, val);
                break;
            case SAVE_READNUM:
                State::getInstance()->setStateData(ECG_READRUM, val);
                break;
            case SAVE_FILE_START_POS:
                State::getInstance()->setStateData(ECG_FILE_START_POS, val);
                break;
            case SAVE_FILE_END_POS:
                State::getInstance()->setStateData(ECG_FILE_END_POS, val);
                break;
            case SAVE_TEST:
                State::getInstance()->setStateData(ECG_TEST, val);
                break;
            case SAVE_SHOWDATA:
                State::getInstance()->setStateData(ECG_SHOWDATA, val);
                break;
            case SAVE_SENDDATA:
                State::getInstance()->setStateData(ECG_SENDDATA, val);
                break;
            default:
                break;
            }
            break;
        case SPO2_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                State::getInstance()->setStateData(SPO2_FRE, val);
                break;
            case SAVE_READNUM:
                State::getInstance()->setStateData(SPO2_READRUM, val);
                break;
            case SAVE_FILE_START_POS:
                State::getInstance()->setStateData(SPO2_FILE_START_POS, val);
                break;
            case SAVE_FILE_END_POS:
                State::getInstance()->setStateData(SPO2_FILE_END_POS, val);
                break;
            case SAVE_TEST:
                State::getInstance()->setStateData(SPO2_TEST, val);
                break;
            case SAVE_SHOWDATA:
                State::getInstance()->setStateData(SPO2_SHOWDATA, val);
                break;
            case SAVE_SENDDATA:
                State::getInstance()->setStateData(SPO2_SENDDATA, val);
                break;
            default:
                break;
            }
            break;
        case CO2_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                State::getInstance()->setStateData(CO2_FRE, val);
                break;
            case SAVE_READNUM:
                State::getInstance()->setStateData(CO2_READRUM, val);
                break;
            case SAVE_FILE_START_POS:
                State::getInstance()->setStateData(CO2_FILE_START_POS, val);
                break;
            case SAVE_FILE_END_POS:
                State::getInstance()->setStateData(CO2_FILE_END_POS, val);
                break;
            case SAVE_TEST:
                State::getInstance()->setStateData(CO2_TEST, val);
                break;
            case SAVE_SHOWDATA:
                State::getInstance()->setStateData(CO2_SHOWDATA, val);
                break;
            case SAVE_SENDDATA:
                State::getInstance()->setStateData(CO2_SENDDATA, val);
                break;
            default:
                break;
            }
            break;
        case NARCO_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                State::getInstance()->setStateData(NARCO_FRE, val);
                break;
            case SAVE_READNUM:
                State::getInstance()->setStateData(NARCO_READRUM, val);
                break;
            case SAVE_FILE_START_POS:
                State::getInstance()->setStateData(NARCO_FILE_START_POS, val);
                break;
            case SAVE_FILE_END_POS:
                State::getInstance()->setStateData(NARCO_FILE_END_POS, val);
                break;
            case SAVE_TEST:
                State::getInstance()->setStateData(NARCO_TEST, val);
                break;
            case SAVE_SHOWDATA:
                State::getInstance()->setStateData(NARCO_SHOWDATA, val);
                break;
            case SAVE_SENDDATA:
                State::getInstance()->setStateData(NARCO_SENDDATA, val);
                break;
            default:
                break;
            }
            break;
        case NIBP_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                State::getInstance()->setStateData(NIBP_FRE, val);
                break;
            case SAVE_READNUM:
                State::getInstance()->setStateData(NIBP_READRUM, val);
                break;
            case SAVE_FILE_START_POS:
                State::getInstance()->setStateData(NIBP_FILE_START_POS, val);
                break;
            case SAVE_FILE_END_POS:
                State::getInstance()->setStateData(NIBP_FILE_END_POS, val);
                break;
            case SAVE_TEST:
                State::getInstance()->setStateData(NIBP_TEST, val);
                break;
            case SAVE_SHOWDATA:
                State::getInstance()->setStateData(NIBP_SHOWDATA, val);
                break;
            case SAVE_SENDDATA:
                State::getInstance()->setStateData(NIBP_SENDDATA, val);
                break;
            default:
                break;
            }
            break;
        case IBP_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                State::getInstance()->setStateData(IBP_FRE, val);
                break;
            case SAVE_READNUM:
                State::getInstance()->setStateData(IBP_READRUM, val);
                break;
            case SAVE_FILE_START_POS:
                State::getInstance()->setStateData(IBP_FILE_START_POS, val);
                break;
            case SAVE_FILE_END_POS:
                State::getInstance()->setStateData(IBP_FILE_END_POS, val);
                break;
            case SAVE_TEST:
                State::getInstance()->setStateData(IBP_TEST, val);
                break;
            case SAVE_SHOWDATA:
                State::getInstance()->setStateData(IBP_SHOWDATA, val);
                break;
            case SAVE_SENDDATA:
                State::getInstance()->setStateData(IBP_SENDDATA, val);
                break;
            default:
                break;
            }
            break;
        default:
                break;
        }
}


int MainWindow::getSaveValue(ClientType_ id, SAVE_TYPE saveType) {
        switch (id) {
        case ECG_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                return State::getInstance()->getStateData(ECG_FRE);
                break;
            case SAVE_READNUM:
                return State::getInstance()->getStateData(ECG_READRUM);
                break;
            case SAVE_FILE_START_POS:
                return State::getInstance()->getStateData(ECG_FILE_START_POS);
                break;
            case SAVE_FILE_END_POS:
                return State::getInstance()->getStateData(ECG_FILE_END_POS);
                break;
            case SAVE_TEST:
                return State::getInstance()->getStateData(ECG_TEST);
                break;
            case SAVE_SHOWDATA:
                return State::getInstance()->getStateData(ECG_SHOWDATA);
                break;
            case SAVE_SENDDATA:
                return State::getInstance()->getStateData(ECG_SENDDATA);
                break;
            default:
                break;
            }
            break;
        case SPO2_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                return State::getInstance()->getStateData(SPO2_FRE);
                break;
            case SAVE_READNUM:
                return State::getInstance()->getStateData(SPO2_READRUM);
                break;
            case SAVE_FILE_START_POS:
                return State::getInstance()->getStateData(SPO2_FILE_START_POS);
                break;
            case SAVE_FILE_END_POS:
                return State::getInstance()->getStateData(SPO2_FILE_END_POS);
                break;
            case SAVE_TEST:
                return State::getInstance()->getStateData(SPO2_TEST);
                break;
            case SAVE_SHOWDATA:
                return State::getInstance()->getStateData(SPO2_SHOWDATA);
                break;
            case SAVE_SENDDATA:
                return State::getInstance()->getStateData(SPO2_SENDDATA);
                break;
            default:
                break;
            }
            break;
        case CO2_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                return State::getInstance()->getStateData(CO2_FRE);
                break;
            case SAVE_READNUM:
                return State::getInstance()->getStateData(CO2_READRUM);
                break;
            case SAVE_FILE_START_POS:
                return State::getInstance()->getStateData(CO2_FILE_START_POS);
                break;
            case SAVE_FILE_END_POS:
                return State::getInstance()->getStateData(CO2_FILE_END_POS);
                break;
            case SAVE_TEST:
                return State::getInstance()->getStateData(CO2_TEST);
                break;
            case SAVE_SHOWDATA:
                return State::getInstance()->getStateData(CO2_SHOWDATA);
                break;
            case SAVE_SENDDATA:
                return State::getInstance()->getStateData(CO2_SENDDATA);
                break;
            default:
                break;
            }
            break;
        case NARCO_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                return State::getInstance()->getStateData(NARCO_FRE);
                break;
            case SAVE_READNUM:
                return State::getInstance()->getStateData(NARCO_READRUM);
                break;
            case SAVE_FILE_START_POS:
                return State::getInstance()->getStateData(NARCO_FILE_START_POS);
                break;
            case SAVE_FILE_END_POS:
                return State::getInstance()->getStateData(NARCO_FILE_END_POS);
                break;
            case SAVE_TEST:
                return State::getInstance()->getStateData(NARCO_TEST);
                break;
            case SAVE_SHOWDATA:
                return State::getInstance()->getStateData(NARCO_SHOWDATA);
                break;
            case SAVE_SENDDATA:
                return State::getInstance()->getStateData(NARCO_SENDDATA);
                break;
            default:
                break;
            }
            break;
        case NIBP_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                return State::getInstance()->getStateData(NIBP_FRE);
                break;
            case SAVE_READNUM:
                return State::getInstance()->getStateData(NIBP_READRUM);
                break;
            case SAVE_FILE_START_POS:
                return State::getInstance()->getStateData(NIBP_FILE_START_POS);
                break;
            case SAVE_FILE_END_POS:
                return State::getInstance()->getStateData(NIBP_FILE_END_POS);
                break;
            case SAVE_TEST:
                return State::getInstance()->getStateData(NIBP_TEST);
                break;
            case SAVE_SHOWDATA:
                return State::getInstance()->getStateData(NIBP_SHOWDATA);
                break;
            case SAVE_SENDDATA:
                return State::getInstance()->getStateData(NIBP_SENDDATA);
                break;
            default:
                break;
            }
            break;
        case IBP_CLIENT:
            switch(saveType){
            case SAVE_FRE:
                return State::getInstance()->getStateData(IBP_FRE);
                break;
            case SAVE_READNUM:
                return State::getInstance()->getStateData(IBP_READRUM);
                break;
            case SAVE_FILE_START_POS:
                return State::getInstance()->getStateData(IBP_FILE_START_POS);
                break;
            case SAVE_FILE_END_POS:
                return State::getInstance()->getStateData(IBP_FILE_END_POS);
                break;
            case SAVE_TEST:
                return State::getInstance()->getStateData(IBP_TEST);
                break;
            case SAVE_SHOWDATA:
                return State::getInstance()->getStateData(IBP_SHOWDATA);
                break;
            case SAVE_SENDDATA:
                return State::getInstance()->getStateData(IBP_SENDDATA);
                break;
            default:
                break;
            }
            break;
        default:
                break;
        }
        return -1;
}


