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





void State::setStateData(ClientType_ id, SAVE_TYPE saveType,int val) {
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->setStateData(ECG_CUR_GLOBALPATH, val);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->setStateData(SPO2_CUR_GLOBALPATH, val);
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
                State::getInstance()->setStateData(CO2_ALARM_VALUE, val);\
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->setStateData(CO2_CUR_GLOBALPATH, val);
                break;
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->setStateData(NARCO_CUR_GLOBALPATH, val);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->setStateData(NIBP_CUR_GLOBALPATH, val);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->setStateData(IBP_CUR_GLOBALPATH, val);
                break;
            default:
                break;
            }
            break;
        default:
                break;
        }
}


int State::getStateData(ClientType_ id, SAVE_TYPE saveType) {
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->getStateData(ECG_CUR_GLOBALPATH);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->getStateData(SPO2_CUR_GLOBALPATH);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->getStateData(CO2_CUR_GLOBALPATH);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->getStateData(NARCO_CUR_GLOBALPATH);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->getStateData(NIBP_CUR_GLOBALPATH);
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
            case SAVE_CUR_GLOBALPATH:
                State::getInstance()->getStateData(IBP_CUR_GLOBALPATH);
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
