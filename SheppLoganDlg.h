
// SheppLogonDlg.h : header file
//

#pragma once


// CSheppLogonDlg dialog
class CSheppLogonDlg : public CDialogEx
{
// Construction
public:
	CSheppLogonDlg(CWnd* pParent = nullptr);	// standard constructor
	~CSheppLogonDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHEPPLOGON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

 
// Implementation
protected:
	HICON m_hIcon;
	CImage* m_pImage = 0;
	void DrawImage(CImage* pImage);
	bool m_bAutoScale = false;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGenerate();
	afx_msg void OnBnClickedCopyImage();
	afx_msg void OnBnClickedAuto();
};
