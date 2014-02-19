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

	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));// 绑定端口

	listen(sockSrv,5);

	SOCKADDR_IN addrClient;// 连接上的客户端ip地址
	int len=sizeof(SOCKADDR);
	SOCKET sockConn =NULL;
	char sendBuf[50];
	//yht .解密
	EncryptServer	m_cEncryptRecv;
	m_cEncryptRecv.Init();
	m_cEncryptRecv.ChangeCode(0);

	while(1)
	{
		 sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);// 接受客户端连接,获取客户端的ip地址
		 char recvBuf[2000];
		if (sockConn)
		{  int n = recv(sockConn,recvBuf,2000,0);// 接受客户端消息)
			if (n)
			{
				m_cEncryptRecv.Encrypt((unsigned char *)recvBuf,n);
				printf("%s\n",recvBuf);
			}
		
		}
		//closesocket(sockConn);//断开连接
	}

}
