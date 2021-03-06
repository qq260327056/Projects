#include "protocol.h"
#include "networkdef.h"
#pragma once
#pragma pack(push,1)

#define _ConstructMsg new (CNetMsg::MsgObjBuf())
//==============================================
typedef struct {
	DWORD	dwWordsColor;           // 颜色
	USHORT	unTxtAttribute;         // 频道
	USHORT	unTxtStyle;             // 显示样式

	union{
		DWORD	dwTime;
		OBJID	idTransmit;
	};

	OBJID   idSpeaker;
	char    szSender[_MAX_NAMESIZE];
	char    szReceiver[_MAX_NAMESIZE];
	char	szBuf[1];
}MSG_Info_Talk;
//==============================================
typedef struct {
	OBJID			idAccount;
	DWORD			dwData;
	char			szInfo[_MAX_NAMESIZE];
	int				nData;
	int				nData2;//id
}MSG_Info_Login;
//==============================================
typedef struct {
	char	szAccount[_MAX_NAMESIZE];
	char	szName[_MAX_NAMESIZE];  // utf8
	OBJID	idAccount;
	UCHAR   ucProf;
	UCHAR   ucSex;  //1,2表示创建成功，>2表示创建失败,3:角色已存在;4:角色数量达到上限; 5:角色名不合法
	OBJID   idUser;
	UCHAR   ucLev;
}MSG_Info_Register;
//==============================================
enum {
actionNone					=0, 
actionEnterMap				=1,		//c-s 登录流程第一步，通知客户端登录成功，玩家已经进入地图。仅玩家! (to client: idUser is Map)
//usAction=actionEnterMap;
//s-c usAction=actionEnterMap,iduser=userid,dwData1=mapid,dwData2=mapdoc(该地图对应的文件编号),dwData3=posx,dwData4=posy,dwData5=方向
actionQueryItemSet		    = 2,     //c-s 查询自己所有背包中的物品信息,usAction=actionQueryItemSet(第一次打开物品背包时查询)
actionQueryLineupHeroSet	= 3, //c-s 查询上阵武将,  idUser=查询对象，查询自己时为空（只查询一次）
actionQuerySubLineupHeroSet = 5, //c-s 查询伙伴,idUser=查询对象，查询自己时为空（只查询一次）
actionQueryCurFormation		= 6,	 //c-s 查询当前阵法,idUser=查询对象，查询自己时为空（只查询一次）
actionQueryHeroEquip		= 7,	 //c-s 查询指定武将的装备，idUser=查询对象，查询自己时为空, dwData1=武将ID（只查询一次）
actionQueryHeroWarBook		= 8,     //c-s 查询指定武将的兵书，idUser=查询对象，查询自己时为空, dwData1=武将ID（只查询一次）

//actionQueryEquipSet     = 4,	//c-s 查询自己装备中的物品信息，登录时查询
actionLoginOk				= 9,    //c-s // s-c 登录成功标记
actionGoddesBeLoved			= 20,   //yht，女神合体，宠幸 dwData1 =1点击合体，2摇晃手机合体，3宠幸。成功返回MsgRoleAttrib消息更新女神经验或等级
actionQueryPayAmount		=56,   // c-s 查询支付额度 s-c 返回支付额度,dwData1=支付额度
// 2000以上的消息C++不用处理，全部交由脚本处理
actionScriptMsg             =2000, //c-s dwData1=消息ID,dwData2~dwData7消息参数
};
typedef struct {
	USHORT		usAction;
	OBJID		idUser;
	U64       dwData1;
	U64       dwData2;
	U64       dwData3;       
	U64       dwData4;
	U64       dwData5;
	U64       dwData6;		
}MSG_Info_Action;
//==============================================
enum BATTLEACT
{
	BATTLEACT_TRIGGER      = 1,   // s-c 战斗触发, dwData1 = 触发者,dwData2=0,dwData3=battletype
	BATTLEACT_ROUND        = 2,   // s-c 通知回合数, dwData1=回合

	BATTLEACT_BATTLERESULT = 5,	  // s-c 整个战斗的结果,dwData1=胜利方（战斗的最后一个消息，收到该消息显示战斗结果以及奖励，需要后台给奖励内容的都会在这个消息之前下发）

	BATTLEACT_KILL         = 7,	  // s-c 击杀,dwData1=击杀者ID,dwData2=被杀者ID，dwData3=获得经验
	BATTLEACT_REBORN       = 8,   // s-c 复活,dwData1=复活者ID,dwData2=复活后的血量
};
typedef struct
{
	UCHAR ucBattleAct;
	U64 dwData1;
	U64 dwData2;
	U64 dwData3;
}MSG_Info_Battle;
//==============================================
struct NET_NOTIFY_INFO
{
	USHORT		usAction;
	DWORD       dwData1;
	DWORD       dwData2;
	DWORD       dwData3;       
	DWORD       dwData4;
	DWORD       dwData5;
	DWORD       dwData6;
};
typedef struct {
	USHORT		usAction;
	DWORD       dwData1;
	DWORD       dwData2;		
}MSG_Info_CommonNotify;
//==============================================
typedef struct {
	OBJID			idAccount;
	DWORD			dwData;
	char			szInfo[_MAX_NAMESIZE];
	int				nData;
	int				nData2;
}MSG_Info_Connect;
//==============================================
enum FIGHTROLE_TYPE
{
	QUERYFIGHTROLE_TRIGGER = 0,           // s-c 表示战斗触发方信息
	QUERYFIGHTROLE_ACCEPT  = 1,		      // s-c 表示战斗接受信息

	//QUERYFIGHTROLE_LINEUP  = 10,		  // s-c 非战斗状态下查询阵型中的角色(FIGHTROLE_INFO中第0个始终是玩家,ucBattleCamp无用)
};
struct FIGHTROLE_INFO
{
	OBJID idObjType;
	OBJID id;
	UCHAR ucPosition;
	DWORD dwData;   // 怪物类型或者武将卡类型
	char  szName[_MAX_NAMESIZE];
	int   nLife;
	int   nMaxLife;		       
	UCHAR ucLev;		// 等级
	int   nFightPower;  // 战力       
};
typedef struct 
{
	UCHAR ucType;
	UCHAR ucNum;
	FIGHTROLE_INFO roles[1];
}MSG_Info_FightRole;
//==============================================
enum 
{	
	ITEMACT_NONE			=0, 
	ITEMACT_DROP,					// c-s/s-c,丢弃物品,id=丢弃物品ID
	ITEMACT_USE,					// c-s,使用物品,id=物品ID，idTarget=使用的目标（自己或者他人）,dwData=位置
	ITEMACT_EQUIP			,		// s-c，通知装备物品,id=装备ID，idTarget=装备到哪个角色,dwData=装备到哪个位置
	ITEMACT_BUY,					// c-s,购买，id=NPCID， idTarget=物品类型, dwData=购买数量
	ITEMACT_SELL,	 				// c-s，卖出,id=NPCID, idTarget=卖出物品ID						
	ITEMACT_UNEQUIP,				// c-s，仅取下装备，idTarget=取下哪个角色的装备，dwData=取下的位置
	// s-c,返回,id=取下的装备ID，idTarget=取下哪个角色的装备, dwData=取下的位置
	ITEMACT_REPAIR,					// c-s,修理单个物品, id=ITEMID
	ITEMACT_REPAIRALL		,		// c-s,修理所有物品,修理成功后会返回更新物品信息
	// s-c,修理所有物品成功后返回该消息，客户端需要自己把所有装备的耐久恢复到最大值
	ITEMACT_IDENT,					// c-s,鉴定物品,id=ITEMID
	ITEMACT_STOREEX,				// s-c通知装载仓库扩展物品到扩展栏,id=物品ID，dwData=装载到哪个扩展栏
	ITEMACT_UNSTOREEX,				// c-s卸载仓库扩展物品,dwData=卸下的扩展栏位置
	// s-c返回,id=取下的道0具ID，dwData=卸下的位置
	ITEMACT_DROPSTROEEX,			// s-c通知删除装备扩展物品,对应扩展仓库里面有物品的时候不可删除,id=道具ID，dwData=哪个扩展栏
	ITEMACT_SYNCHRO_AMOUNT,	        // s-c通知更新物品数量或者装备耐久,id=物品ID, idTarget=物品的拥有角色，dwData=数量或者耐久
	ITEMACT_DROPEQUIPMENT,			// s-c通知删除装备栏的物品，id=装备ID，idTarget=丢弃哪个角色的装备，dwData=哪个装备栏

	//yht
	ITEMACT_MERGE		 = 30,		// c-s，请求合并两个物品，id=源物，idTarget=目标物品,两者必须同时为装备卡或同时为武将卡
	// 合并成功会返回一个ITEMACT_DROP 消息，删除目标物品 ,一个CMsgRoleAttrib的_USERATTRIB_MONEY2消息,同步银两。一个ITEMINFO_UPDATE更新

	ITEMACT_ABSORB		 = 31,		// c-s 装备或武将突破, id =源item, idTarget= 目标item1, dwData = 目标item2.
	// 若dwData=0,则是5，6星武将的合并
	// 操作成功，返回 ITEMACT_DROP(一个或二个目标）消息和update消息

	ITEMACT_CONVERT2CHIP = 32,		// c-s,将装备兑换成碎片, id表示装备的id.返回一个drop,一个add
	ITEMACT_CONVERT2WHOLE = 33,		// c-s,将碎片兑换成装备, id 表示碎片的id, 返回一个drop,一个add
	ITEMACT_REBORN		=	34,		//c-s,id为物品id.只能从背包中转生。成功则返回一个ITEMACT_DROP和ITEMINFO_UPDATE消息
	ITEMACT_ADVANCED	=	35,		//c-s,id为物品id.只能从背包中进阶。
	ITEMACT_EXCHANGE_POSITION = 36, //c-s,id为源上阵武将position , idTarget为目标武将position. 操作成功返回两个update消息
	//其他
	ITEMACT_OVERLAPITEM = 60,		// c-s，请求叠加两个物品,id=拖动物品,idTarget=叠加的目标物品
	ITEMACT_OVERLAPALL  = 61,		// c-s / s-c, 请求叠加背包中所有可叠加物品，叠加完成后返回同样消息
	ITEMACT_TIMELIMIT	= 62,		// s-c 通知更新物品的到期时间,dwData = 到期时间(时间戳)
};
typedef struct 
{
	USHORT		usAction;
	OBJID		id;		
	OBJID		idTarget;	// 目标对象ID，ID_NONE表示自己
	//yht 从32位改为64位
	OBJID		dwData;
}MSG_Info_Item;
//==============================================
enum ITEMINFO_ACT
{	
	ITEMINFO_NONE=0, 
	ITEMINFO_ADDITEM,				// 添加物品,ucInfoAction=ITEMINFO_ADDITEM
	ITEMINFO_OTHERPLAYER, // 返回其他玩家装备// id is user id
	ITEMINFO_UPDATE,				// update item info
	//ITEMINFO_TRADE,				// 公平交易对方添加的物品		
	//ITEMINFO_AUCTION,             // 拍买查看物品
};
typedef struct 
{	
	UCHAR		ucInfoAction;   // ITEMINFO_ACT
	OBJID		id;				// iditem
	OBJID       idOwner;		//当前拥有者ID,如果是武将就是武将ID
	DWORD		dwType;			// item type id
	USHORT		usAmount;		// 数量或耐久
	UCHAR		ucPosition;     // 位置
	DWORD       dwFlag;         // 特殊标记，掩码形式
	//UCHAR		ucQuality;		// 品质
	//UCHAR		ucStrength;		// 强化程度
	//UCHAR		ucStrengthLuck;	// 强化失败后累计的额外成功概率
	DWORD		dwTimeLimit;	// 到期时间(时间戳)
	//DWORD		dwStar;			// 阶数

	//yht Msgiteminfo新增属性------------------
	DWORD		dwLev;			// 等级
	DWORD	    dwExp;			// 经验
	DWORD		dwAbsorbTimes;	// 转生次数
	DWORD		dwRebornTimes;
	DWORD		dwAbility;		//	转生后获得的技能，AAABBB形式，AAA为技能类形，BBB为技能等级
	DWORD		dwAdvanced_times;//进阶后的阶数
	DWORD		dwAdvanced_points;//获得的进阶点数
	//--------------------------------------
	char		szBuf[1];		// 其他属性
}MSG_Info_ItemInfo;
//==============================================
typedef struct 
{
	UCHAR   ucDmgType;	    // 伤害类型，具体参考伤害类型枚举
	OBJID	idRole;			// 技能作用对象
	DWORD	dwData1;		// 技能产生效果1（具体技能意义不同）
	//DWORD   dwData2;
}EffectRoleStruct;
typedef struct
{
	OBJID				idRole;			 // 技能释放者
	OBJID				idTarget;		 // 释放的目标
	USHORT				usType;			 // 技能类型
	UCHAR				ucLevel;		 // 技能等级
	UCHAR				ucAmount;        // 效果数量
	EffectRoleStruct    effect[1];		 // 技能放出产生的效果
}MSG_Info_MagicEffect;
//==============================================
struct MSG_ROLEATTRIB
{
	int   nAttrib;	// 属性类型
	DWORD dwData;	// 值
};
typedef struct
{		
	OBJID				idRole;
	UCHAR				ucNum;
	MSG_ROLEATTRIB		attribs[1];
}MSG_Info_RoleAttrib;
//==============================================
enum STRING_TYPE
{
	//   STRING_TYPE_USERACTTAG  = 3,    // 玩家活动标签
	//   STRING_TYPE_USERFUNTAG  = 4,    // 玩家功能标签
	//   STRING_TYPE_TREASUREAWARD = 5,  // 玩家挖到宝物
	//   STRING_TYPE_CROSSINGAWARD = 6,  // 打关卡掉落
	//STRING_TYPE_ARENADOMAINPRIZE   = 7,   // 校场夺令奖励结果 "金钱,将令类型,将令数量"
	//   STRING_TYPE_TREASUREACCEPTLIST  = 8,    // 夺宝任务接受列表"玩家1名称 藏宝图ID 品质 ... "
	//STRING_TYPE_QUERY_TITLE	 = 9,	// 获得的所有称号"称号1 称号2 ..."
	//   STRING_TYPE_WINE_STATUS  = 10,  // 煮酒状态信息"标识位 帮派ID 帮派坐标 剩余时间 煮酒类型 煮酒的玩家ID"
	//   STRING_TYPE_CHAT_NOUSER  = 11,  // 聊天时玩家不在线，"玩家名字 玩家消息"
	//   STRING_TYPE_INVITE_MEMBER= 12,  // 邀请组队,"玩家ID 玩家名字"
	//STRING_TYPE_ARENA_TYPE = 13,	// 通知自己在校场被挑战了
	//STRING_TYPE_BLOCKATTRIBS = 14,	// 玩家的块属性
	//STRING_TYPE_ARENADECISIVEPRIZE = 15,	// 决战之巅奖励结果"金钱,荣誉"
	//STRING_TYPE_PLANTINFO = 16,		// 植物信息
	//STRING_TYPE_ACTION_PLANT = 17,	// 种植植物
	//STRING_TYPE_ACTION_MATURE = 18,	// 植物成熟

	// 2000以上的由脚本处理
	STRING_TYPE_SCRIPTMSG   = 2000,
};
typedef struct 
{
	DWORD dwAct;
	char  szBuf[1];
}MSG_Info_String;
//==============================================

//==============================================
typedef struct // 这个消息结构变动 游服和NPC服务器必须同时变动
{		
	DWORD dwData; // s-c:服务端时间戳 ;; c-s:clienttime是客户端自己的时间，毫秒级
}MSG_Info_Tick;
//==============================================
typedef struct 
{	
	OBJID			id;
	NAMESTR			szName;			// 名字
	//NAMESTR			szMate;			// 配偶名字	
	//NAMESTR			szMaster;       // 师傅
	//	DWORD			dwMoney;		//身上的游戏币
	DWORD			dwMoney2;		//赠送的游戏币
	//	DWORD			dwMoney_saved;	//存储的游戏币
	//DWORD			dwEmoney;	    //充值的币
	DWORD			dwEmoney2;		//赠送的充值币
	UCHAR           ucProfession;   // 职业
	//UCHAR           ucSex;          // 1为男，2为女
	//	UCHAR           ucCountry;      // COUNTRY_WU  = 1, // 吴国COUNTRY_SHU = 2, // 蜀国COUNTRY_WEI = 3, // 魏国   
	UCHAR			ucLevel;		//等级
	UINT 			nExp;			//当前经验
	//int             nLife;
	int				nPower;			//by yht,当前体力值
	int				nEnergy;		//yht 当前精力值
	//int             nMana;
	//	int				nLifeBank;		//生命库
	//DWORD			dwOnlineTime;	// 当前总在线时长
	UCHAR			ucAdult;		// 0 未成年 1 成年
	//	DWORD			dwReiki;		// 灵气
	int				nGoddessLev;		//yht 当前女神值，
	int				nGoddessExp;		//女神经验
	int				nGoddessBeLovedTimes; //免费合体次数
	int				nEscortTimes;

}MSG_Info_UserInfo;
//==============================================
enum
{
	LOGINACT_ROLELIST = 1,         // s-c下发角色列表,dwData=角色数量，player依次保存dwData个PLAYER_INFO
	LOGINACT_LOGINGAME = 2,        // c-s登录游戏,dwData=idUser
	LOGINACT_REQDELROLE = 3,	   // c-s请求删除角色,dwData=要删除的角色ID
	// s-c请求删除角色返回，dwData=删除的角色ID，ucRet=删除结果0表示删除成功，>0不成功，dwTime=最后删除时间YYMMDDHHmm
	LOGINACT_RECOVERROLE = 4,	   // c-s恢复角色，dwData=要恢复的角色ID
	// s-c恢复角色返回,dwData=恢复的角色ID，ucRet=0表示恢复成功，=1表示角色数据已经被删除无法恢复
	LOGINACT_SERVERTIME = 5,	   // c-s 查询服务器时间
	// s-c服务器时间dwTime=服务端时间戳
	LOGINACT_ERROR_VERSION = 6,	   // s-c版本错误
};
struct PLAYER_INFO
{
	OBJID idUser;
	NAMESTR szName;
	UCHAR ucProf;
	UCHAR ucSex;
	UCHAR ucLev;
	OBJID idMap;
	OBJID idServer;
	OBJID idPlat;
};
struct NET_PLAYER_INFO
{
	OBJID idUser;
	NAMESTR szName;
	UCHAR ucProf;
	UCHAR ucSex;
	UCHAR ucLev;
	OBJID idMap;
};
typedef struct
{
	UCHAR           ucAction;
	DWORD			dwData;
	UCHAR 			ucRet;
	DWORD			dwTime;
	NET_PLAYER_INFO	player[1];
}MSG_Info_UserLogin;
//==============================================
//==============================================

#pragma pack(pop)

class CNetMsg
{
public:
	CNetMsg();
	virtual ~CNetMsg();
protected:
	OBJID		m_unMsgType;
	int			m_unMsgSize;
	char		m_bufMsg[_MAX_MSGSIZE];

	PROCESS_ID	m_idProcess;
	SOCKET_ID	m_idSocket;
	OBJID		m_idNpc;
public:
	virtual bool Create(char* pbufMsg, DWORD dwMsgSize);
	static CNetMsg* CreateMsg(OBJID idMsgType,char* pbufMsg, DWORD dwMsgSize);
	void	Init(void);
	OBJID   GetType(){return m_unMsgType;}
	static void	ReleaseMsgObjBuf();
	static char*   MsgObjBuf();
	virtual void Process	(void *pInfo){}; 
	virtual bool MsgInfo2CString	(void *pInfo){return true;};
	CString mMsgInfo;
	static char* m_pMsgObjBuf;
	
};

class CMsgTalk:public CNetMsg
{
public:
	CMsgTalk();
	virtual ~CMsgTalk();
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_Talk * pMsgInfo;
};

class CMsgTick:public CNetMsg
{
public:
	CMsgTick();
	virtual ~CMsgTick();
public:		
	//virtual void Process	(void *pInfo); 
	virtual bool MsgInfo2CString	(void *pInfo);
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	
	MSG_Info_Tick * pMsgInfo;
};

class CLogin:public CNetMsg
{
public:
	CLogin();
	virtual ~CLogin();
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_Login * pMsgInfo;
};
class CRegister:public CNetMsg
{
public:
	CRegister(){Init();};
	virtual ~CRegister(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_Register * pMsgInfo;
};
class CAction:public CNetMsg
{
public:
	CAction(){Init();};
	virtual ~CAction(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_Action * pMsgInfo;
};

class CBattle:public CNetMsg
{
public:
	CBattle(){Init();};
	virtual ~CBattle(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_Battle * pMsgInfo;
};

class CCommonNotify:public CNetMsg
{
public:
	CCommonNotify(){Init();};
	virtual ~CCommonNotify(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_CommonNotify * pMsgInfo;
};

class CConnect:public CNetMsg
{
public:
	CConnect(){Init();};
	virtual ~CConnect(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_Connect * pMsgInfo;
};

class CFightRole:public CNetMsg
{
public:
	CFightRole(){Init();};
	virtual ~CFightRole(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_FightRole * pMsgInfo;
};

class CItem:public CNetMsg
{
public:
	CItem(){Init();};
	virtual ~CItem(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	bool CString2MsgInfo(CString &csInput);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	bool  Create(OBJID id, int nAction, int nPosition /*= ITEMPOSITION_NONE*/);
	MSG_Info_Item * pMsgInfo;
};

class CItemInfo:public CNetMsg
{
public:
	CItemInfo(){Init();};
	virtual ~CItemInfo(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_ItemInfo * pMsgInfo;
};

class CMagicEffect:public CNetMsg
{
public:
	CMagicEffect(){Init();};
	virtual ~CMagicEffect(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_MagicEffect * pMsgInfo;
};
class CRoleAttrib:public CNetMsg
{
public:
	CRoleAttrib(){Init();};
	virtual ~CRoleAttrib(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_RoleAttrib * pMsgInfo;
};

class CInfoString:public CNetMsg
{
public:
	CInfoString(){Init();};
	virtual ~CInfoString(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_String * pMsgInfo;
};


class CUserInfo:public CNetMsg
{
public:
	CUserInfo(){Init();};
	virtual ~CUserInfo(){};
public:		
	bool MsgInfo2CString(void *pInfo);
	//void	Process	(void *pInfo){};
	bool	Create		(char* pMsgBuf, DWORD dwSize);
	MSG_Info_UserInfo * pMsgInfo;
};