#pragma once

/*
	��ʱ�Ķ��㴰�ڣ�������������رյ�ʱ����Ϊ����������ڣ�ʹ��������ر�����������
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
