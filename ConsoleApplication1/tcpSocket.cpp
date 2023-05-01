#include "tcpSocket.h"
#include <stdio.h>

//��ʼ�������
bool init_Socket()
{
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		err("WSAStartup");
		return false;
	}
	return true;
}
//�ر������
bool close_Socket()
{
	if (0 != WSACleanup()) {
		err("WSACleanup");
	}
	return true;
}

SOCKET create_serverSocket()
{
	//����һ���յ�scoket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == fd) {
	
		err("scoket");
		return INVALID_SOCKET;
	}
	//��socket�󶨱���ip��ַ�Ͷ˿ں�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT); //�ѱ����ֽ���ת�������ֽ���
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr))) {
	
		err("bind")
			return INVALID_SOCKET;
	}
	//��ʼ����
	listen(fd, 10);
	return fd;
}

SOCKET create_clientSocket()
{
	//����һ���յ�scoket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == fd) {

		err("scoket");
		return INVALID_SOCKET;
	}
	//��socket�󶨷�������ip��ַ�Ͷ˿ں�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT); //�ѱ����ֽ���ת�������ֽ���
	addr.sin_addr.S_un.S_addr = htonl(1920103026); //�󶨷�����ip�������������ֽ�������

	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr))) {
		err("connect")
			return INVALID_SOCKET;
	}

	return fd;
}


