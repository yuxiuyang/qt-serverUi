#include "state.h"
State* State::m_instance = new State();
State::State()
{
    for(int i=0;i<STATE_COUNT;i++){
        m_value[i] = 0;
    }

    strcpy(m_fileName,"./configure.conf");
}
State::~State()
{
    delete m_value;
}
void State::setSave(){
    FILE* file = fopen(m_fileName, "w+");
    if(!file){
        //printf("open the file configure failue,m_fileName=%s\n",m_fileName);
        cout<<"open the file configure failue,m_fileName="<<m_fileName<<endl;
        return;
    }
    //cout<<"start save\n";
//    for(int i=0;i<SHUTDOWN_SAVE;i++){
//        //printf("m_value[%d]=%d\n",i,m_value[i]);
//        //cout<<"m_value["<<i<<"]="<<m_value[i]<<endl;
//    }
    //cout<<"end save...\n";
    int size = fwrite(m_value,SHUTDOWN_SAVE*sizeof(m_value[0]),1,file);
    if(size == 0){
        printf("write configure failue,size=%d\n",size);
    }else{
        //printf("write configure success\n");
    }
    fclose(file);
}

void State::setDef(){
        m_value[NIBP_FRE] = 2;
        m_value[NIBP_READRUM] = 6;
        m_value[NIBP_TEST] = 0;
        m_value[NIBP_SHOWDATA] = 0;
        m_value[NIBP_SENDDATA] = 0;
        m_value[SPO2_FRE] = 3;
        m_value[SPO2_READRUM] = 4;
        m_value[SPO2_TEST] = 0;
        m_value[SPO2_SHOWDATA] = 0;
        m_value[SPO2_SENDDATA] = 0;
        m_value[ECG_FRE] = 23;
        m_value[ECG_READRUM] = 4;
        m_value[ECG_TEST] = 0;
        m_value[ECG_SHOWDATA] = 0;
        m_value[ECG_SENDDATA] = 0;
        m_value[IBP_FRE] = 19;
        m_value[IBP_READRUM] = 5;
        m_value[IBP_TEST] = 0;
        m_value[IBP_SHOWDATA] = 0;
        m_value[IBP_SENDDATA] = 0;
        m_value[CO2_FRE] = 12;
        m_value[CO2_READRUM] = 6;
        m_value[CO2_TEST] = 0;
        m_value[CO2_SHOWDATA] = 0;
        m_value[CO2_SENDDATA] = 0;
        m_value[NARCO_FRE] = 14;
        m_value[NARCO_READRUM] = 6;
        m_value[NARCO_TEST] = 0;
        m_value[NARCO_SHOWDATA] = 0;
        m_value[NARCO_SENDDATA] = 0;
        m_value[CUR_CLIENT] = ECG_CLIENT;

        setSave();
        printf("setDef value success\n");
}
void State::loadConf(){
        FILE* file = fopen(m_fileName, "r");
        if(!file){//not configure file
            printf("loadConf  open the file configure failue\n");
            return ;
        }
//        printf("end ...\n");
        int size = fread(m_value,SHUTDOWN_SAVE*sizeof(m_value[0]),1,file);
        if(size==0){
            printf("read configure failue size=%d\n",size);
        }else{
            printf("read configure success\n");
        }
        fclose(file);

//        for(int i=0;i<STATE_COUNT;i++){
//            printf("m_value[%d]=%d\n",i,m_value[i]);
//        }
}
bool State::isExistConf(){
    FILE* file = fopen(m_fileName, "r");
    if(!file) return false;
    return true;
}

int  State::getStateData(STATE_SAVE id){
        return m_value[id];
}

void State::setStateData(STATE_SAVE id,int data){
    assert(id>0 && id<STATE_COUNT);
    m_value[id] = data;
//   cout<<"setStateData id="<<id<<"   value="<<m_value[id]<<endl;

    setSave();
}
