// protocol.h
// maogq 2011.5.8
//////////////////////////////////////////////////////////////////////

#ifndef	PROTOCOL_H
#define	PROTOCOL_H
#include <Winsock2.h>

#include <string.h>

//common.h
typedef  __int64	I64;
typedef  unsigned __int64 U64;
typedef	U64	OBJID;
const int	ID_NONE			= 0;
//define.h
// �汾��
const int	GAME_VERSION	= 11;		// ���汾�ţ��ͻ��˺ͷ���������ͬ���������С�
const int   GAME_HEADTAG    = 0;		// ��Ϸͷ�����,����Ϊ '<'

// ͨ�ó���
const int	IPSTR_SIZE			= 16;				// IP���ռ�
const int	_MAX_NAMESIZE		= 64;
const int	_MAX_TITLESIZE		= 96;				// �ʼ������С
const int	MAX_CONTENTSIZE		= 512;				// �ʼ����ݴ�С
const int	MAX_FIELDSIZE		= 512;				// �洮���ֶεĿռ��С��mysql �Ĵ������ֶ���󳤶�+1
const int	MAX_PARAMSIZE		= 768;				// action param space
const int   MAX_MSGBUFSIZE      = 1024;

const int   MAX_SERVERID_LEN	 = 7;
const int	DBSTR_SIZE				= 32;			     // ���ݿ�INI������
const int	MAX_PACKETSIZE			= 1024;			     // ������Ϣ���ߴ�
const int	MAX_MESSAGESIZE			= MAX_PACKETSIZE+24; // �ڲ���Ϣ���ߴ�
const int   _MAX_MSGSIZE            = MAX_PACKETSIZE-8;  // ���ݳߴ� 
const int	SOCKET_SENDBUFSIZE		= 32*1024;			 // SOCKET_BUF
const int	SOCKET_NPCBUFSIZE		= 128*1024;			 // SOCKET_BUF
const int	SOCKET_ACCOUNTBUFSIZE	= 32*1024;			 // SOCKET_BUF
const int	MAX_MAPGROUPSIZE		= 1;				 // ���1����ͼ��,��ͼ�������ʱû��

//////////////////////////////////////////////////////////////////////
// ����
typedef	unsigned long	PROCESS_ID;						// ͨ�����ڲ���Ϣ�ӿ�ID��ͬ
typedef	long			SOCKET_ID;						// ��Ҷ�Ӧ��SOCKET_ID��ͨ��ΪSET��������
#define	IPP_OF(x)		((void**)&(x))

typedef	char			NAMESTR[_MAX_NAMESIZE];
typedef	char			SQLBUF[1024];
typedef	char			MSGBUF[MAX_MSGBUFSIZE];
typedef	char			MESSAGESTR[MAX_MESSAGESIZE];
typedef	char			PARAMBUF[MAX_PARAMSIZE];



enum{
		//////////////////////////////////////////////////////////////////////
		// ��ͼ������紦�����Ϣ
		KERNEL_BASE					= 1000,
		KERNEL_CLIENTMSG			= KERNEL_BASE + 1,				// CLIENTMSG_PACKET0(size:1024+12), �ͻ����ϴ�����Ϣ��
		KERNEL_NPCMSG				= KERNEL_BASE + 2,				// NPCMSG_PACKET0(size:1024+12), NPC�������ϴ�����Ϣ��
		KERNEL_CLOSEKERNEL			= KERNEL_BASE + 3,				// INT, SOCKET_ID��֪ͨ���Ĺر�(���ı����ٴ�֪ͨSOCKET��!!!)
		KERNEL_OFFLINE				= KERNEL_BASE + 4,				// INT, SOCKET_ID��֪ͨ���ĵ���


		//////////////////////////////////////////////////////////////////////
		// �ɵ�ͼ����Ĵ������Ϣ
		MAPGROUP_BASE				= 10000,
		MAPGROUP_LOGIN				= MAPGROUP_BASE + 1,			// ST_LOGIN, ��ҵ�¼��
		MAPGROUP_BROADCASTMSG		= MAPGROUP_BASE + 2,			// CLIENTMSG_PACKET0(size:1024+12), ת���㲥��Ϣ��
		MAPGROUP_SOCKET_CLOSE_SUCC  = MAPGROUP_BASE + 4,			// ����Ͽ����ǳ����̽���������ͼ���ĵķ���
		MAPGROUP_CHARGE_NOTIFY		= MAPGROUP_BASE + 5,			// ֪ͨ��ֵ
		MAPGROUP_SEND_MAIL			= MAPGROUP_BASE + 6,			// �����ʼ�
		MAPGROUP_PRIZE_NOTIFY		= MAPGROUP_BASE + 7,		    // ���½���֪ͨ
        MAPGROUP_FORBID_TALK        = MAPGROUP_BASE + 8,            // ����
		MAPGROUP_SAVE_ALL			= MAPGROUP_BASE + 9,            // �������������Ϣ
		MAPGROUP_MOBILE_CERTIFY		= MAPGROUP_BASE + 10,			// �ֻ���֤
		MAPGROUP_RELOADSCRIPT		= MAPGROUP_BASE + 11,			// ���¼��ؽű�
		MAPGROUP_RELOADOPENTIME		= MAPGROUP_BASE + 12,
		MAPGROUP_SET_USER_ADULT     = MAPGROUP_BASE + 13,			//�����û�����
		MAPGROUP_MODIFY_ADDICT_CHECK = MAPGROUP_BASE + 14,			//�����Կ���
		MAPGROUP_FORBID_TALK_LEV	= MAPGROUP_BASE + 15,			// ���¼��ؽ��ĵȼ�
		MAPGROUP_RELOADMERGETIME	= MAPGROUP_BASE + 16,			// ���غϷ�ʱ��
		MAPGROUP_RELOAD_ADDICT_CHECK= MAPGROUP_BASE + 17,			// ���ط����Կ���
		MAPGROUP_DELALLNPCMONSTER	= MAPGROUP_BASE + 18,			// ɾ������NPC�����������Ĺ���	


		//////////////////////////////////////////////////////////////////////
		// ��������Ĵ������Ϣ
		WORLD_BASE					= 20000,
		WORLD_SHELLTALK				= WORLD_BASE + 1,				// STRING, ��Ƿ���TALK��Ϣ��
		WORLD_SETPROCESSID			= WORLD_BASE + 2,				// CHANGE_USERDATA, �����µ�PROCESS_ID
		WORLD_CLOSESOCKET			= WORLD_BASE + 3,				// INT, SOCKET_ID������֪ͨSOCKET�ر�(SOCKET����֪ͨ����)
		WORLD_SENDTIME				= WORLD_BASE + 6,				// INT, SOCKET_ID
		WORLD_NPCBREAK				= WORLD_BASE + 7,				// INT, SOCKET_ID


		//////////////////////////////////////////////////////////////////////
		// ��SOCKET���Ĵ������Ϣ
		SOCKET_BASE					= 30000,
		SOCKET_CLOSESOCKET			= SOCKET_BASE + 1,				// INT, SOCKET_ID������֪ͨSOCKET�ر�(SOCKET����֪ͨ����)
		SOCKET_SETPROCESSID			= SOCKET_BASE + 2,				// CHANGE_USERDATA, �����µ�PROCESS_ID
			//!!! ���ķ��͸���Ϣʱ��Ҫͬʱ����CUSER�е�PROCESS_ID��־�������ڴ���KERNEL_CLIENTMSGʱ��һ��Ҫ���PROCESS_ID�Ƿ�ƥ��!!!
		SOCKET_SENDCLIENTMSG		= SOCKET_BASE + 3,				// SENDCLIENTMSG_PACKET0(size:1024+12), ����ͻ��˺�NPC����������Ϣ��
		SOCKET_SENDNPCMSG			= SOCKET_BASE + 4,				// SENDNPCMSG_PACKET0(size:1024+12), ����ͻ��˺�NPC����������Ϣ��
		SOCKET_SETNPCSOCKETID		= SOCKET_BASE + 5,				// INT, SOCKET_ID, ������Ľ��յ�NPC�������ĵ�¼��Ϣʱ��֪ͨSOCKET���ġ�(����ΪSOCKET_NONE)
		SOCKET_SETNPCPROCESSID		= SOCKET_BASE + 6,				// CHANGE_NPCPROCESSID, �����µ�PROCESS_ID
		SOCKET_CHANGECODE			= SOCKET_BASE + 7,				// CHANGE_USERDATA���޸Ķ�̬���롣
		SOCKET_BREAKCONNECT			= SOCKET_BASE + 8,				// INT, SOCKET_ID, �����ʱ���ȶϿ�SOCKET���ӡ�
		SOCKET_BREAKALLCONNECT		= SOCKET_BASE + 11,				// INT, GM_SOCKET_ID, ��������ң���ֹ�������ӡ�
		SOCKET_OFFLINE				= SOCKET_BASE + 13,				// INT, SOCKET_ID, ����SOCKETΪ����״̬�����ͷ�SOCKET
		SOCKET_BROADCASTCLINETMSG   = SOCKET_BASE + 14,				// BROADCASTCLIENTMSG_PACKET0 �㲥����ҵ���Ϣ
		SOCKET_SHOWTEST				= SOCKET_BASE + 15,

		//////////////////////////////////////////////////////////////////////
		// ����Ǵ������Ϣ
		SHELL_BASE					= 40000,
		SHELL_PRINTTEXT				= SHELL_BASE + 1,				// STRING, ���ķ��͵�TEXT��Ϣ
		SHELL_KERNELSTATE			= SHELL_BASE + 2,				// STRING, ���ķ��͵�STATE��������
		SHELL_SQL					= SHELL_BASE + 3,				// STRING, ��Ҫ���͵�UpdateServer��������ݿ����		
};

struct CLIENTMSG_PACKET0			// ���յ�CLIENT��Ϣ
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	int 	idPacket;
	int		nSize;
	DWORD     nTime;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct NPCMSG_PACKET0			// ���յ�NPC��Ϣ
{
	OBJID	idNpc;
	int  	idPacket;
	int		nSize;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct SENDCLIENTMSG_PACKET0
{
	int  	idPacket;
	SOCKET_ID		idSocket;			// SOCKET_ID	
	int		nSize;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct BROADCASTCLIENTMSG_PACKET0  // �㲥������ͻ��˵���Ϣ
{
	int 	idPacket;
	int		nSocketNum; // socket����
	USHORT  idSockets[500];  // socket�б���಻����500��	
	int     nSize;
	char    buf[1];
};

struct SENDNPCMSG_PACKET0
{
	OBJID	idNpc;				// �㲥��Ϣ��BCAST_NPCID
	int 	idPacket;
	int		nSize;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct TRANSMSG_PACKET0			// ת�����������̴������Ϣ
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	OBJID			idNpc;				// ͬʱ֧��NPC����Ϣ
	int 	idPacket;
	int		nSize;
	int		nTrans;				// ��������
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct USERNAMEMSG_PACKET0			// ��WORLDת������Ϣ��������ת��
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	int 	idPacket;
	int		nSize;
	char	szName[_MAX_NAMESIZE];		// ת���������
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct USERIDMSG_PACKET0			// ��WORLDת������Ϣ����IDת��
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	int 	idPacket;
	int		nSize;
	OBJID	idUser;				// ת���������
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};


struct CHANGE_USERDATA
{
	SOCKET_ID	idSocket;
	int			nData;
};

struct ST_CREATENEWNPC
{
	OBJID			id;
	OBJID			idMap;
	OBJID			idData;
	OBJID			idOwner;
	int				nData;
	unsigned short	usPosX;
	unsigned short	usPosY;
	unsigned short	usAction;
	unsigned short	usType;
	unsigned char	ucOwnerType;
};

struct ST_LOGIN
{
	SOCKET_ID	idSocket;
	OBJID		idUser;
	bool		bNewPlayer;
	bool		bIsReconnect;
	bool		bIsAdult; // ����ʱ��Ч
};

struct ST_LOAD_USERDATA
{
	OBJID       idUser;
	int			nData;
	bool		bNewPlayer;
};

struct ST_CHARGE_NOTIFY
{
	OBJID			idUser;
	OBJID			idPay;
};

struct ST_SENDMAIL
{
	OBJID idBegin;
	OBJID idEnd;
};

struct ST_PRIZE_NOTIFY
{
	OBJID idUser;
	OBJID idPrize;
};

struct ST_FORBID_TALK
{
    OBJID idUser;       // �����Ե����ID
    DWORD dwSecs;       // ���Զ�����
};

struct ST_MOBILE_CERTIFY
{
	OBJID idUser;		// ���ID
};
//////////////////////////////////////////////////////////////////////
// C/S Э��Ŀͻ��˲���	

// �ò��ֳ������������������������ʹ��
const int	PROTOCOL_MSG_HEADSIZE = 8;

#pragma pack(push, 1)
// ����Э��̶���ͷ��
struct CProtocolMsgStruct
{
	unsigned short    tagHead   ;       // ͷ����ǣ�""��
	unsigned short    nMsgSize  ;       // �������ݰ����ȣ��ֽ�����
	unsigned short    nVersion  ;
	unsigned short    idPacket  ;       // ������
	char		      pMsg[1];
};
#pragma pack(pop)

// �ֽ���Ϣ��
// return: netpacket size
inline int	SplitPacket(const char* pBuf, int nBufLen, OBJID* pidPacket, char** ppMsg, int* pMsgSize)
{
	if(nBufLen > PROTOCOL_MSG_HEADSIZE)
	{
		CProtocolMsgStruct*	pMsgPtr = (CProtocolMsgStruct*)pBuf;

		if(pMsgPtr->nMsgSize <= nBufLen)
		{
			if(pMsgPtr->nMsgSize < PROTOCOL_MSG_HEADSIZE || pMsgPtr->nMsgSize > MAX_PACKETSIZE
				|| pMsgPtr->nVersion != GAME_VERSION || pMsgPtr->tagHead != GAME_HEADTAG)
				return -1;  // ��������

			*pidPacket	= pMsgPtr->idPacket;
			*pMsgSize	= pMsgPtr->nMsgSize - PROTOCOL_MSG_HEADSIZE;
			*ppMsg		= pMsgPtr->pMsg;
			return pMsgPtr->nMsgSize;
		}
	}
	return 0;
}

// �ϳ���Ϣ��
// return: netpacket size
inline int	UnitePacket(char* pBuf, int nBufLen, OBJID idPacket, const char* pMsg, int nMsgSize)
{
	if(nBufLen >= nMsgSize + PROTOCOL_MSG_HEADSIZE)
	{
		CProtocolMsgStruct*	pMsgPtr = (CProtocolMsgStruct*)pBuf;
		pMsgPtr->idPacket		= ((unsigned short)idPacket);
		pMsgPtr->nMsgSize		= (nMsgSize + PROTOCOL_MSG_HEADSIZE);
		pMsgPtr->tagHead        = GAME_HEADTAG;
		pMsgPtr->nVersion       = GAME_VERSION;
		memcpy(pMsgPtr->pMsg,	pMsg, (size_t)nMsgSize);
		return nMsgSize + PROTOCOL_MSG_HEADSIZE;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// C/S Э���NPC����	

// �ò��ֳ������������������������ʹ��
const int	PROTOCOL_NPCMSG_HEADSIZE		= 16;
struct CProtocolNpcMsgStruct{
	unsigned short    tagHead   ;       // ͷ����ǣ�""��
	unsigned short    nMsgSize  ;       // �������ݰ����ȣ��ֽ�����
	unsigned short    nVersion  ;
	unsigned short    idPacket  ;       // ������
	OBJID		   	  idNpc;
	char			pMsg[1];
};

// �ֽ���Ϣ��
// return: netpacket size
inline int	SplitNpcPacket(const char* pBuf, int nBufLen, OBJID* pidPacket, char** ppMsg, int* pMsgSize, OBJID* pidNpc)
{
	if(nBufLen > PROTOCOL_NPCMSG_HEADSIZE)
	{
		CProtocolNpcMsgStruct*	pMsgPtr = (CProtocolNpcMsgStruct*)pBuf;
		if(pMsgPtr->nMsgSize <= nBufLen)
		{
			if(pMsgPtr->nMsgSize < 4 || pMsgPtr->nMsgSize > MAX_PACKETSIZE)
				return 0;

			*pidPacket	= pMsgPtr->idPacket;
			*pMsgSize	= pMsgPtr->nMsgSize - PROTOCOL_NPCMSG_HEADSIZE;
			*pidNpc		= pMsgPtr->idNpc;
			*ppMsg		= pMsgPtr->pMsg;
			return pMsgPtr->nMsgSize;
		}
	}
	return 0;
}

// �ϳ���Ϣ��
// return: netpacket size
inline int	UniteNpcPacket(char* pBuf, int nBufLen, OBJID idPacket, const char* pMsg, int nMsgSize, OBJID idNpc)
{
	if(nBufLen >= nMsgSize + PROTOCOL_NPCMSG_HEADSIZE)
	{
		CProtocolNpcMsgStruct*	pMsgPtr = (CProtocolNpcMsgStruct*)pBuf;
		pMsgPtr->idPacket		= (unsigned short)idPacket;
		pMsgPtr->nMsgSize		= nMsgSize + PROTOCOL_NPCMSG_HEADSIZE;
		pMsgPtr->idNpc			= idNpc;
		pMsgPtr->tagHead        = GAME_HEADTAG;
		pMsgPtr->nVersion       = GAME_VERSION;

		memcpy(pMsgPtr->pMsg,	pMsg, (size_t)nMsgSize);

		return pMsgPtr->nMsgSize;
	}
	return 0;
}
#endif // PROTOCOL_H