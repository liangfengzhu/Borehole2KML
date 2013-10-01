
// Borehole Data MISDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Borehole Data MIS.h"
#include "Borehole Data MISDlg.h"
#include "afxdialogex.h"
#include "ADOConnect.h"
#include "structFile.h"
#include "CreateKML.h"
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "ConvertCharset.h"
#include <ShlObj.h>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const double PRECISION= 1.0e-9;
// CAboutDlg dialog used for App About

ThreadInfo myInfo;
UINT ThreadProcCreKML(LPVOID lpParam)//线程函数  
{  
	CTime time1,time2;
	time1 = CTime::GetCurrentTime(); 
	HWND hWnd = ::FindWindow(NULL,_T("Borehole2KML"));//获得窗口句柄
	ThreadInfo *tdInfo = (ThreadInfo*) lpParam;

	tdInfo->btn->EnableWindow(FALSE);
	tdInfo->pstTip->ShowWindow(SW_SHOW);
	tdInfo->percent->ShowWindow(SW_SHOW);
	tdInfo->prog->ShowWindow(SW_SHOW);
	tdInfo->prog->SetRange(0,2748);
	tdInfo->prog->SetPos(0);
	
	CString savePathTemp = tdInfo->m_savePath;
	SHCreateDirectory(NULL,savePathTemp);
	savePathTemp += _T("\\");

	string filePathTemp = Unicode2Utf8(savePathTemp.GetString());
	string fileNameTemp = Unicode2Utf8(tdInfo->m_fileName.GetString());

	string totalFilePath = filePathTemp + fileNameTemp;
	string pmFileName;//地标文件名
	ofstream foutAll;
	ofstream foutPM;

	//写总体的网络链接文件
	CreateKMLHead(foutAll,totalFilePath);//创建KML文件的头部
	CreatePPMHead(foutAll,fileNameTemp);//创建网络链接文件头部

	::CoInitialize(NULL);
	_bstr_t bstrSQLBH = "select * from [BoreholeInformation$]";
	_RecordsetPtr recordsetBH;
	recordsetBH = tdInfo->readData->GetRecordSet(bstrSQLBH);
	_BOREHOLEINFO bhInfo;
	while(!recordsetBH->adoEOF)
	{
		bhInfo.m_holeCode = (_bstr_t)recordsetBH->GetCollect((long)0);
		bhInfo.m_holeName = (_bstr_t)recordsetBH->GetCollect((long)1);
		bhInfo.m_holeType = (_bstr_t)recordsetBH->GetCollect((long)2);
		bhInfo.m_waterLevel = atof((_bstr_t)recordsetBH->GetCollect((long)3));
		bhInfo.m_dateStart = "";
		bhInfo.m_dateEnd = "";
		bhInfo.m_Engineer ="";
		bhInfo.m_mark  ="";
		bhInfo.m_holeDiameter = atof((_bstr_t)recordsetBH->GetCollect((long)7));
		bhInfo.m_holeDep = atof((_bstr_t)recordsetBH->GetCollect((long)8));
		bhInfo.m_holeEle = atof((_bstr_t)recordsetBH->GetCollect((long)9));
		bhInfo.m_pt.m_x = atof((_bstr_t)recordsetBH->GetCollect((long)10));
		bhInfo.m_pt.m_y = atof((_bstr_t)recordsetBH->GetCollect((long)11));

		//格式化查找钻孔类型名的字符串
		ostringstream wostrSQLHTN;
		wostrSQLHTN<<"select * from [BoreholeType$] where BoreholeType = "<<bhInfo.m_holeType;
		_RecordsetPtr recordsetHTN;
		recordsetHTN = tdInfo->readData->GetRecordSet((_bstr_t)wostrSQLHTN.str().c_str());
		bhInfo.m_holeTypeName = (_bstr_t)recordsetHTN->GetCollect((long)1);

		//创建网络链接代码
		CreateNetWorkLink(foutAll, bhInfo);
		//创建点地标文件
		pmFileName = filePathTemp + bhInfo.m_holeCode;
		pmFileName += "_Point";
		CreateKMLHead(foutPM,pmFileName);
		CreatePointPM(foutPM,bhInfo);
		CreateKMLRear(foutPM);

		//创建多边形地标文件
		_POINT2D pt2D[13];//保存十三个顶点的二维坐标
		CalculateCoor2D(pt2D,iSide,bhInfo.m_pt,bhInfo.m_holeDiameter/(2*1000)*CONVERT*(tdInfo->m_hirScale/100));
		pmFileName = filePathTemp + bhInfo.m_holeCode; //文件名为钻孔编号+钻孔名
		pmFileName += "_Cylinder";
		CreateKMLHead(foutPM,pmFileName);//文件头

		_HOLESTRATAINFO hsUp;//上层地层信息
		hsUp.m_holeCode = bhInfo.m_holeCode;
		hsUp.m_holeName = bhInfo.m_holeName;
		hsUp.m_layerBottomDep = bhInfo.m_holeEle;//层顶埋深和层底埋深都为孔口标高
		hsUp.m_layerNo = 0;
		hsUp.m_layerTopDep = bhInfo.m_holeEle;
		//hsUp.m_rcdNo = 0;
		hsUp.m_straCode = "";
		hsUp.m_age = "";
		hsUp.m_straCode = "";
		hsUp.m_straColor = "";
		hsUp.m_straName = "";
		hsUp.m_eleTop = bhInfo.m_holeEle;

		//格式化查找钻孔分层信息的字符串
		ostringstream wostrSQLHS;
		wostrSQLHS<<"select * from [StratumInformation$] where BoreholeCode = "<<bhInfo.m_holeCode;
		_RecordsetPtr recordsetHS;
		recordsetHS = tdInfo->readData->GetRecordSet((_bstr_t)wostrSQLHS.str().c_str());
		double height = 0;//地层累计深度
		double dEleTop = bhInfo.m_holeEle;//层顶高层，初始值为钻孔标高，因为第一层的层顶高程就为孔口标高
		while(!recordsetHS->adoEOF)
		{
			_HOLESTRATAINFO curHSInfo;			
			//curHSInfo.m_rcdNo = atoi((_bstr_t)recordsetHS->GetCollect((long)0));
			curHSInfo.m_holeCode = (_bstr_t)recordsetHS->GetCollect((long)0);
			curHSInfo.m_holeName = (_bstr_t)recordsetHS->GetCollect((long)1);
			curHSInfo.m_layerNo = atoi((_bstr_t)recordsetHS->GetCollect((long)2));
			curHSInfo.m_straCode = (_bstr_t)recordsetHS->GetCollect((long)3);
			curHSInfo.m_layerTopDep = atof((_bstr_t)recordsetHS->GetCollect((long)4));
			curHSInfo.m_layerBottomDep = atof((_bstr_t)recordsetHS->GetCollect((long)5));
			//查找总体地层信息
			ostringstream wostrSQLSI;
			wostrSQLSI<<"select * from [OverallStratum$] where StratumCode = \""<<curHSInfo.m_straCode<<"\"";
			_RecordsetPtr recordsetSI;
			recordsetSI = tdInfo->readData->GetRecordSet((_bstr_t)wostrSQLSI.str().c_str());

			curHSInfo.m_straName = (_bstr_t)recordsetSI->GetCollect((long)2);
			curHSInfo.m_age = "";
			curHSInfo.m_genesis = "";

			string colorTemp = (_bstr_t)recordsetSI->GetCollect((long)5);
			string subStr = colorTemp.substr(2,6);
			rotate(subStr.begin(),subStr.begin()+4,subStr.end());
			rotate(subStr.begin()+2,subStr.begin()+4,subStr.end());
			curHSInfo.m_straColor = colorTemp.substr(0,2);
			curHSInfo.m_straColor += subStr;
			curHSInfo.m_eleTop = dEleTop;
			dEleTop -= (curHSInfo.m_layerBottomDep - curHSInfo.m_layerTopDep);

			CreatePolyStyle(foutPM,curHSInfo.m_straColor);//写polystyle代码

			CreatePMForEachLayer(foutPM,bhInfo,hsUp,curHSInfo,tdInfo->m_upHeight,(tdInfo->m_verScale/100));//写分层的点地标文件
			CreatePMHead(foutPM,bhInfo,curHSInfo);
			Create12(foutPM,pt2D,(curHSInfo.m_eleTop+tdInfo->m_upHeight)*(tdInfo->m_verScale/100));//创建每个地层顶层多边形
			for(int i = 0; i < 12; i++)
			{
				Create4(foutPM,pt2D[i],pt2D[i+1],(curHSInfo.m_eleTop+tdInfo->m_upHeight)*(tdInfo->m_verScale/100),
					((curHSInfo.m_eleTop-(curHSInfo.m_layerBottomDep-curHSInfo.m_layerTopDep))+tdInfo->m_upHeight)*(tdInfo->m_verScale/100));
			}
			Create12(foutPM,pt2D,((curHSInfo.m_eleTop-(curHSInfo.m_layerBottomDep-curHSInfo.m_layerTopDep))+tdInfo->m_upHeight)*(tdInfo->m_verScale/100));
			hsUp = curHSInfo;
			CreatePMRear(foutPM);
			recordsetHS->MoveNext();
		}
		_HOLESTRATAINFO hsDown;
		hsDown.m_holeCode = bhInfo.m_holeCode;
		hsDown.m_holeName = bhInfo.m_holeName;
		hsDown.m_layerBottomDep = hsUp.m_layerBottomDep;
		hsDown.m_layerTopDep = hsUp.m_layerBottomDep;
		hsDown.m_layerNo = 0;
		//hsDown.m_rcdNo = 0;
		hsDown.m_straCode = "";
		hsDown.m_eleTop = hsUp.m_eleTop-(hsUp.m_layerBottomDep-hsUp.m_layerTopDep);
		hsDown.m_age = "";
		hsDown.m_genesis = "";
		hsDown.m_straColor = "";
		hsDown.m_straName = "";
		CreatePMForEachLayer(foutPM,bhInfo,hsUp,hsDown,tdInfo->m_upHeight,(tdInfo->m_verScale/100));//写分层的点地标文件
		CreateKMLRear(foutPM); 
		recordsetBH->MoveNext();

		//循环结束前要重新设置进度条的位置
		// 取得当前进度
		int nCurPos = tdInfo->prog->GetPos();
		int nLower = 0;
		int nUpper = 0;
		 tdInfo->prog->GetRange(nLower,nUpper);
		// 如果进度条执行结束，就关闭记时器
		if ( nCurPos == nUpper)
		{
			tdInfo->prog->SetPos(nCurPos);
		}
		else
		{
			tdInfo->prog->SetPos(nCurPos+1);
		}
		int nPos=((tdInfo->prog->GetPos()-nLower)*100/(nUpper-nLower))+1;
		CString strTip;
		strTip.Format(_T("%d"),nPos);
		strTip += _T("%");
		::SetDlgItemTextW(hWnd,IDC_STATIC_PERCENT,strTip);
	}
	CreateKMLRear(foutAll);
	time2 = CTime::GetCurrentTime();
	int time = (time2.GetHour()*3600 + time2.GetMinute()*60 + time2.GetSecond()) - (time1.GetHour()*3600 + time1.GetMinute()*60 + time1.GetSecond());
	CString strTime;
	strTime.Format(_T("All KML files are created completely, and %d seconds are spent!"),time);
	MessageBox(hWnd,strTime,_T("Prompt"),MB_OK|MB_ICONINFORMATION);
	tdInfo->readData->ExitConnect();
	tdInfo->pstTip->ShowWindow(SW_HIDE);
	tdInfo->percent->ShowWindow(SW_HIDE);
	tdInfo->prog->ShowWindow(SW_HIDE);
	tdInfo->btn->EnableWindow(TRUE);
	
	::CoUninitialize();
	return 0;
}

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

CBoreholeDataMISDlg::CBoreholeDataMISDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBoreholeDataMISDlg::IDD, pParent)
	, connecFlag(false)
	, m_count(0)
	, m_fileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_savePath = _T("");
	m_upHeight = 100.0f;
	m_dataPath = _T("");
	m_hirScale = 500.0f;
	m_verScale = 300.0f;
}

void CBoreholeDataMISDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_savePath);
	DDX_Text(pDX, IDC_EDIT_UP, m_upHeight);
	//  DDX_Control(pDX, IDC_COMBO_OUTER, m_comboSelectOT);
	DDX_Text(pDX, IDC_EDIT_DATAPATH, m_dataPath);
	DDX_Text(pDX, IDC_EDIT_HIRSCALE, m_hirScale);
	DDV_MinMaxFloat(pDX, m_hirScale, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_VERSCALE, m_verScale);
	DDV_MinMaxFloat(pDX, m_verScale, 0, 1000);
	DDX_Control(pDX, IDC_PROG, m_prog);
	DDX_Control(pDX, IDC_STATIC_TIP, m_stTip);
	DDX_Control(pDX, IDC_STATIC_PERCENT, m_percent);
	DDX_Control(pDX, IDC_BUTTON_CREATEKML, m_btn);
}

BEGIN_MESSAGE_MAP(CBoreholeDataMISDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CLOSE, &CBoreholeDataMISDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BUTTON_SELECTDATABASE, &CBoreholeDataMISDlg::OnBnClickedButtonSelectdatabase)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPATH, &CBoreholeDataMISDlg::OnBnClickedButtonSavepath)
	ON_BN_CLICKED(IDC_BUTTON_CREATEKML, &CBoreholeDataMISDlg::OnBnClickedButtonCreatekml)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CBoreholeDataMISDlg message handlers

BOOL CBoreholeDataMISDlg::OnInitDialog()
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

	HICON m_hIcon;
	m_hIcon=AfxGetApp()->LoadIcon(IDI_MAINICON);
	SetIcon(m_hIcon,TRUE); //设置为大图标
	SetIcon(m_hIcon,FALSE);//设置为小图标

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBoreholeDataMISDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBoreholeDataMISDlg::OnPaint()
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
HCURSOR CBoreholeDataMISDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBoreholeDataMISDlg::OnBnClickedClose()
{
	// TODO: Add your control notification handler code here
	EndDialog(IDD_BOREHOLEDATAMIS_DIALOG);

}

//选择数据库
void CBoreholeDataMISDlg::OnBnClickedButtonSelectdatabase()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CFileDialog *pFDlg;
	CString strPath;
	pFDlg = new CFileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT);
	TCHAR Filter[] = _T("Excel file(*.xls)\0*.xls\0");
	pFDlg->m_ofn.lpstrFilter = Filter;
	if(pFDlg->DoModal() == IDOK)
	{
		strPath = pFDlg->GetPathName();	//获取文件路径名
		m_fileName =  pFDlg->GetFileTitle();//获取文件名
		m_dataPath = strPath;
		if(m_count==0)
		{
			m_savePath = pFDlg->GetFolderPath();
			m_count++;
		}
		CString strSQL("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");
		strSQL += strPath;
		strSQL += _T(";Extended Properties=Excel 8.0;Persist Security Info = False");
		::CoInitialize(NULL);
		readData.bstrSQL = strSQL;
		connecFlag = readData.OnitConnect();
		::CoUninitialize();
	}
	else
	{
		return;
	}
	delete(pFDlg);
	UpdateData(FALSE);	
}

//选择保存路径
void CBoreholeDataMISDlg::OnBnClickedButtonSavepath()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString sFolderPath;
	BROWSEINFO bi;
	TCHAR Buffer[MAX_PATH];

	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = _T("Select the save path for KML files");
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.ulFlags = BIF_USENEWUI;

	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME;

	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList,Buffer);

		sFolderPath = Buffer;
	}
	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) return;
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
	m_savePath = sFolderPath;
	UpdateData(FALSE);
}

void CBoreholeDataMISDlg::OnBnClickedButtonCreatekml()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	myInfo.connecFlag = connecFlag;
	myInfo.m_dataPath = m_dataPath;
	myInfo.m_fileName = m_fileName;
	myInfo.m_hirScale = m_hirScale;
	myInfo.m_savePath = m_savePath;
	myInfo.m_upHeight = m_upHeight;
	myInfo.m_verScale = m_verScale;
	myInfo.readData = &readData;
	myInfo.btn = &m_btn;
	myInfo.prog = &m_prog;
	myInfo.pstTip = &m_stTip;
	myInfo.percent = &m_percent;

	if(!connecFlag)
	{
		MessageBox(_T("Please select borehole data!"),_T("Error"),MB_OK|MB_ICONERROR);
		return;
	}
	if(m_savePath.IsEmpty())
	{
		MessageBox(_T("Save path can not be empty!"),_T("Error"),MB_OK|MB_ICONERROR);
		return;
	}  
	if(MessageBox(_T("Creating KML files?"),_T("Message"),MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL)
	{
		return;
	}

	GetDlgItem(IDC_BUTTON_CREATEKML)->EnableWindow(FALSE); 
	CWinThread *pThread1 = AfxBeginThread(ThreadProcCreKML, &myInfo,0,0,0,NULL);//创建子线程
	UpdateData(FALSE);
}

