#include "StdAfx.h"
#include "CHVision.h"

double ImageZoomed = 1.0;//缺省倍率
#define  ZoomTimes  64.00//放大或缩小最大倍率

CHVisionWindow*CHVisionWindow::pInstance= new CHVisionWindow();
HalconCpp::HWindow CHVisionWindow::m_Window;
HObject  CHVisionWindow::m_hoImage;
HObject  CHVisionWindow::m_hoWndImage;
HObject  CHVisionWindow::m_hoRegion;

// Hlong  CHVisionWindow::m_hRow1 = 0;
// Hlong  CHVisionWindow::m_hCol1 = 0;
// Hlong  CHVisionWindow::m_hRow2 = 0;
// Hlong  CHVisionWindow::m_hCol2 = 0;

//

CHBase::CHBase(void)
{}

CHBase::~ CHBase(void)
{
	int i =0;
}

void CHBase::OnHException(HTuple hWindowHandle, HException &e)
{
	HTuple  hv_Exception;
	e.ToHTuple(&hv_Exception);

	disp_message(hWindowHandle, hv_Exception,  "window", 50, 12, "red", "true" );
	HTuple  hValue;
	e.GetExceptionData(hv_Exception, "program_line", &hValue);
	e.GetExceptionData(hv_Exception, "procedure", &hValue);
}

void CHBase::dev_display_shape_matching_results (HTuple hv_WindowHandle,  HTuple hv_ModelID, HTuple hv_Color, HTuple hv_Row, 
	HTuple hv_Column, HTuple hv_Angle, HTuple hv_ScaleR, HTuple hv_ScaleC, HTuple hv_Model)
{

	// Local iconic variables
	HObject  ho_ModelContours, ho_ContoursAffinTrans;

	// Local control variables
	HTuple  hv_NumMatches, hv_Index, hv_Match, hv_HomMat2DIdentity;
	HTuple  hv_HomMat2DScale, hv_HomMat2DRotate, hv_HomMat2DTranslate;

	//This procedure displays the results of Shape-Based Matching.
	//
	hv_NumMatches = hv_Row.TupleLength();
	if (0 != (hv_NumMatches>0))
	{
		if (0 != ((hv_ScaleR.TupleLength())==1))
		{
			TupleGenConst(hv_NumMatches, hv_ScaleR, &hv_ScaleR);
		}
		if (0 != ((hv_ScaleC.TupleLength())==1))
		{
			TupleGenConst(hv_NumMatches, hv_ScaleC, &hv_ScaleC);
		}
		if (0 != ((hv_Model.TupleLength())==0))
		{
			TupleGenConst(hv_NumMatches, 0, &hv_Model);
		}
		else if (0 != ((hv_Model.TupleLength())==1))
		{
			TupleGenConst(hv_NumMatches, hv_Model, &hv_Model);
		}
		{
			HTuple end_val15 = (hv_ModelID.TupleLength())-1;
			HTuple step_val15 = 1;
			for (hv_Index=0; hv_Index.Continue(end_val15, step_val15); hv_Index += step_val15)
			{
				GetShapeModelContours(&ho_ModelContours, HTuple(hv_ModelID[hv_Index]), 1);
				if (NULL != hv_WindowHandle)
					SetColor(hv_WindowHandle,HTuple(hv_Color[hv_Index%(hv_Color.TupleLength())]));
				{
					HTuple end_val18 = hv_NumMatches-1;
					HTuple step_val18 = 1;
					for (hv_Match=0; hv_Match.Continue(end_val18, step_val18); hv_Match += step_val18)
					{
						if (0 != (hv_Index==HTuple(hv_Model[hv_Match])))
						{
							HomMat2dIdentity(&hv_HomMat2DIdentity);
							HomMat2dScale(hv_HomMat2DIdentity, HTuple(hv_ScaleR[hv_Match]), HTuple(hv_ScaleC[hv_Match]), 
								0, 0, &hv_HomMat2DScale);
							HomMat2dRotate(hv_HomMat2DScale, HTuple(hv_Angle[hv_Match]), 0, 0, &hv_HomMat2DRotate);
							HomMat2dTranslate(hv_HomMat2DRotate, HTuple(hv_Row[hv_Match]), HTuple(hv_Column[hv_Match]), 
								&hv_HomMat2DTranslate);
							AffineTransContourXld(ho_ModelContours, &ho_ContoursAffinTrans, hv_HomMat2DTranslate);
							if (NULL != hv_WindowHandle)
								DispObj(ho_ContoursAffinTrans, hv_WindowHandle);
						}
					}
				}
			}
		}
	}
	return;
}

void CHBase::disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_Red, hv_Green, hv_Blue, hv_Row1Part;
	HTuple  hv_Column1Part, hv_Row2Part, hv_Column2Part, hv_RowWin;
	HTuple  hv_ColumnWin, hv_WidthWin, hv_HeightWin, hv_MaxAscent;
	HTuple  hv_MaxDescent, hv_MaxWidth, hv_MaxHeight, hv_R1;
	HTuple  hv_C1, hv_FactorRow, hv_FactorColumn, hv_UseShadow;
	HTuple  hv_ShadowColor, hv_Exception, hv_Width, hv_Index;
	HTuple  hv_Ascent, hv_Descent, hv_W, hv_H, hv_FrameHeight;
	HTuple  hv_FrameWidth, hv_R2, hv_C2, hv_DrawMode, hv_CurrentColor;
	//Prepare window
	GetRgb(hv_WindowHandle, &hv_Red, &hv_Green, &hv_Blue);
	GetPart(hv_WindowHandle, &hv_Row1Part, &hv_Column1Part, &hv_Row2Part, &hv_Column2Part);
	GetWindowExtents(hv_WindowHandle, &hv_RowWin, &hv_ColumnWin, &hv_WidthWin, &hv_HeightWin);
	SetPart(hv_WindowHandle, 0, 0, hv_HeightWin-1, hv_WidthWin-1);
	//
	//default settings
	if (0 != (hv_Row==-1))
	{
		hv_Row = 12;
	}
	if (0 != (hv_Column==-1))
	{
		hv_Column = 12;
	}
	if (0 != (hv_Color==HTuple()))
	{
		hv_Color = "";
	}
	//
	hv_String = ((""+hv_String)+"").TupleSplit("\n");
	//
	//Estimate extentions of text depending on font size.
	GetFontExtents(hv_WindowHandle, &hv_MaxAscent, &hv_MaxDescent, &hv_MaxWidth, &hv_MaxHeight);
	if (0 != (hv_CoordSystem==HTuple("window")))
	{
		hv_R1 = hv_Row;
		hv_C1 = hv_Column;
	}
	else
	{
		//Transform image to window coordinates
		hv_FactorRow = (1.*hv_HeightWin)/((hv_Row2Part-hv_Row1Part)+1);
		hv_FactorColumn = (1.*hv_WidthWin)/((hv_Column2Part-hv_Column1Part)+1);
		hv_R1 = ((hv_Row-hv_Row1Part)+0.5)*hv_FactorRow;
		hv_C1 = ((hv_Column-hv_Column1Part)+0.5)*hv_FactorColumn;
	}
	//
	//Display text box depending on text size
	hv_UseShadow = 1;
	hv_ShadowColor = "gray";
	if (0 != (HTuple(hv_Box[0])==HTuple("true")))
	{
		hv_Box[0] = "#fce9d4";
		hv_ShadowColor = "#f28d26";
	}
	if (0 != ((hv_Box.TupleLength())>1))
	{
		if (0 != (HTuple(hv_Box[1])==HTuple("true")))
		{
			//Use default ShadowColor set above
		}
		else if (0 != (HTuple(hv_Box[1])==HTuple("false")))
		{
			hv_UseShadow = 0;
		}
		else
		{
			hv_ShadowColor = ((const HTuple&)hv_Box)[1];
			//Valid color?
			try
			{
				SetColor(hv_WindowHandle, HTuple(hv_Box[1]));
			}
			// catch (Exception) 
			catch (HalconCpp::HException &HDevExpDefaultException)
			{
				HDevExpDefaultException.ToHTuple(&hv_Exception);
				hv_Exception = "Wrong value of control parameter Box[1] (must be a 'true', 'false', or a valid color string)";
				throw HalconCpp::HException(hv_Exception);
			}
		}
	}
	if (0 != (HTuple(hv_Box[0])!=HTuple("false")))
	{
		//Valid color?
		try
		{
			SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		}
		// catch (Exception) 
		catch (HalconCpp::HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			hv_Exception = "Wrong value of control parameter Box[0] (must be a 'true', 'false', or a valid color string)";
			throw HalconCpp::HException(hv_Exception);
		}
		//Calculate box extents
		hv_String = (" "+hv_String)+" ";
		hv_Width = HTuple();
		{
			HTuple end_val93 = (hv_String.TupleLength())-1;
			HTuple step_val93 = 1;
			for (hv_Index=0; hv_Index.Continue(end_val93, step_val93); hv_Index += step_val93)
			{
				GetStringExtents(hv_WindowHandle, HTuple(hv_String[hv_Index]), &hv_Ascent, 
					&hv_Descent, &hv_W, &hv_H);
				hv_Width = hv_Width.TupleConcat(hv_W);
			}
		}
		hv_FrameHeight = hv_MaxHeight*(hv_String.TupleLength());
		hv_FrameWidth = (HTuple(0).TupleConcat(hv_Width)).TupleMax();
		hv_R2 = hv_R1+hv_FrameHeight;
		hv_C2 = hv_C1+hv_FrameWidth;
		//Display rectangles
		GetDraw(hv_WindowHandle, &hv_DrawMode);
		SetDraw(hv_WindowHandle, "fill");
		//Set shadow color
		SetColor(hv_WindowHandle, hv_ShadowColor);
		if (0 != hv_UseShadow)
		{
			DispRectangle1(hv_WindowHandle, hv_R1+1, hv_C1+1, hv_R2+1, hv_C2+1);
		}
		//Set box color
		SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		DispRectangle1(hv_WindowHandle, hv_R1, hv_C1, hv_R2, hv_C2);
		SetDraw(hv_WindowHandle, hv_DrawMode);
	}
	//Write text.
	{
		HTuple end_val115 = (hv_String.TupleLength())-1;
		HTuple step_val115 = 1;
		for (hv_Index=0; hv_Index.Continue(end_val115, step_val115); hv_Index += step_val115)
		{
			hv_CurrentColor = ((const HTuple&)hv_Color)[hv_Index%(hv_Color.TupleLength())];
			if (0 != (HTuple(hv_CurrentColor!=HTuple("")).TupleAnd(hv_CurrentColor!=HTuple("auto"))))
			{
				SetColor(hv_WindowHandle, hv_CurrentColor);
			}
			else
			{
				SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
			}
			hv_Row = hv_R1+(hv_MaxHeight*hv_Index);
			SetTposition(hv_WindowHandle, hv_Row, hv_C1);
			WriteString(hv_WindowHandle, HTuple(hv_String[hv_Index]));
		}
	}
	//Reset changed window settings
	SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
	SetPart(hv_WindowHandle, hv_Row1Part, hv_Column1Part, hv_Row2Part, hv_Column2Part);
	return;
}


CHVisionTool::CHVisionTool(void)
{

}

CHVisionTool::~ CHVisionTool(void)
{
	int i =0;
}


BOOL	CHVisionTool::Load(HDATATYPE eDataType,  HTuple hPath)
{
	try
	{

	}
	catch(HException &e)
	{
		return FALSE;

	}
	return TRUE;
}

BOOL	CHVisionTool::Save(HDATATYPE eDataType, HObject  hData,HTuple hPath)
{

	try
	{
		switch(eDataType)
		{
		case CHVisionTool::IMAGE:
			WriteImage(hData,HTuple("jpeg"),0,hPath);
			break;
		case CHVisionTool::REGION1:
			WriteRegion(hData, hPath+HTuple(".hobj"));
		}
	}
	catch(HException &e)
	{
		return FALSE;
	}
	return TRUE;
}


BOOL	CHVisionTool::Save(HDATATYPE  eDataType,HTuple hData,HTuple hPath)
{
	try
	{
		switch(eDataType)
		{
		case  CHVisionTool::HTUPLE:
			WriteTuple(hData, hPath+HTuple( ".tup"));
			break;
		case CHVisionTool::MODEL_ID:
			WriteShapeModel(hData, hPath+HTuple(".shm"));
			break;
		}
	}
	catch(HException &e)
	{

		return FALSE;
	}
	return TRUE;
}

CHVisionWindow::CHVisionWindow(void)
{
	m_hRow1=m_hCol1=m_hRow2=m_hCol2=0;

	TRACE("CHVisionWindow~~\r\n");
}


CHVisionWindow::~CHVisionWindow(void)
{
}

CHVisionWindow *CHVisionWindow::GetInstance()
{
	return  pInstance;
}


inline HTuple   CHVisionWindow::GetWindowHandle()
{
	return m_Window.GetHandle();
}

 inline  HObject CHVisionWindow::GetSourceImage()
 {
	 return m_hoImage;
 }

 inline  HObject CHVisionWindow::GetWndImage()
 {
	 return m_hoWndImage;
 }

 inline  HObject CHVisionWindow::GetROI()
 {
	 return m_hoRegion;
 }

void CHVisionWindow::InitWindow(CRect  &rt, void*  hwnd)
{
	m_rtImage = rt;
	if (NULL != hwnd)
	{
// 		m_Window.CloseWindow();
	}
	SetWindowAttr("background_color","black");
	m_Window.OpenWindow(m_rtImage.top, m_rtImage.left, m_rtImage.Width(),m_rtImage.Height(), hwnd,"visible","");
}




void CHVisionWindow::ReadFile(CString strPath)
{
	AfxMessageBox(_T("CHVisionWindow"));
	/// 类方法函数的实现
}


void CHVisionWindow::OnLButtonDown()
{
	try
	{
		m_Window.GetMposition( &m_hRowB, &m_hColB, NULL);
	}
	catch(HException e)
	{
	}
}

void CHVisionWindow::OnGetImageVal(CPoint &point,DWORD  *dCoord, DWORD *dGrayVal)
{
	try
	{
		if (m_rtImage.PtInRect(point) && m_hoWndImage.IsInitialized())
		{
			HTuple GrayVal;
			m_Window.GetMposition( &m_hRowE, &m_hColE, NULL );
			GetGrayval(m_hoWndImage, m_hRowE, m_hColE, &GrayVal);
			*dCoord= MAKELONG(m_hRowE, m_hColE);
			int len = GrayVal.TupleLength();
			*dGrayVal = GrayVal[0].L();
			*dGrayVal |= (len << 24);
			for (int i = 1; i < GrayVal.TupleLength(); i++)//
			{
				*dGrayVal |= (GrayVal[i].L() << 8*i);
			}
		}
	}
	catch(HException &e)
	{
		OnHException( m_Window.GetHandle(), e);
	}
}


void CHVisionWindow::OnMoveImage(CPoint &point)
{
 		Hlong row1,col1,row2,col2 ;
 		try
 		{
//  			SetCheck("~give_error");
 			m_Window.GetMposition( &m_hRowE, &m_hColE,NULL );
 			double dbRowMove,dbColMove ;
 			double dbRowB,dbColB,dbRowE,dbColE ;
 			dbRowB = m_hRowB ;
 			dbRowE = m_hRowE ;
 			dbColB = m_hColB ;
 			dbColE = m_hColE ;
 			dbRowMove = -dbRowE + dbRowB ;
 			dbColMove = -dbColE + dbColB ;
 			m_Window.GetPart( &row1,&col1,&row2,&col2 ) ;
			m_hRow1 = row1+dbRowMove;
			m_hCol1 = col1+dbColMove;
			m_hRow2 = row2+dbRowMove;
			m_hCol2 = col2+dbColMove;

 			RePaint(m_hoWndImage);
 		}

 		catch(HException &e)
 		{
			OnHException( m_Window.GetHandle(), e);
 		}
}

void  CHVisionWindow::LoadImage(HString hFilePath)
{
	try
	{
		ReadImage(&m_hoImage,hFilePath );
		m_hRow1 = m_hCol1 = m_hRow2 = m_hCol2=0;
		RePaint(m_hoImage);
	}
	catch(HException &e)
	{
		OnHException( m_Window.GetHandle(), e);
	}
}

void CHVisionWindow::OnShowImage()
{
	m_Window.ClearWindow() ;
	HTuple Width, Height;
	GetImageSize(m_hoWndImage, &Width, &Height);
	m_Window.SetPart(0,0,Height,Width);
	m_Window.DispObj( m_hoWndImage ) ;
}

void CHVisionWindow::ReSet()//恢复默认值
{
	m_hRow1=m_hCol1=m_hRow2=m_hCol2=0;
	ImageZoomed=1.0;
	if (m_hoRegion.IsInitialized())
	{
		m_hoRegion.Clear();
	}
	RePaint(m_hoWndImage);
}


void  CHVisionWindow::ShowRegion(HObject hRegion, HTuple hColor, HTuple hDraw)
{
	m_Window.SetColor(hColor);
	m_Window.SetDraw(hDraw);
	m_Window.DispObj(hRegion);
}

void CHVisionWindow::RePaint()
{
	RePaint(m_hoWndImage);
}

void CHVisionWindow::RePaint(HObject hImage)
{
	try
	{
		if (hImage.IsInitialized())
		{
			SetSystem("flush_graphic", "false");
			m_Window.ClearWindow() ;
			if (0 == m_hRow2)
			{
				HTuple Width,Height;
				GetImageSize(hImage, &Width,&Height);
				m_hRow2 = Height.L();
				m_hCol2 = Width.L();
			}

			m_Window.SetPart(m_hRow1,m_hCol1,m_hRow2,m_hCol2);
			m_Window.DispObj( hImage ) ;
			m_hoWndImage = hImage;
			SetSystem("flush_graphic", "true");
			HObject emptyObject;
			emptyObject.GenEmptyObj();
			m_Window.DispObj(emptyObject);
		}
	}
	catch(HException e)
	{
		OnHException( m_Window.GetHandle(), e);
	}
}


void CHVisionWindow::ZoomImage(ZoomType zoomtype)
{
	Hlong Row, Col;
	Hlong Row0, Column0, Row00, Column00;
	HTuple ZoomTrans, RowShif, ColShif;
	HTuple   Ht, Wt;
	try
	{
		if (ZoomIn == zoomtype)
		{
			ZoomTrans = 1.1;
			if ( ImageZoomed >= ZoomTimes )			return ;
			else		ImageZoomed = ImageZoomed*ZoomTrans;
		}

		else if (ZoomOut == zoomtype)
		{
			ZoomTrans = 0.9;
			if ( ImageZoomed <=1.00*8/ZoomTimes)		return;
			else		ImageZoomed= ImageZoomed*ZoomTrans;
		}
		else 				ZoomTrans = 1.0;
// 		TRACE("%.4f\r\n", ImageZoomed);

		RowShif = ColShif = 0  ;
		m_Window.GetMposition( &Row, &Col, NULL );
		m_Window.GetPart( &Row0, &Column0, &Row00, &Column00);
		Ht = Row00-Row0;
		Wt = Column00-Column0;
		m_hRow1 = (Hlong)(Row0+((1-(1.0/ZoomTrans.D()))*(Row-Row0)))-(RowShif.D()/ZoomTrans.D());
		m_hCol1 = (Hlong)(Column0+((1-(1.0/ZoomTrans.D()))*(Col-Column0)))-(ColShif.D()/ZoomTrans.D());
		m_hRow2 = m_hRow1+(Hlong)(Ht.D()/ZoomTrans.D());
		m_hCol2 = m_hCol1+(Hlong)(Wt.D()/ZoomTrans.D());

		RePaint(m_hoWndImage);
	}
	catch(HException &e)
	{
		TRACE(" ZoomImage error \r\n");
		OnHException( m_Window.GetHandle(), e);
	}
}

void CHVisionWindow::OnDrawRegion(DRAW_ROI  draw_type, REGION_SETS sets, HObject *hoRegion )
{
	HObject hRegion ;
	m_Window.SetColor("red");
	m_Window.SetDraw("margin");
	GenEmptyRegion(&hRegion);
	switch (draw_type)
	{
	case RECTANGLE1:
		{
			double row1,col1,row2,col2;
			m_Window.DrawRectangle1(&row1,&col1,&row2,&col2);
			GenRectangle1(&hRegion, row1,col1,row2,col2);
		}
		break;
	case RECTANGLE2:
		{
			double row1,col1,phi,len1,len2;
			m_Window.DrawRectangle2( &row1,&col1, &phi, &len1, &len2);
			GenRectangle2(&hRegion,row1,col1,phi,len1,len2);
			break;

		}
	case ELLIPSE:
		{
			double row1,col1,phi,radius1,radius2;
			m_Window.DrawEllipse(&row1,&col1,&phi,&radius1,&radius2);
			GenEllipse( &hRegion, row1,col1,phi,radius1,radius2);
		}
		break;
	case USER_DEFINE:
		{
			DrawRegion(&hRegion, m_Window);
		}
		break;
	case CANCEL:
		{
		}
		break;
	}

	if (!m_hoRegion.IsInitialized())	m_hoRegion.GenEmptyObj();

	switch (sets)
	{
	case UNION:
		Union2(m_hoRegion, hRegion, &m_hoRegion);
		break;
	case INTERSECTION:
		Intersection(m_hoRegion, hRegion, &m_hoRegion);
		break;
	case DIFFERENCESET:
		Difference(m_hoRegion, hRegion, &m_hoRegion);
		break;
	case SYMM_DIFFERENCE:
		SymmDifference(m_hoRegion, hRegion, &m_hoRegion);
		break;
	}

	RePaint(m_hoWndImage);
	m_Window.DispRegion(m_hoRegion);
}


void  CHVisionWindow::ReDrawRegion(DRAW_ROI  draw_type)
{
	HTuple row1,col1,row2,col2;
	HTuple DrawID;
	SmallestRectangle1(m_hoRegion, &row1,&col1,&row2,&col2);

	switch (draw_type)
	{
	case RECTANGLE1:
		{
			CreateDrawingObjectRectangle1(row1,col1,row2,col2, &DrawID);
			SetDrawingObjectParams(DrawID, "color", "red");
			AttachDrawingObjectToWindow(m_Window, DrawID);
			AttachBackgroundToWindow(m_hoWndImage,m_Window);
		}
		break;
	case RECTANGLE2:
		{

		}
		break;

	}
}