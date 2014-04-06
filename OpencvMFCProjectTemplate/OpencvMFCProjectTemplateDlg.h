
// OpencvMFCProjectTemplateDlg.h : header file
//

#pragma once


// COpencvMFCProjectTemplateDlg dialog
class COpencvMFCProjectTemplateDlg : public CDialogEx
{
// Construction
public:
	COpencvMFCProjectTemplateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_OPENCVMFCPROJECTTEMPLATE_DIALOG };

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
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedButtonHogtest();
	afx_msg void OnBnClickedButtonSavehogtotxt();
	afx_msg void OnBnClickedButtonMergehogfeatures();
	afx_msg void OnBnClickedButtonReadimageandnumrecognition();
	afx_msg void OnBnClickedButtonDealwithcuttednum();
	afx_msg void OnBnClickedButtonDealwithmnist();
	afx_msg void OnBnClickedButtonBankcardnumrecognition();
};
