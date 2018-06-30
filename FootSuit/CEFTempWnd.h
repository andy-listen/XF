#pragma once

/*
	临时的顶层窗口，用来在浏览器关闭的时候作为浏览器父窗口，使得浏览器关闭流程完整。
*/
class CCEFTempWnd : public CWindowWnd
{
public:
	CCEFTempWnd();
	~CCEFTempWnd();

public:
	void Init();

public:
	LPCTSTR GetWindowClassName() const;
};
