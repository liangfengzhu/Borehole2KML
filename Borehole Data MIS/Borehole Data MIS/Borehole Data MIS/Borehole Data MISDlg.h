
// Borehole Data MISDlg.h : header file
//

#pragma once
#include "adoconnect.h"
#include "structFile.h"
#include <vector>
using namespace std;

const double CONVERT = 9.0e-6;


UINT ThreadProcCreKML(LPVOID lpParam);//声明创建KML文件的子线程函数
struct ThreadInfo
{
	ADOConnect *readData;
	CString m_savePath;
	CString m_fileName;
	CString m_dataPath;
	float m_upHeight;
	bool connecFlag;
	float m_hirScale;
	float m_verScale;
	CProgressCtrl *prog;
	CStatic *pstTip;
	CStatic *percent;
	CButton *btn;
};


// CBoreholeDataMISDlg dialog
class CBoreholeDataMISDlg : public CDialogEx
{
// Construction
public:
	CBoreholeDataMISDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BOREHOLEDATAMIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedButtonSelectdatabase();
	afx_msg void OnBnClickedButtonSavepath();
	CString m_savePath;
	float m_upHeight;
	afx_msg void OnBnClickedButtonCreatekml();
	ADOConnect readData;
	bool connecFlag;
	CString m_dataPath;
	int m_count;
	float m_hirScale;
	float m_verScale;
	CString m_fileName;
	CProgressCtrl m_prog;
	CStatic m_stTip;
	CStatic m_percent;
	CButton m_btn;
};
