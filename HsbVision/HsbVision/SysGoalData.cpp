#include "stdafx.h"
#include "SysGoalData.h"

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
UINT  g_nCXScreen = 0;//屏幕宽度
UINT  g_nCYScreen = 0;//屏幕高度
UINT  g_nCYTitle;//标题栏高度
UINT  g_nCYMenu =22;//菜单栏高度
UINT  g_nCYToolBar = 56;//工具栏高度
UINT  g_nCYClient;//客户区高度
CFont  *g_cFont[4];
vector<LIGHT_INFO> g_LightInfo;
vector<HTEXTTOOLELEM> g_hTextTool;
CDialog  *m_pCaptureDlg;

// Bo_Halcon g_boHalcon;
//------------------------------------------------------------------------------------------------------------

int		g_nMaxEQ			= 28;			//EQ最大值
int		g_nMaxBALANCE		= 40;			//左右平衡范围
int		g_nMaxLOUNDNESS		= 19  ;			//前后左右平衡范围


DWORD	g_dwDvdEndTime		= 0;			//最后退出DVD源的时间
BOOL	g_bInEjectIng		= FALSE	;		//是否正在出碟中


UINT32	g_nEQType			= 0;
int		g_ntreble			= 0;			//高音
int		g_nbass				= 0;			//低音
int		g_nloudness			= 0;			//响度
POINT	g_ptBalance			= { 0,0 };		//当前设置的音效平衡点



BOOL		g_bNavVol		  = FALSE	; //导航是否正在发声
BOOL		g_bNavShow		  = FALSE	; //导航界面是否在前台显示


UINT16		g_nCameraMirror	  = MIR_NONE;	//倒车镜像状态
DWORD		g_dwLangLCID	  = 0X0409;		//当前语言的LCID


//------------------------------------------------------------------------------------------------------------
int					g_nSkinIndex = SKIN_1;

BOOL				g_bNoDvd	= FALSE;
BOOL				g_bNoMcuTV	= FALSE;
BOOL				g_bNoAux1	= FALSE;
BOOL				g_bNoAux2	= FALSE;
BOOL				g_bNoCMMB	= TRUE;
BOOL				g_bNoATV	= TRUE;


BOOL				g_bSerialIpod =  FALSE;


//------------------------------------------------------------------------------------------------------------
//SRC_CMMB,
//SRC_NAVIGATION
// BYTE	g_SrcOrder[0x20]		= {  SRC_RADIO,SRC_DISC,SRC_USB,SRC_USB_REAR,SRC_SD,SRC_BT,
// 										SRC_AUX_1,SRC_AUX_2,SRC_MCUTV,SRC_CMMB,SRC_IPOD ,0,0};

BYTE	g_bytModeCount				= 0x0;

//------------------------------------------------------------------------------------------------------------


BYTE		g_bytSSType		= SCN_TY_0;
DWORD		g_dwLastMouseT	= 0;
BOOL		g_bForbidScreenSave = FALSE;


//------------------------------------------------------------------------------------------------------------
// BYTE	g_bakSrcBefRds = SRC_OFF;
