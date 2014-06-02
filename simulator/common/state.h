#ifndef STATE_H
#define STATE_H
#include "../include/define.h"

enum SAVE_TYPE{
        SAVE_FRE,
        SAVE_READNUM,
        SAVE_FILE_START_POS,
        SAVE_FILE_END_POS,
        SAVE_TEST,
        SAVE_SHOWDATA,
        SAVE_SENDDATA,
        SAVE_DATA_VALUE,
        SAVE_ALARM_VALUE,
};
class State
{
private:
    State();
public:
    ~State();

    void setSave();
    void setDef();
    int  getStateData(STATE_SAVE id);
    void setStateData(STATE_SAVE id,int data);
    void setStateData(ClientType_ id, SAVE_TYPE saveType,int val);
    int getStateData(ClientType_ id, SAVE_TYPE saveType);
    void loadConf();
    bool isExistConf();//
    static State* getInstance(){
        return m_instance;
    }



private:
    int m_value[STATE_COUNT];

    static State* m_instance;
    char m_fileName[200];
};

#endif // STATE_H
