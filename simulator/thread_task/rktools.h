/*================================================================
	file:	rktools.h
	by:		Rick Wang
	date:	2002/4
	discription:
		���ļ�������һЩ��LINUX��ʹ�õĹ���
================================================================*/
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

class CHighClock{
private:
	struct timeval m_tstart;
	struct timeval m_tend;
	struct timezone m_tz;
public:
	CHighClock(){
		Start();
	}
	~CHighClock(){
	}

	//��ʼ��ʱ
	void Start(){
		gettimeofday(&m_tstart,&tz);
	}

	//ֹͣ��ʱ
	void Stop(){
		gettimeofday(&m_tend,&tz);
	}

	//��ȡ����ʱ��
	double getval(){
		double t1,t2;
		t1=(double)m_tstart.tv_sec+(double)m_tstart.tv_usec/(1000*1000);
		t2=(double)m_tend.tv_sec+(double)m_tend.tv_usec/(1000*1000);
		return t2-t1;
	}

	void printval(){
		printf("High-Clock: run time = %.6f sec.\n", getval());
	}
};
