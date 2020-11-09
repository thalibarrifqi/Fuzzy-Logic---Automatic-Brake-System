
// Fuzzy LogicDlg.cpp : implementation file
// Akhmad Thalibar Rifqi

#include "stdafx.h"
#include "Fuzzy Logic.h"
#include "Fuzzy LogicDlg.h"
#include "afxdialogex.h"
#include "CSeries.h"
#include <iostream>
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static float distanceFar[1000], distanceNormal[1000], distanceClose[1000], distanceVeryClose[1000], uDistance[4];
static float speedVL[1000], speedL[1000], speedN[1000], speedF[1000], speedVF[1000], uSpeed[5];
float notAppliedmax, softmax, averagemax, hardmax, veryhardmax;
float notApplied[1000], soft[1000], average[1000], hard[1000], veryHard[1000];
float ruleTable[4][5];
float brake[1000];

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CFuzzyLogicDlg dialog



CFuzzyLogicDlg::CFuzzyLogicDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CFuzzyLogicDlg::IDD, pParent)
	//, m_chartDistance(0)
	//, m_chartSpeed(0)
	//, m_chartOutput(0)
	, m_uSpeed(_T(""))
	, m_inSpeed(0)
	, m_inDist(0)
	, m_uDist(_T(""))
	, m_ruleTable(_T(""))
	, m_MaxUtable(_T(""))
	//, m_chartBrake(0)
	, m_OutputCOG(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFuzzyLogicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_chartDistance);
	DDX_Control(pDX, IDC_TCHART2, m_chartSpeed);
	DDX_Control(pDX, IDC_TCHART3, m_chartOutput);
	//  DDX_Text(pDX, IDC_EDIT4, m_InputDistance);
	//  DDX_Text(pDX, IDC_EDIT3, m_InputSpeed);
	DDX_Text(pDX, IDC_EDIT2, m_uSpeed);
	//  DDX_Text(pDX, IDC_EDIT4, m_inDist);
	//  DDX_Text(pDX, IDC_EDIT3, m_inSpeed);
	DDX_Text(pDX, IDC_EDIT3, m_inSpeed);
	DDX_Text(pDX, IDC_EDIT4, m_inDist);
	DDX_Text(pDX, IDC_EDIT1, m_uDist);
	DDX_Text(pDX, IDC_EDIT7, m_ruleTable);
	DDX_Text(pDX, IDC_EDIT6, m_MaxUtable);
	DDX_Control(pDX, IDC_TCHART4, m_chartBrake);
	DDX_Text(pDX, IDC_EDIT5, m_OutputCOG);
}

BEGIN_MESSAGE_MAP(CFuzzyLogicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFuzzyLogicDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT4, &CFuzzyLogicDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT3, &CFuzzyLogicDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON2, &CFuzzyLogicDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFuzzyLogicDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFuzzyLogicDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CFuzzyLogicDlg message handlers

BOOL CFuzzyLogicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// SPEED
	// Kecepatan Very Low
	for (int i = 0; i <= 20; i++) {
	speedVL[i] = 1.0;
	}
	for (int i = 21; i <= 30; i++) {
		speedVL[i] = ((30.0 - i) / (30.0 - 20.0));
	}
	for (int i = 31; i <= 150; i++) {
		speedVL[i] = 0;
	}
	for (int i = 0; i <= 150; i++) {
	((CSeries)(m_chartSpeed.get_Series(0))).AddXY(i, speedVL[i], NULL, 536870912);
	}

	//Kecepatan Low
	for (int i = 0; i <= 25; i++) {
		speedL[i] = 0.0;
	}
	for (int i = 26; i <= 40; i++) {
		speedL[i] = ((i-25.0) / (40.0 - 25.0));
	}
	for (int i = 41; i <= 60; i++) {
		speedL[i] = ((60.0 - i) / (60.0 - 40.0));
	}
	for (int i = 0; i <= 150; i++) {
		((CSeries)(m_chartSpeed.get_Series(1))).AddXY(i, speedL[i], NULL, 536870912);
	}

	//Kecepatan Normal
	for (int i = 0; i <= 55; i++) {
		speedN[i] = 0.0;
	}
	for (int i = 56; i <= 70; i++) {
		speedN[i] = ((i - 55.0) / (70.0 - 55.0));
	}
	for (int i = 71; i <= 90; i++) {
		speedN[i] = ((90.0 - i) / (90.0 - 70.0));
	}
	for (int i = 0; i <= 150; i++) {
		((CSeries)(m_chartSpeed.get_Series(2))).AddXY(i, speedN[i], NULL, 536870912);
	}

	//Kecepatan Fast
	for (int i = 0; i <= 80; i++) {
		speedF[i] = 0.0;
	}
	for (int i = 81; i <= 100; i++) {
		speedF[i] = ((i - 80.0) / (100.0 - 80.0));
	}
	for (int i = 101; i <= 110; i++) {
		speedF[i] = ((110.0 - i) / (110.0 - 100.0));
	}
	for (int i = 0; i <= 150; i++) {
		((CSeries)(m_chartSpeed.get_Series(3))).AddXY(i, speedF[i], NULL, 536870912);
	}

	//Kecepatan Very Fast
	for (int i = 0; i <= 100; i++) {
		speedVF[i] = 0.0;
	}
	for (int i = 101; i <= 130; i++) {
		speedVF[i] = ((i - 100.0) / (130.0 - 100.0));
	}
	for (int i = 131; i <= 150; i++) {
		speedVF[i] = 1.0;
	}
	for (int i = 0; i <= 150; i++) {
		((CSeries)(m_chartSpeed.get_Series(4))).AddXY(i, speedVF[i], NULL, 536870912);
	}

	// DISTANCE
	// Jarak Very Close
	for (int i = 0; i <= 50; i++) {
		distanceVeryClose[i] = 1.0;
	}
	for (int i = 51; i <= 100; i++) {
		distanceVeryClose[i] = ((100.0 - i) / (100.0 - 50.0));
	}
	for (int i = 101; i <= 500; i++) {
		distanceVeryClose[i] = 0.0;
	}
	for (int i = 0; i <= 500; i++) {
		((CSeries)(m_chartDistance.get_Series(0))).AddXY(i, distanceVeryClose[i], NULL, 536870912);
	}

	// Jarak Close
	for (int i = 0; i <= 50; i++) {
		distanceClose[i] = 0.0;
	}
	for (int i = 51; i <= 150; i++) {
		distanceClose[i] = ((i-50.0) / (150.0 - 50.0));
	}
	for (int i = 151; i <= 250; i++) {
		distanceClose[i] = ((250.0-i)/(250.0-150.0));
	}
	for (int i = 0; i <= 500; i++) {
		((CSeries)(m_chartDistance.get_Series(1))).AddXY(i, distanceClose[i], NULL, 536870912);
	}

	// Jarak Normal
	for (int i = 0; i <= 200; i++) {
		distanceNormal[i] = 0.0;
	}
	for (int i = 201; i <= 300; i++) {
		distanceNormal[i] = ((i - 200.0) / (300.0 - 200.0));
	}
	for (int i = 301; i <= 400; i++) {
		distanceNormal[i] = ((400.0 - i) / (400.0 - 300.0));
	}
	for (int i = 0; i <= 500; i++) {
		((CSeries)(m_chartDistance.get_Series(2))).AddXY(i, distanceNormal[i], NULL, 536870912);
	}

	// Jarak Far
	for (int i = 0; i <= 350; i++) {
		distanceFar[i] = 0.0;
	}
	for (int i = 351; i <= 450; i++) {
		distanceFar[i] = ((i - 350.0) / (450.0 - 350.0));
	}
	for (int i = 451; i <= 500; i++) {
		distanceFar[i] = 1.0;
	}
	for (int i = 0; i <= 500; i++) {
		((CSeries)(m_chartDistance.get_Series(3))).AddXY(i, distanceFar[i], NULL, 536870912);
	}

	// BRAKE
	// Brake Not Applied
	for (int i = 0; i <= 15; i++) {
		notApplied[i] = 1.0;
	}
	for (int i = 16; i <= 20; i++) {
		notApplied[i] = ((20.0 - i) / (20.0 - 15.0));
	}
	for (int i = 21; i <= 100; i++) {
		notApplied[i] = 0.0;
	}
	for (int i = 0; i <= 100; i++) {
		((CSeries)(m_chartOutput.get_Series(0))).AddXY(i, notApplied[i], NULL, 536870912);
	}

	// Brake Soft
	for (int i = 0; i <= 15; i++) {
		soft[i] = 0.0;
	}
	for (int i = 16; i <= 25; i++) {
		soft[i] = ((i - 15) / (25.0 - 15.0));
	}
	for (int i = 26; i <= 30; i++) {
		soft[i] = 1.0;
	}
	for (int i = 31; i <= 35; i++) {
		soft[i] = ((35 - i) / (35.0 - 30.0));
	}
	for (int i = 36; i <= 100; i++) {
		soft[i] = 0.0;
	}
	for (int i = 0; i <= 100; i++) {
		((CSeries)(m_chartOutput.get_Series(1))).AddXY(i, soft[i], NULL, 536870912);
	}

	// Brake Average
	for (int i = 0; i <= 30; i++) {
		average[i] = 0.0;
	}
	for (int i = 31; i <= 40; i++) {
		average[i] = ((i - 30) / (40.0 - 30.0));
	}
	for (int i = 41; i <= 50; i++) {
		average[i] = 1.0;
	}
	for (int i = 51; i <= 55; i++) {
		average[i] = ((55 - i) / (55.0 - 50.0));
	}
	for (int i = 56; i <= 100; i++) {
		average[i] = 0.0;
	}
	for (int i = 0; i <= 100; i++) {
		((CSeries)(m_chartOutput.get_Series(2))).AddXY(i, average[i], NULL, 536870912);
	}

	// Brake Hard
	for (int i = 0; i <= 50; i++) {
		hard[i] = 0.0;
	}
	for (int i = 51; i <= 60; i++) {
		hard[i] = ((i - 50) / (60.0 - 50.0));
	}
	for (int i = 61; i <= 75; i++) {
		hard[i] = 1.0;
	}
	for (int i = 76; i <= 80; i++) {
		hard[i] = ((80 - i) / (80.0 - 75.0));
	}
	for (int i = 81; i <= 100; i++) {
		hard[i] = 0.0;
	}
	for (int i = 0; i <= 100; i++) {
		((CSeries)(m_chartOutput.get_Series(3))).AddXY(i, hard[i], NULL, 536870912);
	}

	// Brake Very Hard
	for (int i = 0; i <= 75; i++) {
		veryHard[i] = 0.0;
	}
	for (int i = 76; i <= 85; i++) {
		veryHard[i] = ((i - 75) / (85.0 - 75.0));
	}
	for (int i = 86; i <= 100; i++) {
		veryHard[i] = 1.0;
	}
	for (int i = 0; i <= 100; i++) {
		((CSeries)(m_chartOutput.get_Series(4))).AddXY(i, veryHard[i], NULL, 536870912);
	}



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFuzzyLogicDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFuzzyLogicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFuzzyLogicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFuzzyLogicDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString strVL, buffVL;
	CString strL, buffL;
	CString strN, buffN;
	CString strF, buffF;
	CString strVF, buffVF;

	CString strVC, buffVC;
	CString strC, buffC;
	CString strNdist, buffNdist;
	CString strFar, buffFar;

	UpdateData(TRUE);
	// SPEED
	// Very Low
	uSpeed[0] = speedVL[m_inSpeed];
	buffVL= " [Very Low] : ";
	strVL.Format(_T("%.4f"), uSpeed[0]);

	// Low
	uSpeed[1] = speedL[m_inSpeed];
	buffL = "\r\n [Low] : ";
	strL.Format(_T("%.4f"), uSpeed[1]);

	// Normal
	uSpeed[2] = speedN[m_inSpeed];
	buffN = "\r\n [Normal] : ";
	strN.Format(_T("%.4f"), uSpeed[2]);

	// Fast
	uSpeed[3] = speedF[m_inSpeed];
	buffF = "\r\n [Fast] : ";
	strF.Format(_T("%.4f"), uSpeed[3]);

	// Very Fast
	uSpeed[4] = speedVF[m_inSpeed];
	buffVF = "\r\n [Very Fast] : ";
	strVF.Format(_T("%.4f"), uSpeed[4]);

	m_uSpeed = buffVL + strVL + buffL + strL + buffN + strN + buffF + strF + buffVF + strVF;
	
	// DISTANCE
	// Very Close
	uDistance[0] = distanceVeryClose[m_inDist];
	buffVC = " [Very Close] : ";
	strVC.Format(_T("%.4f"), uDistance[0]);

	// Close
	uDistance[1] = distanceClose[m_inDist];
	buffC = "\r\n [Close] : ";
	strC.Format(_T("%.4f"), uDistance[1]);

	// Normal
	uDistance[2] = distanceNormal[m_inDist];
	buffNdist = "\r\n [Normal] : ";
	strNdist.Format(_T("%.4f"), uDistance[2]);

	// Far
	uDistance[3] = distanceFar[m_inDist];
	buffFar = "\r\n [Far] : ";
	strFar.Format(_T("%.4f"), uDistance[3]);

	m_uDist = buffVC + strVC + buffC + strC + buffNdist + strNdist + buffFar + strFar;

	UpdateData(FALSE);
}


void CFuzzyLogicDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CFuzzyLogicDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



void CFuzzyLogicDlg::OnBnClickedButton2()
{
	CString strRule[4][5];
	CString str1, str2, str3, str4, str5, str6, str7, str8, str9, str10;
	CString str11, str12, str13, str14, str15, str16, str17, str18, str19, str20;
	CString strSoftmax, strNotAppliedmax, strAveragemax, strHardmax, strveryHardmax;

	UpdateData(TRUE);

	str1 = "[0][0][Soft] : ";
	str2 = " \r\n[0][1][Average] : ";
	str3 = " \r\n[0][2][Hard] : ";
	str4 = " \r\n[0][3][Very Hard] : ";
	str5 = " \r\n[0][4][Very Hard] : ";
	str6 = " \r\n[1][0][Soft] : ";
	str7 = " \r\n[1][1][Soft] : ";
	str8 = " \r\n[1][2][Average] : ";
	str9 = " \r\n[1][3][Hard] : ";
	str10 = " \r\n[1][4][Very Hard] : ";
	str11 = " \r\n[2][0][Not Applied] : ";
	str12 = " \r\n[2][1][Not Applied] : ";
	str13 = " \r\n[2][2][Soft] : ";
	str14 = " \r\n[2][3][Average] : ";
	str15 = " \r\n[2][4][Hard] : ";
	str16 = " \r\n[3][0][Not Applied] : ";
	str17 = " \r\n[3][1][Not Applied] : ";
	str18 = " \r\n[3][2][Not Applied] : ";
	str19 = " \r\n[3][3][Average] : ";
	str20 = " \r\n[3][4][Soft] : ";

	// TODO: Add your control notification handler code here
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 5; j++){
			ruleTable[i][j] = min(uDistance[i], uSpeed[j]);
			strRule[i][j].Format(_T("%.4f"), ruleTable[i][j]);
		}
	}
	m_ruleTable = 
		  str1 + strRule[0][0] + str2 + strRule[0][1] + str3 + strRule[0][2] + str4 + strRule[0][3] + str5 + strRule[0][4] 
		+ str6 + strRule[1][0] + str7 + strRule[1][1] + str8 + strRule[1][2] + str9 + strRule[1][3] + str10 + strRule[1][4]
		+ str11 + strRule[2][0] + str12 + strRule[2][1] + str13 + strRule[2][2] + str14 + strRule[2][3] + str15 + strRule[2][4]
		+ str16 + strRule[3][0] + str17 + strRule[3][1] + str18 + strRule[3][2] + str19 + strRule[3][3] + str20 + strRule[3][4];

	notAppliedmax = ruleTable[2][0];
	notAppliedmax = max(notAppliedmax, ruleTable[2][1]);
	notAppliedmax = max(notAppliedmax, ruleTable[3][0]);
	notAppliedmax = max(notAppliedmax, ruleTable[3][1]);
	notAppliedmax = max(notAppliedmax, ruleTable[3][2]);

	softmax = ruleTable[0][0];
	softmax = max(softmax, ruleTable[1][0]);
	softmax = max(softmax, ruleTable[1][1]);
	softmax = max(softmax, ruleTable[2][2]);
	softmax = max(softmax, ruleTable[3][4]);
	

	averagemax = ruleTable[0][1];
	averagemax = max(averagemax, ruleTable[1][2]);
	averagemax = max(averagemax, ruleTable[2][3]);
	averagemax = max(averagemax, ruleTable[3][3]);

	hardmax = ruleTable[0][2];
	hardmax = max(hardmax, ruleTable[1][3]);
	hardmax = max(hardmax, ruleTable[2][4]);
	
	veryhardmax = ruleTable[0][3];
	veryhardmax = max(veryhardmax, ruleTable[0][4]);
	veryhardmax = max(veryhardmax, ruleTable[1][4]);

	str1 = "Not Applied : ";
	str2 = " \r\nSoft : ";
	str3 = " \r\nAverage : ";
	str4 = " \r\nHard : ";
	str5 = " \r\nVery Hard : ";

	strNotAppliedmax.Format(_T("%.4f"), notAppliedmax);
	strSoftmax.Format(_T("%.4f"), softmax);
	strAveragemax.Format(_T("%.4f"), averagemax);
	strHardmax.Format(_T("%.4f"), hardmax);
	strveryHardmax.Format(_T("%.4f"), veryhardmax);

	m_MaxUtable = str1 + strNotAppliedmax + str2 + strSoftmax + str3 + strAveragemax + str4 + strHardmax + str5 + strveryHardmax;

	UpdateData(FALSE);
}


void CFuzzyLogicDlg::OnBnClickedButton3()
{
	float Brake1[200], Brake2[200], Brake3[200], Brake4[200], Brake5[200], brakeAll[200];
	float data1, data2, data3, data4, data5;
	CString strNot, strSoft, strAv, strHar, strVer, strOut;
	strNot = "Not Applied : ";
	strSoft = " \r\nSoft : ";
	strAv = " \r\nAverage : ";
	strHar = " \r\nHard : ";
	strVer = " \r\nVery Hard : ";
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here

	for (int i = 0; i <= 100; i++){
		Brake1[i] = min(notApplied[i], notAppliedmax);
		Brake2[i] = min(soft[i], softmax);
		Brake3[i] = min(average[i], averagemax);
		Brake4[i] = min(hard[i], hardmax);
		Brake5[i] = min(veryHard[i], veryhardmax);

		brakeAll[i] = max(Brake1[i], Brake2[i]);
		brakeAll[i] = max(brakeAll[i], Brake3[i]);
		brakeAll[i] = max(brakeAll[i], Brake4[i]);
		brakeAll[i] = max(brakeAll[i], Brake5[i]);
	}

	for (int i = 0; i <= 100; i++) {
		((CSeries)(m_chartBrake.get_Series(0))).AddXY(i, brakeAll[i], NULL, 536870912);
	}
	
	float out = 0, out1 = 0, out2 = 0;
	for (int i = 0; i < 100; i++)
	{
		out1 += brakeAll[i] * i;
		out2 += brakeAll[i];
	}

	out = out1 / out2;

	data1 = trapezoidLeft(out, 15.0, 20.0);
	data2 = trapezoidCenter(out, 15.0, 25.0, 30.0, 35.0);
	data3 = trapezoidCenter(out, 30.0, 40.0, 50.0, 55.0);
	data4 = trapezoidCenter(out, 50.0, 60.0, 75.0, 80.0);
	data5 = trapezoidRight(out, 75.0, 85.0);

	if (data1 > data2){
		strNot = "  Not Applied";
		strOut.Format(_T("%.4f"), out);
		m_OutputCOG = strOut + strNot;
	}
	else if (data2>data3)
	{
		strSoft = "  Soft";
		strOut.Format(_T("%.4f"), out);
		m_OutputCOG = strOut + strSoft;
	}
	else if (data3>data4)
	{
		strAv = "  Average";
		strOut.Format(_T("%.4f"), out);
		m_OutputCOG = strOut + strAv;
	}
	else if (data4>data5)
	{
		strHar = "  Hard";
		strOut.Format(_T("%.4f"), out);
		m_OutputCOG = strOut + strHar;
	}
	else
	{
		strVer = "  Very Hard";
		strOut.Format(_T("%.4f"), out);
		m_OutputCOG = strOut + strVer;
	}
	
	UpdateData(FALSE);
}

float CFuzzyLogicDlg::trapezoidLeft(float x, float c, float d)
{
	float u;
	if (x > d)
		u = 0;
	else if (c <= x <= d)
		u = (d - x) / (d - c);
	else
		u = 1;
	return u;

}


float CFuzzyLogicDlg::trapezoidCenter(float x, float a, float b, float c, float d)
{
	float u;
	if ((x < a) | (x > d))
		u = 0;
	else if (a <= x <= b)
		u = (x - a) / (b - a);
	else if (b <= x <= c)
		u = 1;
	else if (c <= x <= d)
		u = (d - x) / (d - c);
	return u;
}


float CFuzzyLogicDlg::trapezoidRight(float x, float a, float b)
{
	float u;
	if (x < a)
		u = 0;
	else if (a <= x <= b)
		u = (x - a) / (b - a);
	else
		u = 1;
	return u;
}

void CFuzzyLogicDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	uDistance[4]=NULL;
	uSpeed[5] = NULL;
	notApplied[1000] = NULL;
	soft[1000] = NULL;
	average[1000] = NULL;
	hard[1000] = NULL;
	veryHard[1000] = NULL;
	ruleTable[4][5] = NULL;
	brake[1000] = NULL;

	((CSeries)(m_chartBrake.get_Series(0))).Clear();

	m_uSpeed = " ";
	m_uDist = " ";
	m_ruleTable = " ";
	m_MaxUtable = " ";
	m_OutputCOG = " ";

	UpdateData(FALSE);
}
