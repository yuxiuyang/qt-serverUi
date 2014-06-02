#ifndef QUEUE_H
#define QUEUE_H
#include "../include/define.h"

//Unidirectional  Cycle list
class Queue
{
public:
    Queue(int size);
    ~Queue();

    int push(const BYTE* data,int len);
    int getDatas(BYTE* data,int len);
    int getunReadCount();//get the data of unreading datas size.
private:
    BYTE* m_dataBuf;
    int m_readPos;
    int m_writePos;
    int m_maxSize;

    UNIT m_readSum;//used to control the Balance between read an write
    UNIT m_writeSum;
};

#endif // QUEUE_H
