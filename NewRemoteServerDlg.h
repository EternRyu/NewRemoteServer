
// NewRemoteServerDlg.h: 头文件
//

#pragma once


// CNewRemoteServerDlg 对话框
class CNewRemoteServerDlg : public CDialogEx
{
// 构造
public:
	CNewRemoteServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWREMOTESERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl LinkList;
	DWORD dwIndex = 0;
	afx_msg LRESULT OnTTwarbListMag1(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRclickListOpenMenu(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOpenProcessDlg();
};
