#include "StdAfx.h"
#include "Config.h"
#include "Markup.h"

TCHAR Config::m_exeFullPath[MAX_PATH];
Config::Config(void)
{
}


Config::~Config(void)
{
}

BOOL     Config::LoadXMLFile(TCHAR *cfgfilename)
{
	if (!cfgfilename)
	{
		return FALSE;
	}
	if (lstrlen (cfgfilename) < 1)
	{
		return FALSE;
	}
	TCHAR szfilePath[MAX_PATH] = {0};
	_tcscpy(szfilePath, m_exeFullPath);
	_tcscat(szfilePath, _T("\\HsbVision.xml"));

	CMarkup XML;
	if ( XML.Load(szfilePath) ) 
	{
		XML.ResetPos();
		XML.FindElem(); //root
		XML.IntoElem();


		while( XML.FindElem( "Tools" ) ) 
		{
			HTEXTTOOLELEM  hToolText;
			strcpy(hToolText.tool_name, XML.GetAttrib("name"));
			while (XML.FindChildElem("item"))
			{
				TCHAR  sztemp[50];
				strcpy(sztemp,XML.GetChildAttrib("name") );
				hToolText.tool_item.push_back(sztemp);
			}
			g_hTextTool.push_back(hToolText);
		}
	}
	return TRUE;
}

BOOL		Config::LoadConfigFile()
{
	GetExePath(m_exeFullPath);
	LoadLightCfg();
	LoadXMLFile(m_exeFullPath);

	return TRUE;
}

BOOL    Config::LoadLightCfg()
{
	TCHAR szfilePath[MAX_PATH] = {0};
	_tcscpy(szfilePath, m_exeFullPath);
	_tcscat(szfilePath, _T("\\Light.ini"));
	LIGHT_INFO LightInfo;
	for (int i =1; i <3; i++)//////////////////////////////////////////////////////////////////////////最多支持3路12条光源
	{
		CHAR tAppName[20] ={0};
		CHAR tbuf[MAX_PATH] = {0};
		int nValue =0;
		wsprintf(tAppName, _T("LightControl%d"), i);
		GetPrivateProfileString(tAppName,_T("Com"), _T(""), tbuf, MAX_PATH,szfilePath);
		GetPrivateProfileInt(tAppName,_T("Com"), nValue, szfilePath);
		if (_tcslen(tbuf) <= 0)
		{
			break;
		}
		LightInfo.ncom = atoi(tbuf);
		GetPrivateProfileString(tAppName,_T("Baud"), _T(""), tbuf, MAX_PATH,szfilePath);
		if (_tcslen(tbuf)> 0)	LightInfo.nbaud = atoi(tbuf);

		GetPrivateProfileString(tAppName,_T("light1"), _T(""), tbuf, MAX_PATH,szfilePath);
		if (_tcslen(tbuf)> 0)	LightInfo.val1 = atoi(tbuf);

		GetPrivateProfileString(tAppName,_T("light2"), _T(""), tbuf, MAX_PATH,szfilePath);
		if (_tcslen(tbuf)> 0)	LightInfo.val2 = atoi(tbuf);

		GetPrivateProfileString(tAppName,_T("light3"), _T(""), tbuf, MAX_PATH,szfilePath);
		if (_tcslen(tbuf)> 0)	LightInfo.val3 = atoi(tbuf);

		GetPrivateProfileString(tAppName,_T("light4"), _T(""), tbuf, MAX_PATH,szfilePath);
		if (_tcslen(tbuf)> 0)	LightInfo.val4 = atoi(tbuf);
		g_LightInfo.push_back(LightInfo);
	}
	return TRUE;
}

BOOL  Config::SaveConfigFile()
{
	return TRUE;

}


