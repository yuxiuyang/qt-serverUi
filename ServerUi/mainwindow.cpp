#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "state.h"
#include "../include/global.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
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
    connect(ui->pStartCollectDatas,SIGNAL(clicked()),this,SLOT(startCollectDatas_click()));
    connect(ui->pStopCollectDatas,SIGNAL(clicked()),this,SLOT(stopCollectDatas_click()));
    connect(ui->pSaveCollectDatas,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect(ui->pDelCollectDatas,SIGNAL(clicked()),this,SLOT(delCollectDatas_click()));

    connect(ui->pAddValue_btn,SIGNAL(clicked()),this,SLOT(addValueToCb_click()));
    connect(ui->pDelValue_btn,SIGNAL(clicked()),this,SLOT(delValueToCb_click()));
    connect(ui->pAddAlarm_btn,SIGNAL(clicked()),this,SLOT(addAlarmToCb_click()));
    connect(ui->pDelAlarm_btn,SIGNAL(clicked()),this,SLOT(delAlarmToCb_click()));


    connect(ui->pUpdateFile,SIGNAL(clicked()),this,SLOT(updateFileFromStartToEndPos_click()));
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

    ui->pStart_btn->setEnabled(false);
    ui->pStop_btn->hide();
    ui->pStart_label->setText("server running");
    ui->pGenerateData_btn->setEnabled(false);


    setWindowTitle("Server....");
    m_pDataMgr = new DataMgr();
    m_pDataMgr->setWindow((void*)this);

    m_dataType = (ClientType_)State::getInstance()->getStateData(CUR_CLIENT);

    ui->pCollectDatasBtnGroup->hide();
    ui->pCheckCollectDatasGroup->hide();


    ui->pReadPos_label->setText("read data from start pos: 0  to end pos: 0");


    m_pTestTimer->start(2000);

    g_InitGlobalText();

    initClient();

    m_oldEnterCollectModeType = NONE_CLIENT;
    m_pDataMgr->getMgrbyId(m_dataType)->sendData(Cmd_Msg,m_dataType,MODE_NORMAL);
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

void MainWindow::activeRadio(ClientType_ id){
    if(id == NIBP_CLIENT)
        ui->pNibp_rb->setChecked(true);
    else if(id == ECG_CLIENT)
        ui->pEcg_rb->setChecked(true);
    else if(id == SPO2_CLIENT)
        ui->pSpo2_rb->setChecked(true);
    else if(id == IBP_CLIENT)
        ui->pIbp_rb->setChecked(true);
    else if(id == CO2_CLIENT)
        ui->pCo2_rb->setChecked(true);
    else if(id == NARCO_CLIENT)
        ui->pNarco_rb->setChecked(true);
    return ;
}

void MainWindow::radioChange(){
    if(State::getInstance()->getStateData(COLLECT_DATA)){
        if(State::getInstance()->getStateData(COLLECT_START)){
            QMessageBox::information(NULL, "notify", "please stop collecting data,first", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
            activeRadio(m_dataType);
            return ;
        }else if(State::getInstance()->getStateData(COLLECT_SAVE) || State::getInstance()->getStateData(COLLECT_DELETE))
        {
            QMessageBox::information(NULL, "notify", "please save or delete the collecting data,first", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
            activeRadio(m_dataType);
            return;
        }
    }

    setSave(m_dataType,SAVE_DATA_VALUE,ui->pValue_cb->currentIndex());
    setSave(m_dataType,SAVE_ALARM_VALUE,ui->pAlarm_cb->currentIndex());
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

    m_pDataMgr->getMgrbyId(m_dataType)->clearTestData();
    State::getInstance()->setStateData(CUR_CLIENT,m_dataType);
    initClient();

    if(State::getInstance()->getStateData(COLLECT_DATA)){
        ui->pFre_edit->setText("");
        ui->pTm_edit->setText("");
        ui->pRc_edit->setText("");
        if(m_pDataMgr->getMgrbyId(m_oldEnterCollectModeType))
            m_pDataMgr->getMgrbyId(m_oldEnterCollectModeType)->sendData(Cmd_Msg,m_oldEnterCollectModeType,MODE_NORMAL);

        m_oldEnterCollectModeType = m_dataType;
        m_pDataMgr->getMgrbyId(m_dataType)->sendData(Cmd_Msg,m_dataType,MODE_COLLECTDATAS);
    }else{
        m_pDataMgr->getMgrbyId(m_dataType)->sendData(Cmd_Msg,m_dataType,MODE_NORMAL);
    }
}

void MainWindow::collectDatasCheckStateChanged(int state){
    cout<<"collectDatasCheckStateChanged"<<endl;
    bool send_nibp = m_pDataMgr->getMgrbyId(NIBP_CLIENT)->getSendDataState();
    bool send_spo2 = m_pDataMgr->getMgrbyId(SPO2_CLIENT)->getSendDataState();
    bool send_ecg = m_pDataMgr->getMgrbyId(ECG_CLIENT)->getSendDataState();
    bool send_ibp = m_pDataMgr->getMgrbyId(IBP_CLIENT)->getSendDataState();
    bool send_co2 = m_pDataMgr->getMgrbyId(CO2_CLIENT)->getSendDataState();
    bool send_narco = m_pDataMgr->getMgrbyId(NARCO_CLIENT)->getSendDataState();

    if(send_nibp || send_spo2 || send_ecg || send_ibp || send_co2 || send_narco){
        QMessageBox::information(NULL, "notify", "please stop send data", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
        ui->pCollectDatas_check->setChecked(false);
        return;
    }
    State::getInstance()->setStateData(COLLECT_DATA,ui->pCollectDatas_check->isChecked());

    ui->pMsg_Txt->clear();

    if(ui->pCollectDatas_check->isChecked()){
        ui->pCollectDatas_check->setText("Collecting data");

        //close all files
        m_pDataMgr->getMgrbyId(ECG_CLIENT)->closeFile();
        m_pDataMgr->getMgrbyId(SPO2_CLIENT)->closeFile();
        m_pDataMgr->getMgrbyId(CO2_CLIENT)->closeFile();
        m_pDataMgr->getMgrbyId(NIBP_CLIENT)->closeFile();
        m_pDataMgr->getMgrbyId(IBP_CLIENT)->closeFile();
        m_pDataMgr->getMgrbyId(NARCO_CLIENT)->closeFile();


        ui->pCollectDatasBtnGroup->move(ui->pBtnGroup->x(),ui->pBtnGroup->y());
        ui->pBtnGroup->hide();
        ui->pCollectDatasBtnGroup->show();

        ui->pCheckCollectDatasGroup->move(ui->pChecksGroup->x(),ui->pChecksGroup->y());
        ui->pChecksGroup->hide();
        ui->pCheckCollectDatasGroup->show();


        ui->pReadEndPos_slider->hide();
        ui->pReadStartPos_slider->hide();
        ui->pReadPos_label->hide();
        ui->pUpdateFile->hide();
        ui->pFreCancel_btn->hide();
        ui->pFreOk_btn->hide();
        ui->pRcCancel_btn->hide();
        ui->pRcOk_btn->hide();

        ui->pFre_edit->setText("");
        ui->pTm_edit->setText("");
        ui->pRc_edit->setText("");
        //ui->pTm_edit->insert(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));

        ui->pStartCollectDatas->setEnabled(true);
        ui->pStopCollectDatas->setEnabled(false);
        ui->pSaveCollectDatas->setEnabled(false);
        ui->pDelCollectDatas->setEnabled(false);

        m_oldEnterCollectModeType = m_dataType;
        m_pDataMgr->getMgrbyId(m_dataType)->sendData(Cmd_Msg,m_dataType,MODE_COLLECTDATAS);
    }else{
        ui->pCollectDatas_check->setText("Collect datas");


        m_pDataMgr->getMgrbyId(ECG_CLIENT)->openFile();
        m_pDataMgr->getMgrbyId(SPO2_CLIENT)->openFile();
        m_pDataMgr->getMgrbyId(CO2_CLIENT)->openFile();
        m_pDataMgr->getMgrbyId(NIBP_CLIENT)->openFile();
        m_pDataMgr->getMgrbyId(IBP_CLIENT)->openFile();
        m_pDataMgr->getMgrbyId(NARCO_CLIENT)->openFile();


        ui->pBtnGroup->show();
        ui->pCollectDatasBtnGroup->hide();
        ui->pChecksGroup->show();
        ui->pCheckCollectDatasGroup->hide();

        ui->pReadEndPos_slider->show();
        ui->pReadStartPos_slider->show();
        ui->pReadPos_label->show();
        ui->pUpdateFile->show();
        ui->pFreCancel_btn->show();
        ui->pFreOk_btn->show();
        ui->pRcCancel_btn->show();
        ui->pRcOk_btn->show();

        ui->pFre_edit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getFrequency()));
        ui->pTm_edit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));
        ui->pRc_edit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getReadNum()));

        m_pDataMgr->getMgrbyId(m_dataType)->sendData(Cmd_Msg,m_dataType,MODE_NORMAL);
    }
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
//    setSave(m_dataType,SAVE_FILE_START_POS,0);//init the datas
//    setSave(m_dataType,SAVE_FILE_END_POS,0);//init the datas
    handleSlider();
    QMessageBox::information(NULL, "notify", "generate file success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
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
}

void MainWindow::saveCollectDatas_click(){//yxy
    QString dir = "";
    switch(m_dataType){
    case ECG_CLIENT:
        dir = "./datafile/ECG";
        break;
    case SPO2_CLIENT:
        dir = "./datafile/SPO2";
        break;
    case NIBP_CLIENT:
        dir = "./datafile/NIBP";
        break;
    case IBP_CLIENT:
        dir = "./datafile/IBP";
        break;
    case CO2_CLIENT:
        dir = "./datafile/CO2";
        break;
    case NARCO_CLIENT:
        dir = "./datafile/NARCO";
        break;
    default:
        dir = "./datafile/ECG";
        break;
    }
    QString fileName = QFileDialog::getOpenFileName(this,"collect dada",dir);
    if (fileName.isEmpty())
    {
        return;
    }

    cout<<"filename="<<fileName.toStdString().c_str()<<endl;
    bool ret = m_pDataMgr->getMgrbyId(m_dataType)->copyFile(fileName.toStdString().c_str(),m_pDataMgr->getMgrbyId(m_dataType)->getCollectDataTmpFile());

    ui->pStartCollectDatas->setEnabled(true);
    ui->pStopCollectDatas->setEnabled(false);
    ui->pSaveCollectDatas->setEnabled(false);
    ui->pDelCollectDatas->setEnabled(false);


    if(ret){
        cout<<"save Collect datas success"<<endl;
        QMessageBox::information(NULL, "notify", "save success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

        QString frestr = ui->pFre_edit->text();
        bool toIntOk = false;
        int val = frestr.toInt(&toIntOk,10)+1;
        m_pDataMgr->getMgrbyId(m_dataType)->setFrequency(val);
        setSave(m_dataType,SAVE_FRE,val);

        QString str = ui->pRc_edit->text();
        toIntOk = false;
        val = str.toInt(&toIntOk,10);
        m_pDataMgr->getMgrbyId(m_dataType)->setReadNum(val);
        setSave(m_dataType,SAVE_READNUM,val);


    }else{
        cout<<"save Collect datas failure"<<endl;
        QMessageBox::information(NULL, "notify", "save failure", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
    }
    State::getInstance()->setStateData(COLLECT_SAVE,0);
    State::getInstance()->setStateData(COLLECT_DELETE,0);
}

void MainWindow::delCollectDatas_click(){
    char cmdLine[100]={0};
    sprintf(cmdLine,"rm -f %s",m_pDataMgr->getMgrbyId(m_dataType)->getCollectDataTmpFile());
    system(cmdLine);
    ui->pStartCollectDatas->setEnabled(true);
    ui->pStopCollectDatas->setEnabled(false);
    ui->pSaveCollectDatas->setEnabled(false);
    ui->pDelCollectDatas->setEnabled(false);
    QMessageBox::information(NULL, "notify", "delete success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
    State::getInstance()->setStateData(COLLECT_DELETE,0);
    State::getInstance()->setStateData(COLLECT_SAVE,0);
}

void MainWindow::startCollectDatas_click(){
    cout<<"start Collect datas success"<<endl;
    State::getInstance()->setStateData(COLLECT_START,1);
    State::getInstance()->setStateData(COLLECT_SAVE,1);
    State::getInstance()->setStateData(COLLECT_DELETE,1);
    printf("startCollectDatas_click  getStateData(COLLECT_START)=%d\n",State::getInstance()->getStateData(COLLECT_START));

    ui->pStartCollectDatas->setEnabled(false);
    ui->pStopCollectDatas->setEnabled(true);
    ui->pSaveCollectDatas->setEnabled(false);
    ui->pDelCollectDatas->setEnabled(false);
}

void MainWindow::stopCollectDatas_click(){
    cout<<"stop Collect datas success"<<endl;
    State::getInstance()->setStateData(COLLECT_START,0);

    ui->pStartCollectDatas->setEnabled(false);
    ui->pStopCollectDatas->setEnabled(false);
    ui->pSaveCollectDatas->setEnabled(true);
    ui->pDelCollectDatas->setEnabled(true);
}

void MainWindow::updateFileFromStartToEndPos_click(){
    cout<<"updateFileFromStartToEndPos_click"<<endl;

    if(m_pDataMgr->getMgrbyId(m_dataType)->getSendDataState()){
        QMessageBox::information(NULL, "notify", "please stop send data", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
        return;
    }
    bool bCloseFile=false;
    char fileName[256]={0};
    if(m_pDataMgr->getMgrbyId(m_dataType)->isOpenFile()){
        strcpy(fileName,m_pDataMgr->getMgrbyId(m_dataType)->getFileName());
        m_pDataMgr->getMgrbyId(m_dataType)->closeFile();
        bCloseFile = true;
    }
    bool rel = m_pDataMgr->getMgrbyId(m_dataType)->updateFileFromStartPosToEndPos();

    if(bCloseFile){
        m_pDataMgr->getMgrbyId(m_dataType)->openFile(fileName);
    }

    char mess[100]={0};
    if(rel){
//        setSave(m_dataType,SAVE_FILE_START_POS,0);//init the datas
//        setSave(m_dataType,SAVE_FILE_END_POS,0);//init the datas
        handleSlider();
        cout<<"updateFileFromStartToEndPos success"<<endl;
        strcpy(mess,"updateFileFromStartToEndPos success");
    }else{
        cout<<"updateFileFromStartToEndPos failure"<<endl;
        strcpy(mess,"updateFileFromStartToEndPos failure");
    }

    QMessageBox::information(NULL, "notify", mess, QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
}

void MainWindow::setValue_slider(int val){
    char buf[200]={0};
    sprintf(buf,"read data from start pos: %lu   to end pos: %lu",ui->pReadStartPos_slider->value(),ui->pReadEndPos_slider->value());

    cout<<"setValue_slider buf="<<buf<<endl;
    ui->pReadPos_label->setText(buf);

    if(sender() == ui->pReadStartPos_slider){
        m_pDataMgr->getMgrbyId(m_dataType)->setReadFileStartPos(ui->pReadStartPos_slider->value());
//        setSave(m_dataType,SAVE_FILE_START_POS,ui->pReadStartPos_slider->value());//save the datas
    }else{
        m_pDataMgr->getMgrbyId(m_dataType)->setReadFileEndPos(ui->pReadEndPos_slider->value());
//        setSave(m_dataType,SAVE_FILE_END_POS,ui->pReadEndPos_slider->value());
    }
}


void MainWindow::exit_click(){
    close();
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

    m_pDataMgr->getMgrbyId(m_dataType)->clearTestData();
}


void MainWindow::sendTimer(){
    //cout<<"helllooo"<<endl;
    QString strTmp="";
    while(!m_queDataLine[m_dataType].empty()){
         strTmp += m_queDataLine[m_dataType].front().c_str();
         //ui->pMsg_Txt->insertPlainText(m_queDataLine[m_dataType].front().c_str());
         m_pMutex.lock();
         m_queDataLine[m_dataType].pop();
         m_pMutex.unlock();
    }
    ui->pMsg_Txt->insertPlainText(strTmp.toStdString().c_str());

    while(!m_queConnectMsgLine.empty()){
         ui->pConnectMsg_txt->append(m_queConnectMsgLine.front().c_str());
         m_pMutex.lock();
         m_queConnectMsgLine.pop();
         m_pMutex.unlock();
    }
    QTextCursor cursor =  ui->pMsg_Txt->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->pMsg_Txt->setTextCursor(cursor);

    while(!m_queStasticMsgLine[m_dataType].empty()){
//         QTextCursor cursor =  ui->pStatistics_txt->textCursor();
//         cursor.movePosition(QTextCursor::End);
//         ui->pStatistics_txt->setTextCursor(cursor);
//         ui->pStatistics_txt->insertPlainText(m_queStasticMsgLine[m_dataType].front().c_str());
         ui->pStatistics_txt->append(m_queStasticMsgLine[m_dataType].front().c_str());
         m_pMutex.lock();
         m_queStasticMsgLine[m_dataType].pop();
         m_pMutex.unlock();
    }

        checkLinkState();
}
void MainWindow::showData(ClientType_ id,const char* buf){
    if(State::getInstance()->getStateData(COLLECT_DATA)){
        //return;//
    }
    if(id != m_dataType) return ;

    m_pMutex.lock();
    m_queDataLine[id].push(buf);
    //cout<<buf<<endl;
    m_pMutex.unlock();
}

void MainWindow::appendMsg(const char* msg){
    m_pMutex.lock();
    //ui->pConnectMsg_txt->append(msg);
    m_queConnectMsgLine.push(msg);
    m_pMutex.unlock();
}
void MainWindow::appendStatisticsMsg(char* buf){
//    QTextCursor cursor =  ui->pStatistics_txt->textCursor();
//    cursor.movePosition(QTextCursor::End);
//    ui->pStatistics_txt->setTextCursor(cursor);
//    ui->pStatistics_txt->append(buf);
    assert(buf);
    m_pMutex.lock();
    //ui->pConnectMsg_txt->append(msg);
    m_queStasticMsgLine[m_dataType].push(buf);
    m_pMutex.unlock();
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


    if(State::getInstance()->getStateData(COLLECT_DATA)){
        printf("msg->times=%d,,msg->usedtimeSum=%d\n",msg->times,msg->usedtimeSum);
        int fre = (float)(1000.0 *msg->times)/(float)msg->usedtimeSum;
        int timeout = 0;
        if(fre){
            timeout = 1000/fre;
            if(timeout%2)//if not 2's Integer multiples
                timeout+=1;//m_iTimeout have to >=2 ms
        }
        int readnum = msg->readSum/msg->times;

        ui->pFre_edit->setText(QString::number(fre));
        ui->pTm_edit->setText(QString::number(timeout));
        ui->pRc_edit->setText(QString::number(readnum));
    }
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
void MainWindow::handleSlider(bool isInit){
    long max = m_pDataMgr->getMgrbyId(m_dataType)->getFileSize();

    long mid = max/2-2;

    if(max<=0){
        max = 0;
        mid = 0;

    }
    cout<<"start slider   range  0 ~ "<<mid<<"  val="<<getSaveValue(m_dataType,SAVE_FILE_START_POS)<<endl;
    cout<<"end slider     range  "<<mid+1<<"~ "<<max<<"  val="<<getSaveValue(m_dataType,SAVE_FILE_END_POS)<<endl;

//    if(isInit){
//        setSave(m_dataType,SAVE_FILE_START_POS,0);//
//        setSave(m_dataType,SAVE_FILE_END_POS,max);
//    }
//    if(getSaveValue(m_dataType,SAVE_FILE_START_POS)==0 || getSaveValue(m_dataType,SAVE_FILE_START_POS)>mid){
//        ui->pReadStartPos_slider->setRange(0,mid);
//        ui->pReadStartPos_slider->setValue(0);
//    }else{
//        ui->pReadStartPos_slider->setRange(0,mid);
//        ui->pReadStartPos_slider->setValue(getSaveValue(m_dataType,SAVE_FILE_START_POS));
//    }
//
//
//    if(getSaveValue(m_dataType,SAVE_FILE_END_POS)==0 || getSaveValue(m_dataType,SAVE_FILE_END_POS)>max){
//        ui->pReadEndPos_slider->setRange(mid,max);
//        ui->pReadEndPos_slider->setValue(max);
//    }else{
//        ui->pReadEndPos_slider->setRange(mid,max);
//        ui->pReadEndPos_slider->setValue(getSaveValue(m_dataType,SAVE_FILE_END_POS));
//    }


    ui->pReadStartPos_slider->setRange(0,mid);
    ui->pReadStartPos_slider->setValue(0);
    ui->pReadEndPos_slider->setRange(mid,max);
    ui->pReadEndPos_slider->setValue(max);

    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileStartPos(ui->pReadStartPos_slider->value());
    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileEndPos(ui->pReadEndPos_slider->value());
}

void MainWindow::handleCB(){
    ui->pAlarm_cb->hide();
    ui->pAddAlarm_btn->hide();
    ui->pDelAlarm_btn->hide();
    ui->pValue_cb->clear();
    switch(m_dataType){
    case ECG_CLIENT:
        {
            ui->pValue_cb->insertItems(0,g_ecgValues);
            if(State::getInstance()->getStateData(ECG_DATA_VALUE)>g_ecgValues.size()){
                State::getInstance()->setStateData(ECG_DATA_VALUE,0);
            }
            ui->pValue_cb->setCurrentIndex(State::getInstance()->getStateData(ECG_DATA_VALUE));

            ui->pAlarm_cb->show();
            ui->pAddAlarm_btn->show();
            ui->pDelAlarm_btn->show();

            ui->pValue_cb->show();
            ui->pAddValue_btn->show();
            ui->pDelValue_btn->show();

            ui->pAlarm_cb->clear();
            if(g_ecgAlarms.size()==0){
                g_ecgAlarms.append("NONE");
            }
            ui->pAlarm_cb->insertItems(0,g_ecgAlarms);
            if(State::getInstance()->getStateData(ECG_ALARM_VALUE)>g_ecgAlarms.size()){
                State::getInstance()->setStateData(ECG_ALARM_VALUE,0);
            }
            ui->pAlarm_cb->setCurrentIndex(State::getInstance()->getStateData(ECG_ALARM_VALUE));

        }
        break;
    case SPO2_CLIENT:
        {
            ui->pValue_cb->insertItems(0,g_spo2Values);
            if(State::getInstance()->getStateData(SPO2_DATA_VALUE)>g_spo2Values.size()){
                State::getInstance()->setStateData(SPO2_DATA_VALUE,0);
            }
            ui->pValue_cb->setCurrentIndex(State::getInstance()->getStateData(SPO2_DATA_VALUE));
        }
        break;
    case NIBP_CLIENT:
        {
            ui->pValue_cb->insertItems(0,g_nibpValues);
            if(State::getInstance()->getStateData(NIBP_DATA_VALUE)>g_nibpValues.size()){
                State::getInstance()->setStateData(NIBP_DATA_VALUE,0);
            }
            ui->pValue_cb->setCurrentIndex(State::getInstance()->getStateData(NIBP_DATA_VALUE));
        }
        break;
    case IBP_CLIENT:
        ui->pValue_cb->insertItems(0,g_ibpValues);
        if(State::getInstance()->getStateData(IBP_DATA_VALUE)>g_ibpValues.size()){
            State::getInstance()->setStateData(IBP_DATA_VALUE,0);
        }
        ui->pValue_cb->setCurrentIndex(State::getInstance()->getStateData(IBP_DATA_VALUE));
        break;
    case CO2_CLIENT:
        ui->pValue_cb->insertItems(0,g_co2Values);
        if(State::getInstance()->getStateData(CO2_DATA_VALUE)>g_co2Values.size()){
            State::getInstance()->setStateData(CO2_DATA_VALUE,0);
        }
        ui->pValue_cb->setCurrentIndex(State::getInstance()->getStateData(CO2_DATA_VALUE));
        break;
    case NARCO_CLIENT:
        ui->pValue_cb->insertItems(0,g_narcoValues);
        if(State::getInstance()->getStateData(NARCO_DATA_VALUE)>g_narcoValues.size()){
            State::getInstance()->setStateData(NARCO_DATA_VALUE,0);
        }
        ui->pValue_cb->setCurrentIndex(State::getInstance()->getStateData(NARCO_DATA_VALUE));
        break;
    default:
        break;
    }
}
void MainWindow::valueChanged(int index){
    cout<<"valuechanged index="<<index<<"   value="<<ui->pValue_cb->currentText().toStdString().c_str()<<endl;
    if(ui->pValue_cb->currentIndex()>=0){
        m_pDataMgr->getMgrbyId(m_dataType)->setTxtValue(ui->pValue_cb->currentText().toStdString().c_str());
    }
    else{
        //m_pDataMgr->getMgrbyId(m_dataType)->closeFile();
    }
    handleSlider(true);
}

void MainWindow::alarmChanged(int index){
    if(ui->pAlarm_cb->currentIndex()==0){//no alarm
        ui->pValue_cb->setEnabled(true);
        ui->pAddValue_btn->setEnabled(true);
        ui->pDelValue_btn->setEnabled(true);
        int ix = ui->pValue_cb->currentIndex();
        if(ix>=0)
            valueChanged(ix);
    }else{
        ui->pValue_cb->setEnabled(false);//has alarm
        ui->pAddValue_btn->setEnabled(false);
        ui->pDelValue_btn->setEnabled(false);

        if(ui->pAlarm_cb->currentIndex()>0)
            m_pDataMgr->getMgrbyId(m_dataType)->setTxtAlarm(ui->pAlarm_cb->currentText().toStdString().c_str());
        //else m_pDataMgr->getMgrbyId(m_dataType)->closeFile();
    }
    //setSave(m_dataType,SAVE_ALARM_VALUE,ui->pAlarm_cb->currentIndex());
    handleSlider(true);
}
void MainWindow::addValueToCb_click(){
    bool isOK=false;
    QString text = QInputDialog::getText(NULL, "Input Dialog","Please input Integer(0-1000)",QLineEdit::Normal,"",&isOK);
    if(!isOK) {
        //QMessageBox::information(NULL, "Information","Your comment is: <b>" + text + "</b>",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }

    QStringList::iterator it = qFind(getValueList(m_dataType).begin(),getValueList(m_dataType).end(),text.toStdString().c_str());
    if(it != getValueList(m_dataType).end()){
        cout<<"this val="<<text.toStdString().c_str()<<" has exist"<<endl;
        return;
    }
    getValueList(m_dataType).append(text);
    qSort(getValueList(m_dataType).begin(), getValueList(m_dataType).end());
    handleCB();

    int ix = ui->pValue_cb->findText(text);
    if(ix>0)
        ui->pValue_cb->setCurrentIndex(ix);

    saveTxtValue(getValueList(m_dataType));
}
void MainWindow::delValueToCb_click(){
    int isOk =QMessageBox::warning(NULL, "warning", "delete this data?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(isOk == QMessageBox::No){
        return;
    }

    cout<<"ui->pValue_cb->currentIndex()="<<ui->pValue_cb->currentIndex()<<endl;

    int index = ui->pValue_cb->currentIndex();
    cout<<"11 getValueList(m_dataType)"<<&(getValueList(m_dataType))<<endl;
    getValueList(m_dataType).removeAt(index);
    handleCB();
    if(index>0&&index<getValueList(m_dataType).count())
        ui->pValue_cb->setCurrentIndex(index);

    cout<<"22 getValueList(m_dataType)"<<&(getValueList(m_dataType))<<endl;
    saveTxtValue(getValueList(m_dataType));
}
void MainWindow::addAlarmToCb_click(){
    bool isOK=false;
    QString text = QInputDialog::getText(NULL, "Input Dialog","Please input alarm string",QLineEdit::Normal,"",&isOK);
    if(!isOK) {
        //QMessageBox::information(NULL, "Information","Your comment is: <b>" + text + "</b>",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }

    QStringList::iterator it = qFind(getAlarmList(m_dataType).begin(),getAlarmList(m_dataType).end(),text.toStdString().c_str());
    if(it != getAlarmList(m_dataType).end()){
        cout<<"this val="<<text.toStdString().c_str()<<" has exist"<<endl;
        return;
    }
    getAlarmList(m_dataType).append(text);
    qSort(getAlarmList(m_dataType).begin(), getAlarmList(m_dataType).end());
    handleCB();

    int ix = ui->pAlarm_cb->findText(text);
    if(ix>0)
        ui->pAlarm_cb->setCurrentIndex(ix);

    saveTxtValue(getAlarmList(m_dataType));
}

void MainWindow::delAlarmToCb_click(){
    int index = ui->pAlarm_cb->currentIndex();
    if(index == 0){
        QMessageBox::information(NULL, "Information","don't this val",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    getAlarmList(m_dataType).removeAt(index);
    handleCB();
    if(index>0&&index<getAlarmList(m_dataType).count())
        ui->pAlarm_cb->setCurrentIndex(index);

    saveTxtValue(getAlarmList(m_dataType));
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
            case SAVE_DATA_VALUE:
                State::getInstance()->setStateData(ECG_DATA_VALUE, val);
                break;
            case SAVE_ALARM_VALUE:
                State::getInstance()->setStateData(ECG_ALARM_VALUE, val);
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
            case SAVE_DATA_VALUE:
                State::getInstance()->setStateData(SPO2_DATA_VALUE, val);
                break;
            case SAVE_ALARM_VALUE:
                State::getInstance()->setStateData(SPO2_ALARM_VALUE, val);
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
            case SAVE_DATA_VALUE:
                State::getInstance()->setStateData(CO2_DATA_VALUE, val);
                break;
            case SAVE_ALARM_VALUE:
                State::getInstance()->setStateData(CO2_ALARM_VALUE, val);
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
//            case SAVE_FILE_START_POS:
//                State::getInstance()->setStateData(NARCO_FILE_START_POS, val);
//                break;
//            case SAVE_FILE_END_POS:
//                State::getInstance()->setStateData(NARCO_FILE_END_POS, val);
//                break;
            case SAVE_TEST:
                State::getInstance()->setStateData(NARCO_TEST, val);
                break;
            case SAVE_SHOWDATA:
                State::getInstance()->setStateData(NARCO_SHOWDATA, val);
                break;
            case SAVE_SENDDATA:
                State::getInstance()->setStateData(NARCO_SENDDATA, val);
                break;
            case SAVE_DATA_VALUE:
                State::getInstance()->setStateData(NARCO_DATA_VALUE, val);
                break;
            case SAVE_ALARM_VALUE:
                State::getInstance()->setStateData(NARCO_ALARM_VALUE, val);
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
            case SAVE_DATA_VALUE:
                State::getInstance()->setStateData(NIBP_DATA_VALUE, val);
                break;
            case SAVE_ALARM_VALUE:
                State::getInstance()->setStateData(NIBP_ALARM_VALUE, val);
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
            case SAVE_DATA_VALUE:
                State::getInstance()->setStateData(IBP_DATA_VALUE, val);
                break;
            case SAVE_ALARM_VALUE:
                State::getInstance()->setStateData(IBP_ALARM_VALUE, val);
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
            case SAVE_DATA_VALUE:
                return State::getInstance()->getStateData(ECG_DATA_VALUE);
                break;
            case SAVE_ALARM_VALUE:
                return State::getInstance()->getStateData(ECG_ALARM_VALUE);
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
            case SAVE_DATA_VALUE:
                return State::getInstance()->getStateData(SPO2_DATA_VALUE);
                break;
            case SAVE_ALARM_VALUE:
                return State::getInstance()->getStateData(SPO2_ALARM_VALUE);
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
            case SAVE_DATA_VALUE:
                return State::getInstance()->getStateData(CO2_DATA_VALUE);
                break;
            case SAVE_ALARM_VALUE:
                return State::getInstance()->getStateData(CO2_ALARM_VALUE);
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
//            case SAVE_FILE_START_POS:
//                return State::getInstance()->getStateData(NARCO_FILE_START_POS);
//                break;
//            case SAVE_FILE_END_POS:
//                return State::getInstance()->getStateData(NARCO_FILE_END_POS);
//                break;
            case SAVE_TEST:
                return State::getInstance()->getStateData(NARCO_TEST);
                break;
            case SAVE_SHOWDATA:
                return State::getInstance()->getStateData(NARCO_SHOWDATA);
                break;
            case SAVE_SENDDATA:
                return State::getInstance()->getStateData(NARCO_SENDDATA);
                break;
            case SAVE_DATA_VALUE:
                return State::getInstance()->getStateData(NARCO_DATA_VALUE);
                break;
            case SAVE_ALARM_VALUE:
                return State::getInstance()->getStateData(NARCO_ALARM_VALUE);
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
            case SAVE_DATA_VALUE:
                return State::getInstance()->getStateData(NIBP_DATA_VALUE);
                break;
            case SAVE_ALARM_VALUE:
                return State::getInstance()->getStateData(NIBP_ALARM_VALUE);
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
            case SAVE_DATA_VALUE:
                return State::getInstance()->getStateData(IBP_DATA_VALUE);
                break;
            case SAVE_ALARM_VALUE:
                return State::getInstance()->getStateData(IBP_ALARM_VALUE);
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


