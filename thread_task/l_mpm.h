/*-----------------------------------------------------------------------*\
	file:		l_mpm.h
	module:		memory pool manager
	descript:	�ڴ�ع��������ṩ���٣�����Ƭ���ڴ�������(ֻ������Linux����)
				���ļ�Ϊ�û�����Ҫ������ͷ�ļ�
	by:			Rick Wang
	date:		2002/3
\*-----------------------------------------------------------------------*/
#ifndef L_MPM_H_91491E4D_15D7_4887_BE65_8323308447CC
#define L_MPM_H_91491E4D_15D7_4887_BE65_8323308447CC

#include "rkTypes.h"

//�쳣���붨��
#define ERR_POOL_DAMAGED					0x1010u
#define ERR_NOT_ENOUGH_MEMORY				0x1011u

/*
	�ڴ�ؽӿ���: CMemPoolInterface
*/
class CMemPoolInterface{
private:
protected:
public:
	CMemPoolInterface();
	~CMemPoolInterface();

	/*
		�ڴ�ز���
	*/
	HANDLE CreatePool(SIZE initsize);								//�����ڴ�أ�����ָ���صĳ�ʼ��С
	HANDLE CreatePool(HANDLE hParentPool, SIZE initsize);			//����ָ���ص��ӳ�
	void EmptyPool(HANDLE hPool);									//����ڴ�أ�����ԭ����������������ڴ�
	void FreePool(HANDLE hPool);									//�ͷ��ڴ�أ�����ռ�õĽ���������ϵͳ
	void FreeAllPools();											//�ͷ������ڴ�أ���ռ�õ��ڴ潻��������ϵͳ
	void DestroyPool(HANDLE hPool);									//�����ڴ�أ�����ռ�õ��ڴ潻�����ڴ�ع�����
	void DestroyAllPools();											//���������ڴ�أ���ռ�õ��ڴ潻�����ڴ�ع�����
	void FreeAllMemory();											//���ڴ�ع����������п��е��ڴ潻��������ϵͳ
	/*
		�ڴ����
	*/
	PVOID Alloc(HANDLE hPool, SIZE size);							//��ָ���ڴ�������ڴ�
	PVOID AllocInit(HANDLE hPool,SIZE size, UCHAR ucInitVal=0);		//��ָ���ڴ�������ڴ沢��ʼ��ÿ���ֽ�Ϊָ����ֵ
	void Free(HANDLE hPool, PVOID pv);								//����������ڴ棨ע�⣬�ڸû��յ�ָ��֮��������ڴ�Ҳ��һ�������գ�
	SIZE GetFreeMemSizeInPoolManeger();						
	SIZE GetTotalMemSizeInPoolManeger();
};

//���ߺ���
extern DWORD GrainAlign(SIZE size);									//����ָ���ĳߴ��Բ��Ϊ���ٸ���������
extern DWORD PageAlign(SIZE size);									//����ָ���ĳߴ��Բ��Ϊ���ٸ��ڴ�ҳ

#endif //#ifndef L_MPM_H_91491E4D_15D7_4887_BE65_8323308447CC
