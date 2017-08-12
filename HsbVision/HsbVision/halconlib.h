#include "HalconCpp.h"
using namespace HalconCpp;

#ifdef DLL1_API
#else
#define DLL1_API extern "C" _declspec(dllimport)
#endif

DLL1_API int _stdcall Add(int a,int b);
DLL1_API HObject _stdcall OnLoadImage(HTuple  ImagePath);