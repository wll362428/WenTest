/************************************************************
* Module:		CKBase.dll
* File:			CKBaseDefs.h
*************************************************************/
#ifndef _CK_BASE_DEF_H_
#define _CK_BASE_DEF_H_

// 导出/导入
#ifdef CKVISION_DLL
#define CKVISION_EXPORT __declspec(dllexport)
#else
#define CKVISION_EXPORT __declspec(dllimport)
#endif

/* API导出定义 */
#define CKVISION_API		CKVISION_EXPORT

/* CKVision dll 标识 */
#define	CKDll

/* 矩形相关定义 */
#define RECT_WIDTH(r)		(r.right-r.left)
#define RECT_HEIGHT(r)		(r.bottom-r.top)

/* 圆周率 */
#define PI					3.141592653589793//2384626433832795

/*
最大范围 
ROI (Region Of Interest),感兴趣区域,在图像处理中(图像压缩、旋转、变换等等),
对某些特定区域(根据特定的规则或方法确定)的简称,
就是在要待处理的图像中提取出的要处理的区域.
*/
#define MaxROI				_maxRect

/* 类型变更定义 */
#define Frame2D				FRAME2D

// 名称空间
namespace CKVision
{

/* 点 */
typedef struct tagIPNT 
{
	int		x;			// X
	int		y;			// Y
} IPNT;

/* 点 */
typedef struct tagDPNT
{
	double	x;			// X
	double	y;			// Y
} DPNT;

/* 线段 */
typedef struct tagDLINE
{
	DPNT	st;			// 起点
	DPNT	ed;			// 终点
} DLINE;

/* 矩形 */
typedef struct tagIRECT 
{
	int		left;		// 左边
	int		top;		// 上边
	int		right;		// 右边
	int		bottom;		// 下边
} IRECT;

/* 旋转矩形 */
typedef struct tagROTRECT
{
	DPNT	center;		// 中心
	double	width;		// 宽度
	double	height;		// 高度
	double	angle;		// 角度
} ROTRECT, RRECT;

/* 圆形 */
typedef struct tagCIRCLE 
{
	DPNT	center;		// 中心
	double	radius;		// 半径
} CIRCLE;

/* 圆环形 */
typedef struct tagRING 
{
	DPNT	center;		// 中心
	double	radius;		// 半径
	double	range;		// 半径范围
	double	angle;		// 角度
	double	sweep;		// 角度范围
} RING;

/* 椭圆形 */
typedef struct tagELLIPSE
{
	DPNT	center;		// 中心
	double	radiusX;	// 半径X
	double	radiusY;	// 半径Y
	double	angle;		// 角度
} ELLIPSE;

/* 2D坐标系框架 */
typedef struct tagFRAME2D
{
	DPNT	point;		// 原点
	double	angle;		// 角度
} FRAME2D;

const IRECT _maxRect = { 0, 0, 0x7FFFFFFF, 0x7FFFFFFF };

};	// End

#endif	// _CK_BASE_DEF_H_
