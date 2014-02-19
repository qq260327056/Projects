// client_simulator3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_simulator3.h"
#include "client_simulator3Dlg.h"
#include "MsgDefine.h"

#include <iostream>
#include <fstream> 
#include <string>
#include   <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cclient_simulator3Dlg dialog


SOCKET  Cclient_simulator3Dlg::mSockClient =NULL;

CRichEditCtrl* Cclient_simulator3Dlg::m_pRichEditRecv =NULL;
CRichEditCtrl* Cclient_simulator3Dlg::m_pRichEditStatus =NULL;

void  Cclient_simulator3Dlg::RichEditAppendString(CRichEditCtrl* pRichEdit,CString strInput)
{
	if (pRichEdit)
	{
		pRichEdit->SetSel(-1, -1);
		pRichEdit->ReplaceSel(strInput);
		pRichEdit->SetSel(-1, -1);
		pRichEdit->ReplaceSel(CString("\n"));
	}
}
Cclient_simulator3Dlg::Cclient_simulator3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cclient_simulator3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cclient_simulator3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cclient_simulator3Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &Cclient_simulator3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(BUTTON_EXIT, &Cclient_simulator3Dlg::OnBnClickedExit)
	ON_BN_CLICKED(BUTTON_CONNECT, &Cclient_simulator3Dlg::OnBnClickedConnect)
	ON_BN_CLICKED(BUTTON_LOGIN, &Cclient_simulator3Dlg::OnBnClickedLogin)
	ON_BN_CLICKED(BUTTON_SENDMSG, &Cclient_simulator3Dlg::OnBnClickedSendmsg)
	

	ON_EN_CHANGE(RICH_RESULT, &Cclient_simulator3Dlg::OnEnChangeResult)
END_MESSAGE_MAP()


// Cclient_simulator3Dlg message handlers

BOOL Cclient_simulator3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pComboBoxIP = ((CComboBox*)GetDlgItem(COMB_SERVERIP));
	m_pComboBoxIP->AddString(_T("127.0.0.1")); 
	m_pComboBoxIP->SetCurSel(0);

	m_pEditPort  = ((CEdit*)GetDlgItem(EDIT_SERVERPORT));
	m_pEditPort->SetWindowText(_T("8080"));

	m_pEditPlatID = ((CEdit*)GetDlgItem(EDIT_PLATID));
	m_pEditPlatID->SetWindowText(_T("1"));

	m_pEditServerID = ((CEdit*)GetDlgItem(EDIT_SERVERID));
	m_pEditServerID->SetWindowText(_T("1"));

	m_pComboBoxAccount = ((CComboBox*)GetDlgItem(COMB_ACCOUNT));
	m_pComboBoxAccount->AddString(_T("maogq"));
	m_pComboBoxIP->SetCurSel(0);


	m_pEditMSGPARA = ((CEdit*)GetDlgItem(EDIT_MSGPARA));
	CRichEditCtrl* pRichEdit =(CRichEditCtrl*)GetDlgItem(RICH_RESULT);
	//pRichEdit->SetBackgroundColor(FALSE,RGB(0,0,0));

	CHARFORMAT mCharFormat;
	ZeroMemory(&mCharFormat, sizeof(CHARFORMAT));
	mCharFormat.cbSize = sizeof(CHARFORMAT);
	mCharFormat.dwMask = CFM_COLOR;
	mCharFormat.crTextColor = RGB(0,255,0);
	
	pRichEdit->SetDefaultCharFormat(mCharFormat);
	pRichEdit->SetBackgroundColor(FALSE,RGB(0,0,0));
	m_pRichEditRecv = pRichEdit;
	
	CFont font1;
	font1.CreateFont(16, 8, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("楷体_GB2312")); 

	m_pRichEditStatus = (CRichEditCtrl*)GetDlgItem(RICH_STATUS);
	m_pRichEditStatus->SetFont(&font1);


	ZeroMemory(&mcfRichEditStatus, sizeof(CHARFORMAT));
	mcfRichEditStatus.cbSize = sizeof(CHARFORMAT);
	mcfRichEditStatus.dwMask = CFM_COLOR;
	mcfRichEditStatus.crTextColor = RGB(0,0,0);



	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//NetWorkInit
	this->NetworkInit();
	this->mSockClient = NULL;
	//Recve Msg Thread
	CWinThread* pThreadRecv = AfxBeginThread(&Cclient_simulator3Dlg::RecMsg,&mSockClient);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cclient_simulator3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cclient_simulator3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cclient_simulator3Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
}

void Cclient_simulator3Dlg::OnBnClickedExit()
{
	this->NetworkDistroy();
	OnOK();
	// TODO: Add your control notification handler code here
}

bool Cclient_simulator3Dlg::Connect2Server(char* szIP, int nPort, int nServerID, int PlatID)
{

	if (mSockClient)
	{
		closesocket(mSockClient);
	
		RichEditAppendString(m_pRichEditStatus,CString("socket be closing..."));
	}
	
	mSockClient=socket(AF_INET,SOCK_STREAM,0);// AF_INET ..tcp连接 初始化连接与端口号
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr(szIP);//本机地址，服务器在本机开启
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons((u_short)nPort);// 设置端口号
	
	connect(mSockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//连接服务器
	RichEditAppendString(m_pRichEditStatus,CString("connecting..."));
	CString cstrTemp;
	cstrTemp.Format(_T("||Port =%d"),nPort);
	RichEditAppendString(m_pRichEditStatus,CString("IP = ") + CString(szIP) + cstrTemp);
	m_cEncryptSend.Init();//重置加密
	m_cEncryptRecv.Init();
	RichEditAppendString(m_pRichEditStatus,CString("m_cEncryptSend Init..."));
	return true;
}


bool Cclient_simulator3Dlg::NetworkInit()
{
	WORD wVersionRequested;
	WSADATA wsaData;//WSAata用来存储系统传回的关于WinSocket的资料。
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return false;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup( );
		return false;
	}
	m_cEncryptSend.Init();
	return true;
}

bool Cclient_simulator3Dlg::NetworkDistroy()
{
	WSACleanup();
	return true;
}
void Cclient_simulator3Dlg::OnBnClickedConnect()
{
	CString strIP;
	m_pComboBoxIP->GetWindowText(strIP);
		
	CString strPort;
	m_pEditPort->GetWindowText(strPort);

	CString strPlat;
	m_pEditPlatID->GetWindowText(strPlat);

	CString strServerID;
	m_pEditPlatID->GetWindowText(strServerID);


	USES_CONVERSION;
	char* szIP=T2A(strIP);
	char* szPort = T2A(strPort); 
	char* szPlat = T2A(strPlat);
	char* szServerID = T2A(strServerID);
	int nPort = atoi(szPort);
	int nPlat = atoi(szPlat);
	int nServerID = atoi(szServerID);
	
	Connect2Server(szIP,nPort,nPlat,nServerID);
}
bool Cclient_simulator3Dlg::UserLogin(LPSTR UserName)
{
	char sendBuf[MAX_PACKETSIZE];
	CProtocolMsgStruct* pSendbuf =(CProtocolMsgStruct*)sendBuf;

	pSendbuf->tagHead  = 0;
	pSendbuf->idPacket = _MSG_CONNECT;
	pSendbuf->nVersion = 11;
	pSendbuf->nMsgSize = 92;

	MSG_Info_Login* pNamebuf = (MSG_Info_Login*) pSendbuf->pMsg;
	pNamebuf->dwData = 0;
	pNamebuf->idAccount = 0;
	memcpy(pNamebuf->szInfo,UserName,strlen(UserName)+1);
	pNamebuf->nData =1;
	pNamebuf->nData2 =1;
	m_cEncryptSend.Encrypt((unsigned char*)sendBuf,92);
	
	if (SOCKET_ERROR == send(mSockClient,sendBuf,92,0))//发送登陆数据
	{
		return false;
	}
	
	m_cEncryptSend.ChangeCode(22646);
	return true;
}
void Cclient_simulator3Dlg::OnBnClickedLogin()
{
	

		CHARFORMAT mCharFormat;	
		ZeroMemory(&mCharFormat, sizeof(CHARFORMAT));
		mCharFormat.cbSize = sizeof(CHARFORMAT);
		mCharFormat.dwMask = CFM_COLOR;
		mCharFormat.crTextColor = RGB(0,255,0);	
		m_pRichEditStatus->LineScroll(m_pRichEditStatus->GetLineCount(),0);
	if (UserLogin("maogq"))
{
		m_pRichEditStatus->SetSelectionCharFormat(mCharFormat);//设置颜色	
		this->RichEditAppendString(m_pRichEditStatus,CString("Login Success!"));
	}

	else
	{
		mCharFormat.crTextColor = RGB(255,0,0);
		m_pRichEditStatus->SetSelectionCharFormat(mCharFormat);//设置颜色
		this->RichEditAppendString(m_pRichEditStatus,CString("Login Fail!"));

	}
		

	this->RichEditAppendString(m_pRichEditStatus,CString("--------------"));
	m_pRichEditStatus->SetSelectionCharFormat(mcfRichEditStatus);//设置颜色
	 
}
UINT  Cclient_simulator3Dlg::RecMsg(LPVOID pParam)
{
	char m_bufMsg[RECV_BUFFER_SIZE];
	//int ret=0;
	CString strTemp=_T("");
	CString strOut =_T("");

	char*  szBuf = NULL;
	OBJID idMsgType = 0;
	int ret = 0;
	using namespace std;
	fstream fMsgLog;
	fMsgLog.open(".\\log.txt");

	
	while(1)
	{
		strOut =_T("");
		ret = recv(mSockClient, m_bufMsg, RECV_BUFFER_SIZE , 0);
		if (ret>0)
		{
			m_cEncryptRecv.Encrypt((unsigned char*)m_bufMsg,ret);

			int j = 0;
			int i=0;
			while (ret>0)
			{
				int nSize = 0;
				SplitPacket(&m_bufMsg[i],ret,&idMsgType,&szBuf,&nSize);

				CNetMsg* pMsg = CNetMsg::CreateMsg( idMsgType, szBuf, nSize );
				if (pMsg)
				{
					pMsg->MsgInfo2CString(szBuf);
				}
				
				if (nSize == 0)
				{
					break;
				}
				strTemp.Format(_T("收到的消息类型为:  %I64d,大小为:  %d"),idMsgType,nSize);
				RichEditAppendString(m_pRichEditRecv,strTemp);
				if (pMsg)
				{
				RichEditAppendString(m_pRichEditRecv,pMsg->mMsgInfo);
				}
				fMsgLog<<strTemp<<endl;
				strOut = _T("");
				for (; i < j + nSize + 8 ; i++)
				{
					strTemp =_T("");
					strTemp.Format(_T("[%d=%02hhx]"),i,(unsigned char)m_bufMsg[i]);
					strOut+=strTemp;
					
				}
				j=i;
				fMsgLog<<strOut<<endl;
				//RichEditAppendString(m_pRichEditRecv,strOut);
				ret = ret - 8 - nSize;
			}

		}
	}
	return 0;
	
}
bool Cclient_simulator3Dlg::SendMsg()
{
	char sendBuf[MAX_PACKETSIZE];
	CProtocolMsgStruct* pSendbuf =(CProtocolMsgStruct*)sendBuf;

	pSendbuf->tagHead  = 0;
	pSendbuf->idPacket = _MSG_TALK;
	pSendbuf->nVersion = 11;
	pSendbuf->nMsgSize = 288;

	MSG_Info_Talk* pNamebuf = (MSG_Info_Talk*) pSendbuf->pMsg;
	pNamebuf->dwTime = 0;
	pNamebuf->dwWordsColor = 0;
	pNamebuf->idSpeaker =1000110000001;

	memcpy(pNamebuf->szSender,"maogqtest",sizeof("maogqtest"));
	memcpy(pNamebuf->szReceiver,"maogqtest",sizeof("maogqtest"));
	
	
	//memcpy(pNamebuf->szInfo,UserName,strlen(UserName)+1);
	CString temp;
	((CEdit*)GetDlgItem(EDIT_MSGPARA))->GetWindowText(temp);
	USES_CONVERSION;
	char* ctemp = T2A(temp);
	//memcpy((char*)pNamebuf->szBuf,(LPCTSTR)temp,3);
	//pNamebuf->szBuf=(LPSTR)(LPCTSTR)temp;
	//char* ctemp=(char*)(LPCTSTR)temp;
	strcpy_s(pNamebuf->szBuf,60,ctemp );
	m_cEncryptSend.Encrypt((unsigned char*)sendBuf,288);
	send(mSockClient,sendBuf,288,0);//发送对话数据
return true;
}
void Cclient_simulator3Dlg::OnBnClickedSendmsg()
{
	
	//SendMsg();

	CString temp;
	m_pEditMSGPARA->GetWindowText(temp);
	CItem itemTemp;
	itemTemp.CString2MsgInfo(temp);

	char sendBuf[MAX_PACKETSIZE];
	CProtocolMsgStruct* pSendbuf =(CProtocolMsgStruct*)sendBuf;

	pSendbuf->tagHead  = 0;
	pSendbuf->idPacket = _MSG_ITEM;
	pSendbuf->nVersion = 11;
	pSendbuf->nMsgSize = sizeof(MSG_Info_Item) + sizeof(CProtocolMsgStruct)-1;

    MSG_Info_Item* pNamebuf = (MSG_Info_Item*) pSendbuf->pMsg;

	memcpy(pNamebuf,itemTemp.pMsgInfo,sizeof(MSG_Info_Item));
	//SendMsg();
	m_cEncryptSend.Encrypt((unsigned char*)sendBuf,pSendbuf->nMsgSize );
	if (send(mSockClient,sendBuf,pSendbuf->nMsgSize ,0) == SOCKET_ERROR);//发送对话数据
	{
		this->RichEditAppendString(m_pRichEditStatus,CString("send message fail!"));
	}
	int errorcode = WSAGetLastError();
	CString temperror;
	temperror.Format(_T("error code  %d"),errorcode);
	this->RichEditAppendString(m_pRichEditStatus,temperror);
                 
}



void Cclient_simulator3Dlg::OnEnChangeResult()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
