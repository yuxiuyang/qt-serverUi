/*****************************************************************************\
	module:	
	file:	rkthread.h
	by:		Rick Wang
	date:	2002/03
	description:
		����ļ�rkthread.cpp���������ļ����������ʽ��װ��Linux��pthread�߳�
		��Ĳ��ֹ��ܡ�Ŀǰ�������У�

	1.������
	2.ͬ���¼���
	3.�߳���ʱ����
	-----------------------------------------------------------------------
	modification records:
	1.	by: ?			date: ?
		description: ?
	2.
\*****************************************************************************/
#ifndef RKTHREAD_H_A9B49AA5_3E20_47e3_8142_E8CA6F3F7A0B
#define RKTHREAD_H_A9B49AA5_3E20_47e3_8142_E8CA6F3F7A0B

#include <pthread.h>
#include "rkTypes.h"

class CEvent;
class CDelayer;

/*
	�̻߳�����
*/
class CMutex{
protected:
	pthread_mutex_t				m_lock;			//������
	pthread_t					m_InsideThread;	//��ǰ���ٽ����е��߳�ID
	UINT						m_uLockCount;	//һ���̵߳��������ô������Ӷ�ȷ������Ľ������ô�����
	
	pthread_mutex_t* GetMutexPtr(){return &m_lock;}

public:
	CMutex();
	~CMutex();

	int Lock();									//����
	int TryLock();								//��������
	int UnLock();								//����
	
	friend class CEvent;
	friend class CDelayer;
};//end of class CMutex

/*
	�߳�ͬ���¼���(��������������)
*/
class CEvent{
protected:
	pthread_cond_t				m_cond;
	pthread_t					m_MutexInsideThread;
	UINT						m_uMutexLockCount;

	CMutex						m_lock;
public:
	CEvent();
	~CEvent();

	/*��¶CMutex�Ľӿ�*/
	int Lock();									//����
	int TryLock();								//��������
	int UnLock();								//����

	int Wait();									//�ȴ�
	int TimeWait(long lSec, long lNSec);		//��ʱ�ȴ�������ʱ�䣬lSec:��, lNSec:���룩

	int SetEvent();
};//end of class CEvent

class CDelayer:public CEvent{
protected:
public:
	CDelayer();
	~CDelayer();
	
	void Delay(ulong ms);						//���̵߳ȴ���Գ��ȵ�ʱ�䣨���룩
};

#endif //#ifndef RKTHREAD_H_A9B49AA5_3E20_47e3_8142_E8CA6F3F7A0B
