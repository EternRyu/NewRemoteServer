// Filemanager.cpp: 实现文件
//

#include "pch.h"
#include "NewRemoteServer.h"
#include "Filemanager.h"
#include "afxdialogex.h"

HTREEITEM g_THD;
// Filemanager 对话框

IMPLEMENT_DYNAMIC(Filemanager, CDialogEx)

Filemanager::Filemanager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Filemanager::~Filemanager()
{
}

void Filemanager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, FileTree);
}


BEGIN_MESSAGE_MAP(Filemanager, CDialogEx)
	ON_MESSAGE(MSG_FUNCTION_CODE_SEND_DRIVE_LEREER, &Filemanager::InitTreeCtrl)
	ON_MESSAGE(MSG_FUNCTION_CODE_SEND_FILE_TRAVERSAL, &Filemanager::FolderInfoAddTree)
END_MESSAGE_MAP()


// Filemanager 消息处理程序


BOOL Filemanager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitFileImageList();
	DWORD dwFuncCode = MSG_FUNCTION_CODE_DEIVE_LETTER;
	send(g_Socket, (char*)&dwFuncCode, sizeof(dwFuncCode), 0);
	SendData((LPVOID)&dwFuncCode, sizeof(dwFuncCode));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//初始化系统图标
VOID Filemanager::InitFileImageList()
{
	auto InfoHd = SHGetFileInfo(L"", 0, &FileInfo, sizeof(FileInfo), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	auto Image_List = CImageList::FromHandle((HIMAGELIST)InfoHd);
	FileTree.SetImageList(Image_List, TVSIL_NORMAL);
}

//盘符初始化
LRESULT Filemanager::InitTreeCtrl(WPARAM wParam, LPARAM lParam)
{
	DriveLetterInfo TempDiskBuffer = *(PDriveLetterInfo)lParam;
	WCHAR wszTempBuffer[MAX_PATH] = { 0 };
	wsprintf(wszTempBuffer, L"%S", TempDiskBuffer.szDisk);
	FileTree.InsertItem(wszTempBuffer, TempDiskBuffer.FileInfo.iIcon, TempDiskBuffer.FileInfo.iIcon, TVI_ROOT);
	//TV_ITEM tvItem;
	//tvItem.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_HANDLE | TVIF_SELECTEDIMAGE | TVIS_SELECTED | TVIS_EXPANDED | TVIF_CHILDREN;
	//tvItem.pszText = wszTempBuffer;
	//tvItem.cchTextMax = MAX_PATH;
	//tvItem.lParam = NULL;  // 额外参数
	//tvItem.iImage = TempDiskBuffer.FileInfo.iIcon;      // 未被选中时显示的图片
	//tvItem.iSelectedImage = TempDiskBuffer.FileInfo.iIcon;   // 选中时显示的图片
	//tvItem.cChildren = 1;
	//TV_INSERTSTRUCT tvInsert;
	//tvInsert.hParent = TVI_ROOT;  // 确定父节点
	//tvInsert.hInsertAfter = TVI_LAST;
	//tvInsert.item = tvItem;
	//FileTree.InsertItem(&tvInsert);
	return LRESULT();
}

//文件夹信息
LRESULT Filemanager::FolderInfoAddTree(WPARAM wParam, LPARAM lParam)
{
	DiskFileInfo TempDiskBuffer = *(PDiskFileInfo)lParam;
	WCHAR wszTempBuffer[MAX_PATH] = { 0 };
	wsprintf(wszTempBuffer, L"%S", TempDiskBuffer.szFilePath);
	FileTree.InsertItem(wszTempBuffer, TempDiskBuffer.FileInfo.iIcon, TempDiskBuffer.FileInfo.iIcon, g_THD);
	return LRESULT();
}

//获取树中的文件路径
BOOL Filemanager::GetPathInTree(PCHAR pcPath)
{
	HTREEITEM THD = FileTree.GetSelectedItem();
	if (THD == NULL)
	{
		return FALSE;
	}
	g_THD = THD;
	WCHAR szPath[MAX_PATH] = { 0 };
	CString csTempPath;
	do
	{
		CString FileName = FileTree.GetItemText(THD);
		THD = FileTree.GetParentItem(THD);

		if (FileName.Find(L":") == -1)
		{
			FileName.Insert(0, L"\\");
		}
		csTempPath.Insert(0, FileName);

	} while (csTempPath.Find(L":") == -1);
	csTempPath.Append(L"\\");
	WideCharToMultiByte(CP_ACP, 0, csTempPath, -1, pcPath, MAX_PATH, NULL, NULL);//CStringToChar
	return TRUE;
}

//获取树中的文件路径
BOOL Filemanager::GetFilePathInTree(PCHAR pcPath)
{
	HTREEITEM THD = FileTree.GetSelectedItem();
	if (THD == NULL)
	{
		return FALSE;
	}
	WCHAR szPath[MAX_PATH] = { 0 };
	g_THD = THD;
	CString csTempPath;
	do
	{
		CString FileName = FileTree.GetItemText(THD);
		THD = FileTree.GetParentItem(THD);

		if (FileName.Find(L":") == -1)
		{
			FileName.Insert(0, L"\\");
		}
		csTempPath.Insert(0, FileName);

	} while (csTempPath.Find(L":") == -1);
	WideCharToMultiByte(CP_ACP, 0, csTempPath, -1, pcPath, MAX_PATH, NULL, NULL);//CStringToChar
	return TRUE;
}