#ifndef GLOBAL_H
#define GLOBAL_H
#include "QStringList"
#include "file.h"
QStringList g_ecgValues;
QStringList g_ecgAlarms;
QStringList g_spo2Values;
QStringList g_nibpValues;
QStringList g_ibpValues;
QStringList g_co2Values;
QStringList g_narcoValues;

void loadTxtValue(QStringList& strList,const char* filename);

void g_InitGlobalText(){
//    g_ecgValues.append("60");
//    g_ecgValues.append("80");
//    g_ecgValues.append("120");
//    g_ecgValues.append("140");
//    g_ecgValues.append("160");
//    g_ecgValues.append("240");
//    g_ecgValues.append("290");
//    g_ecgValues.append("300");
//    g_ecgValues.append("320");
//    g_ecgValues.append("350");
//
//    g_ecgAlarms.append("NORMAL");
//    g_ecgAlarms.append("VPC_TRIGEMINY");
//    g_ecgAlarms.append("VPC_BIGEMINY");
//    g_ecgAlarms.append("VPC_VT");
//    g_ecgAlarms.append("VPC_VEB_PAIR");
//    g_ecgAlarms.append("VPC_R_ON_T");
//    g_ecgAlarms.append("VPC_VEB");
//    g_ecgAlarms.append("VPC_TACHYCARDIA");
//    g_ecgAlarms.append("VPC_BRADYCARDIA");
//    g_ecgAlarms.append("VPC_MISSEDBEATS");
//    g_ecgAlarms.append("VPC_VFID");
//    g_ecgAlarms.append("VPC_ARRHYTHMIA");
//    g_ecgAlarms.append("VPC_NOVPC");
//    g_ecgAlarms.append("VPC_UNKNOWN");
//    g_ecgAlarms.append("VPC_ST");
//    g_ecgAlarms.append("VPC_VT_OVER_2");
//
//
//    g_spo2Values.append("90");
//    g_spo2Values.append("100");
//
//    g_nibpValues.append("120/80 (50)");
//    g_nibpValues.append("150/40 (80)");
//
//
//    g_ibpValues.append("120/80 (50)");
//    g_ibpValues.append("150/40 (80)");
//
//    g_co2Values.append("30");
//    g_co2Values.append("50");
//
//    g_narcoValues.append("27");
//    g_narcoValues.append("40");
    loadTxtValue(g_ecgValues,"../ServerUi/datafile/ECG/value_data.txt");
    loadTxtValue(g_ecgAlarms,"../ServerUi/datafile/ECG/alarm_data.txt");

    loadTxtValue(g_spo2Values,"../ServerUi/datafile/SPO2/value_data.txt");
    loadTxtValue(g_nibpValues,"../ServerUi/datafile/NIBP/value_data.txt");
    loadTxtValue(g_ibpValues,"../ServerUi/datafile/IBP/value_data.txt");
    loadTxtValue(g_co2Values,"../ServerUi/datafile/CO2/value_data.txt");
    loadTxtValue(g_narcoValues,"../ServerUi/datafile/NARCO/value_data.txt");

}
QStringList& getValueList(ClientType_ id){
    switch(id){
    case ECG_CLIENT:
        return g_ecgValues;
        break;
    case SPO2_CLIENT:
        return g_spo2Values;
        break;
    case NIBP_CLIENT:
        return g_nibpValues;
        break;
    case IBP_CLIENT:
        return g_ibpValues;
        break;
    case CO2_CLIENT:
        return g_co2Values;
        break;
    case NARCO_CLIENT:
        return g_narcoValues;
        break;
    }
    return g_ecgValues;
}

QStringList& getAlarmList(ClientType_ id){
    switch(id){
    case ECG_CLIENT:
        return g_ecgAlarms;
        break;
    case SPO2_CLIENT:
        break;
    case NIBP_CLIENT:
        break;
    case IBP_CLIENT:
        break;
    case CO2_CLIENT:
        break;
    case NARCO_CLIENT:
        break;
    }
    return g_ecgAlarms;
}

void saveTxtValue(QStringList strList){
    char* filename = "";

    if(g_ecgValues == strList)
        filename = "../ServerUi/datafile/ECG/value_data.txt";
    else if(g_ecgAlarms == strList)
        filename = "../ServerUi/datafile/ECG/alarm_data.txt";
    else if(g_spo2Values == strList)
        filename = "../ServerUi/datafile/SPO2/value_data.txt";
    else if(g_nibpValues == strList)
        filename = "../ServerUi/datafile/NIBP/value_data.txt";
    else if(g_ibpValues == strList)
        filename = "../ServerUi/datafile/IBP/value_data.txt";
    else if(g_co2Values == strList)
        filename = "../ServerUi/datafile/CO2/value_data.txt";
    else if(g_narcoValues == strList)
        filename = "../ServerUi/datafile/NARCO/value_data.txt";


    File file;
    file.setFileName(filename);
    if(!file.open("w")) return;

    cout<<"strList.size="<<strList.size()<<endl;
    QString str;
    for(QStringList::iterator iter=strList.begin();iter != strList.end();++iter){
        str = *iter;
        file.writeLine(str.toStdString().c_str());
    }
    file.flush();
    file.close();
}
void loadTxtValue(QStringList& strList,const char* filename){
    File file;
    file.setFileName(filename);
    if(!file.open("r")) return;

    char buf[1024];
    int ret=-1;
    while( (ret = file.readLine(buf,sizeof(buf),'.')) != -1){
        cout<<"yxy buf="<<buf<<endl;
        if(!ret)//read a line success
            strList.append(buf);
        memset(buf,0,sizeof(buf));
    }
    file.close();
}

#endif // GLOBAL_H
