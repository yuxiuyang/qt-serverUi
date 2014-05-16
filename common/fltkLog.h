/*
 * fltkLog.h
 *
 *  Created on: Oct 11, 2011
 *      Author: root
 */

#ifndef FLTKLOG_H_
#define FLTKLOG_H_

#include <sys/stat.h>
#include <assert.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
using namespace std;
#include <fstream>
using namespace std;
enum
{
	WRITE_FLASH,//写入到FLASH文件中“/logdir/core”,这样可以导入到 u盘
	WRITE_TXT,//写入到一般的文本中
};
enum
{
	MANNAL,//手动换行
	AUTO,//自动换行
	MANNAL_50,//当手动时,50个数据自动换行
	MANNAL_25,//当手动时,25个数据自动换行

};
class fltkLog {
public:
	fltkLog(const char* pathName = "log",const short WriteType=WRITE_TXT);
	virtual ~fltkLog();

public:
    void Write(const char* msg);
    void Write(const int d);
    void Write(const char* msg,const int d);
    void Write(const char* msg,const char* s);
    void Write(const char* msg,const int d1,const int d2);
    void Write(const char* msg,const int d,const char* s);
    void Write(const char* msg,const char* s,const int d);
    void Write(const char* msg,const char* s1,const char* s2);
    void Write(const char* msg,const int d1,const int d2,const int d3);
    void Write(const char* msg,const int d1,const int d2,const char* s);
    void Write(const char* msg,const int d1,const char* s,const int d2);
    void Write(const char* msg,const char* s,const int d1,const int d2);
    void Write(const char* msg,const char* s1,const char* s2,const char* s3);
    void Write(const char* msg,const char* s1,const char* s2,const int d);
    void Write(const char* msg,const char* s1,const int d,const char* s2);
    void Write(const char* msg,const int d,const char* s1,const char* s2);
    void Write(const char* msg,const int d1,const int d2,int d3,const int d4);
    void Write(const char* msg,const int d1,const int d2,const int d3,const char* s);
    void Write(const char* msg,const int d1,const int d2,const char* s,const int d3);
    void Write(const char* msg,const int d1,const char* s,const int d2,const int d3);
    void Write(const char* msg,const char* s,const int d1,const int d2,const int d3);
    void Write(const char* msg,const int d1,int d2,const char* s1,const char* s2);
    void Write(const char* msg,const int d1,const char* s1,const int d2,const char* s2);
    void Write(const char* msg,const int d1,const char* s1,const char* s2,const int d2);
    void Write(const char* msg,const char* s1,const char* s2,int d1,const int d2);
    void Write(const char* msg,const char* s1,int d1,const char* s2,const int d2);
    void Write(const char* msg,const char* s1,int d1,const int d2,const char* s2);
    void Write(const char* msg,const int d1,const char* s1,const char* s2,const char* s3);
    void Write(const char* msg,const char* s1,const int d,const char* s2,const char* s3);
    void Write(const char* msg,const char* s1,const char* s2,const int d,const char* s3);
    void Write(const char* msg,const char* s1,const char* s2,const char* s3,const int d);
    void Write(const char* msg,const char* s1,const char* s2,const char* s3,const char* s4);

    void Write(const char* msg,const int d1,const int d2,int d3,const int d4,const int d5);
    char* Read();
    void  ReadMemory();//读出内存信息
public:
	void SetPathName(const char* strPathName);
	void SetWriteType(const short iWriteType);
	void SetState(bool bWrite){m_bWrite = bWrite;}
	bool GetState(){return m_bWrite;}

	void SetEnter(char bEnter=AUTO){
		m_iEnter = bEnter;
		if(m_iEnter == MANNAL_50)
			m_iEnterCount = 50;
		else if(m_iEnter == MANNAL_25)
		    m_iEnterCount = 25;
	}
	void SetEnterCount(int iEnterCount=25){m_iEnterCount = iEnterCount;}

	long int GetMaxLines(){return m_MaxLines;}
	long int GetCurLines(){return m_CurrentLines;}
	//void SetMaxLines(long int maxLines){m_MaxLines = maxLines;}
	void ClearOldData();//清空 前面的老数据
private:
	void Create_Folder(const char* strPathName);
	/*
		  返回值列表：
		-1 文件结束；
		0 读取一行成功；
		1 首字符等于ellipsis值。
		 *
		 */
	int  ReadLine(FILE   *fPtr,char   *strPtr,int   strlen,char   ellipsis);//读出一行
private:
	char m_strPathName[256];
	bool m_bWrite;//是否写入日志，true写入日志
	char m_iEnter;//是否换行

	short m_WriteType;//写入类型，是写入普通日志，还是写入 FLASH中


	int m_iCount;//当不换行时，所接收的数据量
	int m_iEnterCount;//换行基数

	long int m_MaxLines;//当达到保存记录超过最大行数，则全部清空
	long int m_CurrentLines;//当前 保存记录的行数
	//临时缓冲区
	char* m_buf;
	char* m_str;
};

class fltkLog_Ex
{
public:
	fltkLog_Ex(const char* pathName = "log");
	virtual ~fltkLog_Ex();
	void write(const char*,...);//外部接口
	void SetPath(const char* strPath);
	void start(int iMode=AUTO);
	void end();

	void Create_Folder(const char* strPathName);
		/*
			  返回值列表：
			-1 文件结束；
			0 读取一行成功；
			1 首字符等于ellipsis值。
			 *
			 */
	int  ReadLine(FILE   *fPtr,char   *strPtr,int   strlen,char   ellipsis);//读出一行

private:
	char *m_strData;//数据缓冲区
	char *m_strBuf;//临时缓冲区
	char m_strPath[256];//文件路径
	char m_strFileName[100];//文件名
	char m_strFilePathName[400];//路径＋文件名
	char m_strCurDate[30];//当前日期
	int  m_iCount_Line;//当选择MANNAL_25,MANNAL_50时，一行 数据的个数

	long int m_MaxLines;//当达到保存记录超过最大行数，则全部清空
	long int m_CurrentLines;//当前 保存记录的行数

	int m_iMode;//手动还是自动模式
	void Init();//初始化
	void Refresh();//刷新日期，文本名称
	void MySprintf(char* buf,const char* msg);//格式化字串msg，对msg作一些处理
	void write_file(const char* msg);//将字串msg写入到 文件
};

#endif /* FLTKLOG_H_ */
