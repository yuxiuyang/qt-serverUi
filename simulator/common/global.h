#ifndef GLOBAL_H
#define GLOBAL_H
#include "QStringList"
#include "file.h"
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

};

#endif // GLOBAL_H
