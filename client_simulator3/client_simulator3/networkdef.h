#ifndef _NETWORKDEF_H
#define _NETWORKDEF_H



// max size define
const int _MAX_WORDSSIZE	=768;
const int _MAX_IDLETIME		=600;	// 600s idle time
const int	MSG_HEAD_SIZE		= 6;					// ��Ϣͷ�ĳߴ�
const int	RECV_BUFFER_SIZE	= 16*1024;				// Ӧ�ó����ڲ�BUFFER�ߴ硣


typedef	char	WORDSSTR[_MAX_WORDSSIZE];

// msg type define
const unsigned short _MSG_NONE			=0;
const unsigned short _MSG_GENERAL		=1000;
const unsigned short _MSG_REGISTER		=_MSG_GENERAL+1;
const unsigned short _MSG_NPCLOGIN		=_MSG_GENERAL+2;
const unsigned short _MSG_LOGOUT		=_MSG_GENERAL+3;
const unsigned short _MSG_TALK			=_MSG_GENERAL+4;
const unsigned short _MSG_WALK			=_MSG_GENERAL+5;
const unsigned short _MSG_USERINFO		=_MSG_GENERAL+6;
const unsigned short _MSG_MAGIC			=_MSG_GENERAL+7;
const unsigned short _MSG_MAGICINFO		=_MSG_GENERAL+8;
const unsigned short _MSG_ROLEATTRIB    =_MSG_GENERAL+9;
const unsigned short _MSG_ACTION		=_MSG_GENERAL+10;
const unsigned short _MSG_ITEMINFO      =_MSG_GENERAL+11;
const unsigned short _MSG_ITEM		    =_MSG_GENERAL+12;
const unsigned short _MSG_GOODS         =_MSG_GENERAL+13;
const unsigned short _MSG_PLAYER		=_MSG_GENERAL+14;
const unsigned short _MSG_DIALOG		=_MSG_GENERAL+15;
const unsigned short _MSG_PACKAGE       =_MSG_GENERAL+16;
const unsigned short _MSG_STATUS		=_MSG_GENERAL+17;
const unsigned short _MSG_TASK			=_MSG_GENERAL+18;
const unsigned short _MSG_TEAMLIST      =_MSG_GENERAL+19;
const unsigned short _MSG_TEAM			=_MSG_GENERAL+20;
const unsigned short _MSG_TEAMINFO	    =_MSG_GENERAL+21;
const unsigned short _MSG_CREATEMONSTER =_MSG_GENERAL+22;
const unsigned short _MSG_PLAYER2NPC	=_MSG_GENERAL+23;

const unsigned short _MSG_ARENALIST 	=_MSG_GENERAL+24;
const unsigned short _MSG_CHAPTERINFO	=_MSG_GENERAL+25;
const unsigned short _MSG_MAIL			=_MSG_GENERAL+26;
const unsigned short _MSG_MAILINFO		=_MSG_GENERAL+27;
const unsigned short _MSG_ACHIEVEINFO	=_MSG_GENERAL+28;
const unsigned short _MSG_ACHIEVE		=_MSG_GENERAL+29;
const unsigned short _MSG_PKMATCH		=_MSG_GENERAL+30;
const unsigned short _MSG_PKMATCHINFO	=_MSG_GENERAL+31;
const unsigned short _MSG_ARENARESULTLIST=_MSG_GENERAL+32;
const unsigned short _MSG_RANKLIST       =_MSG_GENERAL+33;

const unsigned short _MSG_MAGICEFFECT   =_MSG_GENERAL+40;

const unsigned short _MSG_CONNECT		=_MSG_GENERAL+52;
const unsigned short _MSG_USERLOGIN     =_MSG_GENERAL+53;
const unsigned short _MSG_FIGHTROLE_INFO=_MSG_GENERAL+60;
const unsigned short _MSG_BATTLE	    =_MSG_GENERAL+61;
//const unsigned short _MSG_LINEUP        =_MSG_GENERAL+62;
const unsigned short _MSG_PETINFO		=_MSG_GENERAL+63;
const unsigned short _MSG_PET			=_MSG_GENERAL+64;
const unsigned short _MSG_CLIENTCTRLBUF =_MSG_GENERAL+65;
const unsigned short _MSG_ANIMALSOUL    =_MSG_GENERAL+66;
const unsigned short _MSG_ANIMALSOULINFO=_MSG_GENERAL+67;
const unsigned short _MSG_TUISHEN		=_MSG_GENERAL+68;
//const unsigned short _MSG_ATTRIBGROW    =_MSG_GENERAL+64;
//const unsigned short _MSG_RIDING        =_MSG_GENERAL+65;
//const unsigned short _MSG_PRACTICELIST  =_MSG_GENERAL+68;
//const unsigned short _MSG_HANGUP        =_MSG_GENERAL+69;
//const unsigned short _MSG_BATTLEARRAY   =_MSG_GENERAL+70;
const unsigned short _MSG_STRING        =_MSG_GENERAL+71;
//const unsigned short _MSG_ARRAY         =_MSG_GENERAL+72;
const unsigned short _MSG_QUERYOTHER	=_MSG_GENERAL+73;
const unsigned short _MSG_FRIEND        =_MSG_GENERAL+74;
const unsigned short _MSG_FRIENDINFO    =_MSG_GENERAL+75;
const unsigned short _MSG_GANG          =_MSG_GENERAL+76;
const unsigned short _MSG_GANGINFO      =_MSG_GENERAL+77;
const unsigned short _MSG_GANGMEMBERLIST=_MSG_GENERAL+78;
//const unsigned short _MSG_MYSTERYSTORELIST = _MSG_GENERAL+79;
//const unsigned short _MSG_ROBWEALTHGOD  =_MSG_GENERAL+80;
//const unsigned short _MSG_ROBWEALTHGODLIST = _MSG_GENERAL+81;
//const unsigned short _MSG_GANGWARINFOLIST=_MSG_GENERAL+82;
//const unsigned short _MSG_GANGWAR		 =_MSG_GENERAL+83;
//const unsigned short _MSG_HANDLUCKYLIST  =_MSG_GENERAL+84;
//const unsigned short _MSG_ARENADOMAININFO=_MSG_GENERAL+85;
//const unsigned short _MSG_ARENADECISIVEINFO=_MSG_GENERAL+86;
//const unsigned short _MSG_ARENADOMAIN	 =_MSG_GENERAL+87;
//const unsigned short _MSG_ARENADECISIVE  =_MSG_GENERAL+88;
//const unsigned short _MSG_GEMSTONE		 =_MSG_GENERAL+89;
//const unsigned short _MSG_GEMSTONEINFO	 =_MSG_GENERAL+90;
//const unsigned short _MSG_USERHOME		 =_MSG_GENERAL+91;

const unsigned short _MSG_TICK          =_MSG_GENERAL+2004;
const unsigned short _MSG_WALKEX		=_MSG_GENERAL+2005;
const unsigned short _MSG_COMMON_NOTIFY =_MSG_GENERAL+2006;//ͨ��֪ͨ

// phpͨѶ
const unsigned short _MSG_PHP	= 10000;
const unsigned short _MSG_PHP_LOGINKET	=_MSG_PHP+1;	// ��¼��ȡ�ͻ���KEY
const unsigned short _MSG_CHARGE_NOTIFY	=_MSG_PHP+2;	// ��ֵ֪ͨ
const unsigned short _MSG_PHP_BROADCAST =_MSG_PHP+3;	// PHP����
const unsigned short _MSG_PHP_SENDMAIL  =_MSG_PHP+4;	// PHP���ʼ�֪ͨ
const unsigned short _MSG_PHP_KIKCOUT	=_MSG_PHP+5;	// PHP���������
const unsigned short _MSG_PHP_PRIZENOTIFY=_MSG_PHP+6;	// oss���½���֪ͨ
const unsigned short _MSG_PHP_FORBID_TALK=_MSG_PHP+7;   // ����
const unsigned short _MSG_PHP_MOBILE_CERTIFY = _MSG_PHP+8;	// �ֻ���֤
const unsigned short _MSG_PHP_COMMON_NOTIFY = _MSG_PHP+9;	// ͨ��֪ͨ
const unsigned short _MSG_PHP_USER_ADDICT_CHANGE = _MSG_PHP+10; //�޸ĸ��˳����־
const unsigned short _MSG_PHP_MODIFY_ADDICT_CHECK = _MSG_PHP+11; //�޸ķ����Լ��
const unsigned short _MSG_PHP_RELOADFORBIDTALKLEV = _MSG_PHP+12; //���¶�����ĵȼ�


const unsigned short _MSG_PHP_SAVEALL   =_MSG_PHP+ 10094;	// ������������
const unsigned short _MSG_PHP_RELOADOPENTIME=_MSG_PHP+10095;// ���¶��뿪��ʱ��
const unsigned short _MSG_PHP_RELOADSCRIPT = _MSG_PHP+10096;// ���¼��ؽű�
const unsigned short _MSG_PHP_TICK		= _MSG_PHP+10097;	// ����
const unsigned short _MSG_PHP_KICKOUTALL=_MSG_PHP+10098;	// �ߵ������������
const unsigned short _MSG_PHP_SHUTDOWN	=_MSG_PHP+10099;	// �ط�
const unsigned short _MSG_PHP_RELOADMERGETIME = _MSG_PHP+10100; // ���غϷ�ʱ��
const unsigned short _MSG_PHP_RELOADADDICKCHECK = _MSG_PHP+10101; //���ط����Լ��



// color define
const unsigned long	_COLOR_WHITE	=0x00ffffff;

// msg style define
const unsigned short _TXT_NORMAL	=0;        // ϵͳĬ������
const unsigned short _TXT_SCROLL	=0x0001;   // ������

// msg attribute define
const unsigned short _TXTATR_NORMAL		=2000;
const unsigned short _TXTATR_GLOBAL 	=_TXTATR_NORMAL;	// ����Ƶ��
const unsigned short _TXTATR_COUNTRY 	=_TXTATR_NORMAL+1;	// ����Ƶ��
//const unsigned short _TXTATR_ROOM       =_TXTATR_NORMAL+2;  // ��ǰƵ��
const unsigned short _TXTATR_TEAM       =_TXTATR_NORMAL+3;  // ����Ƶ��
const unsigned short _TXTATR_PRIVATE	=_TXTATR_NORMAL+4;	// ˽��Ƶ��
const unsigned short _TXTATR_GANG     	=_TXTATR_NORMAL+5;	// ����Ƶ��Ŀǰ���Ż�Ƶ��
const unsigned short _TXTATR_SPECIALGLOBAL=_TXTATR_NORMAL+6;	// ����Ƶ����ǧ�ﴫ����

const unsigned short _TXTATR_FIGHTINFO  =_TXTATR_NORMAL+7;			// ս����Ϣ
const unsigned short _TXTATR_SYSTEMTIPS =_TXTATR_NORMAL+8;			// ϵͳ��ʾ(�쳣��ʾ)
const unsigned short _TXTATR_SYSTEMBROADCAST =_TXTATR_NORMAL+9;		// ϵͳ��������
const unsigned short _TXTATR_USERINFO   =_TXTATR_NORMAL+10;			// ��ҹ�����Ϣ
const unsigned short _TXTATR_SPECAILUSERINFO   =_TXTATR_NORMAL+11;	// �����ҫ��Ϣ
const unsigned short _TXTATR_SYSTEMINFO = _TXTATR_NORMAL+12;        // ϵͳ��Ϣ
const unsigned short _TXTATR_ARENA		= _TXTATR_NORMAL+13;		// ������Ƶ��(��ʾ�ھ���������)

// ....... �뱣������ID


const unsigned short _TXTATR_DIALOG_BEGIN	=_TXTATR_NORMAL+500;	// �Ի����һ��
const unsigned short _TXTATR_DIALOG_UI_WARNING = _TXTATR_NORMAL+501;// �գɾ�ʾ��
// ... �м�ı�������֪ͨ�ͻ��˴򿪽���
const unsigned short _TXTATR_DIALOG_END		=_TXTATR_NORMAL+600;	// �Ի������һ�� + 1
#endif