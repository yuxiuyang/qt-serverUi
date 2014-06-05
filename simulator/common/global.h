#ifndef GLOBAL_H
#define GLOBAL_H
#include "QStringList"
#include "file.h"
struct FRE_READCOUNT{
    int fre;
    int readcount;
};

class Global{
public:
    Global();
    static Global* getInstance(){
        return m_instance;
    }

    QStringList g_ecgValues;
    QStringList g_ecgAlarms;
    QStringList g_spo2Values;
    QStringList g_nibpValues;
    QStringList g_ibpValues;
    QStringList g_co2Values;
    QStringList g_narcoValues;

    static Global* m_instance;
    void g_InitGlobalText();
    QStringList& getValueList(ClientType_ id);
    QStringList& getAlarmList(ClientType_ id);
    void saveTxtValue(QStringList& strList);
    void loadTxtValue(QStringList& strList,const char* filename);





    QStringList g_globalPath[CLIENT_NUM];
    string g_curGlobalPathName[CLIENT_NUM];

    string getGlobalPath(ClientType_ id){
        return g_curGlobalPathName[id];
    }
    void setGlobalPath(ClientType_ id,char* path){
        g_curGlobalPathName[id] = path;
    }

    QStringList& getGlobalPathList(ClientType_ id);


    void saveFreAndCount(ClientType_ id,int fre,int count);
    void getFreAndCount(ClientType_ id,FRE_READCOUNT& data);

    static void create_Folder(const char* strPathName);
};

#endif // GLOBAL_H
