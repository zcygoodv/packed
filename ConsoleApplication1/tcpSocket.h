#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
#include <WinSock2.h>                //ͷ�ļ�
#pragma comment(lib,"ws2_32.lib")    //���ļ�

//�궨��
#define err(errMsg) printf("[error]%s failed,code %d line:%d",errMsg,WSAGetLastError(),__LINE__);

#define PORT 65520


//��ʼ�������
bool init_Socket();
//�ر������
bool close_Socket();
//�������� ����������socket
SOCKET create_serverSocket();
//�ͻ��ˣ������ͻ��� socket
SOCKET create_clientSocket();
#endif // !_TCPSOCKET_H_