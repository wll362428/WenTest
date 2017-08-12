#pragma once

/*******************************************************************
* Copyright (C)  2016-2017 HSB Team. 
*All rights reserved.
* Model   Name： CHVision.h 
* Function    ： 
* Author      ： Willion
* Date Created： 2016年8月19日 
* Remark      ： Halcon基类
* 
*******************************************************************/
#define DLL_EXPORT
#ifdef  DLL_EXPORT
#define H_DLL_EXPORT			__declspec(dllexport)
#else
#define H_DLL_EXPORT			__declspec(dllimport)
#endif



#include "HalconCpp.h"
using namespace HalconCpp;
extern "C" __declspec(dllimport)  void HLICancelDraw();


enum 
{
	s_OK=0,
	s_No_MODEL_ID,
};

class  CHBase
{
public:
	CHBase(void);
	~ CHBase(void);


public:
	void OnHException(HTuple hWindowHandle,HException &e);
	void CHBase::dev_display_shape_matching_results (HTuple hv_WindowHandle,  HTuple hv_ModelID, HTuple hv_Color, HTuple hv_Row, 
		HTuple hv_Column, HTuple hv_Angle, HTuple hv_ScaleR, HTuple hv_ScaleC, HTuple hv_Model);

	void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
};


class  H_DLL_EXPORT CHVisionWindow :public  CHBase
{
public:
	CHVisionWindow(void);
	~CHVisionWindow(void);

	enum ZoomType
	{
		ZoomIn=1,
		ZoomOut,
	};

	enum CursorType
	{
		arrow= 0,
		hand=1,
		zoomin,
		zoomout,
	};

	enum  DRAW_ROI
	{
		RECTANGLE1 = 1,//
		RECTANGLE2 ,//
		ELLIPSE ,//
		USER_DEFINE,//
		CANCEL,//取消绘制
	};

	enum REGION_SETS
	{
		UNION=1,
		INTERSECTION,
		DIFFERENCESET,
		SYMM_DIFFERENCE,
	};


public: 
	static  CHVisionWindow *GetInstance();

	void InitWindow(CRect  &rt,void*  hwnd);

	void ReadFile(CString strPath);

public:
// 	void OnHException(HException &e);

public:
	void  LoadImage(HString hFilePath);
	void  OnShowImage();
	void  ReSet();
	void  OnLButtonDown();
	void  OnMoveImage(CPoint &point);
	void  OnGetImageVal(CPoint &point,DWORD  *dCoord, DWORD *dGrayVal);

	void  ZoomImage(ZoomType  zoomtype);
	void  OnDrawRegion(DRAW_ROI  draw_type, REGION_SETS sets, HObject *hoRegion );
	void  ReDrawRegion(DRAW_ROI  draw_type);

	void  RePaint(HObject hImage);
	void  RePaint();
	void  ShowRegion(HObject hRegion, HTuple hColor="red", HTuple hDraw="margin");

	inline HTuple  GetWindowHandle();
	inline HObject GetSourceImage();
	inline HObject GetROI();
	inline HObject GetWndImage();



private:
		static CHVisionWindow*pInstance;//
		static HalconCpp::HWindow  m_Window;//
		static HObject  m_hoImage;//原始图像
		static HObject  m_hoWndImage;//
		static HObject m_hoRegion;//


private:
	CursorType  m_CursorType;
	CRect  m_rtImage;
	Hlong  m_hRowB,m_hColB,m_hRowE,m_hColE;
	Hlong m_hRow1;
	Hlong m_hCol1;
	Hlong m_hRow2;
	Hlong m_hCol2;
};


class  CHVisionTool :public  CHBase
{
public:
	enum HDATATYPE
	{
		IMAGE=0,
		REGION1,
		HTUPLE,
		MODEL_ID,
	};

	CHVisionTool(void);
	~ CHVisionTool(void);
	inline HTuple  GetWindowHandle(){return CHVisionWindow::GetInstance()->GetWindowHandle();}
	inline HObject GetSourceImage(){return  CHVisionWindow::GetInstance()->GetSourceImage();}
	inline HObject GetWndImage(){return  CHVisionWindow::GetInstance()->GetWndImage();}
	inline HObject GetROI(){return  CHVisionWindow::GetInstance()->GetROI();}


public:
	BOOL	Load(HDATATYPE eDataType,  HTuple hPath);

	BOOL	Save(HDATATYPE eDataType, HObject  hData,HTuple hPath);
	BOOL	Save(HDATATYPE  eDataType,HTuple hData,HTuple hPath);

	 
};
