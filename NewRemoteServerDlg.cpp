
// NewRemoteServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "NewRemoteServer.h"
#include "NewRemoteServerDlg.h"
#include "afxdialogex.h"

#include <vector>
#include "CProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SOCKET  g_Socket;
std::vector<ClientSocketInfo> g_ClientSocket;
// CNewRemoteServerDlg 对话框



CNewRemoteServerDlg::CNewRemoteServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWREMOTESERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewRemoteServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, LinkList);
}

BEGIN_MESSAGE_MAP(CNewRemoteServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(MSG_FUNCTION_CODE_SEND_EQULSIT, &CNewRemoteServerDlg::OnTTwarbListMag1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CNewRemoteServerDlg::OnRclickListOpenMenu)
	ON_COMMAND(ID_32771, &CNewRemoteServerDlg::OnOpenProcessDlg)
END_MESSAGE_MAP()


// CNewRemoteServerDlg 消息处理程序

BOOL CNewRemoteServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	InitSocket();
	HANDLE hTerad = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SocketThreadCallBack, NULL, NULL, NULL);
	LinkList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	LinkList.InsertColumn(0, L"外网IP", 0, 120);
	LinkList.InsertColumn(1, L"内网IP", 0, 120);
	LinkList.InsertColumn(2, L"计算机名称", 0, 150);
	LinkList.InsertColumn(3, L"计算机系统", 0, 170);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNewRemoteServerDlg::OnPaint()
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
HCURSOR CNewRemoteServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//初始化设备信息面板
LRESULT CNewRemoteServerDlg::OnTTwarbListMag1(WPARAM wParam, LPARAM lParam)
{
	LinkInfo TempNetWorkingBuffer = *(PLinkInfo)lParam;
	WCHAR wczTempBuffer[MAX_PATH] = { 0 };

	swprintf(wczTempBuffer, MAX_PATH, L"%hs", TempNetWorkingBuffer.szNetWorkIP);
	LinkList.InsertItem(dwIndex, wczTempBuffer);
	memset(wczTempBuffer, 0, MAX_PATH);
	swprintf(wczTempBuffer, MAX_PATH, L"%hs", TempNetWorkingBuffer.szIntranetIP);
	
	LinkList.SetItemText(dwIndex, 1, wczTempBuffer);
	memset(wczTempBuffer, 0, MAX_PATH);
	swprintf(wczTempBuffer, MAX_PATH, L"%hs", TempNetWorkingBuffer.szComputerName);
	
	LinkList.SetItemText(dwIndex, 2, wczTempBuffer);
	memset(wczTempBuffer, 0, MAX_PATH);
	swprintf(wczTempBuffer, MAX_PATH, L"%hs", TempNetWorkingBuffer.szSystenVersion);
	
	LinkList.SetItemText(dwIndex, 3, wczTempBuffer);
	dwIndex++;
	return LRESULT();
}

BOOL CNewRemoteServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (pMsg->message)//拦截功能号
	{
	case USER_MSG:
	{
		switch (pMsg->wParam)
		{
		case USER_MSG_SOCKET:
		{
			g_ClientSocket.push_back(*(PClientSocketInfo)pMsg->lParam);
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CNewRemoteServerDlg::OnRclickListOpenMenu(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	POINT pt = { 0 };
	GetCursorPos(&pt);
	HMENU hMenu = LoadMenu(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MENU1));
	HMENU hSubMenu = GetSubMenu(hMenu, 0);
	TrackPopupMenu(hSubMenu, TPM_CENTERALIGN, pt.x, pt.y, 0, m_hWnd, NULL);
	*pResult = 0;
}


CProcess* DlgProcess;
DWORD DlgThreadCallBack(LPVOID lpBuffer)
{
	DlgProcess = new CProcess;
	DlgProcess->DoModal();
	delete DlgProcess;
	return 0;
}

void CNewRemoteServerDlg::OnOpenProcessDlg()
{
	int nPos = (int)LinkList.GetFirstSelectedItemPosition();
	nPos -= 1;
	CString csNetWorkIP = LinkList.GetItemText(nPos, 0);
	for (size_t i = 0; i < g_ClientSocket.size(); i++)
	{
		CString csTempIP;
		csTempIP = g_ClientSocket[i].szNetWorkIP;
		if (csTempIP == csNetWorkIP)
		{
			g_Socket = g_ClientSocket[i].SockClient;
			break;
		}
	}

	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DlgThreadCallBack, NULL, NULL, NULL);
}
