// Header file ~
//

#if !defined(AFX_SIMCITY2DLG_H__D0A40502_A019_4CA6_8E78_D54371361C10__INCLUDED_)
#define AFX_SIMCITY2DLG_H__D0A40502_A019_4CA6_8E78_D54371361C10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSimCity2Dlg dialog

//There are 15 possible cursor selections... An enumerated type was used to make things
//easier on the eyes
enum TOOL{BULLDOZER=1,ROAD,RAIL,PLINE,PARK,RES,COM,IND,POLICE,FIREDEPT,STADIUM,SEAPORT,COAL,NUCLEAR,AIRPORT};

class CSimCity2Dlg : public CDialog
{
// Construction
public:
	CSimCity2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSimCity2Dlg)
	enum { IDD = IDD_SIMCITY2_DIALOG };
	CButton	m_tb9;
	CButton	m_tb8;
	CButton	m_tb7;
	CButton	m_tb6;
	CButton	m_tb5;
	CButton	m_tb4;
	CButton	m_tb10;
	CButton	m_tb11;
	CButton	m_tb12;
	CButton	m_tb14;
	CButton	m_tb13;
	CButton	m_tb15;
	CButton	m_tb3;
	CButton	m_tb2;
	CButton	m_tb1;
	CScrollBar	m_scrollv;
	CScrollBar	m_scrollh;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimCity2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	TOOL cursor; //Whichever tool is active currently.
	int cursorsize; //If the cursors could actually display properly, this would have some meaning..
	int xpos; //See above. These were to be used to store the x and y co-ordinates of the mouse..
	int ypos;
	int hscrollpos;//The position of the horizontal scroll bar.
	int vscrollpos;//Same for vertical scrollbar.
	int money; //How much funds the player currently has.
	int population; //The city's current population.
	int counter; //To avoid needing multiple timers. The counter just keeps track of how many times
	             //the timer has been 'set off' so that a game year (much longer increment of time)
				 //can be accounted for..
	bool taxcol;
    CMaskedBitmap m_res; //These are to store the game's images.
	CMaskedBitmap m_com;
	CMaskedBitmap m_ind;
	CMaskedBitmap m_park;
	CMaskedBitmap m_airport;
	CMaskedBitmap m_blank;
	CMaskedBitmap m_coal;
	CMaskedBitmap m_policedept;
	CMaskedBitmap m_firedept;
	CMaskedBitmap m_forest;
	CMaskedBitmap m_seaport;
	CMaskedBitmap m_stadium;
	CMaskedBitmap m_nuclear;
	CMaskedBitmap m_water;
	CMaskedBitmap m_ch1;
	CMaskedBitmap m_ch2;
	CMaskedBitmap m_ch3;
	CMaskedBitmap m_ch4;
	CMaskedBitmap m_cl1;
	CMaskedBitmap m_cl2;
	CMaskedBitmap m_cl3;
	CMaskedBitmap m_cl4;
	CMaskedBitmap m_cm1;
	CMaskedBitmap m_cm2;
	CMaskedBitmap m_cm3;
	CMaskedBitmap m_cm4;
	CMaskedBitmap m_cu1;
	CMaskedBitmap m_cu2;
	CMaskedBitmap m_cu3;
	CMaskedBitmap m_cu4;
	CMaskedBitmap m_ih1;
	CMaskedBitmap m_ih2;
	CMaskedBitmap m_ih3;
	CMaskedBitmap m_ih4;
	CMaskedBitmap m_il1;
	CMaskedBitmap m_il2;
	CMaskedBitmap m_il3;
	CMaskedBitmap m_il4;
	CMaskedBitmap m_rh1;
	CMaskedBitmap m_rh2;
	CMaskedBitmap m_rh3;
	CMaskedBitmap m_rh4;
	CMaskedBitmap m_rl1;
	CMaskedBitmap m_rl2;
	CMaskedBitmap m_rl3;
	CMaskedBitmap m_rl4;
	CMaskedBitmap m_rm1;
	CMaskedBitmap m_rm2;
	CMaskedBitmap m_rm3;
	CMaskedBitmap m_rm4;
	CMaskedBitmap m_ru1;
	CMaskedBitmap m_ru2;
	CMaskedBitmap m_ru3;
	CMaskedBitmap m_ru4;
	CMaskedBitmap m_rail3ir;
	CMaskedBitmap m_rail3id;
	CMaskedBitmap m_rail3il;
	CMaskedBitmap m_rail3iu;
	CMaskedBitmap m_rail4i;
	CMaskedBitmap m_railbl;
	CMaskedBitmap m_railbr;
	CMaskedBitmap m_railtl;
	CMaskedBitmap m_railtr;
	CMaskedBitmap m_railh;
	CMaskedBitmap m_railv;
	CMaskedBitmap m_road3ir;
	CMaskedBitmap m_road3id;
	CMaskedBitmap m_road3il;
	CMaskedBitmap m_road3iu;
	CMaskedBitmap m_road4i;
	CMaskedBitmap m_roadbl;
	CMaskedBitmap m_roadbr;
	CMaskedBitmap m_roadtl;
	CMaskedBitmap m_roadtr;
	CMaskedBitmap m_roadh;
	CMaskedBitmap m_roadv;
	CMaskedBitmap m_ti1;
	CMaskedBitmap m_ti2;
	CMaskedBitmap m_ti3;
	CMaskedBitmap m_ti4;
	CMaskedBitmap m_ti5;
	CMaskedBitmap m_ti6;
	CMaskedBitmap m_ti7;
	CMaskedBitmap m_ti8;
	CMaskedBitmap m_ti9;
	CMaskedBitmap m_ti10;
	CMaskedBitmap m_ti11;
	CMaskedBitmap m_ti12;
	CMaskedBitmap m_ti13;
	CMaskedBitmap m_ti14;
	CMaskedBitmap m_ti15;
	CMaskedBitmap m_cursorfill;
	CMaskedBitmap m_pline3ir;
	CMaskedBitmap m_pline3id;
	CMaskedBitmap m_pline3il;
	CMaskedBitmap m_pline3iu;
	CMaskedBitmap m_pline4i;
	CMaskedBitmap m_plinebl;
	CMaskedBitmap m_plinebr;
	CMaskedBitmap m_plinetl;
	CMaskedBitmap m_plinetr;
	CMaskedBitmap m_plineh;
	CMaskedBitmap m_plinev;
	CMaskedBitmap m_nopower;
	void CalcPollute(); //These functions explain themselves...
	void CalcLandvalue();
	void CalcCrime();
	void CalcResProxim();
	void CalcPop(); //Calculate population
	bool IsFree(int x, int y); //These are explained when they're written...
	bool IsFree(int x, int y, int size);
	void Raise(int x,int y, int radius, int bywhat, int type);
	void Develop(HWND window,int hscrollpos,int vscrollpos);
	void FindPower(int x,int y);
	void FindPowerStart(HWND window,int hscrollpos, int vscrollpos);

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSimCity2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTb1();
	afx_msg void OnTb2();
	afx_msg void OnTb3();
	afx_msg void OnTb4();
	afx_msg void OnTb5();
	afx_msg void OnTb6();
	afx_msg void OnTb7();
	afx_msg void OnTb8();
	afx_msg void OnTb9();
	afx_msg void OnTb10();
	afx_msg void OnTb11();
	afx_msg void OnTb12();
	afx_msg void OnTb13();
	afx_msg void OnTb14();
	afx_msg void OnTb15();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMCITY2DLG_H__D0A40502_A019_4CA6_8E78_D54371361C10__INCLUDED_)
