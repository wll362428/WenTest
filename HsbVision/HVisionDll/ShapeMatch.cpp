#include "StdAfx.h"
#include "ShapeMatch.h"

HTuple  CShapeMatch::m_hvmodelID;
CShapeMatch::CShapeMatch(void)
{
}


CShapeMatch::~CShapeMatch(void)
{
	int i =0;
	m_hvmodelID.Clear();
}


void CShapeMatch::OnSetMincontrast(HTuple hLow, HTuple hHigh, HTuple hMod)
{
	HObject ho_Reduced,ShapeModelImage,ShapeModelRegion;
	try
	{
		if (GetWndImage().IsInitialized())
		{
			ReduceDomain(GetWndImage(),GetROI(),&ho_Reduced);
			InspectShapeModel (ho_Reduced, &ShapeModelImage, &ShapeModelRegion, 1, ( (hLow.Append(hHigh)).Append(hMod) )    );

			CHVisionWindow::GetInstance()->RePaint();
			CHVisionWindow::GetInstance()->ShowRegion(ShapeModelRegion);
		}
	}
	catch(HException &e)
	{
		OnHException(GetWindowHandle(), e);
	}
}

HTuple   CShapeMatch::CreateShape(HTuple hLow, HTuple hHigh, HTuple hMod)
{
	HObject ho_Reduced,ModelContours,ShapeModelRegion;
	HTuple hv_ModelID;
	try
	{
		if (GetWndImage().IsInitialized())
		{
			ReduceDomain(GetWndImage(),GetROI(),&ho_Reduced);
			CreateShapeModel(ho_Reduced, "auto",  -(HTuple(30).TupleRad()), HTuple(30).TupleRad(), "auto", "auto", "use_polarity",   (hLow.Append(hHigh)).Append(hMod)  ,3,&hv_ModelID);
			GetShapeModelContours( &ModelContours,hv_ModelID,1 );
		}
	}
	catch(HException &e)
	{
		OnHException(GetWindowHandle(), e);
	}

	return hv_ModelID;
}


BOOL CShapeMatch::OnSave(HTuple hPath)
{

	return Save(CHVisionTool::MODEL_ID, m_hvmodelID,hPath);

}

BOOL CShapeMatch::Run( HTuple hModelId, HTuple hScore, HTuple hName, bool bReverse)
{
	BOOL bRet = TRUE;
	HTuple hRow, hCol, hPhi, hMatchScore;
	try
	{
		if (hModelId.TupleLength() > 0)
		{
			HObject ho_Reduced,ModelContours,ShapeModelRegion;
			if (GetWndImage().IsInitialized())
			{
				FindShapeModel(GetWndImage(), hModelId,  -(HTuple(30).TupleRad()), HTuple(30).TupleRad(), hScore,1,0.5, "least_squares", 0, 0.6, &hRow, &hCol, &hPhi, &hMatchScore );
// 				m_hvmodelID= hModelId.Clone();
			
				if (hMatchScore.TupleLength()> 0)
				{
					dev_display_shape_matching_results(GetWindowHandle(), hModelId,"green", hRow, hCol, hPhi,1,1,0);
				}
				ClearShapeModel(hModelId);
			}
		}
	}

	catch(HException e)
	{
		bRet = FALSE;
		OnHException(GetWindowHandle(), e);
	}

	return bRet;
}

