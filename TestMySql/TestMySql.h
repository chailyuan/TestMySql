
// TestMySql.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestMySqlApp:
// �йش����ʵ�֣������ TestMySql.cpp
//

class CTestMySqlApp : public CWinApp
{
public:
	CTestMySqlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestMySqlApp theApp;