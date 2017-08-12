#pragma once
/*******************************************************************
* Copyright (C)  2016-2017 HSB Team. 
*All rights reserved.
* Model   Name： ImagePreProcessing.h 
* Function    ： 图像预处理
* Author      ： Willion
* Date Created： 2016年8月19日 
* Remark      ：
* 
*******************************************************************/
#include "chvision.h"
class H_DLL_EXPORT CImagePreProcessing :public CHVisionTool
{
public:
	CImagePreProcessing(void);
	~CImagePreProcessing(void);

	HObject   RGB2SingleChannel(int nChannel,bool bShow = true);
	BOOL  Emphasize();
};
