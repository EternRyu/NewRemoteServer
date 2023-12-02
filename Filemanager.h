#pragma once


// Filemanager 对话框

class Filemanager : public CDialogEx
{
	DECLARE_DYNAMIC(Filemanager)

public:
	Filemanager(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Filemanager();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl FileTree;
	afx_msg LRESULT InitTreeCtrl(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT FolderInfoAddTree(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	VOID InitFileImageList();
	SHFILEINFO FileInfo;;
	BOOL GetPathInTree(PCHAR pcPath);
	BOOL GetFilePathInTree(PCHAR pcPath);
};
