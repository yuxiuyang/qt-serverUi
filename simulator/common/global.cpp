#include "global.h"
Global* Global::m_instance = new Global();

Global::Global(){
    g_InitGlobalText();
}

void Global::g_InitGlobalText(){
    loadTxtValue(g_ecgValues,"./datafile/ECG/value_data.txt");
    loadTxtValue(g_ecgAlarms,"./datafile/ECG/alarm_data.txt");
    loadTxtValue(g_spo2Values,"./datafile/SPO2/value_data.txt");
    loadTxtValue(g_nibpValues,"./datafile/NIBP/value_data.txt");
    loadTxtValue(g_ibpValues,"./datafile/IBP/value_data.txt");
    loadTxtValue(g_co2Values,"./datafile/CO2/value_data.txt");
    loadTxtValue(g_narcoValues,"./datafile/NARCO/value_data.txt");

}
QStringList& Global::getValueList(ClientType_ id){
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

QStringList& Global::getAlarmList(ClientType_ id){
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

void Global::saveTxtValue(QStringList& strList){
    char* filename = "";

    if(&g_ecgValues == &strList)
        filename = "./datafile/ECG/value_data.txt";
    else if(&g_ecgAlarms == &strList)
        filename = "./datafile/ECG/alarm_data.txt";
    else if(&g_spo2Values == &strList)
        filename = "./datafile/SPO2/value_data.txt";
    else if(&g_nibpValues == &strList)
        filename = "./datafile/NIBP/value_data.txt";
    else if(&g_ibpValues == &strList)
        filename = "./datafile/IBP/value_data.txt";
    else if(&g_co2Values == &strList)
        filename = "./datafile/CO2/value_data.txt";
    else if(&g_narcoValues == &strList)
        filename = "./datafile/NARCO/value_data.txt";


    File file;
    file.setFileName(filename);
    if(!file.open("w")) return;

    cout<<"strList.size="<<strList.size()<< "filename="<<filename<<endl;
    QString str;
    for(QStringList::iterator iter=strList.begin();iter != strList.end();++iter){
        str = *iter;
        cout<<"write  str="<<str.toStdString().c_str();
        file.writeLine(str.toStdString().c_str());
    }
    file.flush();
    file.close();
}
void Global::loadTxtValue(QStringList& strList,const char* filename){
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
