#if !defined(AFX_TOOLSDLG_H__80F84009_C419_4526_B3A0_D6D4B4A82F02__INCLUDED_)
#define AFX_TOOLSDLG_H__80F84009_C419_4526_B3A0_D6D4B4A82F02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolsDlg dialog

class CToolsDlg : public CDialog
{
// Construction
public:
	CToolsDlg(CWnd* pParent = NULL);   // standard constructor
	CMaskedBitmap m_res;

	// Dialog Data
	//{{AFX_DATA(CToolsDlg)
	enum { IDD = IDD_TOOLS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLSDLG_H__80F84009_C419_4526_B3A0_D6D4B4A82F02__INCLUDED_)
