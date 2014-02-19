// yht_test_unsignedlong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "test.h"
//enum ABC;
const int	MAX_PACKETSIZE			= 1024;//包大小
const int   MAX_NAMELENGTH			= 64;  //名字长度
#pragma pack(1)
struct CProtocolMsgStruct{
	unsigned short    tagHead   ;       // 头部标记（""）
	unsigned short    nMsgSize  ;       // 整个数据包长度（字节数）
	unsigned short    nVersion  ;
	unsigned short    idPacket  ;       // 命令编号
	char		      pMsg[1];
};
//class Point;
class Point {

	static Point a;
	int func(){Point B;
	return 0;};

};


class A
{
public:
	int abc(){return 1;}
	int m_abc;
	int funca(ABC eType)
	{
		return 1;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	printf("%d",sizeof(CProtocolMsgStruct));
	return 0;

	int (A::* funac) () = &(A::abc);
	A* tempA = new A;

  int ac=	(tempA->*funac)();
}

