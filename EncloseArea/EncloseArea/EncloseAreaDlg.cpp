
// EncloseAreaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EncloseArea.h"
#include "EncloseAreaDlg.h"
#include "afxdialogex.h"

#include "Line.h"
#include "Polyline.h"
#include "Point.h"
#include "Base.h"
#include <vector>
#include "InputAndOutput.h"
#include "ModalEntity.h"
#include "MinimumClosedArea.h"
using namespace std;


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


// CEncloseAreaDlg 对话框



CEncloseAreaDlg::CEncloseAreaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncloseAreaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncloseAreaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEncloseAreaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CEncloseAreaDlg::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_OPENDATA, &CEncloseAreaDlg::OnBnClickedButtonOpendata)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDATA, &CEncloseAreaDlg::OnBnClickedButtonSavedata)
	ON_BN_CLICKED(IDC_BUTTON_OPENMODAL, &CEncloseAreaDlg::OnBnClickedButtonOpenmodal)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CEncloseAreaDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CEncloseAreaDlg 消息处理程序

BOOL CEncloseAreaDlg::OnInitDialog()
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
	m_FilePath = '0';

	m_bFilePath = FALSE;

	CWnd* pOpenModal = GetDlgItem(IDC_BUTTON_OPENMODAL);
	pOpenModal->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEncloseAreaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEncloseAreaDlg::OnPaint()
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
HCURSOR CEncloseAreaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//导入线段和多段线
void CEncloseAreaDlg::OnBnClickedButtonInput()
{
	// TODO: 在此添加控件通知处理程序代码

	static TCHAR BASED_CODE szFilters[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("文本文件"), _T("*.txt"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (dlg.DoModal() == IDOK)
	{
		m_bFilePath = TRUE;  //标记已经导入数据

		CString FileName = dlg.GetFileName();
		//读取文档中的数据   
		CInputAndOutput output;
		char *filename =FileName.GetBuffer(FileName.GetLength());
		output.InputData(filename,Entity);
		
		FileName.ReleaseBuffer();
	}
	CWnd* pOpenModal = GetDlgItem(IDC_BUTTON_OPENMODAL);
	pOpenModal->EnableWindow(TRUE);
}

//打开模型数据
void CEncloseAreaDlg::OnBnClickedButtonOpendata()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bFilePath == FALSE)
	{
		MessageBox(_T("请您先导入数据!"));
		return;
	}
	UpdateData(); 
	CFile file;  
	file.Open(m_FilePath, CFile::modeWrite | CFile::modeCreate); 
	file.Close();  
}

//保存模型数据
void CEncloseAreaDlg::OnBnClickedButtonSavedata()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bFilePath == FALSE)
	{
		AfxMessageBox(_T("请您先导入数据!"));
		return;

	}

	static TCHAR BASED_CODE szFilters[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");

	CFileDialog FileDlg(FALSE, _T("txt"), m_FilePath); 
	FileDlg.m_ofn.lpstrTitle = _T("Save File");
	FileDlg.m_ofn.lpstrFilter = szFilters;

	if (IDOK == FileDlg.DoModal())
	{
		CFile File(FileDlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);

		char szBufData[100] = {"hello word!"};
		//写入文件内容,不包含/0
		File.Write(szBufData, strlen(szBufData));
		//立即写入，不缓冲
		File.Flush();
		//文件操作结束关闭
		File.Close();
	}

}

//在对话框中绘制出模型
void CEncloseAreaDlg::OnBnClickedButtonOpenmodal()
{
	// TODO: 在此添加控件通知处理程序代码

	CWnd *pwnd = GetDlgItem(IDC_STATIC_OPENMODAL);
	CDC *pDC = pwnd->GetDC();
	pwnd->Invalidate();
	pwnd->UpdateWindow();

	pDC->Rectangle(0, 0, 400, 400);

	CPen *ppenRed = new CPen;

	ppenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CGdiObject *pOldpen = pDC->SelectObject(ppenRed);

	//绘制直线
	int nLineNum = Entity.getLineNum();
	for (int i=0;i<nLineNum;i++)
	{
		CLine line = Entity.GetLine(i);
		line.draw(pDC);
	}

	//绘制多段线
	vector<CPolyline> PolylineVector = Entity.GetPolylineVector();
	for (unsigned int i = 0;i < PolylineVector.size(); i++)
	{
		PolylineVector[i].draw(pDC);
	}

}


void CEncloseAreaDlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pwnd = GetDlgItem(IDC_STATIC_TESTMODEL);
	CDC *pDC = pwnd->GetDC();
	pwnd->Invalidate();
	pwnd->UpdateWindow();
	pDC->Rectangle(0, 0, 380, 400);

	CPen *ppenRed = new CPen;
	ppenRed->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CGdiObject *pOldpen = pDC->SelectObject(ppenRed);

	//计算最小闭合区域
	CMinimumClosedArea ClosedArea;
	//1.得到全部线段集合
	vector<CLine> AllLineSegment =  ClosedArea.get_line(Entity.GetLineVector(),Entity.GetPolylineVector());
	Point crossPoint = ClosedArea.getcrosspoint(AllLineSegment[0],AllLineSegment[1]);
	//2.移除孤立的线段（两端的点都是孤立的）
	vector<CLine> nonisolatedLine = ClosedArea.remove_isolated_line(AllLineSegment);
 	//3.拆分所有的线段（就是将所有的相交线线段拆分开，得到新的线段集合S）
	vector<CLine> breaklines = ClosedArea.breaklines(nonisolatedLine);
	//4.移除一个端点孤立的线段（一个端点孤立的线段是不构成多边形的）
	vector<CLine> nonefieldlines = ClosedArea.removenonefieldlines(breaklines);
	for (unsigned int k = 0; k < nonefieldlines.size();k++ )
	{

		nonefieldlines[k].draw(pDC);
	}
/*
	vector<vector<CLine>> get_all_big_field = ClosedArea.get_all_big_field(nonefieldlines);

	//测试
	for (unsigned int i= 0;i<get_all_big_field.size();i++)
	{
		vector<CLine> lines;
		for (auto j = get_all_big_field[i].begin();j != get_all_big_field[i].end(); j++)
		{
			lines.push_back(*j);

		}
		//pDC->BeginPath();
		for (unsigned int k = 0; k < lines.size();k++ )
		{

			lines[k].draw(pDC);
		}
		pDC->EndPath();
		CRgn rgn;
		rgn.CreateFromPath(pDC);
		pDC->InvertRgn(&rgn);

		CBrush brush(RGB(100, 150, 200));
		CBrush *pBrush = pDC->SelectObject(&brush);
		pDC->FillRgn(&rgn,pBrush);


	}

*/

}
