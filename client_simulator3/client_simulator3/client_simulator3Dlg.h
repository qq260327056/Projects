// client_simulator3Dlg.h : header file
//

#pragma once

#include "EncryptServer.h"
#include "protocol.h"

#include "networkdef.h"

// Cclient_simulator3Dlg dialog
class Cclient_simulator3Dlg : public CDialog
{
// Construction
public:
	Cclient_simulator3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_SIMULATOR3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	bool Connect2Server(LPSTR szIP, int nPort, int nServerID, int PlatID);
	bool NetworkInit();
	bool NetworkDistroy();
	bool UserLogin(LPSTR UserName);
	bool SendMsg();
	static UINT  RecMsg(LPVOID pParam);
	//static UnPackMsg(LPSTR MsgPacket);
	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedSendmsg();

	static SOCKET mSockClient;
	static CRichEditCtrl* m_pRichEditRecv;
	static CRichEditCtrl* m_pRichEditStatus;
	
	CComboBox* m_pComboBoxIP;
	CComboBox* m_pComboBoxAccount;
	CEdit*     m_pEditPort;
	CEdit*     m_pEditPlatID;
	CEdit*     m_pEditServerID;
	CEdit*		m_pEditMSGPARA;
	CHARFORMAT mcfRichEditStatus;
	static void RichEditAppendString(CRichEditCtrl* pRichEdit,CString strInput);
	
	afx_msg void OnEnChangeResult();
};
typedef	CEncryptServer<LOGIN_KEY1, LOGIN_KEY2>	EncryptServer;
 static EncryptServer m_cEncryptRecv, m_cEncryptSend;