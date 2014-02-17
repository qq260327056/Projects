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
// 版本号
const int	GAME_VERSION	= 11;		// 主版本号，客户端和服务器必须同步才能运行。
const int   GAME_HEADTAG    = 0;		// 游戏头部标记,不可为 '<'

// 通用常量
const int	IPSTR_SIZE			= 16;				// IP串空间
const int	_MAX_NAMESIZE		= 64;
const int	_MAX_TITLESIZE		= 96;				// 邮件标题大小
const int	MAX_CONTENTSIZE		= 512;				// 邮件内容大小
const int	MAX_FIELDSIZE		= 512;				// 存串型字段的空间大小。mysql 的串类型字段最大长度+1
const int	MAX_PARAMSIZE		= 768;				// action param space
const int   MAX_MSGBUFSIZE      = 1024;

const int   MAX_SERVERID_LEN	 = 7;
const int	DBSTR_SIZE				= 32;			     // 数据库INI串长度
const int	MAX_PACKETSIZE			= 1024;			     // 网络消息包尺寸
const int	MAX_MESSAGESIZE			= MAX_PACKETSIZE+24; // 内部消息包尺寸
const int   _MAX_MSGSIZE            = MAX_PACKETSIZE-8;  // 数据尺寸 
const int	SOCKET_SENDBUFSIZE		= 32*1024;			 // SOCKET_BUF
const int	SOCKET_NPCBUFSIZE		= 128*1024;			 // SOCKET_BUF
const int	SOCKET_ACCOUNTBUFSIZE	= 32*1024;			 // SOCKET_BUF
const int	MAX_MAPGROUPSIZE		= 1;				 // 最多1个地图组,地图组概念暂时没用

//////////////////////////////////////////////////////////////////////
// 类型
typedef	unsigned long	PROCESS_ID;						// 通常与内部消息接口ID相同
typedef	long			SOCKET_ID;						// 玩家对应的SOCKET_ID，通常为SET的索引号
#define	IPP_OF(x)		((void**)&(x))

typedef	char			NAMESTR[_MAX_NAMESIZE];
typedef	char			SQLBUF[1024];
typedef	char			MSGBUF[MAX_MSGBUFSIZE];
typedef	char			MESSAGESTR[MAX_MESSAGESIZE];
typedef	char			PARAMBUF[MAX_PARAMSIZE];



enum{
		//////////////////////////////////////////////////////////////////////
		// 地图组或世界处理的消息
		KERNEL_BASE					= 1000,
		KERNEL_CLIENTMSG			= KERNEL_BASE + 1,				// CLIENTMSG_PACKET0(size:1024+12), 客户端上传的消息。
		KERNEL_NPCMSG				= KERNEL_BASE + 2,				// NPCMSG_PACKET0(size:1024+12), NPC服务器上传的消息。
		KERNEL_CLOSEKERNEL			= KERNEL_BASE + 3,				// INT, SOCKET_ID。通知核心关闭(核心必须再次通知SOCKET层!!!)
		KERNEL_OFFLINE				= KERNEL_BASE + 4,				// INT, SOCKET_ID。通知核心掉线


		//////////////////////////////////////////////////////////////////////
		// 由地图组核心处理的消息
		MAPGROUP_BASE				= 10000,
		MAPGROUP_LOGIN				= MAPGROUP_BASE + 1,			// ST_LOGIN, 玩家登录。
		MAPGROUP_BROADCASTMSG		= MAPGROUP_BASE + 2,			// CLIENTMSG_PACKET0(size:1024+12), 转发广播消息。
		MAPGROUP_SOCKET_CLOSE_SUCC  = MAPGROUP_BASE + 4,			// 网络断开（登出流程结束）给地图核心的反馈
		MAPGROUP_CHARGE_NOTIFY		= MAPGROUP_BASE + 5,			// 通知充值
		MAPGROUP_SEND_MAIL			= MAPGROUP_BASE + 6,			// 发送邮件
		MAPGROUP_PRIZE_NOTIFY		= MAPGROUP_BASE + 7,		    // 线下奖励通知
        MAPGROUP_FORBID_TALK        = MAPGROUP_BASE + 8,            // 禁言
		MAPGROUP_SAVE_ALL			= MAPGROUP_BASE + 9,            // 保存所有玩家信息
		MAPGROUP_MOBILE_CERTIFY		= MAPGROUP_BASE + 10,			// 手机认证
		MAPGROUP_RELOADSCRIPT		= MAPGROUP_BASE + 11,			// 重新加载脚本
		MAPGROUP_RELOADOPENTIME		= MAPGROUP_BASE + 12,
		MAPGROUP_SET_USER_ADULT     = MAPGROUP_BASE + 13,			//设置用户成年
		MAPGROUP_MODIFY_ADDICT_CHECK = MAPGROUP_BASE + 14,			//防沉迷开关
		MAPGROUP_FORBID_TALK_LEV	= MAPGROUP_BASE + 15,			// 重新加载禁聊等级
		MAPGROUP_RELOADMERGETIME	= MAPGROUP_BASE + 16,			// 重载合服时间
		MAPGROUP_RELOAD_ADDICT_CHECK= MAPGROUP_BASE + 17,			// 重载防沉迷开关
		MAPGROUP_DELALLNPCMONSTER	= MAPGROUP_BASE + 18,			// 删除所有NPC服务器创建的怪物	


		//////////////////////////////////////////////////////////////////////
		// 由世界核心处理的消息
		WORLD_BASE					= 20000,
		WORLD_SHELLTALK				= WORLD_BASE + 1,				// STRING, 外壳发送TALK消息。
		WORLD_SETPROCESSID			= WORLD_BASE + 2,				// CHANGE_USERDATA, 设置新的PROCESS_ID
		WORLD_CLOSESOCKET			= WORLD_BASE + 3,				// INT, SOCKET_ID，核心通知SOCKET关闭(SOCKET不再通知核心)
		WORLD_SENDTIME				= WORLD_BASE + 6,				// INT, SOCKET_ID
		WORLD_NPCBREAK				= WORLD_BASE + 7,				// INT, SOCKET_ID


		//////////////////////////////////////////////////////////////////////
		// 由SOCKET核心处理的消息
		SOCKET_BASE					= 30000,
		SOCKET_CLOSESOCKET			= SOCKET_BASE + 1,				// INT, SOCKET_ID，核心通知SOCKET关闭(SOCKET不再通知核心)
		SOCKET_SETPROCESSID			= SOCKET_BASE + 2,				// CHANGE_USERDATA, 设置新的PROCESS_ID
			//!!! 核心发送该消息时，要同时更新CUSER中的PROCESS_ID标志。核心在处理KERNEL_CLIENTMSG时，一定要检查PROCESS_ID是否匹配!!!
		SOCKET_SENDCLIENTMSG		= SOCKET_BASE + 3,				// SENDCLIENTMSG_PACKET0(size:1024+12), 发向客户端和NPC服务器的消息。
		SOCKET_SENDNPCMSG			= SOCKET_BASE + 4,				// SENDNPCMSG_PACKET0(size:1024+12), 发向客户端和NPC服务器的消息。
		SOCKET_SETNPCSOCKETID		= SOCKET_BASE + 5,				// INT, SOCKET_ID, 世界核心接收到NPC服务器的登录消息时，通知SOCKET核心。(可能为SOCKET_NONE)
		SOCKET_SETNPCPROCESSID		= SOCKET_BASE + 6,				// CHANGE_NPCPROCESSID, 设置新的PROCESS_ID
		SOCKET_CHANGECODE			= SOCKET_BASE + 7,				// CHANGE_USERDATA。修改动态密码。
		SOCKET_BREAKCONNECT			= SOCKET_BASE + 8,				// INT, SOCKET_ID, 踢玩家时，先断开SOCKET连接。
		SOCKET_BREAKALLCONNECT		= SOCKET_BASE + 11,				// INT, GM_SOCKET_ID, 踢所有玩家，禁止所有连接。
		SOCKET_OFFLINE				= SOCKET_BASE + 13,				// INT, SOCKET_ID, 设置SOCKET为掉线状态，不释放SOCKET
		SOCKET_BROADCASTCLINETMSG   = SOCKET_BASE + 14,				// BROADCASTCLIENTMSG_PACKET0 广播给玩家的消息
		SOCKET_SHOWTEST				= SOCKET_BASE + 15,

		//////////////////////////////////////////////////////////////////////
		// 由外壳处理的消息
		SHELL_BASE					= 40000,
		SHELL_PRINTTEXT				= SHELL_BASE + 1,				// STRING, 核心发送的TEXT消息
		SHELL_KERNELSTATE			= SHELL_BASE + 2,				// STRING, 核心发送的STATE串，多行
		SHELL_SQL					= SHELL_BASE + 3,				// STRING, 需要发送到UpdateServer处理的数据库语句		
};

struct CLIENTMSG_PACKET0			// 接收的CLIENT消息
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	int 	idPacket;
	int		nSize;
	DWORD     nTime;
	char	buf[1];				// 用于结构指针，不需要空间
};

struct NPCMSG_PACKET0			// 接收的NPC消息
{
	OBJID	idNpc;
	int  	idPacket;
	int		nSize;
	char	buf[1];				// 用于结构指针，不需要空间
};

struct SENDCLIENTMSG_PACKET0
{
	int  	idPacket;
	SOCKET_ID		idSocket;			// SOCKET_ID	
	int		nSize;
	char	buf[1];				// 用于结构指针，不需要空间
};

struct BROADCASTCLIENTMSG_PACKET0  // 广播给多个客户端的消息
{
	int 	idPacket;
	int		nSocketNum; // socket数量
	USHORT  idSockets[500];  // socket列表，最多不超过500个	
	int     nSize;
	char    buf[1];
};

struct SENDNPCMSG_PACKET0
{
	OBJID	idNpc;				// 广播消息用BCAST_NPCID
	int 	idPacket;
	int		nSize;
	char	buf[1];				// 用于结构指针，不需要空间
};

struct TRANSMSG_PACKET0			// 转发给其它进程处理的消息
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	OBJID			idNpc;				// 同时支持NPC的消息
	int 	idPacket;
	int		nSize;
	int		nTrans;				// 附加数据
	char	buf[1];				// 用于结构指针，不需要空间
};

struct USERNAMEMSG_PACKET0			// 让WORLD转发的消息，按名字转发
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	int 	idPacket;
	int		nSize;
	char	szName[_MAX_NAMESIZE];		// 转发给该玩家
	char	buf[1];				// 用于结构指针，不需要空间
};

struct USERIDMSG_PACKET0			// 让WORLD转发的消息，按ID转发
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	int 	idPacket;
	int		nSize;
	OBJID	idUser;				// 转发给该玩家
	char	buf[1];				// 用于结构指针，不需要空间
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
	bool		bIsAdult; // 重连时有效
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
    OBJID idUser;       // 被禁言的玩家ID
    DWORD dwSecs;       // 禁言多少秒
};

struct ST_MOBILE_CERTIFY
{
	OBJID idUser;		// 玩家ID
};
//////////////////////////////////////////////////////////////////////
// C/S 协议的客户端部分	

// 该部分常量、定义仅由以下两个函数使用
const int	PROTOCOL_MSG_HEADSIZE = 8;

#pragma pack(push, 1)
// 数据协议固定的头部
struct CProtocolMsgStruct
{
	unsigned short    tagHead   ;       // 头部标记（""）
	unsigned short    nMsgSize  ;       // 整个数据包长度（字节数）
	unsigned short    nVersion  ;
	unsigned short    idPacket  ;       // 命令编号
	char		      pMsg[1];
};
#pragma pack(pop)

// 分解消息包
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
				return -1;  // 发生错误

			*pidPacket	= pMsgPtr->idPacket;
			*pMsgSize	= pMsgPtr->nMsgSize - PROTOCOL_MSG_HEADSIZE;
			*ppMsg		= pMsgPtr->pMsg;
			return pMsgPtr->nMsgSize;
		}
	}
	return 0;
}

// 合成消息包
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
// C/S 协议的NPC部分	

// 该部分常量、定义仅由以下两个函数使用
const int	PROTOCOL_NPCMSG_HEADSIZE		= 16;
struct CProtocolNpcMsgStruct{
	unsigned short    tagHead   ;       // 头部标记（""）
	unsigned short    nMsgSize  ;       // 整个数据包长度（字节数）
	unsigned short    nVersion  ;
	unsigned short    idPacket  ;       // 命令编号
	OBJID		   	  idNpc;
	char			pMsg[1];
};

// 分解消息包
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

// 合成消息包
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