/*
 * fltkLog.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: root
 */

#include "fltkLog.h"
#define MAX_LEN 1024
#define DEFAULT_MAX_LINES  10000000//默认  能够存储最大行数
fltkLog::fltkLog(const char* pathName, const short WriteType) {
	// TODO Auto-generated constructor stub
	strcpy(m_strPathName, pathName);
	m_bWrite = true;
	m_WriteType = WriteType;
	m_iEnter = AUTO;
	if (WRITE_TXT == m_WriteType)
		Create_Folder(m_strPathName);

	m_iCount = 0;
	m_iEnterCount = 25;

	m_MaxLines = DEFAULT_MAX_LINES;
	m_CurrentLines = 0;

	m_buf = new char[MAX_LEN];
	m_str = new char[MAX_LEN + 200];}

fltkLog::~fltkLog() {
	// TODO Auto-generated destructor stub
	delete m_buf;
	m_buf = NULL;

	delete m_str;
	m_str = NULL;
}
void fltkLog::SetPathName(const char* strPathName) {
	strcpy(m_strPathName, strPathName);
	if (WRITE_TXT == m_WriteType)
		Create_Folder(m_strPathName);
}
void fltkLog::SetWriteType(const short iWriteType) {
	m_WriteType = iWriteType;
	if (WRITE_TXT == m_WriteType)
		Create_Folder(m_strPathName);
}
void fltkLog::Write(const char* msg) {
	if (GetState() == false)
		return;
	if (m_iEnter == MANNAL_50 || m_iEnter == MANNAL_25)
		m_iCount++;
	char nowTime[30] = { 0 };
	char nowDate[30] = { 0 };

	//获取时间
	struct tm *local_time = NULL;
	time_t utc_time;
	utc_time = time(NULL);
	local_time = localtime(&utc_time);
	strftime(nowTime, 30, "%H:%M:%S", local_time);
	strftime(nowDate, 30, "%Y-%m-%d", local_time);

	char fileName[300] = { 0 };
	sprintf(fileName, "%s//%s.txt", m_strPathName, nowDate);

	FILE *fp;
	if (AUTO == m_iEnter) {
		sprintf(m_str, "%s %s\n", nowTime, msg);
		m_CurrentLines++;
	} else if (MANNAL == m_iEnter) {
		sprintf(m_str, "%s", msg);
		m_CurrentLines++;
	} else if (MANNAL_50 == m_iEnter || MANNAL_25 == m_iEnter) {
		if (m_iCount % m_iEnterCount == 0) {
			sprintf(m_str, "%s\n", msg);
			m_iCount = 0;

			m_CurrentLines++;
		} else
			sprintf(m_str, "%s", msg);
	}

	if (WRITE_FLASH == m_WriteType) //写入到FLASH中
			{
		if (m_CurrentLines > m_MaxLines) {
			fp = fopen(m_strPathName, "w");
			m_CurrentLines = 0;
		} else
			fp = fopen(m_strPathName, "a");
	} else {
		if (m_CurrentLines > m_MaxLines) {
			fp = fopen(fileName, "w");
			m_CurrentLines = 0;
		} else
			fp = fopen(fileName, "a");
	}

	if (fp == NULL)
		return;

	fwrite(m_str, strlen(m_str), 1, fp);
	fclose(fp);
}

void fltkLog::Write(const int d) {
	if (GetState() == false)
		return;
	char buf[20] = { 0 };
	sprintf(buf, "%d ", d);
	Write(buf);
}
void fltkLog::Write(const char* msg, const int d) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s);
	Write(m_buf);
}

void fltkLog::Write(const char* msg, const int d1, const int d2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d, const char* s) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d, s);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s, const int d) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s, d);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const char* s2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, s2);
	Write(m_buf);
}

void fltkLog::Write(const char* msg, const int d1, const int d2, const int d3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2, d3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const int d2,
		const char* s) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2, s);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const char* s,
		const int d2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, s, d2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s, int d1, int d2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s, d1, d2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const char* s2,
		const char* s3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, s2, s3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const char* s2,
		const int d) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, s2, d);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const int d,
		const char* s2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, d, s2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d, const char* s1,
		const char* s2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d, s1, s2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const int d2, const int d3,
		const int d4) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2, d3, d4);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const int d2, const int d3,
		const char* s) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2, d3, s);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const int d2, const char* s,
		const int d3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2, s, d3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const char* s, const int d2,
		const int d3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, s, d2, d3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s, const int d1, const int d2,
		const int d3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s, d1, d2, d3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const int d2, const char* s1,
		const char* s2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2, s1, s2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const char* s1, const int d2,
		const char* s2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, s1, d2, s2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const char* s1,
		const char* s2, const int d2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, s1, s2, d2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const char* s2,
		const int d1, const int d2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, s2, d1, d2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const int d1,
		const char* s2, const int d2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, d1, s2, d2);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const int d1, const int d2,
		const char* s2) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, d1, d2, s2);
	Write(m_buf);
}

void fltkLog::Write(const char* msg, const int d1, const char* s1,
		const char* s2, const char* s3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, s1, s2, s3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const int d,
		const char* s2, const char* s3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, d, s2, s3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const char* s2,
		const int d, const char* s3) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, s2, d, s3);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const char* s2,
		const char* s3, const int d) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, s2, s3, d);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const char* s1, const char* s2,
		const char* s3, const char* s4) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, s1, s2, s3, s4);
	Write(m_buf);
}
void fltkLog::Write(const char* msg, const int d1, const int d2, int d3,
		const int d4, const int d5) {
	if (GetState() == false)
		return;

	memset(m_buf, 0, MAX_LEN);
	sprintf(m_buf, msg, d1, d2, d3, d4, d5);
	Write(m_buf);
}
char* fltkLog::Read() {
	return NULL;
}
void fltkLog::ReadMemory() {
	FILE *fp;
	fp = fopen("/proc/meminfo", "r");
	if (fp == NULL
	)
		return;

	char buf[3][200];
	int i = 0;
	while (ReadLine(fp, buf[i], 200, '.') != -1) {
		if (i > 3)
			break;
		printf("%s\n", buf[i]);
		i++;
	}
	fclose(fp);
}

void fltkLog::Create_Folder(const char* strPathName) {
	if (access(strPathName, 0) == 0) //存在
		return;

	//不存在，创建
	if (mkdir(strPathName, 0) == 0) {
		printf("Create directory Success\n");
	} else {
		printf("Problem creating directory\n");
	}
}

/*
 返回值列表：
 -1 文件结束；
 0 读取一行成功；
 1 首字符等于ellipsis值。
 *
 */
int fltkLog::ReadLine(FILE *fPtr, char *strPtr, int strlen, char ellipsis) {
	/*   文件指针，存储读取数据的字符串数组，字符串数组长度，当一行数据以ellipsis值开头时废弃该行，注：ellipsis值为“.”时，直接输出所有行   */
	int ch;
	char *tmpPtr;

	memset(strPtr, 0x0, strlen);
	ch = 0x0;
	tmpPtr = strPtr;

	if (feof(fPtr))/*如果文件结束，返回错误代码   -1   */
		return -1;

	while (!feof(fPtr) && ch != 0xa) { /*   读入一行数据   */
		ch = fgetc(fPtr);
		if (ch != EOF && ch != '\n ') {
			 *strPtr = ch;
			 strPtr++;
		}
	}
	if (*tmpPtr == ellipsis || *tmpPtr == '\0 ' || *tmpPtr == '\n ')/*   如果行首字符等于ellipsis，返回错误代码   1   */
		return 1;
	else
		return 0;
}
void fltkLog::ClearOldData() //清空 前面的老数据
{
	int Lines = m_MaxLines / 2;
	if (Lines == 0)
		Lines = 1;
	else if (Lines > 500)
		Lines = 500;

	FILE *fp;
	fp = fopen("/proc/meminfo", "r");
	if (fp == NULL
	)
		return;
}

//fltkLog_Ex  使用变参
#include <stdarg.h>
fltkLog_Ex::fltkLog_Ex(const char* pathName){
	strcpy(m_strPath,pathName);
	Init();
}
fltkLog_Ex::~fltkLog_Ex(){
	if(m_strData){
		delete m_strData;
		m_strData = NULL;
	}
	if(m_strBuf){
		delete m_strBuf;
		m_strBuf = NULL;
	}
}
void fltkLog_Ex::MySprintf(char* buf,const char* msg){
	if(buf == NULL) return;

	switch(m_iMode)
	{
	case MANNAL:
		snprintf(buf,MAX_LEN,"%s",msg);
		//m_CurrentLines++;  //手动模式下，暂不支持
		break;
	case AUTO:
		snprintf(buf,MAX_LEN,"%s %s\n",m_strCurDate,msg);
		m_CurrentLines++;
		break;
	case MANNAL_50:
		if(m_iCount_Line==50-1){
			m_iCount_Line = 0;
			snprintf(buf,MAX_LEN,"%s\n",msg);
			m_CurrentLines++;
		}else{
			snprintf(buf,MAX_LEN,"%s",msg);
			m_iCount_Line++;
		}

		break;
	case MANNAL_25:
		if (m_iCount_Line == 25-1) {
			m_iCount_Line = 0;
			snprintf(buf, MAX_LEN, "%s\n", msg);
			m_CurrentLines++;
		} else {
			snprintf(buf, MAX_LEN, "%s", msg);
			m_iCount_Line++;
		}

		break;
	default:
		break;
	}
	//printf(buf);
}
void fltkLog_Ex::SetPath(const char* strPath){
	strncpy(m_strPath,strPath,256);
	Refresh();//刷新
}
void fltkLog_Ex::write_file(const char* msg){
	FILE* pFile=NULL;
	if(m_CurrentLines>=m_MaxLines)
	{
		m_CurrentLines = 0;
		pFile = fopen(m_strFilePathName,"w");//删除老数据
	}
	else pFile = fopen(m_strFilePathName,"a");
	if(pFile == NULL){
		printf("open file failue!!!\n");
		return;
	}


	printf(msg);
	fwrite(msg, strlen(msg), 1, pFile);
	fclose(pFile);
}
void fltkLog_Ex::write(const char*msg, ...)
{
	va_list ap;
	int arg;
	va_start(ap, msg);
	memset(m_strBuf,0,MAX_LEN);
	memset(m_strData,0,MAX_LEN);
	int len = vsnprintf(m_strBuf,MAX_LEN,msg,ap);//其返回值是 拷贝字串的字节数
	if(len<0)
	{
		printf("can't format msg to bufTmp\n");
		va_end(ap);
		return;
	}
	va_end(ap);

	MySprintf(m_strData,m_strBuf);//将数据m_strBuf 拷贝到m_strData，并作一些处理

	write_file(m_strData);
	return;
}

void fltkLog_Ex::Init(){
	Refresh();
	m_strData = new char[MAX_LEN];
	m_strBuf  = new char[MAX_LEN];
	memset(m_strBuf,0,MAX_LEN);
	memset(m_strData,0,MAX_LEN);

	m_iMode = AUTO;
	m_iCount_Line = 0;
	m_MaxLines = DEFAULT_MAX_LINES;
	m_CurrentLines = 0;
}
void fltkLog_Ex::Refresh(){//刷新，文本名称
	char nowDate[30] = { 0 };

	//获取时间
	struct tm *local_time = NULL;
	time_t utc_time;
	utc_time = time(NULL);
	local_time = localtime(&utc_time);
	//strftime(nowTime, 30, "%H:%M:%S", local_time);
	strftime(nowDate, 30, "%Y-%m-%d", local_time);

	strncpy(m_strCurDate, nowDate, 30);
	snprintf(m_strFileName,100,"%s.txt", m_strCurDate);

	Create_Folder(m_strPath);//创建文件夹路径
	snprintf(m_strFilePathName,400,"%s//%s",m_strPath,m_strFileName);
	return;
}
void fltkLog_Ex::start(int iMode){
	m_iMode = iMode;
	if(m_iCount_Line!=0)//换一行
	{
		m_iCount_Line = 0;
		write_file("\n");
	}

	if(iMode == MANNAL_50)
		write_file("\n-----------------------------------------------------------start  MANNAL_50---------------------------------------------\n");
	else if(iMode == MANNAL_25)
		write_file("\n--------------------------------start  MANNAL_25------------------------------------\n");
	else return;
}
void fltkLog_Ex::end(){
	if(m_iMode == AUTO || m_iMode == MANNAL)
		return;

	write_file("\n---------------------------------------------end-----------------------------------------------\n");
}
void fltkLog_Ex::Create_Folder(const char* strPathName) {
	if (access(strPathName, 0) == 0) //存在
		return;

	//不存在，创建
	if (mkdir(strPathName, 0) == 0) {
		printf("Create directory Success\n");
	} else {
		printf("Problem creating directory\n");
	}
}

/*
 返回值列表：
 -1 文件结束；
 0 读取一行成功；
 1 首字符等于ellipsis值。
 *
 */
int fltkLog_Ex::ReadLine(FILE *fPtr, char *strPtr, int strlen, char ellipsis) {
	/*   文件指针，存储读取数据的字符串数组，字符串数组长度，当一行数据以ellipsis值开头时废弃该行，注：ellipsis值为“.”时，直接输出所有行   */
	int ch;
	char *tmpPtr;

	memset(strPtr, 0x0, strlen);
	ch = 0x0;
	tmpPtr = strPtr;

	if (feof(fPtr))/*如果文件结束，返回错误代码   -1   */
		return -1;

	while (!feof(fPtr) && ch != 0xa) { /*   读入一行数据   */
		ch = fgetc(fPtr);
		if (ch != EOF && ch != '\n ') {
			*strPtr = ch;
			strPtr++;
		}
	}
	if (*tmpPtr == ellipsis || *tmpPtr == '\0 ' || *tmpPtr == '\n ')/*   如果行首字符等于ellipsis，返回错误代码   1   */
		return 1;
	else
		return 0;

}
