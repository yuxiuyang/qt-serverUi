#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <fstream>
#include <string.h>

#include <unistd.h>
#include <assert.h>
#include <iostream>
#include "../include/define.h"
using namespace std;
#define BUF_LEN 1024
class File
{
public:
    File();
    virtual ~File();

public:
    int write(const BYTE* buf,int len);
    int read(char *buffer,int size);
//    void resolveProtocol(const char* buf,int size,BYTE* recieveBuf,int& recieveBuf_len);
    void setFileName(const char* name);
    bool isOpen(){
        return m_pFile==NULL?false:true;
    }
    void resolveProtocol(const char* buf,int size,BYTE* recieveBuf,int& recieveBuf_len);
    bool open(const char* type);
    bool close();
    long getFileSize();
    int flush();//the cache is written to file
    void clear();//clear all data in the file
    void reset(){
        m_readCurPos = 0;
    }
    bool saveDataFromStartPosToEndPos(const char* filename);

    /*
     返回值列表：
     -1 文件结束；
     0 读取一行成功；
     1 首字符等于ellipsis值。
     *
     */
    int readLine(char *strPtr, int strlen, char ellipsis);

    void setFileCurPos(long pos){
        if(m_readCurPos<=m_fileSize)
            m_readCurPos=pos;
    }
    void setReadFileProperty(bool isRepeatReadFile){
        m_isRepeatReadFile = isRepeatReadFile;
    }

    void setStartPos(long pos){
        if(pos>=0 && pos<=m_endPos)
            m_startPos = pos;
        else cout<<"set start pos failue"<<endl;
    }

    void setEndPos(long pos){
        if(pos>=m_startPos&&pos<=m_fileSize)
            m_endPos = pos;
        else cout<<"set end pos failure"<<endl;
    }

private:
    int write(const char*,...);//external interface
    char m_strFileName[256];//path+ filename
    FILE *m_pFile;
    char m_strBuf[BUF_LEN];//just a buffer

    long m_fileSize;//file's size
    long m_readCurPos;//reading currend position in file
    bool m_isRepeatReadFile;//is need to repeat the file.

    long m_startPos;
    long m_endPos;

};

#endif // FILE_H
