#pragma once
// #include "Bo_Halcon.h"

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

typedef struct tagHTEXTTOOLELEM
{
	CHAR  tool_name[MAX_PATH];
	vector<string > tool_item;
} HTEXTTOOLELEM;

struct  LIGHT_INFO{
	WORD  ncom;
	WORD  nbaud;
	WORD  val1;
	WORD  val2;
	WORD  val3;
	WORD  val4;
	LIGHT_INFO()
	{
		ncom = 1;
		nbaud = 19200;
		val1 = val2 = val3 = val4 =0;
	}
};

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
extern UINT  g_nCXScreen;//屏幕宽度
extern UINT  g_nCYScreen;//屏幕高度
extern UINT  g_nCYTitle;//标题栏高度
extern UINT  g_nCYMenu;//菜单栏高度
extern UINT  g_nCYToolBar;//工具栏高度
extern UINT  g_nCYClient;//客户区高度

/*extern UINT  g_nCYClient;//客户区高度*/
extern CFont  *g_cFont[4];

extern   vector<LIGHT_INFO> g_LightInfo;
extern   vector<HTEXTTOOLELEM> g_hTextTool;
extern   CDialog  *m_pCaptureDlg;

// extern Bo_Halcon g_boHalcon;

//-----------------------------------------------------------------------------------------------------------------

extern int		g_nMaxEQ;
extern int		g_nMaxBALANCE  ;	//前后左右平衡范围
extern int		g_nMaxLOUNDNESS  ;	//前后左右平衡范围

extern UINT16	g_nCameraMirror;	//倒车镜像状态
extern DWORD	g_dwLangLCID;		//当前语言的LCID

//-----------------------------------------------------------------------------------------------------------------
//------------------------------------------ 主界面背景   ----------------------------------------------------------

enum	SKIN_TYPE { SKIN_0, SKIN_1,SKIN_2,SKIN_3,SKIN_4,SKIN_5,SKIN_6,SKIN_7,SKIN_8,SKIN_9,SKIN_ALL };
extern  int   g_nSkinIndex;

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//镜像类型
enum  MIRROR_TYPE { MIR_NONE,MIR_HOR,MIR_VER,MIR_H_V,MIR_ALL };


extern  UINT32		g_nEQType;			//当前选择的音效类型
extern  POINT		g_ptBalance;		//当前设置的音效平衡点

extern  int			g_ntreble;			//高音
extern  int			g_nbass;			//低音
extern  int			g_nloudness;		//响度
 
extern	BOOL		g_bNavVol;			//导航是否正在发声
extern  BOOL		g_bNavShow;			//导航界面是否在前台显示

extern  BOOL		g_bInEjectIng;		//按出碟后进入正在出碟状态

//最后退出DVD源的时间
extern DWORD		g_dwDvdEndTime;


//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//目前状态是默认所有源都认为存在，只有配置文件里定义了不存在时，APP才认为不存在
extern  BOOL		g_bNoDvd;
extern  BOOL		g_bNoMcuTV;
extern  BOOL		g_bNoAux1;
extern  BOOL		g_bNoAux2;
extern  BOOL		g_bNoCMMB;
extern  BOOL		g_bNoATV;


extern  BOOL		g_bSerialIpod;

//-----------------------------------------------------------------------------------------------------------------
#define COUNT_M_SRC			0x0B
extern  BYTE		g_SrcOrder[0x20];

extern	BYTE		g_bytModeCount;

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

enum SCREEN_SAVE_TYPE { SCN_TY_0,SCN_TY_15S,SCN_TY_30S,SCN_TY_1M,SCN_TY_3M,SCN_TY_5M,SCN_TY_ALL };
extern	BYTE		g_bytSSType;
extern	DWORD		g_dwLastMouseT;
extern  BOOL		g_bForbidScreenSave;

//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
extern	BYTE	g_bakSrcBefRds;
