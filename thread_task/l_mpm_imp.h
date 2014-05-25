/*-----------------------------------------------------------------------*\
	file:		l_mpm_imp.h
	module:		memory pool manager
	descript:	�ڴ�ع��������ṩ���٣�����Ƭ���ڴ�������(ֻ������Linux����)
				���ļ�Ϊ�ڲ�ʵ�ֵ�ͷ�ļ�
	by:			Rick Wang
	date:		2002/3
\*-----------------------------------------------------------------------*/
#ifndef L_MPM_IMP_H_91491E4D_15D7_4887_BE65_8323308447CC
#define L_MPM_IMP_H_91491E4D_15D7_4887_BE65_8323308447CC
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include "l_mpm.h"
#include "rkthread.h"
#include "rkTypes.h"

#include "stdio.h"
#include "assert.h"

#ifndef NDEBUG
#define dbout(x,y) \
	do{printf(x,y);printf("\n");}while(0)
#else
#define dbout(x,y)
#endif

#define MPM_GRAINSIZE	4096							//�ڴ��������(����ʱ������ϵͳҳ���С����Բ��)

extern DWORD	g_dwDataAlign;							//��ַ�߽�
extern SIZE		g_PageSize;								//ϵͳ�ڴ�ҳ��С
extern SIZE		g_GrainSize;							//��ģ��������ȴ�С

class CMemPool;
class CMemPoolMgr;
/*
	�ڴ��ͷ
*/
class CBlkHdr{
private:
protected:
	/*
		�ڴ��ͷ��Ϣ�ṹ -----------------------------------------------------
	*/
	struct BLKHDR{
		DWORD			dwGrainCount;					//��������ķ��������
		CBlkHdr*		pNext;							//��һ��
		CBlkHdr*		pPrev;							//��һ��
		CBlkHdr*		pBigger;						//�ϴ��һ��
		PUCHAR			pNextAvail;						//��һ�����õĿ���ָ��
		PUCHAR			pEnd;							//������β�ֽ�
		UCHAR			ucData[0];						//������
	}m_blk;
	/*------------------------------------------------------------------------*/
	static DWORD		ms_TotalBlkCount;
	static SIZE		ms_TotalMemSize;
	static CMutex		ms_mtxGuard;
public:
	CBlkHdr();
	~CBlkHdr();

	bool IsAddressInBlk(PVOID pv) const;				//�ж�һ����ַ�Ƿ��ڱ��ڴ�����������						
	bool IsFit(SIZE size) const;						//�жϱ����Ƿ���Ӧ����
	DWORD GetGrainCount() const;						//��ȡ����ķ��������
	bool IsFull() const;								//�жϱ����Ƿ�����
	SIZE GetAvailSize() const;							//��ȡ������ÿ�������С
	PVOID AlignAddress(PVOID pv) const;					//��ָ��������ݶ��룬���ض����˵�ָ��ֵ

	void* operator new(SIZE size);						//����һ���¿�
	void* operator new(SIZE size, 
						SIZE initsize);					//����һ��ָ��������������¿�
	void operator delete(void* pblk);					//ɾ��һ�飬�ͷ������ڴ�

	void operator delete[](void* pv){return;};
	void* operator new[](SIZE size){return NULL;};

	CBlkHdr* GetNext() const;
	CBlkHdr* GetPrev() const;
	CBlkHdr* GetBigger() const;
	void SetNext(CBlkHdr* pNext);
	void SetPrev(CBlkHdr* pPrev);
	void SetBigger(CBlkHdr* pBigger);

	void InsertAfter(CBlkHdr* pblk_before);				//���뵽ָ����֮��
	void InsertBefore(CBlkHdr* pblk_after);				//���뵽ָ����֮ǰ
	void RemoveOut();									//�ӵ�ǰ�������Ƴ�

	PVOID Alloc(SIZE size);								//�����ڴ�
	void Free(PVOID pv);								//��������ָ��λ��֮����ڴ���Ϊ���ã������գ�
	void Empty();										//��ձ���

	static DWORD GetTotalMemBlkCount();
	static SIZE GetTotalMemSize();

	void DebugDump(){
		dbout("--! CBlkHdr dump : blk[0x%08x]----",this);
		dbout("--! dwGrainCount = %u",m_blk.dwGrainCount);
		dbout("--! pNext = 0x%08x",m_blk.pNext);
		dbout("--! pPrev = 0x%08x",m_blk.pPrev);		
		dbout("--! pBigger = 0x%08x",m_blk.pBigger);		
		dbout("--! pNextAvail = 0x%08x",m_blk.pNextAvail);		
		dbout("--! ucData = 0x%08x",m_blk.ucData);	
		dbout("--! Total blk count = %d",ms_TotalBlkCount);
		dbout("--! Total blk size = %d",ms_TotalMemSize);
		dbout("--! Dump end ---------------------------",NULL);
		assert(m_blk.pNextAvail && m_blk.dwGrainCount);
	}	
};

/*
	�ڴ�ع�����
*/
class CMemPoolMgr{
private:
protected:
	CBlkHdr*				m_pFreeBlks;				//���п���
	CBlkHdr*				m_pLastFreeBlk;				//���п������һ��

	CMemPool*				m_pTopLevelPools;			//�����ڴ����


	CMutex					m_mtxFreeBlksGuard;
	CMutex					m_mtxPoolsGuard;
	
	DWORD					m_dwFreeBlkCount;
	SIZE					m_szFreeBlkSize;
public:
	CMemPoolMgr();
	~CMemPoolMgr();

	/*
		�ڴ��������
	*/
	void FreeAllBlks();									//�����п��������е��ڴ���ͷ�
	CBlkHdr* AllocBlkFromFreeChain(DWORD dwGrainCount);	//�ӿ��п���������һ��
	void ReturnBlksToFreeChain(CBlkHdr* pblks);			//��һ����Żؿ��п���
	
	/*
		�ڴ��������
	*/
	void AddPool(CMemPool* pPool);						//��һ�������ڴ�ؼ��뵽�ڴ�����У�
														//�óصĸ���ָ�뽫���ÿ�
	void AddPool(CMemPool* pParent,CMemPool* pPool);	//��һ���ؼ��뵽�ڴ�����У�pParent��ΪNULL����óؼ��뵽
														//����������

	void RemovePool(CMemPool* pPool);					//��һ���ڴ�ش��ڴ�������Ƴ�
	CMemPool* CreatePool(CMemPool* pParent,
						SIZE initsize);					//����һ���ڴ��
	void DestroyPool(CMemPool* pPool);
	void DestroyAllPools();
	void FreePool(CMemPool* pPool);
	void FreeAllPools();
	
	DWORD GetFreeBlkCount(){return m_dwFreeBlkCount;};

	SIZE GetFreeBlkSize(){return m_szFreeBlkSize;};
};



/*
	�ڴ��
*/
class CMemPool{
private:
	CBlkHdr*		m_pBlks;							//����
	CBlkHdr*		m_pLastBlk;							//ĩ��
	
	CMemPool*		m_pNext;							//��һ���ֵܳ�
	CMemPool*		m_pPrev;							//��һ���ֵܳ�
	CMemPool*		m_pParent;							//����
	CMemPool*		m_pChild;							//�ӳ�

	CMutex			m_mtxBlksGuard;						//�����ڴ�����Ļ���������

	bool			m_bFree;

	//���ڴ��Ĳ���
	static CBlkHdr* AllocBlk(SIZE size);				//����һ��
	static void ReturnBlks(CBlkHdr* pBlks);				//�������ɿ�
	static void FreeBlks(CBlkHdr* pBlks);				//�ͷ����ɿ�

	CBlkHdr* AppendBlk(SIZE size);						//���ڴ��׷��һ��ָ����С���ڴ��
protected:

	CMemPool();
	~CMemPool();

	CMemPool* GetParent() const;
	CMemPool* GetChild() const;
	CMemPool* GetNext() const;
	CMemPool* GetPrev() const;
	void SetParent(CMemPool* pParent);
	void SetChild(CMemPool* pChild);
	void SetNext(CMemPool* pNext);
	void SetPrev(CMemPool* pPrev);

	void InsertAfter(CMemPool* pBefore);
	void InsertBefore(CMemPool* pAfter);
	void RemoveOut();

	void* operator new(SIZE size);
	void* operator new(SIZE size, 
						SIZE initsize);
	//����delete�������ȷ���������ͷ��ڴ��ʱ��������������ȷ����
	void operator delete(void* pPool);

	void* operator new[](SIZE size){return NULL;};
	void operator delete[](void* pv){return;};

	void Destroy();
	void FreePool();

	friend class CMemPoolMgr;
public:
	PVOID Alloc(SIZE size);
	PVOID Alloc(SIZE size, UCHAR ucInitVal);

	void Free(PVOID pv);
	void Empty();
};

#endif //#ifndef L_MPM_IMP_H_91491E4D_15D7_4887_BE65_8323308447CC
