/***
	file:	ak_types.h
	by:		rick
	date:	2002/12
	discription:
		���Ͷ���ͷ�ļ�
***/

#ifndef AK_TYPES_H_2002_12_05
#define AK_TYPES_H_2002_12_05

#ifndef WIN32
#include <sys/types.h>
#include <errno.h>

typedef unsigned long			DWORD;	//˫����(32λ�޷���)
typedef unsigned char			BYTE;	//�ֽ���
typedef unsigned short			WORD;	//������
typedef float					FLOAT;	//������
typedef unsigned int			UINT;	//�޷�������
typedef UINT					WPARAM;	//W����
typedef DWORD					LPARAM;	//L����


typedef long					LONG;	//�з��ų�����
typedef long*					PLONG;	//�з��ų�����ָ��
typedef unsigned long			ULONG;	//�޷��ų�����
typedef ULONG*					PULONG;	//�޷��ų�����ָ��
typedef unsigned short			USHORT;	//�޷��Ŷ�����
typedef USHORT*					PUSHORT;	//�޷��Ŷ�����ָ��
typedef unsigned char			UCHAR;	//�޷����ַ���
typedef UCHAR*					PUCHAR;	//�޷����ַ���ָ��
typedef char*					PSZ;		//�ַ���ָ��

#endif //WIN32

/*
	���µ����ֳ����������ڱ�ʾ�������������ַ�������
	AK_SIZE�ͱ�����ʾ�������ֽ�����,��һ����������ʵ�ʴ�С
	AK_LEN�ͱ�����ʾһ���ַ����ĳ���,�������ַ�����β��NULL�ַ�(����ֵ+1���Ǹ��ַ���ռ�õĻ���������)
*/
typedef UINT					AK_SIZE;	//�������ֽ�����
typedef UINT					AK_LEN;	//�ַ�������


typedef void*					HANDLE;	//���
typedef void*					PVOID;	//��ָ��

#define SUCCESS					0
#endif //AK_TYPES_H_2002_12_05



