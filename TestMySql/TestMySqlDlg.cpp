
// TestMySqlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMySql.h"
#include "TestMySqlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestMySqlDlg 对话框




CTestMySqlDlg::CTestMySqlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestMySqlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestMySqlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestMySqlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestMySqlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestMySqlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestMySqlDlg 消息处理程序

BOOL CTestMySqlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestMySqlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestMySqlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestMySqlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestMySqlDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDatabase db;
	CString conn;
	//conn.Format(L"ODBC;DSN=mysql;UID=%s;PWD=%s","root","admin");
	conn = "ODBC;DSN=mysql;UID=root;PWD=admin";
	BOOL a=db.Open(NULL,FALSE,FALSE,conn);

	CRecordset cr;
	cr.m_pDatabase=&db;
	cr.Open(CRecordset::forwardOnly,_T("SELECT * FROM lundui_num01"));
	CDBVariant varValue;
	short nFields = cr.GetODBCFieldCount();
	while (!cr.IsEOF())
	{
		for (short index = 0; index<nFields;index++)
		{
			cr.GetFieldValue(index,varValue);
			TRACE("%f\n",varValue.m_dblVal);
		}
		cr.MoveNext();
	}

	cr.Close();
	db.Close();

// 	try
// 	{
// 		db.ExecuteSQL(
// 			_T("UPDATE Taxes ")
// 			_T("SET Rate = '36' ")
// 			_T("WHERE Name = 'Federal'"));
// 	}
// 	catch(CDBException* pe)
// 	{
// 		// The error code is in pe->m_nRetCode
// 
// 		pe->ReportError();
// 		pe->Delete();
// 	}

	
}


void CTestMySqlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	int totalSize = 0;
	char url[1024] = "http://www.baidu.com";

	CURL* handle = curl_easy_init();
	curl_easy_setopt(handle,CURLOPT_URL,url);
	curl_easy_setopt(handle,CURLOPT_HEADER,true);
	curl_easy_setopt(handle,CURLOPT_NOBODY,1L);
	curl_easy_setopt(handle,CURLOPT_TIMEOUT,3000);

	int return_code = curl_easy_perform(handle);

}
