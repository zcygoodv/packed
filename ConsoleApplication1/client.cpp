#include <WinSock2.h>                //ͷ�ļ�
#pragma comment(lib,"ws2_32.lib")    //���ļ�
#include "tcpSocket.h"
#include "fileOperation.h"
#include <stdio.h>

void ClientSocketUpload(const char* filePath) {
	init_Socket();
	SOCKET fd = create_clientSocket();
	if (fd == INVALID_SOCKET) {
		printf("\n�ͻ������ӷ����ʧ��,ѹ���ļ������ڱ���...\n");
	}else {
		printf("\n�ͻ������ӷ���˳ɹ�...\n");
	}
	//�ͻ��˸�����˷����ļ�
	sendFile(fd, filePath);
	closesocket(fd);
	close_Socket();
}