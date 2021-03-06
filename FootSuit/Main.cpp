//FootSuit.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "include/cef_sandbox_win.h"
#include "CefClientApp.h"
#include "MainDialog.h"
#include "CefUtils.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//CEF 相关初始化
	HRESULT Hr = ::CoInitialize(NULL);
	::OleInitialize(NULL);
	if (FAILED(Hr)) return 0;
	
	CefEnableHighDPISupport();

	void* sandbox_info = NULL;
	CefMainArgs main_args(hInstance);

	CefRefPtr<CefCommandLine> command_line = CreateCommandLine(main_args);

	CefRefPtr<CefApp> app;
	switch (GetProcessType(command_line)) {
	case PROCESS_TYPE_BROWSER:
		app = new CCefClientBrowserApp();
		break;
	case PROCESS_TYPE_RENDERER:
		app = new CCefClientRendererApp();
		break;
	}
	int exit_code = CefExecuteProcess(main_args, app, sandbox_info);
	if (exit_code >= 0) {
		return exit_code;
	}
	// Initialize CEF.
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	CefInitialize(main_args, settings, app.get(), sandbox_info);


	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("Res"));
	//Duilib窗口
	CMainDialog* pMainFrame = new CMainDialog();
	if (NULL == pMainFrame) return -1;
	pMainFrame->Create(NULL, _T(FRAME_TITLE), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 0, 0);
	pMainFrame->CenterWindow();
	::ShowWindow(*pMainFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();


	::OleUninitialize();
	::CoUninitialize();
	CefShutdown();

	return 0;

	return 0;
}



