#include "StdAfx.h"
#include "BlobIns.h"


CBlobIns::CBlobIns(void)
{
}


CBlobIns::~CBlobIns(void)
{
}


void CBlobIns::OnThreshold(HTuple MinGray, HTuple MaxGray,HTuple minArea)
{
	HObject ho_GrayReduced,ShapeModelImage,ShapeModelRegion;

 	if (GetWndImage().IsInitialized())
	{
		ReduceDomain(GetWndImage(),GetROI(),&ho_GrayReduced);
		Threshold(ho_GrayReduced, &ho_GrayReduced, MinGray, MaxGray);

		CHVisionWindow::GetInstance()->RePaint();
		CHVisionWindow::GetInstance()->ShowRegion(ShapeModelRegion);


	}
}
