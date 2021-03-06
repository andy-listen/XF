// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 在此处引用程序需要的其他头文件


#include "UIDef.h"
#include "include/cef_app.h"

#include "..\DuiLib\UIlib.h"
using namespace DuiLib;
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif


//定义在DUILIB 消息循环中需要处理的浏览器事件。
#define  CEF_ON_LOAD_START			WM_USER+100
#define  CEF_ON_LOAD_END			WM_USER+101
#define  CEF_ON_BEFORE_POPUP		WM_USER+102
#define  CEF_ON_TITLE_CHANGE		WM_USER+103
#define  CEF_ON_URL_CHANGE			WM_USER+104
#define  CEF_ON_ICON_CHANGE			WM_USER+105
#define  CEF_ON_AFETER_CREATE		WM_USER+106
#define  CEF_ON_BEFORE_CLOSE		WM_USER+107
#define  CEF_ON_LOGIN_SUCCESS		WM_USER+108
#define  CEF_DO_CLOSE				WM_USER+109
#define	 SOME_JS_CALL_BACK_MSG		WM_USER+110