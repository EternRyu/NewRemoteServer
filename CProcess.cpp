// CProcess.cpp: 实现文件
//

#include "pch.h"
#include "NewRemoteServer.h"
#include "CProcess.h"
#include "afxdialogex.h"


// CProcess 对话框

IMPLEMENT_DYNAMIC(CProcess, CDialogEx)

CProcess::CProcess(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CProcess::~CProcess()
{
}

void CProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ProcessList);
}


BEGIN_MESSAGE_MAP(CProcess, CDialogEx)
	ON_MESSAGE(MSG_FUNCTION_CODE_SEND_PROCESSLIST, &CProcess::OnProcessListMag)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CProcess::OnRclickListOpenMeun)
	ON_COMMAND(ID_32772, &CProcess::OnKillProcess)
END_MESSAGE_MAP()


// CProcess 消息处理程序


BOOL CProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ProcessList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	ProcessList.InsertColumn(0, L"进程名称", 0, 120);
	ProcessList.InsertColumn(1, L"进程ID", 0, 60);
	ProcessList.InsertColumn(2, L"父进程ID", 0, 70);
	ProcessList.InsertColumn(3, L"进程路径", 0, 300);
	DWORD dwFuncCode = MSG_FUNCTION_CODE_GET_PROCESS_LIST;
	SendData(&dwFuncCode, sizeof(dwFuncCode));
	//send(g_Socket, (char*)&dwFuncCode, sizeof(dwFuncCode), 0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


LRESULT CProcess::OnProcessListMag(WPARAM wParam, LPARAM lParam)
{
	ProcessListInfo TempProcessBuffer = *(ProcessListInfo_PTR)lParam;
	WCHAR wczTempBuffer[MAX_PATH] = { 0 };

	CharToWchar(wczTempBuffer, TempProcessBuffer.szProcessName);
	//swprintf(wczTempBuffer, MAX_PATH, L"%hs", TempProcessBuffer.szProcessName);
	ProcessList.InsertItem(dwProcessIndex, wczTempBuffer);
	memset(wczTempBuffer, 0, MAX_PATH);
	swprintf(wczTempBuffer, MAX_PATH, L"%d", TempProcessBuffer.dwProcessID);
	ProcessList.SetItemText(dwProcessIndex, 1, wczTempBuffer);
	memset(wczTempBuffer, 0, MAX_PATH);
	swprintf(wczTempBuffer, MAX_PATH, L"%d", TempProcessBuffer.dwParenProcessID);
	ProcessList.SetItemText(dwProcessIndex, 2, wczTempBuffer);

	memset(wczTempBuffer, 0, MAX_PATH);
	CharToWchar(wczTempBuffer, TempProcessBuffer.szProcessPath);
	//swprintf(wczTempBuffer, MAX_PATH, L"%hs", TempProcessBuffer.szProcessPath);
	ProcessList.SetItemText(dwProcessIndex, 3, wczTempBuffer);
	dwProcessIndex++;
	return LRESULT();
}

void CProcess::OnRclickListOpenMeun(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POINT pt = { 0 };
	GetCursorPos(&pt);
	HMENU hMenu = LoadMenu(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MENU2));
	HMENU hSubMenu = GetSubMenu(hMenu, 0);
	TrackPopupMenu(hSubMenu, TPM_CENTERALIGN, pt.x, pt.y, 0, m_hWnd, NULL);
	*pResult = 0;
}


void CProcess::OnKillProcess()
{
	KillProcessInfo KillProcessBuffer;
	int nPos = (int)ProcessList.GetFirstSelectedItemPosition();
	nPos -= 1;
	CString csProcessID = ProcessList.GetItemText(nPos, 1);
	KillProcessBuffer.dwFuncCode = MSG_FUNCTION_CODE_KEILL_PROCESS;
	KillProcessBuffer.dwProcessID = _ttoi(csProcessID);
	SendData((LPVOID)&KillProcessBuffer, sizeof(KillProcessBuffer));
}
