// yht_test_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;//WSAata用来存储系统传回的关于WinSocket的资料。
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup( );
		return;
	}
	SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);// AF_INET ..tcp连接
	//初始化连接与端口号
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//本机地址，服务器在本机开启
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(8080);// 设置端口号
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//连接服务器
	int i = 0;

		char sendBuf[100];
		char recvBuf[50];
	
		   //接受数据
			printf("%s\n",recvBuf);
			sprintf(sendBuf,"hello,%d",i);
			//send(sockClient,sendBuf,strlen(sendBuf)+1,0);//发送数据	
	
	getchar();
	closesocket(sockClient);//关闭连接
	WSACleanup();
} 