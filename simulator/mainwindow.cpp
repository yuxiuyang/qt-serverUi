#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Simulator");
    move(150,20);
    resize(980,700);

    m_pDataMgr = new DataMgr();
    m_pDataMgr->setWindow((void*)this);


    ui->pConnectMsgBrowser->resize(200,540);
    ui->pClearConnectMsgBtn->move(ui->pConnectMsgBrowser->x(),ui->pConnectMsgBrowser->y()+ui->pConnectMsgBrowser->height()+10);
    m_tabWidget = new QTabWidget(this);
    m_groupEcg = new GroupEcgWindow(this,m_pDataMgr);
    m_groupSpo2 = new GroupSpo2Window(this,m_pDataMgr);
    m_groupNibp = new GroupNibpWindow(this,m_pDataMgr);
    m_groupIbp = new GroupIbpWindow(this,m_pDataMgr);
    m_groupCo2 = new GroupCo2Window(this,m_pDataMgr);
    m_groupNarco = new GroupNarcoWindow(this,m_pDataMgr);

    m_tabWidget->addTab(m_groupEcg, tr("ECG"));
    m_tabWidget->addTab(m_groupSpo2, tr("SPO2"));
    m_tabWidget->addTab(m_groupNibp, tr("NIBP"));
    m_tabWidget->addTab(m_groupIbp, tr("IBP"));
    m_tabWidget->addTab(m_groupCo2, tr("CO2"));
    m_tabWidget->addTab(m_groupNarco, tr("NARCO"));
    m_tabWidget->move(ui->pConnectMsgBrowser->x()+ui->pConnectMsgBrowser->width()+10,ui->pConnectMsgBrowser->y()+20);
    m_tabWidget->resize(710,580);
    //m_tabWidget->setCurrentIndex(1);



    m_pDataMgr->getMgrbyId(ECG_CLIENT)->setWindow(m_groupEcg);
    m_pDataMgr->getMgrbyId(SPO2_CLIENT)->setWindow(m_groupSpo2);
    m_pDataMgr->getMgrbyId(NIBP_CLIENT)->setWindow(m_groupNibp);
    m_pDataMgr->getMgrbyId(IBP_CLIENT)->setWindow(m_groupIbp);
    m_pDataMgr->getMgrbyId(CO2_CLIENT)->setWindow(m_groupCo2);
    m_pDataMgr->getMgrbyId(NARCO_CLIENT)->setWindow(m_groupNarco);


    m_pTimer = new QTimer(this);
    connect( m_pTimer, SIGNAL(timeout()), this, SLOT(sendTimer()) );
    connect(ui->pStartServerBtn, SIGNAL(clicked()), this, SLOT(start_click()));
    connect(ui->pStopServerBtn, SIGNAL(clicked()), this, SLOT(stop_click()));
    connect(ui->pClearConnectMsgBtn, SIGNAL(clicked()), this, SLOT(clearConnectMsg_click()));
    connect(ui->pCollectDataCheckBox,SIGNAL(stateChanged(int)),this,SLOT(collectDatasCheckStateChanged(int)));
    connect(m_tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChange(int)));


    connect(ui->pAddGlobalPathBtn,SIGNAL(clicked()),this,SLOT(addGlobalPathToCb_click()));
    connect(ui->pDelGlobalPathBtn,SIGNAL(clicked()),this,SLOT(delGlobalPathToCb_click()));
    connect(ui->pGlobalPathCb, SIGNAL(currentIndexChanged(int)), this, SLOT(globalPathChanged(int)));


    ui->pStartServerBtn->setEnabled(false);
    ui->pStopServerBtn->hide();
    ui->pServerStateLaber->setText("server running");
    m_pTimer->start(2000);

    m_dataType = ECG_CLIENT;
    tabChange(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
GroupBasicWindow* MainWindow::getCurGroupWinodw(ClientType_ id){
    switch(id){
    case ECG_CLIENT:
        return m_groupEcg;
        break;
    case SPO2_CLIENT:
        return m_groupSpo2;
        break;
    case NIBP_CLIENT:
        return m_groupNibp;
        break;
    case IBP_CLIENT:
        return m_groupIbp;
        break;
    case CO2_CLIENT:
        return m_groupCo2;
        break;
    case NARCO_CLIENT:
        return m_groupNarco;
        break;
    default:
        break;
    }
    return NULL;
}

void MainWindow::tabChange(int index){
    //int ix = m_tabWidget->currentIndex();
    cout<<"index = "<<index<<endl;

    ui->pGlobalPathCb->hide();
    ui->pAddGlobalPathBtn->hide();
    ui->pDelGlobalPathBtn->hide();
    ui->pGlobalLabel->hide();

    ui->pGlobalPathCb->clear();
    switch(index){
    case 0:
        m_dataType = ECG_CLIENT;
        ui->pGlobalPathCb->insertItems(0,Global::getInstance()->getGlobalPathList(ECG_CLIENT));
        if(Global::getInstance()->getGlobalPathList(ECG_CLIENT).count()<=1){
            ui->pGlobalPathCb->setCurrentIndex(0);
        }
        ui->pGlobalPathCb->setCurrentIndex(State::getInstance()->getStateData(ECG_CUR_GLOBALPATH));
        ui->pGlobalPathCb->show();
        ui->pAddGlobalPathBtn->show();
        ui->pDelGlobalPathBtn->show();
        ui->pGlobalLabel->show();
        break;
    case 1:
        m_dataType = SPO2_CLIENT;
        ui->pGlobalPathCb->insertItems(0,Global::getInstance()->getGlobalPathList(SPO2_CLIENT));
        if(Global::getInstance()->getGlobalPathList(SPO2_CLIENT).count()<=1){
            ui->pGlobalPathCb->setCurrentIndex(0);
        }
        else ui->pGlobalPathCb->setCurrentIndex(State::getInstance()->getStateData(SPO2_CUR_GLOBALPATH));
        ui->pGlobalPathCb->show();
        ui->pAddGlobalPathBtn->show();
        ui->pDelGlobalPathBtn->show();
        ui->pGlobalLabel->show();

        break;
    case 2:
        m_dataType = NIBP_CLIENT;

        break;
    case 3:
        m_dataType = IBP_CLIENT;

        break;
    case 4:
        m_dataType = CO2_CLIENT;

        getCurGroupWinodw(CO2_CLIENT)->sendDataCheck_SetChecked(State::getInstance()->getStateData(CO2_CLIENT,SAVE_SENDDATA));

        ui->pGlobalPathCb->insertItems(0,Global::getInstance()->getGlobalPathList(CO2_CLIENT));
        if(Global::getInstance()->getGlobalPathList(SPO2_CLIENT).count()<=1){
            ui->pGlobalPathCb->setCurrentIndex(0);
        }
        ui->pGlobalPathCb->setCurrentIndex(State::getInstance()->getStateData(CO2_CUR_GLOBALPATH));
        ui->pGlobalPathCb->show();
        ui->pAddGlobalPathBtn->show();
        ui->pDelGlobalPathBtn->show();
        ui->pGlobalLabel->show();

        break;
    case 5:
        m_dataType = NARCO_CLIENT;
        getCurGroupWinodw(NARCO_CLIENT)->sendDataCheck_SetChecked(State::getInstance()->getStateData(NARCO_CLIENT,SAVE_SENDDATA));
        if(Global::getInstance()->getGlobalPathList(NARCO_CLIENT).count()<=1){
            ui->pGlobalPathCb->setCurrentIndex(0);
        }
        ui->pGlobalPathCb->insertItems(0,Global::getInstance()->getGlobalPathList(NARCO_CLIENT));

        ui->pGlobalPathCb->setCurrentIndex(State::getInstance()->getStateData(NARCO_CUR_GLOBALPATH));
        ui->pGlobalPathCb->show();
        ui->pAddGlobalPathBtn->show();
        ui->pDelGlobalPathBtn->show();
        ui->pGlobalLabel->show();
        break;
    default:
        break;
    }

    GroupBasicWindow* group=getCurGroupWinodw(m_dataType);
    if(group == NULL)return ;

    group->handleSlider(true);
}

void MainWindow::sendTimer(){
    while(!m_queConnectMsgLine.empty()){
         ui->pConnectMsgBrowser->append(m_queConnectMsgLine.front().c_str());
         m_pMutex.lock();
         m_queConnectMsgLine.pop();
         m_pMutex.unlock();
    }

    m_groupEcg->sendTimer();
    m_groupSpo2->sendTimer();
    m_groupNibp->sendTimer();
    m_groupIbp->sendTimer();
    m_groupCo2->sendTimer();
    m_groupNarco->sendTimer();
}
void MainWindow::appendConnectMsg(const char* msg){
    m_pMutex.lock();
    m_queConnectMsgLine.push(msg);
    m_pMutex.unlock();
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
void MainWindow::start_click(){
    ui->pServerStateLaber->setText("server running");
    ui->pStartServerBtn->setEnabled(false);
    ui->pStopServerBtn->setEnabled(true);

    DataDev::getInstance()->start();
}

void MainWindow::stop_click(){
    ui->pStartServerBtn->setEnabled(true);
    ui->pStopServerBtn->setEnabled(false);
    ui->pServerStateLaber->setText("server stop");
    DataDev::getInstance()->stop();
}

void MainWindow::clearConnectMsg_click(){
    ui->pConnectMsgBrowser->clear();
}
void MainWindow::collectDatasCheckStateChanged(int state){
    cout<<"collectDatasCheckStateChanged"<<"  isChecked()="<<ui->pCollectDataCheckBox->isChecked()<<endl;
    bool send_nibp = m_pDataMgr->getMgrbyId(NIBP_CLIENT)->getSendDataState();
    bool send_spo2 = m_pDataMgr->getMgrbyId(SPO2_CLIENT)->getSendDataState();
    bool send_ecg = m_pDataMgr->getMgrbyId(ECG_CLIENT)->getSendDataState();
    bool send_ibp = m_pDataMgr->getMgrbyId(IBP_CLIENT)->getSendDataState();
    bool send_co2 = m_pDataMgr->getMgrbyId(CO2_CLIENT)->getSendDataState();
    bool send_narco = m_pDataMgr->getMgrbyId(NARCO_CLIENT)->getSendDataState();

    if(send_nibp || send_spo2 || send_ecg || send_ibp || send_co2 || send_narco){
        QMessageBox::information(NULL, "notify", "please stop send data", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
        ui->pCollectDataCheckBox->setChecked(false);
        return;
    }
    State::getInstance()->setStateData(COLLECT_DATA,ui->pCollectDataCheckBox->isChecked());


    if(ui->pCollectDataCheckBox->isChecked()){
        ui->pCollectDataCheckBox->setText("Collecting data");

        //close all files
        m_groupEcg->updateWindow(COLLECTING_DATA_MODE);
        m_groupSpo2->updateWindow(COLLECTING_DATA_MODE);
        m_groupNibp->updateWindow(COLLECTING_DATA_MODE);
        m_groupIbp->updateWindow(COLLECTING_DATA_MODE);
        m_groupCo2->updateWindow(COLLECTING_DATA_MODE);
        m_groupNarco->updateWindow(COLLECTING_DATA_MODE);

        m_pDataMgr->sendCmd(MODE_COLLECTDATAS,0);
    }else{
        ui->pCollectDataCheckBox->setText("Collect datas");

        m_groupEcg->updateWindow(SIMULATOR_MODE);
        m_groupSpo2->updateWindow(SIMULATOR_MODE);
        m_groupNibp->updateWindow(SIMULATOR_MODE);
        m_groupIbp->updateWindow(SIMULATOR_MODE);
        m_groupCo2->updateWindow(SIMULATOR_MODE);
        m_groupNarco->updateWindow(SIMULATOR_MODE);

        m_pDataMgr->sendCmd(MODE_NORMAL,0);
    }
}

void MainWindow::addGlobalPathToCb_click(){
    bool isOK=false;
    QString text = QInputDialog::getText(NULL, "Input Dialog","Please input Integer(0-1000)",QLineEdit::Normal,"",&isOK);
    if(!isOK) {
        //QMessageBox::information(NULL, "Information","Your comment is: <b>" + text + "</b>",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    QStringList::iterator it = qFind(Global::getInstance()->getGlobalPathList(m_dataType).begin(),Global::getInstance()->getGlobalPathList(m_dataType).end(),text.toStdString().c_str());
    if(it != Global::getInstance()->getGlobalPathList(m_dataType).end()){
        cout<<"this val="<<text.toStdString().c_str()<<" has exist"<<endl;
        return;
    }
    Global::getInstance()->getGlobalPathList(m_dataType).append(text);
    qSort(Global::getInstance()->getValueList(m_dataType).begin(), Global::getInstance()->getValueList(m_dataType).end());
    ui->pGlobalPathCb->clear();
    ui->pGlobalPathCb->insertItems(0,Global::getInstance()->getGlobalPathList(m_dataType));

    int ix = ui->pGlobalPathCb->findText(text);
    if(ix>0)
        ui->pGlobalPathCb->setCurrentIndex(ix);
    getCurGroupWinodw(m_dataType)->handleSlider(true);

    Global::getInstance()->saveTxtValue(Global::getInstance()->getGlobalPathList(m_dataType));
}

void MainWindow::delGlobalPathToCb_click(){

    if(ui->pGlobalPathCb->count()<=1){
        //return;
    }
    int index = ui->pGlobalPathCb->currentIndex();
    Global::getInstance()->getGlobalPathList(m_dataType).removeAt(index);

    ui->pGlobalPathCb->clear();
    ui->pGlobalPathCb->insertItems(0,Global::getInstance()->getGlobalPathList(m_dataType));

    if(index>0&&index<Global::getInstance()->getGlobalPathList(m_dataType).count())
        ui->pGlobalPathCb->setCurrentIndex(index);
    getCurGroupWinodw(m_dataType)->handleSlider(true);

    Global::getInstance()->saveTxtValue(Global::getInstance()->getGlobalPathList(m_dataType));
}

void MainWindow::globalPathChanged(int index){
    if(index<0)return;

    char buf[1024]={0};
    sprintf(buf,"%s",ui->pGlobalPathCb->currentText().toStdString().c_str());
    cout<<"buf="<<buf<<endl;
    Global::getInstance()->setGlobalPath(m_dataType,buf);

    GroupBasicWindow* group = getCurGroupWinodw(m_dataType);
    m_pDataMgr->getMgrbyId(m_dataType)->setTxtValue(group->getCurValue());

    group->handleSlider(true);
    FRE_READCOUNT data;
    Global::getInstance()->getFreAndCount(m_dataType,data);
    group->setFreAndReadCount(data.fre,data.readcount);

    if(ui->pGlobalPathCb->currentIndex()>0)
        State::getInstance()->setStateData(m_dataType,SAVE_CUR_GLOBALPATH,ui->pGlobalPathCb->currentIndex());

}
