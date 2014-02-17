// yht_test.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <stdio.h>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "EncryptServer.h"

typedef	CEncryptServer<LOGIN_KEY1, LOGIN_KEY2>	EncryptServer;

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
			WSACleanup( );
			return;
	}
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(8080);

	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));// �󶨶˿�

	listen(sockSrv,5);

	SOCKADDR_IN addrClient;// �����ϵĿͻ���ip��ַ
	int len=sizeof(SOCKADDR);
	SOCKET sockConn =NULL;
	char sendBuf[50];
	//yht .����
	EncryptServer	m_cEncryptRecv;
	m_cEncryptRecv.Init();
	m_cEncryptRecv.ChangeCode(0);

	while(1)
	{
		 sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);// ���ܿͻ�������,��ȡ�ͻ��˵�ip��ַ
		 char recvBuf[2000];
		if (sockConn)
		{  int n = recv(sockConn,recvBuf,2000,0);// ���ܿͻ�����Ϣ)
			if (n)
			{
				m_cEncryptRecv.Encrypt((unsigned char *)recvBuf,n);
				printf("%s\n",recvBuf);
			}
		
		}
		//closesocket(sockConn);//�Ͽ�����
	}

}
