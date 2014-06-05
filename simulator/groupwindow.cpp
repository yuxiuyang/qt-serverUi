#include "groupwindow.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include "common/file.h"
GroupBasicWindow::GroupBasicWindow(QWidget *parent,ClientType_ dataType,DataMgr* pMgr) :
    QWidget(parent)
    //ui(new Ui::GroupBasicWindow)
{
    m_dataType = dataType;
    m_pDataMgr = pMgr;
    assert(m_pDataMgr);
}
void GroupBasicWindow::initLayout(){
    m_pTextBrowser = new QTextBrowser();

    //m_pTextBrowser->setGeometry(62,40,75,30);

    m_clearBtn = new QPushButton("clear");

    m_sendComfireBtn = new QPushButton("send commfire id");

    m_valueCb = new QComboBox();
    m_alarmCb = new QComboBox();

    m_generateTestDataBtn = new QPushButton("generate test data");

    QVBoxLayout *mainlayout = new QVBoxLayout;
    m_mainLayout1 = new QHBoxLayout;
    QHBoxLayout *layout1 = new QHBoxLayout;

    layout1->addWidget(m_pTextBrowser);

    m_layout2 = new QVBoxLayout;
    //ecgLayout->addSpacing(20);
    m_layout2->addWidget(m_clearBtn);
    m_layout2->addWidget(m_sendComfireBtn);
    m_layout12 = new QHBoxLayout;
    m_addValueBtn = new QPushButton("add");
    m_delValueBtn = new QPushButton("del");
    m_layout12->addWidget(m_valueCb);

    m_layout12->addWidget(m_addValueBtn);
    m_layout12->addWidget(m_delValueBtn);
    m_layout2->addLayout(m_layout12);

    m_layout13 = new QHBoxLayout;
    m_addAlarmBtn = new QPushButton("add");
    m_delAlarmBtn = new QPushButton("del");

    if(NIBP_CLIENT==m_dataType){
        m_nibpModeCb = new QComboBox();
        m_layout2->addWidget(m_nibpModeCb);
    }
    //if(m_dataType == ECG_CLIENT){
    m_layout13->addWidget(m_alarmCb);
    m_layout13->addWidget(m_addAlarmBtn);
    m_layout13->addWidget(m_delAlarmBtn);
    m_layout2->addLayout(m_layout13);
    //}

    m_layout2->addWidget(m_generateTestDataBtn);

        //ecgLayout->addStretch(2);

    QHBoxLayout *layout3 = new QHBoxLayout;
    m_posStartToEndLabel = new QLabel("read data from start pos:     to end pos:");
    m_saveCurPosBtn = new QPushButton("update file from start to end pos");
    layout3->addWidget(m_posStartToEndLabel);
    layout3->addSpacing(50);
    layout3->addWidget(m_saveCurPosBtn);

    QHBoxLayout *layout4 = new QHBoxLayout;
    m_readStartPos_slider = new QSlider(Qt::Horizontal);
    m_readEndPos_slider = new QSlider(Qt::Horizontal);
    layout4->addWidget(m_readStartPos_slider);
    layout4->addWidget(m_readEndPos_slider);

    QHBoxLayout *mainlayout2 = new QHBoxLayout;
    QVBoxLayout *layoutV1 = new QVBoxLayout;
    QHBoxLayout *layoutH2 = new QHBoxLayout;
    mainlayout2->addLayout(layoutV1);
    mainlayout2->addLayout(layoutH2);

    QHBoxLayout *layout5 = new QHBoxLayout;
    QVBoxLayout *layout6 = new QVBoxLayout;
    m_startTestCheckBox = new QCheckBox("start test");
    m_showDataCheckBox = new QCheckBox("show data");
    layout5->addWidget(m_startTestCheckBox);
    layout5->addWidget(m_showDataCheckBox);
    m_sendDataCheckBox = new QCheckBox("send data");
    layout6->addWidget(m_sendDataCheckBox);
    layoutV1->addLayout(layout5);
    layoutV1->addLayout(layout6);

    QHBoxLayout *layout7 = new QHBoxLayout;
    QLabel* freLabel = new QLabel("frequence");
    m_freEdit = new QLineEdit();
    m_freOkBtn = new QPushButton("OK");
    m_freCancelBtn = new QPushButton("Cancel");
    layout7->addWidget(freLabel);
    layout7->addSpacing(5);
    layout7->addWidget(m_freEdit);
    layout7->addWidget(m_freOkBtn);
    layout7->addWidget(m_freCancelBtn);

    QHBoxLayout *layout8 = new QHBoxLayout;
    QLabel* timeoutLabel = new QLabel("timeout");
    m_timeoutEdit = new QLineEdit();
//    QGroupBox* space1 = new QGroupBox("");
//    QGroupBox* space2 = new QGroupBox("");
    layout8->addWidget(timeoutLabel);
    layout8->addSpacing(20);
    layout8->addWidget(m_timeoutEdit);
    m_timeoutEdit->setEnabled(false);
//    layout8->addWidget(space1);
//    layout8->addWidget(space2);

    QHBoxLayout *layout9 = new QHBoxLayout;
    QLabel* readcountLabel = new QLabel("readcount");
    m_readcountEdit = new QLineEdit();
    m_readcountOkBtn = new QPushButton("OK");
    m_readcountCancelBtn = new QPushButton("Cancel");
    layout9->addWidget(readcountLabel);
    layout9->addWidget(m_readcountEdit);
    layout9->addWidget(m_readcountOkBtn);
    layout9->addWidget(m_readcountCancelBtn);

    layoutV1->addLayout(layout7);
    layoutV1->addLayout(layout8);
    layoutV1->addLayout(layout9);


    m_statisticsBrowser = new QTextBrowser();
    layoutH2->addWidget(m_statisticsBrowser);



    m_mainLayout1->addLayout(layout1);
    //mainlayout->removeItem(layout1);
    m_mainLayout1->addLayout(m_layout2);
    mainlayout->addLayout(m_mainLayout1);
    mainlayout->addLayout(layout3);
    mainlayout->addLayout(layout4);
    mainlayout->addLayout(mainlayout2);
    setLayout(mainlayout);


    m_startCollectData = new QPushButton("start collecting datas");
    m_stopCollectData = new QPushButton("stop collecting datas");
    m_saveCollectData = new QPushButton("save datas");
    m_delCollectData = new QPushButton("delete datas");
    m_layoutData = new QHBoxLayout();
    m_layoutData->addWidget(m_saveCollectData);
    m_layoutData->addWidget(m_delCollectData);

}

void GroupBasicWindow::updateWindow(MODE_TYPE mode){
    m_pTextBrowser->clear();
    switch(mode){
    case COLLECTING_DATA_MODE:
        m_pDataMgr->getMgrbyId(ECG_CLIENT)->closeFile();
        m_valueCb->hide();
        m_generateTestDataBtn->hide();
        m_startCollectData->show();
        m_stopCollectData->show();
        m_saveCollectData->show();
        m_delCollectData->show();

        if(NIBP_CLIENT==m_dataType){
            m_layout2->removeWidget(m_nibpModeCb);
            m_nibpModeCb->hide();
        }
        //if(m_dataType == ECG_CLIENT){// alarm combobox
            m_alarmCb->hide();
            m_addAlarmBtn->hide();
            m_delAlarmBtn->hide();
            //m_layout2->removeItem(m_layout13);
        //}

        m_addValueBtn->hide();
        m_delValueBtn->hide();

        m_layout2->removeItem(m_layout12);
        m_layout2->removeItem(m_layout13);
        m_layout2->removeWidget(m_generateTestDataBtn);

        m_posStartToEndLabel->hide();
        m_saveCurPosBtn->hide();
        m_readStartPos_slider->hide();
        m_readEndPos_slider->hide();
        m_startTestCheckBox->setEnabled(false);
        m_sendDataCheckBox->setEnabled(false);

        m_layout2->addWidget(m_startCollectData);
        m_layout2->addWidget(m_stopCollectData);
        m_layout2->addLayout(m_layoutData);

        m_freEdit->setText("0");
        m_timeoutEdit->setText("0");
        m_readcountEdit->setText("0");
        //m_mainLayout1
        break;
    case SIMULATOR_MODE:
        m_pDataMgr->getMgrbyId(ECG_CLIENT)->openFile();
        m_valueCb->show();

        m_generateTestDataBtn->show();
        m_startCollectData->hide();
        m_stopCollectData->hide();
        m_saveCollectData->hide();
        m_delCollectData->hide();

        m_addValueBtn->show();
        m_delValueBtn->show();

        //if(m_dataType == ECG_CLIENT){// alarm combobox
            m_alarmCb->show();
            m_addAlarmBtn->show();
            m_delAlarmBtn->show();
            //m_layout2->addLayout(m_layout13);
        //}


        m_posStartToEndLabel->show();
        m_saveCurPosBtn->show();
        m_readStartPos_slider->show();
        m_readEndPos_slider->show();
        m_startTestCheckBox->setEnabled(true);
        m_sendDataCheckBox->setEnabled(true);
//m_startCollectData->layout()
        m_layout2->removeWidget(m_startCollectData);
        m_layout2->removeWidget(m_stopCollectData);
        m_layout2->removeItem(m_layoutData);

        m_layout2->addLayout(m_layout12);
        if(NIBP_CLIENT==m_dataType){
            m_layout2->addWidget(m_nibpModeCb);
            m_nibpModeCb->show();
        }
        m_layout2->addLayout(m_layout13);

        m_layout2->addWidget(m_generateTestDataBtn);

        m_freEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getFrequency()));
        m_timeoutEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));
        m_readcountEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getReadNum()));
        break;
    }
}

void GroupBasicWindow::init(){
    handleCB();
    handleSlider();

    m_freOkBtn->setEnabled(false);
    m_readcountOkBtn->setEnabled(false);
    m_readcountEdit->setEnabled(false);
    m_freEdit->setEnabled(false);
    m_freCancelBtn->setEnabled(true);
    m_readcountCancelBtn->setEnabled(true);

    m_freEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getFrequency()));
    m_timeoutEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));
    m_timeoutEdit->setReadOnly(true);
    m_timeoutEdit->setEnabled(false);
    m_readcountEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getReadNum()));

    m_freOkBtn->setEnabled(false);
    m_readcountOkBtn->setEnabled(false);
    m_readcountEdit->setEnabled(false);
    m_freEdit->setEnabled(false);
    m_freCancelBtn->setEnabled(true);
    m_readcountCancelBtn->setEnabled(true);

    if(m_pDataMgr->getMgrbyId(m_dataType)->isTestRunning()){
        m_startTestCheckBox->setChecked(true);
    }else{
        m_startTestCheckBox->setChecked(false);
    }
    if(m_pDataMgr->getMgrbyId(m_dataType)->isShowData()){
        m_showDataCheckBox->setChecked(true);
    }else{
        m_showDataCheckBox->setChecked(false);
    }
    if(m_pDataMgr->getMgrbyId(m_dataType)->getSendDataState()){
        m_sendDataCheckBox->setChecked(true);
    }else{
        m_sendDataCheckBox->setChecked(false);
    }

    m_pTextBrowser->clear();
    m_statisticsBrowser->clear();

    cout<<"m_dataType="<<m_dataType<<"   State::getInstance()->setStateData(m_dataType,SAVE_ALARM_VALUE)="<<State::getInstance()->getStateData(m_dataType,SAVE_ALARM_VALUE)<<endl;
    if(State::getInstance()->getStateData(m_dataType,SAVE_ALARM_VALUE)==0){//no alarm
        m_valueCb->setEnabled(true);
        m_addValueBtn->setEnabled(true);
        m_delValueBtn->setEnabled(true);
    }else{
        m_valueCb->setEnabled(false);//has alarm
        m_addValueBtn->setEnabled(false);
        m_delValueBtn->setEnabled(false);
    }
}

void GroupBasicWindow::sendTimer(){
        QString strTmp="";
        while(!m_queDataLine.empty()){
             strTmp += m_queDataLine.front().c_str();
             m_pMutex.lock();
             m_queDataLine.pop();
             m_pMutex.unlock();
        }
        if(strTmp!=""){
            m_pTextBrowser->insertPlainText(strTmp.toStdString().c_str());

            QTextCursor cursor =  m_pTextBrowser->textCursor();
            cursor.movePosition(QTextCursor::End);
            m_pTextBrowser->setTextCursor(cursor);
        }


        while(!m_queStasticMsgLine.empty()){
             m_statisticsBrowser->append(m_queStasticMsgLine.front().c_str());
             m_pMutex.lock();
             m_queStasticMsgLine.pop();
             m_pMutex.unlock();
        }

        checkLinkState();
}

void GroupBasicWindow::appendStatisticsMsg(char* buf){
    assert(buf);
    m_pMutex.lock();
    m_queStasticMsgLine.push(buf);
    m_pMutex.unlock();
}
void GroupBasicWindow::displayStatisicsResult(TESTMSG* msg){
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

        m_freEdit->setText(QString::number(fre));
        m_timeoutEdit->setText(QString::number(timeout));
        m_readcountEdit->setText(QString::number(readnum));
    }
}

void GroupBasicWindow::generateTestData_click(){
    m_pDataMgr->generateTestFile(m_dataType);
    handleSlider();
    QMessageBox::information(NULL, "notify", "generate file success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
}

void GroupBasicWindow::checkLinkState(){
    LinkState state = m_pDataMgr->m_pLinkMgr->getLinkState(m_dataType);
    switch(state){
    case link_not_comfirmId:
        m_sendComfireBtn->setText("send comfire id commond");
        m_sendComfireBtn->setEnabled(true);
        break;
    case link_and_comfirmId:
        m_sendComfireBtn->setText("had comfirem id");
        m_sendComfireBtn->setEnabled(false);
        break;
    case dis_link:
        m_sendComfireBtn->setText("send comfire id commond");
        m_sendComfireBtn->setEnabled(true);
        break;
    default:
        break;
    }

}

void GroupBasicWindow::clearTextBrowser_click(){
    m_pTextBrowser->clear();
}
void GroupBasicWindow::sendRequestData_click(){
    m_pDataMgr->m_pLinkMgr->requestLinkMsg();
}

void GroupBasicWindow::handleCB(){
//    m_alarmCb->hide();
//    m_addValueBtn->hide();
//    m_delValueBtn->hide();
    m_valueCb->clear();
    switch(m_dataType){
    case ECG_CLIENT:
        {
            m_valueCb->insertItems(0,Global::getInstance()->g_ecgValues);
            if(State::getInstance()->getStateData(ECG_DATA_VALUE) > Global::getInstance()->g_ecgValues.size()){
                State::getInstance()->setStateData(ECG_DATA_VALUE,0);
            }
            m_valueCb->setCurrentIndex(State::getInstance()->getStateData(ECG_DATA_VALUE));

            m_alarmCb->clear();
            if(Global::getInstance()->g_ecgAlarms.size()==0){
                Global::getInstance()->g_ecgAlarms.append("NONE");
            }
            m_alarmCb->insertItems(0,Global::getInstance()->g_ecgAlarms);
            if(State::getInstance()->getStateData(ECG_ALARM_VALUE)>Global::getInstance()->g_ecgAlarms.size()){
                State::getInstance()->setStateData(ECG_ALARM_VALUE,0);
            }
            m_alarmCb->setCurrentIndex(State::getInstance()->getStateData(ECG_ALARM_VALUE));

        }
        break;
    case SPO2_CLIENT:
        {
            m_valueCb->insertItems(0,Global::getInstance()->g_spo2Values);
            if(State::getInstance()->getStateData(SPO2_DATA_VALUE)>Global::getInstance()->g_spo2Values.size()){
                State::getInstance()->setStateData(SPO2_DATA_VALUE,0);
            }
            m_valueCb->setCurrentIndex(State::getInstance()->getStateData(SPO2_DATA_VALUE));
            m_alarmCb->addItem("NONE");
        }
        break;
    case NIBP_CLIENT:
        {
            m_valueCb->insertItems(0,Global::getInstance()->g_nibpValues);
            if(State::getInstance()->getStateData(NIBP_DATA_VALUE)>Global::getInstance()->g_nibpValues.size()){
                State::getInstance()->setStateData(NIBP_DATA_VALUE,0);
            }
            m_valueCb->setCurrentIndex(State::getInstance()->getStateData(NIBP_DATA_VALUE));
            m_alarmCb->addItem("NONE");
        }
        break;
    case IBP_CLIENT:
        m_valueCb->insertItems(0,Global::getInstance()->g_ibpValues);
        if(State::getInstance()->getStateData(IBP_DATA_VALUE)>Global::getInstance()->g_ibpValues.size()){
            State::getInstance()->setStateData(IBP_DATA_VALUE,0);
        }
        m_valueCb->setCurrentIndex(State::getInstance()->getStateData(IBP_DATA_VALUE));
        m_alarmCb->addItem("NONE");
        break;
    case CO2_CLIENT:
        m_valueCb->insertItems(0,Global::getInstance()->g_co2Values);
        if(State::getInstance()->getStateData(CO2_DATA_VALUE)>Global::getInstance()->g_co2Values.size()){
            State::getInstance()->setStateData(CO2_DATA_VALUE,0);
        }
        m_valueCb->setCurrentIndex(State::getInstance()->getStateData(CO2_DATA_VALUE));
        m_alarmCb->addItem("NONE");
        break;
    case NARCO_CLIENT:
        m_valueCb->insertItems(0,Global::getInstance()->g_narcoValues);
        if(State::getInstance()->getStateData(NARCO_DATA_VALUE)>Global::getInstance()->g_narcoValues.size()){
            State::getInstance()->setStateData(NARCO_DATA_VALUE,0);
        }
        m_valueCb->setCurrentIndex(State::getInstance()->getStateData(NARCO_DATA_VALUE));
        m_alarmCb->addItem("NONE");
        break;
    default:
        break;
    }
}
void GroupBasicWindow::valueChanged(int index){
    cout<<"valuechanged index="<<index<<"   value="<<m_valueCb->currentText().toStdString().c_str()<<endl;
    if(m_valueCb->currentIndex()>=0){
        m_pDataMgr->getMgrbyId(m_dataType)->setTxtValue(m_valueCb->currentText().toStdString().c_str());
    }
    else{
        //m_pDataMgr->getMgrbyId(m_dataType)->closeFile();
    }
    handleSlider(true);
}

void GroupBasicWindow::alarmChanged(int index){
    if(m_alarmCb->currentIndex()==0){//no alarm
        m_valueCb->setEnabled(true);
        m_addValueBtn->setEnabled(true);
        m_delValueBtn->setEnabled(true);
        int ix = m_valueCb->currentIndex();
        if(ix>=0)
            valueChanged(ix);
    }else{
        m_valueCb->setEnabled(false);//has alarm
        m_addValueBtn->setEnabled(false);
        m_delValueBtn->setEnabled(false);

        if(m_alarmCb->currentIndex()>0)
            m_pDataMgr->getMgrbyId(m_dataType)->setTxtAlarm(m_alarmCb->currentText().toStdString().c_str());
        //else m_pDataMgr->getMgrbyId(m_dataType)->closeFile();
    }
    State::getInstance()->setStateData(m_dataType,SAVE_ALARM_VALUE,m_alarmCb->currentIndex());
    handleSlider(true);
}
void GroupBasicWindow::addValueToCb_click(){
    bool isOK=false;
    QString text = QInputDialog::getText(NULL, "Input Dialog","Please input Integer(0-1000)",QLineEdit::Normal,"",&isOK);
    if(!isOK) {
        //QMessageBox::information(NULL, "Information","Your comment is: <b>" + text + "</b>",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }

    QStringList::iterator it = qFind(Global::getInstance()->getValueList(m_dataType).begin(),Global::getInstance()->getValueList(m_dataType).end(),text.toStdString().c_str());
    if(it != Global::getInstance()->getValueList(m_dataType).end()){
        cout<<"this val="<<text.toStdString().c_str()<<" has exist"<<endl;
        return;
    }
    Global::getInstance()->getValueList(m_dataType).append(text);
    qSort(Global::getInstance()->getValueList(m_dataType).begin(), Global::getInstance()->getValueList(m_dataType).end());
    handleCB();

    int ix = m_valueCb->findText(text);
    if(ix>0)
        m_valueCb->setCurrentIndex(ix);

    Global::getInstance()->saveTxtValue(Global::getInstance()->getValueList(m_dataType));
}
void GroupBasicWindow::delValueToCb_click(){
    int isOk =QMessageBox::warning(NULL, "warning", "delete this data?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(isOk == QMessageBox::No){
        return;
    }

    cout<<"m_valueCb->currentIndex()="<<m_valueCb->currentIndex()<<endl;

    int index = m_valueCb->currentIndex();
    cout<<"11 Global::getInstance()->getValueList(m_dataType)"<<&(Global::getInstance()->getValueList(m_dataType))<<endl;
    Global::getInstance()->getValueList(m_dataType).removeAt(index);
    handleCB();
    if(index>0&&index<Global::getInstance()->getValueList(m_dataType).count())
        m_valueCb->setCurrentIndex(index);

    cout<<"22 Global::getInstance()->getValueList(m_dataType)"<<&(Global::getInstance()->getValueList(m_dataType))<<endl;
    Global::getInstance()->saveTxtValue(Global::getInstance()->getValueList(m_dataType));
}
void GroupBasicWindow::addAlarmToCb_click(){
    bool isOK=false;
    QString text = QInputDialog::getText(NULL, "Input Dialog","Please input alarm string",QLineEdit::Normal,"",&isOK);
    if(!isOK) {
        //QMessageBox::information(NULL, "Information","Your comment is: <b>" + text + "</b>",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }

    QStringList::iterator it = qFind(Global::getInstance()->getAlarmList(m_dataType).begin(),Global::getInstance()->getAlarmList(m_dataType).end(),text.toStdString().c_str());
    if(it != Global::getInstance()->getAlarmList(m_dataType).end()){
        cout<<"this val="<<text.toStdString().c_str()<<" has exist"<<endl;
        return;
    }
    Global::getInstance()->getAlarmList(m_dataType).append(text);
    qSort(Global::getInstance()->getAlarmList(m_dataType).begin(), Global::getInstance()->getAlarmList(m_dataType).end());


    QStringList::iterator iter = qFind(Global::getInstance()->getAlarmList(m_dataType).begin(),Global::getInstance()->getAlarmList(m_dataType).end(),"NONE");
    while(iter!=Global::getInstance()->getAlarmList(m_dataType).end()){
        Global::getInstance()->getAlarmList(m_dataType).erase(iter);
        iter = qFind(Global::getInstance()->getAlarmList(m_dataType).begin(),Global::getInstance()->getAlarmList(m_dataType).end(),"NONE");
    }
    Global::getInstance()->getAlarmList(m_dataType).insert(0,"NONE");
    handleCB();

    int ix = m_alarmCb->findText(text);
    if(ix>0)
        m_alarmCb->setCurrentIndex(ix);

    Global::getInstance()->saveTxtValue(Global::getInstance()->getAlarmList(m_dataType));
}

void GroupBasicWindow::delAlarmToCb_click(){
    int index = m_alarmCb->currentIndex();
    if(index == 0){
        QMessageBox::information(NULL, "Information","don't this val",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    Global::getInstance()->getAlarmList(m_dataType).removeAt(index);
    handleCB();
    if(index>0&&index<Global::getInstance()->getAlarmList(m_dataType).count())
        m_alarmCb->setCurrentIndex(index);

    Global::getInstance()->saveTxtValue(Global::getInstance()->getAlarmList(m_dataType));
}

void GroupBasicWindow::updateFileFromStartToEndPos_click(){
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
        handleSlider();
        cout<<"updateFileFromStartToEndPos success"<<endl;
        strcpy(mess,"updateFileFromStartToEndPos success");
    }else{
        cout<<"updateFileFromStartToEndPos failure"<<endl;
        strcpy(mess,"updateFileFromStartToEndPos failure");
    }

    QMessageBox::information(NULL, "notify", mess, QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
}

void GroupBasicWindow::setValue_slider(int val){
    char buf[200]={0};
    sprintf(buf,"read data from start pos: %lu  to end pos: %lu",m_readStartPos_slider->value(),m_readEndPos_slider->value());

    cout<<"setValue_slider buf="<<buf<<endl;
    m_posStartToEndLabel->setText(buf);

    if(sender() == m_readStartPos_slider){
        m_pDataMgr->getMgrbyId(m_dataType)->setReadFileStartPos(m_readStartPos_slider->value());
        State::getInstance()->setStateData(m_dataType,SAVE_FILE_START_POS,m_readStartPos_slider->value());//save the datas
    }else{
        m_pDataMgr->getMgrbyId(m_dataType)->setReadFileEndPos(m_readEndPos_slider->value());
        State::getInstance()->setStateData(m_dataType,SAVE_FILE_END_POS,m_readEndPos_slider->value());
    }
}
void GroupBasicWindow::startTestCheckStateChanged(int state){
    State::getInstance()->setStateData(m_dataType,SAVE_TEST,m_startTestCheckBox->isChecked());
    if(m_startTestCheckBox->isChecked()){
        m_pDataMgr->getMgrbyId(m_dataType)->startTest();
        showData("");
    }else{
        m_pDataMgr->getMgrbyId(m_dataType)->stopTest();
    }
}
void GroupBasicWindow::showReadDataCheckStateChanged(int state){
    //cout<<"pShowReadData_check->isChecked()="<<m_showDataCheckBox->isChecked()<<endl;
    State::getInstance()->setStateData(m_dataType,SAVE_SHOWDATA,m_showDataCheckBox->isChecked());
    m_pDataMgr->getMgrbyId(m_dataType)->setShowDataSign(m_showDataCheckBox->isChecked());
}
void GroupBasicWindow::sendDataCheckStateChanged(int state){
    m_pDataMgr->getMgrbyId(m_dataType)->resetDataFile();
    State::getInstance()->setStateData(m_dataType,SAVE_SENDDATA,m_sendDataCheckBox->isChecked());
    m_pDataMgr->getMgrbyId(m_dataType)->startSendData(m_sendDataCheckBox->isChecked());

    m_pDataMgr->getMgrbyId(m_dataType)->clearTestData();
}
void GroupBasicWindow::freOk_click(){
    m_freOkBtn->setEnabled(false);
    m_freCancelBtn->setEnabled(true);
    m_freEdit->setEnabled(false);
    m_freCancelBtn->setFocus();

    QString str = m_freEdit->text();
    bool toIntOk = false;
    int val = str.toInt(&toIntOk,10);
    if(!toIntOk){
        m_freEdit->insert("error");
        return;
    }
    m_pDataMgr->getMgrbyId(m_dataType)->setFrequency(val);

    cout<<"freOk_click src="<<str.toStdString().c_str()<<"val="<<val<<endl;
    m_timeoutEdit->clear();
    m_timeoutEdit->insert(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));

    State::getInstance()->setStateData(m_dataType,SAVE_FRE,val);

    //if(m_dataType == ECG_CLIENT){
        Global::getInstance()->saveFreAndCount(m_dataType,m_pDataMgr->getMgrbyId(m_dataType)->getFrequency(),m_pDataMgr->getMgrbyId(m_dataType)->getReadNum());
    //}
}

void GroupBasicWindow::freCancel_click(){
    m_freOkBtn->setEnabled(true);
    m_freCancelBtn->setEnabled(false);
    m_freEdit->setEnabled(true);
    m_freOkBtn->setFocus();

}

void GroupBasicWindow::rcOk_click(){
    m_readcountOkBtn->setEnabled(false);
    m_readcountCancelBtn->setEnabled(true);
    m_readcountEdit->setEnabled(false);
    m_readcountCancelBtn->setFocus();

    QString str = m_readcountEdit->text();


    bool toIntOk = false;
    int val = str.toInt(&toIntOk,10);
    if(!toIntOk){
        m_freEdit->insert("error");
        return;
    }
    m_pDataMgr->getMgrbyId(m_dataType)->setReadNum(val);
    cout<<"rcOk_click src="<<str.toStdString().c_str()<<"val="<<val<<endl;
    State::getInstance()->setStateData(m_dataType,SAVE_READNUM,val);

    //if(m_dataType == ECG_CLIENT){
        Global::getInstance()->saveFreAndCount(m_dataType,m_pDataMgr->getMgrbyId(m_dataType)->getFrequency(),m_pDataMgr->getMgrbyId(m_dataType)->getReadNum());
    //}
}

void GroupBasicWindow::rcCancel_click(){
    m_readcountOkBtn->setEnabled(true);
    m_readcountCancelBtn->setEnabled(false);
    m_readcountEdit->setEnabled(true);
    m_readcountOkBtn->setFocus();
}

void GroupBasicWindow::showData(const char* buf){
    m_pMutex.lock();
    m_queDataLine.push(buf);
    m_pMutex.unlock();
}

void GroupBasicWindow::handleSlider(bool isInit){
    long max = m_pDataMgr->getMgrbyId(m_dataType)->getFileSize();

    long mid = max/2-2;

    if(max<=0){
        max = 0;
        mid = 0;

    }
    cout<<"start slider   range  0 ~ "<<mid<<endl;
    cout<<"end slider     range  "<<mid+1<<"~ "<<max<<endl;

    m_readStartPos_slider->setRange(0,mid);
    m_readStartPos_slider->setValue(0);
    m_readEndPos_slider->setRange(mid,max);
    m_readEndPos_slider->setValue(max);

    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileStartPos(m_readStartPos_slider->value());
    m_pDataMgr->getMgrbyId(m_dataType)->setReadFileEndPos(m_readEndPos_slider->value());
}
void GroupBasicWindow::startCollectDatas_click(){
    char cmdbuf[200]={0};
    sprintf(cmdbuf,"rm -f %s",m_pDataMgr->getMgrbyId(m_dataType)->getCollectDataTmpFile());
    system(cmdbuf);
    cout<<"start Collect datas success"<<endl;
    State::getInstance()->setStateData(COLLECT_START,1);
    State::getInstance()->setStateData(COLLECT_SAVE,1);
    State::getInstance()->setStateData(COLLECT_DELETE,1);
    printf("startCollectDatas_click  getStateData(COLLECT_START)=%d\n",State::getInstance()->getStateData(COLLECT_START));

    m_startCollectData->setEnabled(false);
    m_stopCollectData->setEnabled(true);
    m_saveCollectData->setEnabled(false);
    m_delCollectData->setEnabled(false);
}

void GroupBasicWindow::stopCollectDatas_click(){
    QString frestr = m_freEdit->text();
    bool toIntOk = false;
    int val = frestr.toInt(&toIntOk,10);
    cout<<"stop Collect datas success"<<endl;
    State::getInstance()->setStateData(COLLECT_START,0);

    m_startCollectData->setEnabled(false);
    m_stopCollectData->setEnabled(false);
    m_saveCollectData->setEnabled(true);
    m_delCollectData->setEnabled(true);
}
void GroupBasicWindow::saveCollectDatas_click(){//yxy
    QString dir = "";
    char Buf[1024]={0};
    switch(m_dataType){
    case ECG_CLIENT:
        sprintf(Buf,"./datafile/ECG/%s",Global::getInstance()->getGlobalPath(ECG_CLIENT).c_str());
        dir = Buf;
        break;
    case SPO2_CLIENT:
        sprintf(Buf,"./datafile/SPO2/%s",Global::getInstance()->getGlobalPath(SPO2_CLIENT).c_str());
        dir = Buf;
        break;
    case NIBP_CLIENT:
        sprintf(Buf,"./datafile/NIBP/%s",m_pDataMgr->getMgrbyId(NIBP_CLIENT)->getPatientType());
        dir = "./datafile/NIBP";
        break;
    case IBP_CLIENT:
        dir = "./datafile/IBP";
        break;
    case CO2_CLIENT:
        sprintf(Buf,"./datafile/CO2/%s",Global::getInstance()->getGlobalPath(CO2_CLIENT).c_str());
        dir = Buf;
        break;
    case NARCO_CLIENT:
        sprintf(Buf,"./datafile/NARCO/%s",Global::getInstance()->getGlobalPath(NARCO_CLIENT).c_str());
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

    m_startCollectData->setEnabled(true);
    m_stopCollectData->setEnabled(false);
    m_saveCollectData->setEnabled(false);
    m_delCollectData->setEnabled(false);

    QString frestr = m_freEdit->text();
    bool toIntOk = false;
    int val = frestr.toInt(&toIntOk,10);

    if(ret/*&&val>0*/){

        val += 1;
        m_pDataMgr->getMgrbyId(m_dataType)->setFrequency(val);
        State::getInstance()->setStateData(m_dataType,SAVE_FRE,val);

        QString str = m_readcountEdit->text();
        toIntOk = false;
        val = str.toInt(&toIntOk,10);
        m_pDataMgr->getMgrbyId(m_dataType)->setReadNum(val);
        State::getInstance()->setStateData(m_dataType,SAVE_READNUM,val);

        cout<<"save Collect datas success"<<endl;
        //if(m_dataType == ECG_CLIENT){
            Global::getInstance()->saveFreAndCount(m_dataType,m_pDataMgr->getMgrbyId(m_dataType)->getFrequency(),m_pDataMgr->getMgrbyId(m_dataType)->getReadNum());
        //}
        QMessageBox::information(NULL, "notify", "save success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);


    }else{
        cout<<"save Collect datas failure"<<endl;
        QMessageBox::information(NULL, "notify", "save failure", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
        delCollectDatas_click();
    }
    State::getInstance()->setStateData(COLLECT_SAVE,0);
    State::getInstance()->setStateData(COLLECT_DELETE,0);
}

void GroupBasicWindow::delCollectDatas_click(){
    char cmdLine[100]={0};
    sprintf(cmdLine,"rm -f %s",m_pDataMgr->getMgrbyId(m_dataType)->getCollectDataTmpFile());
    system(cmdLine);
    m_startCollectData->setEnabled(true);
    m_stopCollectData->setEnabled(false);
    m_saveCollectData->setEnabled(false);
    m_delCollectData->setEnabled(false);
    QMessageBox::information(NULL, "notify", "delete success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
    State::getInstance()->setStateData(COLLECT_DELETE,0);
    State::getInstance()->setStateData(COLLECT_SAVE,0);
}

void GroupBasicWindow::nibpModeChange(int index){
    m_pDataMgr->getMgrbyId(NIBP_CLIENT)->setPatientType(m_nibpModeCb->currentText().toStdString().c_str());
    m_pDataMgr->getMgrbyId(NIBP_CLIENT)->setTxtValue(m_valueCb->currentText().toStdString().c_str());
    handleSlider(true);
}

const char* GroupBasicWindow::getCurValue(){
    if(m_valueCb->isEnabled()){
        return m_valueCb->currentText().toStdString().c_str();
    }else
        return m_alarmCb->currentText().toStdString().c_str();
}
void GroupBasicWindow::setFreAndReadCount(int fre,int count){
    m_pDataMgr->getMgrbyId(m_dataType)->setFrequency(fre);
    m_pDataMgr->getMgrbyId(m_dataType)->setReadNum(count);

    m_freEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getFrequency()));
    m_timeoutEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getTimeout()));
    m_readcountEdit->setText(QString::number(m_pDataMgr->getMgrbyId(m_dataType)->getReadNum()));

}

GroupEcgWindow::GroupEcgWindow(QWidget *parent,DataMgr* pMgr): GroupBasicWindow(parent,ECG_CLIENT,pMgr)
{
    initLayout();
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearTextBrowser_click()));
    connect(m_sendComfireBtn, SIGNAL(clicked()), this, SLOT(sendRequestData_click()));
    connect(m_generateTestDataBtn,SIGNAL(clicked()),this,SLOT(generateTestData_click()));
    connect(m_addValueBtn,SIGNAL(clicked()),this,SLOT(addValueToCb_click()));
    connect(m_delValueBtn,SIGNAL(clicked()),this,SLOT(delValueToCb_click()));
    connect(m_addAlarmBtn,SIGNAL(clicked()),this,SLOT(addAlarmToCb_click()));
    connect(m_delAlarmBtn,SIGNAL(clicked()),this,SLOT(delAlarmToCb_click()));
    connect(m_saveCurPosBtn,SIGNAL(clicked()),this,SLOT(updateFileFromStartToEndPos_click()));
    connect(m_readStartPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));
    connect(m_readEndPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));

    connect(m_valueCb, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(m_alarmCb, SIGNAL(currentIndexChanged(int)), this, SLOT(alarmChanged(int)));

    connect(m_startTestCheckBox, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(m_showDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(m_sendDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));

    connect(m_freOkBtn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(m_freCancelBtn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(m_readcountOkBtn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(m_readcountCancelBtn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));

    connect(m_startCollectData,SIGNAL(clicked()),this,SLOT(startCollectDatas_click()));
    connect(m_stopCollectData,SIGNAL(clicked()),this,SLOT(stopCollectDatas_click()));
    connect(m_saveCollectData,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect(m_delCollectData,SIGNAL(clicked()),this,SLOT(delCollectDatas_click()));

    init();

}
void GroupEcgWindow::initLayout(){
    GroupBasicWindow::initLayout();
}

void GroupEcgWindow::updateWindow(MODE_TYPE mode){
    GroupBasicWindow::updateWindow(mode);
}

//////////////////////////////////////////////////////////////////////////


GroupSpo2Window::GroupSpo2Window(QWidget *parent,DataMgr* pMgr): GroupBasicWindow(parent,SPO2_CLIENT,pMgr)
{
    initLayout();
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearTextBrowser_click()));
    connect(m_sendComfireBtn, SIGNAL(clicked()), this, SLOT(sendRequestData_click()));
    connect(m_generateTestDataBtn,SIGNAL(clicked()),this,SLOT(generateTestData_click()));
    connect(m_addValueBtn,SIGNAL(clicked()),this,SLOT(addValueToCb_click()));
    connect(m_delValueBtn,SIGNAL(clicked()),this,SLOT(delValueToCb_click()));
    connect(m_addAlarmBtn,SIGNAL(clicked()),this,SLOT(addAlarmToCb_click()));
    connect(m_delAlarmBtn,SIGNAL(clicked()),this,SLOT(delAlarmToCb_click()));
    connect(m_saveCurPosBtn,SIGNAL(clicked()),this,SLOT(updateFileFromStartToEndPos_click()));
    connect(m_readStartPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));
    connect(m_readEndPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));

    connect(m_valueCb, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(m_alarmCb, SIGNAL(currentIndexChanged(int)), this, SLOT(alarmChanged(int)));

    connect(m_startTestCheckBox, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(m_showDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(m_sendDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));

    connect(m_freOkBtn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(m_freCancelBtn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(m_readcountOkBtn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(m_readcountCancelBtn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));

    connect(m_startCollectData,SIGNAL(clicked()),this,SLOT(startCollectDatas_click()));
    connect(m_stopCollectData,SIGNAL(clicked()),this,SLOT(stopCollectDatas_click()));
    connect(m_saveCollectData,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect(m_delCollectData,SIGNAL(clicked()),this,SLOT(delCollectDatas_click()));

    init();

}
void GroupSpo2Window::initLayout(){
    GroupBasicWindow::initLayout();

    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}

void GroupSpo2Window::updateWindow(MODE_TYPE mode){
    GroupBasicWindow::updateWindow(mode);
    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}


//////////////////////////////////////////////////////////////////
GroupNibpWindow::GroupNibpWindow(QWidget *parent,DataMgr* pMgr): GroupBasicWindow(parent,NIBP_CLIENT,pMgr)
{
    initLayout();
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearTextBrowser_click()));
    connect(m_sendComfireBtn, SIGNAL(clicked()), this, SLOT(sendRequestData_click()));
    connect(m_generateTestDataBtn,SIGNAL(clicked()),this,SLOT(generateTestData_click()));
    connect(m_addValueBtn,SIGNAL(clicked()),this,SLOT(addValueToCb_click()));
    connect(m_delValueBtn,SIGNAL(clicked()),this,SLOT(delValueToCb_click()));
    connect(m_addAlarmBtn,SIGNAL(clicked()),this,SLOT(addAlarmToCb_click()));
    connect(m_delAlarmBtn,SIGNAL(clicked()),this,SLOT(delAlarmToCb_click()));
    connect(m_saveCurPosBtn,SIGNAL(clicked()),this,SLOT(updateFileFromStartToEndPos_click()));
    connect(m_readStartPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));
    connect(m_readEndPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));

    connect(m_valueCb, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(m_alarmCb, SIGNAL(currentIndexChanged(int)), this, SLOT(alarmChanged(int)));

    connect(m_startTestCheckBox, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(m_showDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(m_sendDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));

    connect(m_freOkBtn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(m_freCancelBtn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(m_readcountOkBtn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(m_readcountCancelBtn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));

    connect(m_startCollectData,SIGNAL(clicked()),this,SLOT(startCollectDatas_click()));
    connect(m_stopCollectData,SIGNAL(clicked()),this,SLOT(stopCollectDatas_click()));
    connect(m_saveCollectData,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect(m_delCollectData,SIGNAL(clicked()),this,SLOT(delCollectDatas_click()));

    connect(m_nibpModeCb, SIGNAL(currentIndexChanged(int)), this, SLOT(nibpModeChange(int)));

    init();

    m_nibpModeCb->addItem("Adult");
    m_nibpModeCb->addItem("Enfant");
    m_nibpModeCb->addItem("Baby");

}
void GroupNibpWindow::initLayout(){
    GroupBasicWindow::initLayout();

    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}

void GroupNibpWindow::updateWindow(MODE_TYPE mode){
    GroupBasicWindow::updateWindow(mode);
    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}



////////////////////////////////////////////////////////////////////////////////
GroupIbpWindow::GroupIbpWindow(QWidget *parent,DataMgr* pMgr): GroupBasicWindow(parent,IBP_CLIENT,pMgr)
{
    initLayout();
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearTextBrowser_click()));
    connect(m_sendComfireBtn, SIGNAL(clicked()), this, SLOT(sendRequestData_click()));
    connect(m_generateTestDataBtn,SIGNAL(clicked()),this,SLOT(generateTestData_click()));
    connect(m_addValueBtn,SIGNAL(clicked()),this,SLOT(addValueToCb_click()));
    connect(m_delValueBtn,SIGNAL(clicked()),this,SLOT(delValueToCb_click()));
    connect(m_addAlarmBtn,SIGNAL(clicked()),this,SLOT(addAlarmToCb_click()));
    connect(m_delAlarmBtn,SIGNAL(clicked()),this,SLOT(delAlarmToCb_click()));
    connect(m_saveCurPosBtn,SIGNAL(clicked()),this,SLOT(updateFileFromStartToEndPos_click()));
    connect(m_readStartPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));
    connect(m_readEndPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));

    connect(m_valueCb, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(m_alarmCb, SIGNAL(currentIndexChanged(int)), this, SLOT(alarmChanged(int)));

    connect(m_startTestCheckBox, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(m_showDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(m_sendDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));

    connect(m_freOkBtn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(m_freCancelBtn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(m_readcountOkBtn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(m_readcountCancelBtn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));

    connect(m_startCollectData,SIGNAL(clicked()),this,SLOT(startCollectDatas_click()));
    connect(m_stopCollectData,SIGNAL(clicked()),this,SLOT(stopCollectDatas_click()));
    connect(m_saveCollectData,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect(m_delCollectData,SIGNAL(clicked()),this,SLOT(delCollectDatas_click()));

    init();

}
void GroupIbpWindow::initLayout(){
    GroupBasicWindow::initLayout();

    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}

void GroupIbpWindow::updateWindow(MODE_TYPE mode){
    GroupBasicWindow::updateWindow(mode);
    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}

////////////////////////////////////////////////////////////////////////////////
GroupCo2Window::GroupCo2Window(QWidget *parent,DataMgr* pMgr): GroupBasicWindow(parent,CO2_CLIENT,pMgr)
{
    initLayout();
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearTextBrowser_click()));
    connect(m_sendComfireBtn, SIGNAL(clicked()), this, SLOT(sendRequestData_click()));
    connect(m_generateTestDataBtn,SIGNAL(clicked()),this,SLOT(generateTestData_click()));
    connect(m_addValueBtn,SIGNAL(clicked()),this,SLOT(addValueToCb_click()));
    connect(m_delValueBtn,SIGNAL(clicked()),this,SLOT(delValueToCb_click()));
    connect(m_addAlarmBtn,SIGNAL(clicked()),this,SLOT(addAlarmToCb_click()));
    connect(m_delAlarmBtn,SIGNAL(clicked()),this,SLOT(delAlarmToCb_click()));
    connect(m_saveCurPosBtn,SIGNAL(clicked()),this,SLOT(updateFileFromStartToEndPos_click()));
    connect(m_readStartPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));
    connect(m_readEndPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));

    connect(m_valueCb, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(m_alarmCb, SIGNAL(currentIndexChanged(int)), this, SLOT(alarmChanged(int)));

    connect(m_startTestCheckBox, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(m_showDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(m_sendDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));

    connect(m_freOkBtn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(m_freCancelBtn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(m_readcountOkBtn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(m_readcountCancelBtn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));

    connect(m_startCollectData,SIGNAL(clicked()),this,SLOT(startCollectDatas_click()));
    connect(m_stopCollectData,SIGNAL(clicked()),this,SLOT(stopCollectDatas_click()));
    connect(m_saveCollectData,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect(m_delCollectData,SIGNAL(clicked()),this,SLOT(delCollectDatas_click()));

    init();

}
void GroupCo2Window::initLayout(){
    GroupBasicWindow::initLayout();

    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}

void GroupCo2Window::updateWindow(MODE_TYPE mode){
    GroupBasicWindow::updateWindow(mode);
    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}


////////////////////////////////////////////////////////////////////////////////
GroupNarcoWindow::GroupNarcoWindow(QWidget *parent,DataMgr* pMgr): GroupBasicWindow(parent,NARCO_CLIENT,pMgr)
{
    initLayout();
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearTextBrowser_click()));
    connect(m_sendComfireBtn, SIGNAL(clicked()), this, SLOT(sendRequestData_click()));
    connect(m_generateTestDataBtn,SIGNAL(clicked()),this,SLOT(generateTestData_click()));
    connect(m_addValueBtn,SIGNAL(clicked()),this,SLOT(addValueToCb_click()));
    connect(m_delValueBtn,SIGNAL(clicked()),this,SLOT(delValueToCb_click()));
    connect(m_addAlarmBtn,SIGNAL(clicked()),this,SLOT(addAlarmToCb_click()));
    connect(m_delAlarmBtn,SIGNAL(clicked()),this,SLOT(delAlarmToCb_click()));
    connect(m_saveCurPosBtn,SIGNAL(clicked()),this,SLOT(updateFileFromStartToEndPos_click()));
    connect(m_readStartPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));
    connect(m_readEndPos_slider,SIGNAL(valueChanged(int)),this,SLOT(setValue_slider(int)));

    connect(m_valueCb, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(m_alarmCb, SIGNAL(currentIndexChanged(int)), this, SLOT(alarmChanged(int)));

    connect(m_startTestCheckBox, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(m_showDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(m_sendDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(sendDataCheckStateChanged(int)));

    connect(m_freOkBtn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(m_freCancelBtn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(m_readcountOkBtn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(m_readcountCancelBtn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));

    connect(m_startCollectData,SIGNAL(clicked()),this,SLOT(startCollectDatas_click()));
    connect(m_stopCollectData,SIGNAL(clicked()),this,SLOT(stopCollectDatas_click()));
    connect(m_saveCollectData,SIGNAL(clicked()),this,SLOT(saveCollectDatas_click()));
    connect(m_delCollectData,SIGNAL(clicked()),this,SLOT(delCollectDatas_click()));

    init();

}
void GroupNarcoWindow::initLayout(){
    GroupBasicWindow::initLayout();

    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}

void GroupNarcoWindow::updateWindow(MODE_TYPE mode){
    GroupBasicWindow::updateWindow(mode);
    m_alarmCb->setCurrentIndex(0);
    m_alarmCb->setEnabled(false);
    m_addAlarmBtn->setEnabled(false);
    m_delAlarmBtn->setEnabled(false);
}
