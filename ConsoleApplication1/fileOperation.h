#ifndef __FILEOP_H_
#define __FILEOP_H_
#include "tcpSocket.h"

/***�ͻ���***/
//��ȡ�ļ�
bool readFile(const char* fileName);
//���ļ�
bool sendFile(SOCKET s, const char* fileName);
/**�����***/
//�����ļ�
bool recvFile(SOCKET s, const char* fileName);
//�����ļ���д��
bool saveFile(const char* fileName);
#endif // ! __FILEOP_H_
