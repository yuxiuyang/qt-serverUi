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


    ui->pStartServerBtn->setEnabled(false);
    ui->pStopServerBtn->hide();
    ui->pServerStateLaber->setText("server running");
    m_pTimer->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tabChange(int index){
    //int ix = m_tabWidget->currentIndex();
    cout<<"index = "<<index<<" cur ix="<<endl;

    GroupBasicWindow* group=NULL;
    switch(index){
    case 0:
        group = m_groupEcg;
        break;
    case 1:
        group = m_groupSpo2;
        break;
    case 2:
        group = m_groupNibp;
        break;
    case 3:
        group = m_groupIbp;
        break;
    case 4:
        group = m_groupCo2;
        break;
    case 5:
        group = m_groupNarco;
        break;
    default:
        break;
    }

    if(group == NULL)return ;

//    if(State::getInstance()->getStateData(COLLECT_DATA)){
//        group->updateWindow(COLLECTING_DATA_MODE);
//    }else{
//        group->updateWindow(SIMULATOR_MODE);
//    }
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

        m_pDataMgr->getMgrbyId(ECG_CLIENT)->sendData(Cmd_Msg,ECG_CLIENT,MODE_COLLECTDATAS);
    }else{
        ui->pCollectDataCheckBox->setText("Collect datas");

        m_groupEcg->updateWindow(SIMULATOR_MODE);
        m_groupSpo2->updateWindow(SIMULATOR_MODE);
        m_groupNibp->updateWindow(SIMULATOR_MODE);
        m_groupIbp->updateWindow(SIMULATOR_MODE);
        m_groupCo2->updateWindow(SIMULATOR_MODE);
        m_groupNarco->updateWindow(SIMULATOR_MODE);

        m_pDataMgr->getMgrbyId(ECG_CLIENT)->sendData(Cmd_Msg,ECG_CLIENT,MODE_NORMAL);
    }
}
