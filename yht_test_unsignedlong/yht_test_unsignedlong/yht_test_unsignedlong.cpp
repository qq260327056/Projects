// yht_test_unsignedlong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "test.h"
//enum ABC;
const int	MAX_PACKETSIZE			= 1024;//����С
const int   MAX_NAMELENGTH			= 64;  //���ֳ���
#pragma pack(1)
struct CProtocolMsgStruct{
	unsigned short    tagHead   ;       // ͷ����ǣ�""��
	unsigned short    nMsgSize  ;       // �������ݰ����ȣ��ֽ�����
	unsigned short    nVersion  ;
	unsigned short    idPacket  ;       // ������
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

