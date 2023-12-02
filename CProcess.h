#pragma once


// CProcess 对话框

class CProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CProcess)

public:
	CProcess(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl ProcessList;
	afx_msg LRESULT OnProcessListMag(WPARAM wParam, LPARAM lParam);
	DWORD dwProcessIndex = 0;
	afx_msg void OnRclickListOpenMeun(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillProcess();
};
