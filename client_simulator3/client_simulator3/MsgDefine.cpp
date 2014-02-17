

#include "stdafx.h"
#include "MsgDefine.h"

char* CNetMsg::m_pMsgObjBuf = NULL;
//////////////////////////////////////////////////////////////////////
char* CNetMsg::MsgObjBuf()
{	
	if (!m_pMsgObjBuf)
		m_pMsgObjBuf = new char [_MAX_MSGSIZE+500];

	return m_pMsgObjBuf;
}

void CNetMsg::ReleaseMsgObjBuf()
{
	if (m_pMsgObjBuf)
		delete [] m_pMsgObjBuf;
	m_pMsgObjBuf = NULL;
}

bool CNetMsg::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);

	return true;
}
CNetMsg* CNetMsg::CreateMsg(OBJID idMsgType,char* pbufMsg, DWORD dwMsgSize)
{
// make it...
	CNetMsg* pMsg	=NULL;
	switch(idMsgType)
	{
	case _MSG_TALK:
		pMsg    = _ConstructMsg CMsgTalk;
		break;

	case _MSG_TICK:
		pMsg    = _ConstructMsg CMsgTick;
		break;
	case _MSG_REGISTER:
		pMsg    = _ConstructMsg CRegister;
		break;
	case _MSG_USERLOGIN:
		pMsg    = _ConstructMsg CLogin;
		break;
	case _MSG_ACTION:
		pMsg    = _ConstructMsg CAction;
		break;
	case _MSG_BATTLE:
		pMsg    = _ConstructMsg CBattle;
		break;
	case _MSG_COMMON_NOTIFY:
		pMsg    = _ConstructMsg CCommonNotify;
		break;
	case _MSG_CONNECT:
		pMsg    = _ConstructMsg CConnect;
		break;
	case _MSG_FIGHTROLE_INFO:
		pMsg    = _ConstructMsg CFightRole;
		break;
	case _MSG_ITEM:
		pMsg    = _ConstructMsg CItem;
		break;
	case _MSG_ITEMINFO:
		pMsg    = _ConstructMsg CItemInfo;
		break;
	case _MSG_MAGICEFFECT:
		pMsg    = _ConstructMsg CMagicEffect;
		break;
	case _MSG_ROLEATTRIB:
		pMsg    = _ConstructMsg CRoleAttrib;
		break;
	case _MSG_STRING:
		pMsg    = _ConstructMsg CInfoString;
		break;
	case _MSG_USERINFO:
		pMsg    = _ConstructMsg CUserInfo;		
	default:
		//LOGERROR("�յ������mapgroupkernelû����ӵ�ָ��[%I64u]", idMsg);
		break;
	}
	return pMsg;
}

void CNetMsg::Init(void)
{
	memset(m_bufMsg, 0L, sizeof(m_bufMsg));
	m_unMsgSize	=0;
	m_unMsgType	=_MSG_NONE;
}
CNetMsg::CNetMsg()
{
	Init();
}

CNetMsg::~CNetMsg()
{

}
CMsgTalk::CMsgTalk()
{
	Init();
}

CMsgTalk::~CMsgTalk()
{

}
bool CMsgTalk::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_Talk *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("idSpeaker|%d,szSender|%s,szReceiver|%s,szBuf|%s"),pMsgInfo->idSpeaker,pMsgInfo->szReceiver,pMsgInfo->szReceiver,pMsgInfo->szBuf);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
bool CMsgTalk::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_TALK != this->GetType())
		return false;	

	return true;
}

CMsgTick::CMsgTick()
{
	Init();
}

CMsgTick::~CMsgTick()
{

}
bool CMsgTick::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_TICK != this->GetType())
		return false;	
	return true;
}

bool CMsgTick::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_Tick *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("dwData|%d"),pMsgInfo->dwData);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
CLogin::CLogin()
{

}
 CLogin::~CLogin()
 {

 }
bool CLogin:: MsgInfo2CString(void *pInfo)
{
	OBJID			idAccount;
	DWORD			dwData;
	char			szInfo[_MAX_NAMESIZE];
	int				nData;
	int				nData2;//id
	pMsgInfo = (MSG_Info_Login *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("idAccount|%I64d,dwData|%I32d,szInfo|%s,nData|%d,nData2|%d"),
			pMsgInfo->idAccount,
			pMsgInfo->dwData,
			pMsgInfo->szInfo,
			pMsgInfo->nData,
			pMsgInfo->nData2 );	
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
	
}
	//void	Process	(void *pInfo){};
bool CLogin::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_USERLOGIN != this->GetType())
		return false;	
	return true;
}

//////////////////////////////////////////////////////////
bool CAction::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_ACTION != this->GetType())
		return false;	
	return true;
}

bool CAction::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_Action *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("usAction|%I16d,idUser|%I64d,dwData1|%d,dwData2|%d,dwData3|%d,dwData4|%d,dwData5|%d,dwData6|%d"),
		pMsgInfo->usAction,
		pMsgInfo->idUser,
		pMsgInfo->dwData1,
		pMsgInfo->dwData2,
		pMsgInfo->dwData3,       
		pMsgInfo->dwData4,
		pMsgInfo->dwData5,
		pMsgInfo->dwData6);	
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CBattle::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_BATTLE != this->GetType())
		return false;	
	return true;
}

bool CBattle::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_Battle *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("ucBattleAct|%c,dwData1|%I64d,dwData2|%I64d,dwData3|%I64d")
		,pMsgInfo->ucBattleAct
		,pMsgInfo->dwData1
		,pMsgInfo->dwData2
		,pMsgInfo->dwData3);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CCommonNotify::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_TICK != this->GetType())
		return false;	
	return true;
}

bool CCommonNotify::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_CommonNotify *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("ucBattleAct|%I16d,dwData1|%d,dwData2|%d"),
		pMsgInfo->usAction,
		pMsgInfo->dwData1,
		pMsgInfo-> dwData2);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}

//======================================================
bool CConnect::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_CONNECT != this->GetType())
		return false;	
	return true;
}

bool CConnect::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_Connect *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("idAccount|%I64d,dwData|%d,szInfo|%s,nData|%d,nData2|%d"),
		pMsgInfo->idAccount,
		pMsgInfo->dwData,
		pMsgInfo->szInfo[_MAX_NAMESIZE],
		pMsgInfo->nData,
		pMsgInfo->nData2);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CFightRole::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_TICK != this->GetType())
		return false;	
	return true;
}

bool CFightRole::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_FightRole *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("ucType|%c,ucNum|%c,idObjType|%I64d,id|%I64d,ucPosition|%c,dwData|%d,szName|%s,nLife|%d,nMaxLife|%d,ucLev|%c,nFightPower|%d")
		,pMsgInfo-> ucType
		,pMsgInfo-> ucNum,
		pMsgInfo->roles[0]. idObjType,
		pMsgInfo->roles[0]. id,
		pMsgInfo->roles[0]. ucPosition,
		pMsgInfo->roles[0]. dwData,   // �������ͻ����佫������
		pMsgInfo->roles[0].  szName[_MAX_NAMESIZE],
		pMsgInfo->roles[0].   nLife,
		pMsgInfo->roles[0].   nMaxLife,		       
		pMsgInfo->roles[0]. ucLev,	// �ȼ�
		pMsgInfo->roles[0].   nFightPower);  // ս��    
		
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CInfoString::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_FIGHTROLE_INFO != this->GetType())
		return false;	
	return true;
}

bool CInfoString::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_String *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("dwAct|%d,szBuf|%s"),
		pMsgInfo->dwAct,
		pMsgInfo->szBuf[1]);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CItem::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_ITEM != this->GetType())
		return false;	
	return true;
}
bool CItem::Create(OBJID id, int nAction, int nPosition /*= ITEMPOSITION_NONE*/)
{
	//CHECKF(nAction);		// REPAIRALL ����Ҫ id && 

	// fill info now
	pMsgInfo = (MSG_Info_Item*)m_bufMsg;
	pMsgInfo->usAction	= (nAction);
	pMsgInfo->id			= (id);
	pMsgInfo->dwData		= (nPosition);

	m_unMsgType	=_MSG_ITEM;
	m_unMsgSize	=sizeof(MSG_Info_Item);

	return true;
}
bool CItem::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_Item *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("usAction|%d,id|%I64d,idTargetdw|%I64d,dwData|%I64d"),
		pMsgInfo->usAction,
		pMsgInfo->id,		
		pMsgInfo->idTarget,	// Ŀ�����ID��ID_NONE��ʾ�Լ�
		//yht ��32λ��Ϊ64λ
		pMsgInfo->dwData);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}

bool CItem::CString2MsgInfo(CString &csInput)
{
	CString sSubStr,szResult;

	int nPosBegin,nPosEnd;
	 nPosBegin=0;
	 nPosEnd =0;
	 nPosBegin = csInput.Find(_T("usAction="));
	 nPosBegin +=strlen("usAction=");
	 sSubStr = csInput.Mid(nPosBegin ,csInput.GetLength()-nPosBegin); 
	 nPosEnd =  sSubStr.Find(_T(","));
	 szResult = sSubStr.Mid(0,nPosEnd); 
	 USES_CONVERSION;
	 char* strResult = T2A(szResult);
	 USHORT idAction = atoi(strResult);
	 ///////////////////////////////
	  nPosBegin=0;
	 nPosEnd =0;

	 nPosBegin = csInput.Find(_T("id="));
	 nPosBegin +=strlen("id=");
	 sSubStr = csInput.Mid(nPosBegin ,csInput.GetLength()-nPosBegin); 
	 nPosEnd =  sSubStr.Find(_T(",")); 
	 szResult = sSubStr.Mid(0,nPosEnd);
	 strResult = T2A(szResult);
	 OBJID id = _atoi64(strResult);
	 ///////////////////////////////////////
	  nPosBegin=0;
	 nPosEnd =0;

	 nPosBegin = csInput.Find(_T("idTarget="));
	 nPosBegin +=strlen("idTarget=");
	 sSubStr = csInput.Mid(nPosBegin ,csInput.GetLength()-nPosBegin); 
	 nPosEnd =  sSubStr.Find(_T(","));
	 szResult = sSubStr.Mid(0,nPosEnd);
	 strResult = T2A(szResult);
	 OBJID idTarget = _atoi64(strResult);

	 ///////////////////////////////////////
	 nPosBegin=0;
	 nPosEnd =0;
	 nPosBegin = csInput.Find(_T("dwData="));
	 nPosBegin +=strlen("dwData=");
	 sSubStr = csInput.Mid(nPosBegin ,csInput.GetLength()-nPosBegin); 
	 nPosEnd =  sSubStr.Find(_T(","));
	 szResult = sSubStr.Mid(0,nPosEnd);
	 strResult = T2A(szResult);
	 OBJID dwData = _atoi64(strResult);
	
	 MSG_Info_Item msgInfo;
	 msgInfo.usAction = idAction;
	 msgInfo.id = id;
	 msgInfo.idTarget = idTarget;
	 msgInfo.dwData = dwData;

	 this->Create(id,idAction,dwData);

return true;
}
//======================================================
bool CItemInfo::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_ITEM != this->GetType())
		return false;	
	return true;
}

bool CItemInfo::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_ItemInfo *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("ucInfoAction|%c,id|%I64d,idOwner|%I64d,dwType|%d,usAmount|%d,ucPosition|%c,dwFlag|%d,dwTimeLimit|%d,dwLev|%d,dwExp|%d,dwAbsorbTimes|%d,dwRebornTimes|%d,dwAbility|%d,dwAdvanced_times|%d,dwAdvanced_points|%d,szBuf|%s")
		,pMsgInfo->		ucInfoAction  // ITEMINFO_ACT
		,pMsgInfo->		id	// iditem
		,pMsgInfo->       idOwner	//��ǰӵ����ID,������佫�����佫ID
		,pMsgInfo->		dwType			// item type id
		,pMsgInfo->		usAmount		// �������;�
		,pMsgInfo->ucPosition	     // λ��
		,pMsgInfo->       dwFlag	         // �����ǣ�������ʽ
		,pMsgInfo->		dwTimeLimit		// ����ʱ��(ʱ���)
		,pMsgInfo->		dwLev			// �ȼ�
		,pMsgInfo->	    dwExp		// ����
		,pMsgInfo->		dwAbsorbTimes		// ת������
		,pMsgInfo->		dwRebornTimes	
		,pMsgInfo->		dwAbility		//	ת�����õļ��ܣ�AAABBB��ʽ��AAAΪ�������Σ�BBBΪ���ܵȼ�
		,pMsgInfo->		dwAdvanced_times	//���׺�Ľ���
		,pMsgInfo->		dwAdvanced_points	//��õĽ��׵���
		//--------------------------------------
		,pMsgInfo->			szBuf[1]);		// ��������
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CMagicEffect::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_TICK != this->GetType())
		return false;	
	return true;
}

bool CMagicEffect::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_MagicEffect *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("dwData|%d"),pMsgInfo->idRole);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CRegister::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_MAGICEFFECT != this->GetType())
		return false;	
	return true;
}

bool CRegister::MsgInfo2CString(void *pInfo)
{
	//pMsgInfo = (MSG_Info_Register *)pInfo;
	//if (pMsgInfo)
	//{
	//	mMsgInfo.Format(_T("dwData|%d"),pMsgInfo->idAccount);
	//}
	//else
	//	mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CRoleAttrib::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_ROLEATTRIB != this->GetType())
		return false;	
	return true;
}

bool CRoleAttrib::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_RoleAttrib *)pInfo;
	if (pMsgInfo)
	{
		mMsgInfo.Format(_T("idRole|%I64d,ucNum|%d,nAttrib|%d,dwData|%d"),pMsgInfo->idRole,pMsgInfo->ucNum,pMsgInfo->attribs[0].nAttrib,pMsgInfo->attribs[0].dwData);

	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
//======================================================
bool CUserInfo::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	if(_MSG_USERINFO != this->GetType())
		return false;	
	return true;
}

bool CUserInfo::MsgInfo2CString(void *pInfo)
{
	pMsgInfo = (MSG_Info_UserInfo *)pInfo;
	if (pMsgInfo)
	{
	mMsgInfo.Format(_T(" id|%I64d;szName|%s;dwMoney2|%I32d,dwEmoney2|%I32d,ucProfession|%d,ucLevel|%d,nExp|%d,nPower|%d,nEnergy|%d,ucAdult|%c,nGoddessLev|%d,nGoddessExp|%d,nGoddessBeLovedTimes|%d,nEscortTimes|%d"),		//Ů����
	pMsgInfo->id,
	pMsgInfo->szName,			// ����
	pMsgInfo->dwMoney2,		//���͵���Ϸ��
	pMsgInfo->dwEmoney2,		//���͵ĳ�ֵ��
	pMsgInfo->ucProfession,   // ְҵ   
	pMsgInfo->ucLevel,		//�ȼ�
	pMsgInfo->nExp,			//��ǰ����
	pMsgInfo->nPower,			//by yht,��ǰ����ֵ
	pMsgInfo->nEnergy,		//yht ��ǰ����ֵ
	pMsgInfo->ucAdult,		// 0 δ���� 1 ����
	//	DWORD			dwReiki;		// ����
	pMsgInfo->nGoddessLev,		//yht ��ǰŮ��ֵ��
	pMsgInfo->nGoddessExp,		//Ů����
	pMsgInfo->nGoddessBeLovedTimes, //��Ѻ������
	pMsgInfo->nEscortTimes);
	}
	else
		mMsgInfo.Format(_T("Msg=None"));

	return true;
}
