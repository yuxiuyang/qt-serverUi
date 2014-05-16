#ifndef STATE_H
#define STATE_H
#include "../include/define.h"
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
