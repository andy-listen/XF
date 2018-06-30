#include "stdafx.h"
#include "MainDialog.h"
#include "UIDef.h"
#include "WindowShadow.h"
#include "CEFBrowserUI.h"

CMainDialog::CMainDialog()
{

}

CMainDialog::~CMainDialog()
{

}

DuiLib::CDuiString CMainDialog::GetSkinFolder()
{
	return CDuiString(CPaintManagerUI::GetInstancePath()) + _T("Reg\\");
}

DuiLib::CDuiString CMainDialog::GetSkinFile()
{
	return _T("");
}

LPCTSTR CMainDialog::GetWindowClassName(void) const
{
	return _T("LoginWnd");
}

void CMainDialog::InitWindow()
{
}

void CMainDialog::OnFinalMessage(HWND hWnd)
{
	delete this;
}

void CMainDialog::Notify(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	
	__super::Notify(msg);
}

LRESULT CMainDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_CREATE:
		lRes = OnCreate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_CLOSE:
		lRes = OnClose(uMsg, wParam, lParam, bHandled);
		break;
	case WM_DESTROY:
		lRes = OnDestroy(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCACTIVATE:
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCCALCSIZE:
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCPAINT:
		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCHITTEST:
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SIZE:
		lRes = OnSize(uMsg, wParam, lParam, bHandled);
		break;
	case WM_GETMINMAXINFO:
		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SYSCOMMAND:
		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled);
		break;
	case WM_MOVE:
		lRes = OnMove(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SHOWWINDOW:
		lRes = OnVisibleChanged(uMsg, wParam, lParam, bHandled);
		break;
	case WM_KEYDOWN:
		lRes = OnKeyDown(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;

	lRes = HandleCustomMessage(uMsg, wParam, lParam, bHandled);
	if (bHandled) return lRes;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainDialog::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	LRESULT lRes = 0;

	return lRes;
}

LRESULT CMainDialog::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);


	m_PaintManager.Init(m_hWnd);

	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(MAIN_XML, (UINT)0, this, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");

	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);

	InitWindow();
	if (m_PaintManager.HasWindowShadow())
	{
		m_wShadow = new WindowShadow(m_hWnd);
		if (m_wShadow)
		{
			m_wShadow->Create(m_hWnd, _T("shadow"), WS_POPUP | WS_SYSMENU, 0 ^ WS_EX_NOACTIVATE ^ WS_EX_TOOLWINDOW);
			m_wShadow->ShowWindow(true, false);
		}
	}

	HINSTANCE  hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	return 0;
}

LRESULT CMainDialog::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_PaintManager.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0))
	{
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++;
		rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	if (m_wShadow != NULL && m_PaintManager.HasWindowShadow())
	{
		::SendMessage(m_wShadow->GetHWND(), WM_SIZE, wParam, lParam);
	}


	bHandled = FALSE;

	return 0;
}

LRESULT CMainDialog::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	
	bHandled = FALSE;
	return 0;
}

LRESULT CMainDialog::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed)
	{
		if (!bZoomed)
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(true);
		}
		else
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(false);
		}
	}
	return lRes;

}

LRESULT CMainDialog::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_PaintManager.HasWindowShadow() && m_wShadow != NULL && ::IsWindow(m_wShadow->GetHWND()))
	{
		RECT rcWnd = { 0 };
		::GetWindowRect(m_hWnd, &rcWnd);
		rcWnd.bottom += 7;
		rcWnd.left -= 5;
		rcWnd.right += 5;
		rcWnd.top -= 3;
		::SetWindowPos(*m_wShadow, m_hWnd, rcWnd.left, rcWnd.top, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top,
			SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
	}
	return 0;
}

LRESULT CMainDialog::OnVisibleChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_wShadow != NULL && m_PaintManager.HasWindowShadow())
	{
		::ShowWindow(m_wShadow->GetHWND(), wParam);
	}
	return 0;
}

DuiLib::CControlUI* CMainDialog::CreateControl(LPCTSTR pstrClass)
{
	if (_tcscmp(pstrClass, _T("CEFBrowser")) == 0)
	{
		return new CCEFBrowserUI();
	}
	return NULL;
}
