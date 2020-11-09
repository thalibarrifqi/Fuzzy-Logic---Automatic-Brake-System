
// Fuzzy LogicDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "tchart1.h"


// CFuzzyLogicDlg dialog
class CFuzzyLogicDlg : public CDialogEx
{
// Construction
public:
	CFuzzyLogicDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FUZZYLOGIC_DIALOG };

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
//	CEdit m_InputDistance;
//	CEdit m_InputSpeed;
//	float m_OutputBrake;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit3();
//	CTchart1 m_Far;
	CTchart1 m_chartDistance;
	CTchart1 m_chartSpeed;
	CTchart1 m_chartOutput;
//	int m_InputDistance;
//	int m_InputSpeed;
	float triangle(float x, float a, float b, float c, float result);
	CString m_uSpeed;
//	CString m_inDist;
//	CString m_inSpeed;
	int m_inSpeed;
	int m_inDist;
	CString m_uDist;
	afx_msg void OnBnClickedButton2();
	CString m_ruleTable;
	CString m_MaxUtable;
	CTchart1 m_chartBrake;
	afx_msg void OnBnClickedButton3();
	CString m_OutputCOG;
	float trapezoidLeft(float x, float c, float d);
	float trapezoidCenter(float x, float a, float b, float c, float d);
	float trapezoidRight(float x, float a, float b);
	afx_msg void OnBnClickedButton4();
};
