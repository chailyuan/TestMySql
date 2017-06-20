
// TestMySqlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestMySql.h"
#include "TestMySqlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestMySqlDlg �Ի���




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


// CTestMySqlDlg ��Ϣ�������

BOOL CTestMySqlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestMySqlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestMySqlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestMySqlDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int totalSize = 0;
	char url[1024] = "http://www.baidu.com";

	CURL* handle = curl_easy_init();
	curl_easy_setopt(handle,CURLOPT_URL,url);
	curl_easy_setopt(handle,CURLOPT_HEADER,true);
	curl_easy_setopt(handle,CURLOPT_NOBODY,1L);
	curl_easy_setopt(handle,CURLOPT_TIMEOUT,3000);

	int return_code = curl_easy_perform(handle);

}
