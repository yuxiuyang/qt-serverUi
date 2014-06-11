#include "global.h"
#include <sys/stat.h>
#include <sys/types.h>
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



    loadTxtValue(g_globalPath[ECG_CLIENT],"./datafile/ECG/global_path.txt");
    loadTxtValue(g_globalPath[SPO2_CLIENT],"./datafile/SPO2/global_path.txt");
    loadTxtValue(g_globalPath[CO2_CLIENT],"./datafile/CO2/global_path.txt");
    loadTxtValue(g_globalPath[NARCO_CLIENT],"./datafile/NARCO/global_path.txt");

}
QStringList& Global::getGlobalPathList(ClientType_ id){
    return g_globalPath[id];
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
    char* filename = NULL;

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
    else if(&g_globalPath[ECG_CLIENT] == &strList)
        filename = "./datafile/ECG/global_path.txt";
    else if(&g_globalPath[SPO2_CLIENT] == &strList)
        filename = "./datafile/SPO2/global_path.txt";
    else if(&g_globalPath[CO2_CLIENT] == &strList)
        filename = "./datafile/CO2/global_path.txt";
    else if(&g_globalPath[NARCO_CLIENT] == &strList)
        filename = "./datafile/NARCO/global_path.txt";

    if(!filename){
        cout<<"maybe a error strlist"<<endl;
        return;
    }

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
        //cout<<"yxy buf="<<buf<<endl;
        if(ret>0)//read a line success
            strList.append(buf);
        memset(buf,0,sizeof(buf));
    }
    file.close();
}

void Global::saveFreAndCount(ClientType_ id,int fre,int count){
    FRE_READCOUNT data;
    data.fre = fre;
    data.readcount = count;

    char buf[1024]={0};
    switch(id){
    case ECG_CLIENT:
        sprintf(buf,"./datafile/ECG/%s/fre_count.txt",g_curGlobalPathName[ECG_CLIENT].c_str());
        break;
    case SPO2_CLIENT:
        sprintf(buf,"./datafile/SPO2/%s/fre_count.txt",g_curGlobalPathName[SPO2_CLIENT].c_str());
        break;
    case CO2_CLIENT:
        sprintf(buf,"./datafile/CO2/%s/fre_count.txt",g_curGlobalPathName[CO2_CLIENT].c_str());
        break;
    case NARCO_CLIENT:
        sprintf(buf,"./datafile/NARCO/%s/fre_count.txt",g_curGlobalPathName[NARCO_CLIENT].c_str());
        break;
    default:
        break;
    }


    FILE* file = fopen(buf, "w");
    if(!file){
        cout<<"open file="<<buf<<"  failue"<<endl;
        return;
    }
    fwrite(&data, 1,sizeof(data), file);
    fclose(file);

}

void Global::getFreAndCount(ClientType_ id,FRE_READCOUNT& data){
    data.fre = 0;
    data.readcount = 0;
    char buf[1024]={0};
    switch(id){
    case ECG_CLIENT:
        sprintf(buf,"./datafile/ECG/%s/fre_count.txt",g_curGlobalPathName[ECG_CLIENT].c_str());
        break;
    case SPO2_CLIENT:
        sprintf(buf,"./datafile/SPO2/%s/fre_count.txt",g_curGlobalPathName[SPO2_CLIENT].c_str());
        break;
    case CO2_CLIENT:
        sprintf(buf,"./datafile/CO2/%s/fre_count.txt",g_curGlobalPathName[CO2_CLIENT].c_str());
        break;
    case NARCO_CLIENT:
        sprintf(buf,"./datafile/NARCO/%s/fre_count.txt",g_curGlobalPathName[NARCO_CLIENT].c_str());
        break;
    default:
        break;
    }
    FILE* file = fopen(buf, "r");
    if(!file){
        cout<<"open file="<<buf<<"  failue"<<endl;
        return;
    }
    fread(&data,1,sizeof(data),file);
    fclose(file);

}
void Global::create_Folder(const char* strPathName) {
        if (access(strPathName, 0) == 0) //存在
                return;

        //不存在，创建
        if (mkdir(strPathName, 0) == 0) {
                printf("Create directory Success\n");
        } else {
                printf("Problem creating directory\n");
        }
}
