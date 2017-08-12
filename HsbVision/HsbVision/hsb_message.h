
/***************************************************************************
      Funtion:hsb 通信消息定义 @wenlangliu
***************************************************************************/
static UINT NEAR WM_HSB_CLOSE =RegisterWindowMessage(_T("WM_HSB_CLOSE"));//系统关闭消息
static UINT NEAR WM_HSB_CLOSE_LOGIN= RegisterWindowMessage(_T("WM_HSB_CLOSE_LOGIN"));//关闭启动窗口
static UINT NEAR WM_HSB_CAPTURE =RegisterWindowMessage(_T("WM_HSB_CAPTURE"));//采集图像消息(软采集)
static UINT NEAR WM_HSB_CAPTURE_END =RegisterWindowMessage(_T("WM_HSB_CAPTURE_END"));//采集完成
static UINT NEAR WM_HSB_ALG_PROCESS_END =RegisterWindowMessage(_T("WM_HSB_ALG_PROCESS_END"));//算法处理完成

