
// MdxfTextDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MdxfText.h"
#include "MdxfTextDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMdxfTextDlg 对话框



CMdxfTextDlg::CMdxfTextDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MDXFTEXT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMdxfTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMdxfTextDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMdxfTextDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CMdxfTextDlg 消息处理程序

BOOL CMdxfTextDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMdxfTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMdxfTextDlg::OnPaint()
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
HCURSOR CMdxfTextDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMdxfTextDlg::OnBnClickedButtonLoad()
{
	CString displayText;
	CString filter;
	CString fileFullStr, fileStr,foldername;
	filter = "AutoCad document(*.DXF)|*.dxf";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	dlg.m_ofn.lpstrTitle = _T("Crane Open Dxf file");
	if (dlg.DoModal() == IDOK)
	{
		displayText = "Start...";
		GetDlgItem(IDC_STATIC_Display2)->SetWindowTextW(displayText);
		fileFullStr = dlg.GetPathName();
		fileStr = dlg.GetFileName();
		foldername = fileFullStr.Left(fileFullStr.GetLength()- fileStr.GetLength());

#ifdef __DEBUG
		MessageBoxA(NULL, fileFullStr, "Open", MB_OK);
#endif
	}
	else
		return ;

	if (fileFullStr.GetLength() < 0)
		return ;
	fileFullStr.MakeUpper();
	//CString fileName = CStringToSTDStr(fileFullStr);
	if (fileFullStr.IsEmpty()) return;
	//定义一个新的文件变量m_pfile，CFile::modeRead以只读方式打开文件
	GetDlgItem(IDC_STATIC_Display)->SetWindowTextW(fileFullStr);

	CStdioFile m_pfile,m_newfile;
	CString newfilename;
	newfilename = "test.dxf";
	m_pfile.Open(fileFullStr, CFile::modeRead | CFile::typeText);
	m_newfile.Open(newfilename, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	CString m_strFileContent;
	CString str1,str2,str3;
	//CStidoFile提供了函数Readstring来读取文本
	while (m_pfile.ReadString(str1))
	{
		m_newfile.WriteString(str1 + "\n");
		if (str1 == "TEXT")
		{
			m_pfile.ReadString(str2);
			m_newfile.WriteString(str2 + "\n");
			str2.TrimLeft();
			str2.TrimRight();
			if (str2 == "8") {
				str3 = "20\n";
				m_newfile.WriteString(str3);
				m_pfile.ReadString(str3);//多读一行，但是不写
			}
			else {
				m_pfile.ReadString(str3);
				m_newfile.WriteString(str3+"\n");
			}
		}
		str1 = "";
		str2 = "";
	}
//	UpdateData(false);
	m_newfile.Flush();

	m_pfile.Close();
//	m_pfile.Remove(fileFullStr,NULL );
	//m_newfile.Rename(fileStr, NULL);
	m_newfile.Close();

	CFile hFile;
	int len;
	hFile.Open(newfilename, CFile::modeRead|CFile::typeBinary,NULL);
	len = hFile.GetLength();
	//分配缓冲区
	char* buf;
	buf = new char[len + 1];

	hFile.Read(buf, len); //读文件
	hFile.Close();

	//--------------------------------------------
	//只写|二进制|创建的方式打开第二个文件
	hFile.Open(fileFullStr, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate, 0);

	hFile.Write(buf, len);//写文件
	hFile.Close();

	delete[] buf;//释放缓冲区
//	m_newfile.Remove(fileFullStr, NULL);
	displayText = "Done.";
	GetDlgItem(IDC_STATIC_Display2)->SetWindowTextW(displayText);
}
