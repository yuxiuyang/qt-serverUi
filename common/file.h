#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <fstream>
#include <string.h>
using namespace std;
#include <unistd.h>
#define BUF_LEN 1024
class File
{
public:
    File();
    virtual ~File();

public:
    int write(const char*,...);//external interface
    int read(char *buffer,int size);
    void setFileName(const char* name);
    bool open(const char* type);
    bool close();
    long getFileSize();
    int flush();//the cache is written to file
    void clear();//clear all data in the file
    void reset(){
        m_readCurPos = 0;
    }

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


private:
    char m_strFileName[256];//path+ filename
    FILE *m_pFile;
    char m_strBuf[BUF_LEN];//just a buffer

    long m_fileSize;//file's size
    long m_readCurPos;//reading currend position in file
    bool m_isRepeatReadFile;//is need to repeat the file.
};

#endif // FILE_H
