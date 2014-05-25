
#ifndef RKTYPES_H_2002_03_12
#define RKTYPES_H_2002_03_12

#include <sys/types.h>
#include <errno.h>

typedef unsigned long       DWORD;	//˫����(32λ�޷���)
typedef unsigned char       BYTE;	//�ֽ���
typedef unsigned short      WORD;	//������
typedef float               FLOAT;	//������
typedef unsigned int		UINT;	//�޷�������
typedef UINT				WPARAM;	//W����
typedef DWORD				LPARAM;	//L����

/*
	���µ����ֳ����������ڱ�ʾ�������������ַ�������
	SIZE�ͱ�����ʾ�������ֽ�����,��һ����������ʵ�ʴ�С
	LEN�ͱ�����ʾһ���ַ����ĳ���,�������ַ�����β��NULL�ַ�(����ֵ+1���Ǹ��ַ���ռ�õĻ���������)
*/
typedef UINT SIZE;					//�������ֽ�����
typedef UINT LEN;					//�ַ�������


typedef void* HANDLE;				//���
typedef void* PVOID;				//��ָ��

typedef long				LONG;	//�з��ų�����
typedef long*				PLONG;	//�з��ų�����ָ��
typedef unsigned long		ULONG;	//�޷��ų�����
typedef ULONG*				PULONG;	//�޷��ų�����ָ��
typedef unsigned short		USHORT;	//�޷��Ŷ�����
typedef USHORT*				PUSHORT;//�޷��Ŷ�����ָ��
typedef unsigned char		UCHAR;	//�޷����ַ���
typedef UCHAR*				PUCHAR;	//�޷����ַ���ָ��
typedef char*				PSZ;	//�ַ���ָ��

#define SUCCESS 0

#endif// #ifndef RKTYPES_H_2002_03_12
