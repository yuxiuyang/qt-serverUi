#ifndef GLOBAL_H
#define GLOBAL_H
#include "QStringList"

QStringList g_ecgValues;
QStringList g_ecgAlarms;
QStringList g_spo2Values;
QStringList g_nibpValues;
QStringList g_ibpValues;
QStringList g_co2Values;
QStringList g_narcoValues;

void g_InitGlobalText(){
    g_ecgValues.append("60");
    g_ecgValues.append("80");
    g_ecgValues.append("120");
    g_ecgValues.append("140");
    g_ecgValues.append("160");
    g_ecgValues.append("240");
    g_ecgValues.append("290");
    g_ecgValues.append("300");
    g_ecgValues.append("320");
    g_ecgValues.append("350");

    g_ecgAlarms.append("NORMAL");
    g_ecgAlarms.append("VPC_TRIGEMINY");
    g_ecgAlarms.append("VPC_BIGEMINY");
    g_ecgAlarms.append("VPC_VT");
    g_ecgAlarms.append("VPC_VEB_PAIR");
    g_ecgAlarms.append("VPC_R_ON_T");
    g_ecgAlarms.append("VPC_VEB");
    g_ecgAlarms.append("VPC_TACHYCARDIA");
    g_ecgAlarms.append("VPC_BRADYCARDIA");
    g_ecgAlarms.append("VPC_MISSEDBEATS");
    g_ecgAlarms.append("VPC_VFID");
    g_ecgAlarms.append("VPC_ARRHYTHMIA");
    g_ecgAlarms.append("VPC_NOVPC");
    g_ecgAlarms.append("VPC_UNKNOWN");
    g_ecgAlarms.append("VPC_ST");
    g_ecgAlarms.append("VPC_VT_OVER_2");


    g_spo2Values.append("90");
    g_spo2Values.append("100");

    g_nibpValues.append("120/80 (50)");
    g_nibpValues.append("150/40 (80)");


    g_ibpValues.append("120/80 (50)");
    g_ibpValues.append("150/40 (80)");

    g_co2Values.append("30");
    g_co2Values.append("50");

    g_narcoValues.append("27");
    g_narcoValues.append("40");

}

#endif // GLOBAL_H
