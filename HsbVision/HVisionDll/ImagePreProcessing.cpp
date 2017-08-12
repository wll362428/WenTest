#include "StdAfx.h"
#include "ImagePreProcessing.h"


CImagePreProcessing::CImagePreProcessing(void)
{
}


CImagePreProcessing::~CImagePreProcessing(void)
{
}

HObject   CImagePreProcessing::RGB2SingleChannel(int nChannel,bool bShow )
{
	HObject  ho_GrayImage,ho_R,ho_G,ho_B, ho_H,ho_S,ho_V;
	HTuple hv_Channels;
	ho_GrayImage.GenEmptyObj();
	try
	{
		if (GetSourceImage().IsInitialized())
		{
			CountChannels(GetSourceImage(), &hv_Channels);
			if (hv_Channels.L() >1)
			{
				Decompose3(GetSourceImage(),&ho_R,&ho_G,&ho_B);
				TransFromRgb(ho_R,ho_G,ho_B, &ho_H,&ho_S,&ho_V,"hsv");
				switch(nChannel)
				{
				case 0:
					Rgb1ToGray(GetSourceImage(), &ho_GrayImage);
					break;
				case 1:
					ho_GrayImage = ho_R;
					break;
				case 2:
					ho_GrayImage = ho_G;
					break;
				case 3:
					ho_GrayImage = ho_B;
					break;
				case 4:
					ho_GrayImage = ho_H;
					break;
				case 5:
					ho_GrayImage = ho_S;
					break;
				case 6:
					ho_GrayImage = ho_V;
					break;
				}
				if (bShow)
				{
					CHVisionWindow::GetInstance()->RePaint(ho_GrayImage);
				}
			}
		}
	}
	catch(HException &e)
	{
		OnHException(GetWindowHandle(),e);
	}

	return ho_GrayImage;
}
