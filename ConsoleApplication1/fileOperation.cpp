#define _CRT_SECURE_NO_WARNINGS
#include "fileOperation.h"
#include <cstdio>
#include <iostream>
using namespace std;

long g_filesize = 3145728; //��ȡ�ļ���С��Ĭ��2m��
char* g_fileBuf;  //�����ļ�����

/*�ͻ��˲���*/
bool readFile(const char* fileName)
{
	//���ļ�
	FILE* read = fopen(fileName,"rb");
	if (!read) {
		perror("file open failed: \n");
		return false;
		
	}
	//��ȡ�ļ���С
	fseek(read, 0, SEEK_END);  
	g_filesize  = ftell(read);
	fseek(read, 0, SEEK_SET);
	printf("�ļ���СΪ: %d\n", g_filesize);
	
	//�����ļ�����
	g_fileBuf = (char*)calloc(g_filesize,sizeof(char));
	if (!g_fileBuf) {
		return false;
	}
	//���ļ������ڴ�����
	fread(g_fileBuf, sizeof(char), g_filesize, read);

	fclose(read);
	return true;
}


bool sendFile(SOCKET s, const char* filePath)
{
	string::size_type pos;
	std::string fileName;
	//��ȡ�ļ��� const char*תstd::string
	pos = std::string(filePath).rfind("\\");
	//�ļ����� ret.substr(pos + 1)
	fileName = std::string(filePath).substr(pos + 1);

	//�����ļ�����
	if (send(s, (char*)fileName.data(), sizeof(fileName), 0) < 0) {
		perror("send filename error");
		exit(-1);
	}
	//���ļ�
	readFile(filePath);
	//�����ļ�
	int ret = send(s, g_fileBuf, g_filesize, 0);
	if (ret == SOCKET_ERROR) {
		err("sendFile");
		return false;
	}
	printf("�����ļ��ɹ�: %d", g_filesize);
	return true;
}


/*����˲���*/


bool saveFile(const char* fileName)
{
	//���ļ�
	FILE* write = fopen(fileName, "wb");
	if (!write) {
		perror("file open failed: \n");
		return false;

	}
	//д�ļ�
	fwrite(g_fileBuf, sizeof(char), g_filesize, write);

	fclose(write);
	return true;
}

bool recvFile(SOCKET s, const char* fileName)
{
	//�����ڴ�
	if (g_fileBuf == NULL) {
	
		g_fileBuf = (char*)calloc(g_filesize, sizeof(char));
		if (!g_fileBuf) { return false; }
	}

		
	//�����ļ�
	int ret = recv(s, g_fileBuf, g_filesize, 0);
	if (ret == 0) {

		printf("�ͻ�����������...\n");
	}
	else if (ret < 0) {

		err("recv");
	}
	//�����ļ�
	saveFile(fileName);
	return true;
}
