
// EncloseAreaDlg.h : 头文件
//

#pragma once

#include "Line.h"
#include "Polyline.h"
#include "Point.h"
#include <vector>
#include "ModalEntity.h"
using namespace std;

// CEncloseAreaDlg 对话框
class CEncloseAreaDlg : public CDialogEx
{
// 构造
public:
	CEncloseAreaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ENCLOSEAREA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnBnClickedButtonOpendata();
	afx_msg void OnBnClickedButtonSavedata();

private:
	CString m_FilePath;
	//CString m_FileName;
	BOOL m_bFilePath;
	//CLine m_line;
	//vector<CLine> m_LineVector;
	//vector<vector<Point>> m_PolylineVector;
	CModalEntity Entity;
public:
	afx_msg void OnBnClickedButtonOpenmodal();
	afx_msg void OnBnClickedButtonTest();
};
