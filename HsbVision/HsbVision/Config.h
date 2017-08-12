#pragma once

class Config
{
public:
	Config(void);
	~Config(void);



	static BOOL		LoadConfigFile( );
	static BOOL     LoadLightCfg();
	static  BOOL	SaveConfigFile();
	static BOOL     LoadXMLFile(TCHAR *cfgfilename);

private:
	static TCHAR  m_exeFullPath[MAX_PATH];
};