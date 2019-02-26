//
// ~~My first step towards world domination~~
//
//

/*
This is basically a simplified version of Simcity for the SNES.
Not all of its features are here, but this is what is included:
-Scrollable map
-Ability to construct any buildings included in the original game
-Roads, railways, and power lines curve/intersect depending on their placement
-Zones should to be wired directly or indirectly to a power plant in order to be usable
-Overlapping of zones is prevented
-A 'Pseudo-3D' effect using image transparencies
-A timer is used to make development seem realistic
-Residential, commercial, and industrial zones develop depending on a number of factors

But, it should be noted that a cursor was meant to be also included in this game.
I tried using one (a bitmap image w/ transparency) and it worked, but the flashing of the
cursor was so bad and the movement was so choppy that I ended up removing it. (it left a 
'tail')... So, there are some spaces left where information regarding the cursor should go... 
Also, I experienced problems using TextOut (it only worked sometimes) so whenever taxes 
are collected, the information is MessageBox-ed to the user instead.
*/

//Includes
#include "stdafx.h"
#include "MaskedBitmap.h" //A class that makes it easier to load and draw images.
#include "Classes.h" //A class I made called CGridspace. (There used to be two...)
#include "SimCity2.h" //The header file for the application.
#include "SimCity2Dlg.h" //The header file for the dialog. There's only one dialog window, so...
//SPECIAL NOTE:
//The MaskedBitmap class was not written by me. I am not sure of the author- this class was from
//a file found in ICS4M's groupwork folder. The comment crediting it is here, since it felt
//not-right to comment this person's headerfile and .cpp file...

//Things that the ClassWizard makes for you
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Note: All of these functions below interact directly with the everything[][] grid.
//So, it seemed best to declare them this way rather than inside the header file. 
//I experienced some problems trying to declare everything[][] in the header file
//(it acted as if it'd never heard of CGridspace, even when the includes were in the
//right order) so this seemed like the only way (even though it's bad style)
CGridspace everything[100][100]; //The map used throughout the game (100 by 100).
bool hadpower[100][100]; //Explained in FindPower(...)
void MakeBlankGrid(CGridspace grid[100][100]); //All gridspaces are assigned be have blank land.


/////////////////////////////////////////////////////////////////////////////
// More gifts from the ClassWizard

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The constructor.

CSimCity2Dlg::CSimCity2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimCity2Dlg::IDD, pParent)
{
	hscrollpos=0; //The position for the horizontal scrollbar (It starts at zero)
	vscrollpos=0; //Same, for the vertical scrollbar.
	xpos=0; //The x-position of the mouse...
	ypos=0; //And the y-position of the mouse.
	money=10000; //The amount of money the player starts out with.; 
	population=0; //No one is at your city to start
	counter=0; //No time has elapsed yet..
	cursorsize=0; //Size of the cursor. If this value is 0, it's a 1x1 cursor, if it's 
	//1, it's 3x3, if it's 2, it's 4x4, and if it's 3, it's 6x6. These were arbitrarily chosen..
	cursor=BULLDOZER; //The 'Bulldozer' button is active by default when the player starts
	//the game. Also arbitarily chosen (and same as in the SNES game...)
	//From the ClassWizard
	//
	//   |
	//   |
	//   V

	//{{AFX_DATA_INIT(CSimCity2Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimCity2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimCity2Dlg)
	DDX_Control(pDX, IDC_TB9, m_tb9);
	DDX_Control(pDX, IDC_TB8, m_tb8);
	DDX_Control(pDX, IDC_TB7, m_tb7);
	DDX_Control(pDX, IDC_TB6, m_tb6);
	DDX_Control(pDX, IDC_TB5, m_tb5);
	DDX_Control(pDX, IDC_TB4, m_tb4);
	DDX_Control(pDX, IDC_TB10, m_tb10);
	DDX_Control(pDX, IDC_TB11, m_tb11);
	DDX_Control(pDX, IDC_TB12, m_tb12);
	DDX_Control(pDX, IDC_TB14, m_tb14);
	DDX_Control(pDX, IDC_TB13, m_tb13);
	DDX_Control(pDX, IDC_TB15, m_tb15);
	DDX_Control(pDX, IDC_TB3, m_tb3);
	DDX_Control(pDX, IDC_TB2, m_tb2);
	DDX_Control(pDX, IDC_TB1, m_tb1);
	DDX_Control(pDX, IDC_SCROLLV, m_scrollv);
	DDX_Control(pDX, IDC_SCROLLH, m_scrollh);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimCity2Dlg, CDialog)
	//{{AFX_MSG_MAP(CSimCity2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_TB1, OnTb1)
	ON_BN_CLICKED(IDC_TB2, OnTb2)
	ON_BN_CLICKED(IDC_TB3, OnTb3)
	ON_BN_CLICKED(IDC_TB4, OnTb4)
	ON_BN_CLICKED(IDC_TB5, OnTb5)
	ON_BN_CLICKED(IDC_TB6, OnTb6)
	ON_BN_CLICKED(IDC_TB7, OnTb7)
	ON_BN_CLICKED(IDC_TB8, OnTb8)
	ON_BN_CLICKED(IDC_TB9, OnTb9)
	ON_BN_CLICKED(IDC_TB10, OnTb10)
	ON_BN_CLICKED(IDC_TB11, OnTb11)
	ON_BN_CLICKED(IDC_TB12, OnTb12)
	ON_BN_CLICKED(IDC_TB13, OnTb13)
	ON_BN_CLICKED(IDC_TB14, OnTb14)
	ON_BN_CLICKED(IDC_TB15, OnTb15)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimCity2Dlg message handlers

BOOL CSimCity2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//Everything here is done on startup.

	MakeBlankGrid(everything); //All of the gridspaces should start with just blank land.
	
	//The game's images were painstakingly screencapped from the SNES rom- edited and
	//given transparencies, then loaded here. There's over 100 of them (lots of
	//program resources)
	m_res.LoadBitmap(IDB_RES); //The starting residential, commercial and industrial zones,
	m_com.LoadBitmap(IDB_COM); //buildings that aren't part of zoning, and landscaping images.
	m_ind.LoadBitmap(IDB_IND);
	m_park.LoadBitmap(IDB_PARK);
	m_airport.LoadBitmap(IDB_AIRPORT);
	m_blank.LoadBitmap(IDB_BLANK);
	m_coal.LoadBitmap(IDB_COAL);
	m_policedept.LoadBitmap(IDB_POLICEDEPT);
	m_firedept.LoadBitmap(IDB_FIREDEPT);
	m_forest.LoadBitmap(IDB_FOREST);
	m_seaport.LoadBitmap(IDB_SEAPORT);
	m_stadium.LoadBitmap(IDB_STADIUM);
	m_nuclear.LoadBitmap(IDB_NUCLEAR);
	m_water.LoadBitmap(IDB_WATER);
	m_ch1.LoadBitmap(IDB_CH1); //Commercial zones...
	m_ch2.LoadBitmap(IDB_CH2);
	m_ch3.LoadBitmap(IDB_CH3);
	m_ch4.LoadBitmap(IDB_CH4);
	m_cl1.LoadBitmap(IDB_CL1);
	m_cl2.LoadBitmap(IDB_CL2);
	m_cl3.LoadBitmap(IDB_CL3);
	m_cl4.LoadBitmap(IDB_CL4);
	m_cm1.LoadBitmap(IDB_CM1);
	m_cm2.LoadBitmap(IDB_CM2);
	m_cm3.LoadBitmap(IDB_CM3);
	m_cm4.LoadBitmap(IDB_CM4);
	m_cu1.LoadBitmap(IDB_CU1);
	m_cu2.LoadBitmap(IDB_CU2);
	m_cu3.LoadBitmap(IDB_CU3);
	m_cu4.LoadBitmap(IDB_CU4);
	m_ih1.LoadBitmap(IDB_IH1); //Industrial zones.. (the SNES game only included 8 and not
	m_ih2.LoadBitmap(IDB_IH2); //16 like the others)
	m_ih3.LoadBitmap(IDB_IH3);
	m_ih4.LoadBitmap(IDB_IH4);
	m_il1.LoadBitmap(IDB_IL1);
	m_il2.LoadBitmap(IDB_IL2);
	m_il3.LoadBitmap(IDB_IL3);
	m_il4.LoadBitmap(IDB_IL4);
	m_rh1.LoadBitmap(IDB_RH1); //Residential zones...
	m_rh2.LoadBitmap(IDB_RH2);
	m_rh3.LoadBitmap(IDB_RH3);
	m_rh4.LoadBitmap(IDB_RH4);
	m_rl1.LoadBitmap(IDB_RL1);
	m_rl2.LoadBitmap(IDB_RL2);
	m_rl3.LoadBitmap(IDB_RL3);
	m_rl4.LoadBitmap(IDB_RL4);
	m_rm1.LoadBitmap(IDB_RM1);
	m_rm2.LoadBitmap(IDB_RM2);
	m_rm3.LoadBitmap(IDB_RM3);
	m_rm4.LoadBitmap(IDB_RM4);
	m_ru1.LoadBitmap(IDB_RU1);
	m_ru2.LoadBitmap(IDB_RU2);
	m_ru3.LoadBitmap(IDB_RU3);
	m_ru4.LoadBitmap(IDB_RU4);
	m_rail3ir.LoadBitmap(IDB_RAIL3IR); //Railway images- different images need to be loaded
	m_rail3id.LoadBitmap(IDB_RAIL3ID); //for curves, intersections,etc.
	m_rail3il.LoadBitmap(IDB_RAIL3IL);
	m_rail3iu.LoadBitmap(IDB_RAIL3IU);
	m_rail4i.LoadBitmap(IDB_RAIL4I);
	m_railbl.LoadBitmap(IDB_RAILBL);
	m_railbr.LoadBitmap(IDB_RAILBR);
	m_railtl.LoadBitmap(IDB_RAILTL);
	m_railtr.LoadBitmap(IDB_RAILTR);
	m_railh.LoadBitmap(IDB_RAILH);
	m_railv.LoadBitmap(IDB_RAILV);
	m_road3ir.LoadBitmap(IDB_ROAD3IR); //Road images..
	m_road3id.LoadBitmap(IDB_ROAD3ID);
	m_road3il.LoadBitmap(IDB_ROAD3IL);
	m_road3iu.LoadBitmap(IDB_ROAD3IU);
	m_road4i.LoadBitmap(IDB_ROAD4I);
	m_roadbl.LoadBitmap(IDB_ROADBL);
	m_roadbr.LoadBitmap(IDB_ROADBR);
	m_roadtl.LoadBitmap(IDB_ROADTL);
	m_roadtr.LoadBitmap(IDB_ROADTR);
	m_roadh.LoadBitmap(IDB_ROADH);
	m_roadv.LoadBitmap(IDB_ROADV);
	m_pline3ir.LoadBitmap(IDB_PLINE3IR); //Power line images. They have 'curves' and 
	m_pline3id.LoadBitmap(IDB_PLINE3ID); //intersections too, so..
	m_pline3il.LoadBitmap(IDB_PLINE3IL);
	m_pline3iu.LoadBitmap(IDB_PLINE3IU);
	m_pline4i.LoadBitmap(IDB_PLINE4I);
	m_plinebl.LoadBitmap(IDB_PLINEBL);
	m_plinebr.LoadBitmap(IDB_PLINEBR);
	m_plinetl.LoadBitmap(IDB_PLINETL);
	m_plinetr.LoadBitmap(IDB_PLINETR);
	m_plineh.LoadBitmap(IDB_PLINEH);
	m_plinev.LoadBitmap(IDB_PLINEV);
	m_nopower.LoadBitmap(IDB_NOPOWER); //The lightning-bolt icon that zones show in their centers 
	m_ti1.LoadBitmap(IDB_T1); //When they don't have power.
	m_ti2.LoadBitmap(IDB_T2);
	m_ti3.LoadBitmap(IDB_T3);//These are the 15 icons displayed on the toolbar.
	m_ti4.LoadBitmap(IDB_T4);
	m_ti5.LoadBitmap(IDB_T5);
	m_ti6.LoadBitmap(IDB_T6);
	m_ti7.LoadBitmap(IDB_T7);
	m_ti8.LoadBitmap(IDB_T8);
	m_ti9.LoadBitmap(IDB_T9);
	m_ti10.LoadBitmap(IDB_T10);
	m_ti11.LoadBitmap(IDB_T11);
	m_ti12.LoadBitmap(IDB_T12);
	m_ti13.LoadBitmap(IDB_T13);
	m_ti14.LoadBitmap(IDB_T14);
	m_ti15.LoadBitmap(IDB_T15);
	m_cursorfill.LoadBitmap(IDB_CURSOR); //The game's cursor would have an image...
	m_tb1.SetBitmap(m_ti1);
	m_tb2.SetBitmap(m_ti2);//The 15 toolbar buttons need to have their images set to them.
	m_tb3.SetBitmap(m_ti3);
	m_tb4.SetBitmap(m_ti4);
	m_tb5.SetBitmap(m_ti5);
	m_tb6.SetBitmap(m_ti6);
	m_tb7.SetBitmap(m_ti7);
	m_tb8.SetBitmap(m_ti8);
	m_tb9.SetBitmap(m_ti9);
	m_tb10.SetBitmap(m_ti10);
	m_tb11.SetBitmap(m_ti11);
	m_tb12.SetBitmap(m_ti12);
	m_tb13.SetBitmap(m_ti13);
	m_tb14.SetBitmap(m_ti14);
	m_tb15.SetBitmap(m_ti15);
	m_scrollh.SetScrollRange(0,1000); //The scroll ranges and scroll positions's values are
	m_scrollh.SetScrollPos(0);        //set arbitarily.
	m_scrollv.SetScrollRange(0,1000);
	m_scrollv.SetScrollPos(0);
	cursor=RAIL;
	taxcol=FALSE;
	SetTimer(1,6000,NULL); //The game's timer is set to go off one every 6 seconds.
	return TRUE; 
}

void CSimCity2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimCity2Dlg::OnPaint() //This is where the screen in painted.
//InvalidateRect is used when needed to just paint a small part of the screen.
{
	CPaintDC dc(this); //Make a device context for this window. (SimCity2Dlg)

/*

  
Here are what the .image numbers mean:
Blank land            0
Forest                1
Park                  2
Water                 3
The 11 road images    4-14
The 11 rail images    15-25   
The 11 power line images   26-36 	
	
In two for loops, each gridspace's image is drawn properly. There will be multiple sets of
for loops. This is the first one. It is for drawing landscaping (i.e. ground, water, etc.)	
*/

	for (int i=0;i<100;i++)
	{
		for (int j=0;j<100;j++)
		{
			if (everything[i][j].image==0)
			{
				m_blank.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));		
			}
			else if (everything[i][j].image==1)
			{
				m_forest.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
			}
			else if (everything[i][j].image==2)
			{
				m_park.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
			}
			else if (everything[i][j].image==3)
			{
				m_water.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
			}
			if (everything[i][j].road)
			{ //Depending on how the roads are connected, the appropriate image needs to be drawn.
			  //For example, if the piece of road currently being checked is linked to roads in all 
			  //directions, the current road will be drawn as a four-way intersection.
			  //All of the cases are accounted for..
				if (everything[i][j].left && everything[i][j].right && everything[i][j].up && everything[i][j].down)
					m_road4i.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].right && everything[i][j].down)
					m_road3id.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].up && everything[i][j].down)
					m_road3il.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].right && everything[i][j].up && everything[i][j].down)
					m_road3ir.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].right && everything[i][j].up)
					m_road3iu.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].down)
					m_roadbl.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].right && everything[i][j].down)
					m_roadbr.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left &&  everything[i][j].up)
					m_roadtl.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].right && everything[i][j].up)
					m_roadtr.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left || everything[i][j].right)
					m_roadh.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].up || everything[i][j].down)
					m_roadv.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else
					m_roadh.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
			}
			if (everything[i][j].rail)
			{
				//It works similarly to the roads.
				if (everything[i][j].left && everything[i][j].right && everything[i][j].up && everything[i][j].down)
					m_rail4i.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].right && everything[i][j].down)
					m_rail3id.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].up && everything[i][j].down)
					m_rail3il.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].right && everything[i][j].up && everything[i][j].down)
					m_rail3ir.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].right && everything[i][j].up)
					m_rail3iu.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left && everything[i][j].down)
					m_railbl.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].right && everything[i][j].down)
					m_railbr.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left &&  everything[i][j].up)
					m_railtl.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].right && everything[i][j].up)
					m_railtr.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].left || everything[i][j].right)
					m_railh.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else if (everything[i][j].up || everything[i][j].down)
					m_railv.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
				else
					m_railh.Draw(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos));
			}
			if (everything[i][j].pline && !everything[i][j].builpart)
			{
				//These also work in the same way as roads.
				if (everything[i][j].pLeft && everything[i][j].pRight && everything[i][j].pUp && everything[i][j].pDown)
					m_pline4i.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pLeft && everything[i][j].pRight && everything[i][j].pDown)
					m_pline3id.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pLeft && everything[i][j].pUp && everything[i][j].pDown)
					m_pline3il.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pRight && everything[i][j].pUp && everything[i][j].pDown)
					m_pline3ir.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pLeft && everything[i][j].pRight && everything[i][j].pUp)
					m_pline3iu.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pLeft && everything[i][j].pDown)
					m_plinebl.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pRight && everything[i][j].pDown)
					m_plinebr.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pLeft &&  everything[i][j].pUp)
					m_plinetl.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pRight && everything[i][j].pUp)
					m_plinetr.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pLeft || everything[i][j].pRight)
					m_plineh.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else if (everything[i][j].pUp || everything[i][j].pDown)
					m_plinev.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
				else
					m_plineh.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
			}
		}
	}
	//Next, the map is searched for centers of buildings. If a 'bcenter' is found, the appropriate
	//image is drawn there so its center matches the bcenter. All of the numbers for 'bcenter'
	//were chosen arbitrarily...
	/*
	The numbers are like follows:
	Residential: 1-17 
	Commercial: 18-34
	Industrial: 35-43
	Everything else: 44-58
	*/
	//The images are drawn from top to bottom, then from left to right, so that the pseudo-3D
	//effect works properly.
	for (int j=0;j<100;j++)
	{
		for (int i=0;i<100;i++)
		{
			if (everything[i][j].bcenter)
			{
				if(everything[i][j].bcenter==1)
				{
					m_res.DrawTransparent(&dc,i*8-(8*hscrollpos)-8,j*8-(8*vscrollpos)-8,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==2)
				{
					m_rl2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==3)
				{
					m_rl3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==4)
				{
					m_rl4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==5)
				{
					m_rm2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==6)
				{
					m_rm3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==7)
				{
					m_rm4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==8)
				{
					m_ru2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==9)
				{
					m_ru3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==10)
				{
					m_ru4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==11)
				{
					m_rh2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==12)
				{
					m_rh3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==13)
				{
					m_rh4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==18)
				{
					m_com.DrawTransparent(&dc,i*8-(8*hscrollpos)-8,j*8-(8*vscrollpos)-8,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==19)
				{
					m_cl1.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==20)
				{
					m_cl2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==21)
				{
					m_cl3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==22)
				{
					m_cl4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==23)
				{
					m_cm1.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==24)
				{
					m_cm2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==25)
				{
					m_cm3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==26)
				{
					m_cm4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==27)
				{
					m_cu1.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==28)
				{
					m_cu2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==29)
				{
					m_cu3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==30)
				{
					m_cu4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==31)
				{
					m_ch1.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==32)
				{
					m_ch2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==33)
				{
					m_ch3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==34)
				{
					m_ch4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==35)
				{
					m_ind.DrawTransparent(&dc,i*8-(8*hscrollpos)-8,j*8-(8*vscrollpos)-8,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==36)
				{
					m_il1.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==37)
				{
					m_il2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==38)
				{
					m_il3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==39)
				{
					m_il4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==40)
				{
					m_ih1.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==41)
				{
					m_ih2.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==42)
				{
					m_ih3.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==43)
				{
					m_ih4.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==52)
				{
					m_policedept.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-15,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==53)
				{
					m_firedept.DrawTransparent(&dc,i*8-(8*hscrollpos)-11,j*8-(8*vscrollpos)-15,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==54)
				{
					m_stadium.DrawTransparent(&dc,i*8-(8*hscrollpos)-24,j*8-(8*vscrollpos)-24,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==55)
				{
					m_seaport.DrawTransparent(&dc,i*8-(8*hscrollpos)-24,j*8-(8*vscrollpos)-24,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==56)
				{
					m_coal.DrawTransparent(&dc,i*8-(8*hscrollpos)-24,j*8-(8*vscrollpos)-24,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==57)
				{
					m_nuclear.DrawTransparent(&dc,i*8-(8*hscrollpos)-24,j*8-(8*vscrollpos)-24,RGB(255,0,255));
				}
				else if(everything[i][j].bcenter==58)
				{
					m_airport.DrawTransparent(&dc,i*8-(8*hscrollpos)-16,j*8-(8*vscrollpos)-16,RGB(255,0,255));
				}
				if (!everything[i][j].power)
					m_nopower.DrawTransparent(&dc,i*8-(8*hscrollpos),j*8-(8*vscrollpos),RGB(255,0,255));
			}
		}
	}//There was to be a cursor here...
	if (cursorsize==0)
	{
		//m_cursorfill.DrawTransparent(&dc,xpos-(8*hscrollpos),ypos-(8*vscrollpos),RGB(255,255,255));
	}
	CString ftext,ptext; //The current population/amount of funds is outputted.
	ftext.Format("%i          ",money);
	TextOut(dc,20,400,ftext,sizeof(ftext));
	ptext.Format("%i          ",population);
	TextOut(dc,20,440,ptext,sizeof(ptext));
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimCity2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void MakeBlankGrid(CGridspace grid[100][100])
//All of the grid spaces need to be assigned to blank land before the user starts playing.
{
	for (int i=0;i<100;i++)
	{
		for (int j=0;j<100;j++)
		{
			grid[i][j].image=0;
		}
	}
}

//This function allows the horizontal scroll bar to be useable. The nSBCode
//indicates whether to scroll left or right, and whether the arrow or scroll
//bar itself was clicked. 
//After scrolling, the whole screen needs to be InvalidateRect-ed.
void CSimCity2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect temp;
	temp.bottom=1000;
	temp.top=0;
	temp.left=0;
	temp.right=1000;
	if(nSBCode==1)
		m_scrollh.SetScrollPos(m_scrollh.GetScrollPos()+5);
	if(nSBCode==0)
		m_scrollh.SetScrollPos(m_scrollh.GetScrollPos()-5);
	if(nSBCode==3)
		m_scrollh.SetScrollPos(m_scrollh.GetScrollPos()+10);
	if(nSBCode==2)
		m_scrollh.SetScrollPos(m_scrollh.GetScrollPos()-10);
	hscrollpos=m_scrollh.GetScrollPos();
	InvalidateRect(temp);
}

//This is for the vertical scrollbar-it works in exactly the same way as the horizontal one.
void CSimCity2Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	CRect temp;
	temp.bottom=1000;
	temp.top=-1000;
	temp.left=-1000;
	temp.right=1000;
	if(nSBCode==1)
		m_scrollv.SetScrollPos(m_scrollv.GetScrollPos()+5);
	if(nSBCode==0)
		m_scrollv.SetScrollPos(m_scrollv.GetScrollPos()-5);
	if(nSBCode==3)
		m_scrollv.SetScrollPos(m_scrollv.GetScrollPos()+10);
	if(nSBCode==2)
		m_scrollv.SetScrollPos(m_scrollv.GetScrollPos()-10);
	vscrollpos=m_scrollv.GetScrollPos();
	InvalidateRect(temp);
}

void CSimCity2Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect temp; //This will contain the information that needs to be passed to InvalidateRect.
	CPaintDC dc(this); //The device context
	int x,y; //Variables for which gridspace the user clicked on
	x=point.x+(8*hscrollpos);
	y=point.y+(8*vscrollpos);//The gridspace is calculated from the co-ordinates
	x=x/8; //at which the user clicked (point.x and point.y)
	y=y/8;
	//Exactly what should be built/destroyed is determined from what button on the
	//toolbar is currently active. (There's 15 different buttons)
	if (cursor==BULLDOZER && !everything[x][y].builpart && money>=1)
	{
	//The bulldozer can destroy landscaping and buildings.
		if (everything[x][y].bcenter)
		{
		//If the user has clicked on the center of a building (that's the only way to demolish
		//a building, same as in SNES game) then the whole building will be destroyed as
		//well as all of its invisible 'power lines'. The size of the building can be found out
		//through what number bcenter it has. The cases for all 3 building sizes are included.
			if (everything[x][y].bcenter<=53) //3x3 zones
			{
				temp.bottom=point.y-(point.y%8)+16;
				temp.top=point.y-(point.y%8)-16;
				temp.left=point.x-(point.x%8)-8;
				temp.right=point.x-(point.x%8)+16;
				everything[x][y].bcenter=0;
				everything[x-1][y].builpart=FALSE;
				everything[x+1][y].builpart=FALSE;
				everything[x][y-1].builpart=FALSE;
				everything[x-1][y-1].builpart=FALSE;
				everything[x+1][y-1].builpart=FALSE;
				everything[x][y+1].builpart=FALSE;
				everything[x-1][y+1].builpart=FALSE;
				everything[x+1][y+1].builpart=FALSE;
				everything[x][y].bcenter=0;
				everything[x-1][y].pline=FALSE;
				everything[x+1][y].pline=FALSE;
				everything[x][y-1].pline=FALSE;
				everything[x-1][y-1].pline=FALSE;
				everything[x+1][y-1].pline=FALSE;
				everything[x][y+1].pline=FALSE;
				everything[x-1][y+1].pline=FALSE;
				everything[x+1][y+1].pline=FALSE;
			}
			else if (everything[x][y].bcenter!=58) //4x4 zones
			{
				temp.bottom=point.y-(point.y%8)+24;
				temp.top=point.y-(point.y%8)-16;
				temp.left=point.x-(point.x%8)-16;
				temp.right=point.x-(point.x%8)+24;
				cursorsize=2;
				everything[x][y].bcenter=0;
				everything[x-1][y-1].builpart=FALSE;
				everything[x][y-1].builpart=FALSE;
				everything[x+1][y-1].builpart=FALSE;
				everything[x+2][y-1].builpart=FALSE;
				everything[x-1][y].builpart=FALSE;
				everything[x+1][y].builpart=FALSE;
				everything[x+2][y].builpart=FALSE;
				everything[x-1][y+1].builpart=FALSE;
				everything[x][y+1].builpart=FALSE;
				everything[x+1][y+1].builpart=FALSE;
				everything[x+2][y+1].builpart=FALSE;
				everything[x-1][y+2].builpart=FALSE;
				everything[x][y+2].builpart=FALSE;
				everything[x+1][y+2].builpart=FALSE;
				everything[x+2][y+2].builpart=FALSE;
				everything[x-1][y-1].pline=FALSE;
				everything[x][y-1].pline=FALSE;
				everything[x+1][y-1].pline=FALSE;
				everything[x+2][y-1].pline=FALSE;
				everything[x-1][y].pline=FALSE;
				everything[x+2][y].pline=FALSE;
				everything[x-1][y+1].pline=FALSE;
				everything[x+2][y+1].pline=FALSE;
				everything[x-1][y+2].pline=FALSE;
				everything[x][y+2].pline=FALSE;
				everything[x+1][y+2].pline=FALSE;
				everything[x+2][y+2].pline=FALSE;
			}
			else //the 6x6 zone
			{
				temp.bottom=point.y-(point.y%8)+36;
				temp.top=point.y-(point.y%8)-24;
				temp.left=point.x-(point.x%8)-16;
				temp.right=point.x-(point.x%8)+36;
				everything[x][y].bcenter=0;
				everything[x-2][y-2].builpart=FALSE;
				everything[x-1][y-2].builpart=FALSE;
				everything[x][y-2].builpart=FALSE;
				everything[x+1][y-2].builpart=FALSE;
				everything[x+2][y-2].builpart=FALSE;
				everything[x+3][y-2].builpart=FALSE;
				everything[x-2][y-1].builpart=FALSE;
				everything[x-1][y-1].builpart=FALSE;
				everything[x][y-1].builpart=FALSE;
				everything[x+1][y-1].builpart=FALSE;
				everything[x+2][y-1].builpart=FALSE;
				everything[x+3][y-1].builpart=FALSE;
				everything[x-2][y].builpart=FALSE;
				everything[x-1][y].builpart=FALSE;
				everything[x+1][y].builpart=FALSE;
				everything[x+2][y].builpart=FALSE;
				everything[x+3][y].builpart=FALSE;
				everything[x-2][y+1].builpart=FALSE;
				everything[x-1][y+1].builpart=FALSE;
				everything[x][y+1].builpart=FALSE;
				everything[x+1][y+1].builpart=FALSE;
				everything[x+2][y+1].builpart=FALSE;
				everything[x+3][y+1].builpart=FALSE;
				everything[x-2][y+2].builpart=FALSE;
				everything[x-1][y+2].builpart=FALSE;
				everything[x][y+2].builpart=FALSE;
				everything[x+1][y+2].builpart=FALSE;
				everything[x+2][y+2].builpart=FALSE;
				everything[x+3][y+2].builpart=FALSE;
				everything[x-2][y+3].builpart=FALSE;
				everything[x-1][y+3].builpart=FALSE;
				everything[x][y+3].builpart=FALSE;
				everything[x+1][y+3].builpart=FALSE;
				everything[x+2][y+3].builpart=FALSE;
				everything[x+3][y+3].builpart=FALSE;
				everything[x-2][y-2].pline=FALSE;
				everything[x-1][y-2].pline=FALSE;
				everything[x][y-2].pline=FALSE;
				everything[x+1][y-2].pline=FALSE;
				everything[x+2][y-2].pline=FALSE;
				everything[x+3][y-2].pline=FALSE;
				everything[x-2][y-1].pline=FALSE;
				everything[x+3][y-1].pline=FALSE;
				everything[x-2][y].pline=FALSE;
				everything[x+3][y].pline=FALSE;
				everything[x-2][y+1].pline=FALSE;
				everything[x+3][y+1].pline=FALSE;
				everything[x-2][y+2].pline=FALSE;
				everything[x+3][y+2].pline=FALSE;
				everything[x-2][y+3].pline=FALSE;
				everything[x-1][y+3].pline=FALSE;
				everything[x][y+3].pline=FALSE;
				everything[x+1][y+3].pline=FALSE;
				everything[x+2][y+3].pline=FALSE;
				everything[x+3][y+3].pline=FALSE;
			}
		}
		else
		{
			//This is executed if the user didn't click on a bcenter, but rather some other 
			//non-building gridspace on the map. All powerlines, roads, rails, and landscaping 
			//will be removed from the gridspace.
			//If it's a linked road/rail/pline, the space around it will also have to be
			//InvalidateRect-ed, so those cases are also considered.
			temp.bottom=point.y-(point.y%8)+8;
			temp.top=point.y-(point.y%8);
			temp.left=point.x-(point.x%8);
			temp.right=point.x-(point.x%8)+8;
			cursorsize=0;
			everything[x][y].image=0;
			everything[x][y].left=FALSE;
			everything[x][y].right=FALSE;
			everything[x][y].up=FALSE;
			everything[x][y].down=FALSE;
			everything[x][y].road=FALSE;
			everything[x][y].rail=FALSE;
			everything[x+1][y].left=FALSE;
			everything[x-1][y].right=FALSE;
			everything[x][y+1].up=FALSE;
			everything[x][y-1].down=FALSE;
			everything[x][y].pLeft=FALSE;
			everything[x][y].pRight=FALSE;
			everything[x][y].pUp=FALSE;
			everything[x][y].pDown=FALSE;
			everything[x][y].pline=FALSE;
			everything[x+1][y].pLeft=FALSE;
			everything[x-1][y].pRight=FALSE;
			everything[x][y+1].pUp=FALSE;
			everything[x][y-1].pDown=FALSE;
			if (everything[x-1][y-1].road || everything[x-1][y].road || everything[x-1][y+1].road || everything[x-1][y-1].rail || everything[x-1][y].rail || everything[x-1][y+1].rail || everything[x-1][y-1].pline || everything[x-1][y].pline || everything[x-1][y+1].pline)
				temp.left-=8;
			if (everything[x+1][y-1].road || everything[x+1][y].road || everything[x+1][y+1].road || everything[x+1][y-1].rail || everything[x+1][y].rail || everything[x+1][y+1].rail || everything[x+1][y-1].pline || everything[x+1][y].pline || everything[x+1][y+1].pline)
				temp.right+=8;
			if (everything[x-1][y+1].road || everything[x][y+1].road || everything[x+1][y+1].road || everything[x-1][y+1].rail || everything[x][y+1].rail || everything[x+1][y+1].rail || everything[x-1][y+1].pline || everything[x][y+1].pline || everything[x+1][y+1].pline)
				temp.bottom+=8;
			if (everything[x-1][y-1].road || everything[x][y-1].road || everything[x+1][y-1].road || everything[x-1][y-1].rail || everything[x][y-1].rail || everything[x+1][y-1].rail || everything[x-1][y-1].pline || everything[x][y-1].pline || everything[x+1][y-1].pline)
				temp.top-=8;
		}
		money--;
	}
	else if (cursor==ROAD && IsFree(x,y) && money>=10)
	//The function 'IsFree' is used often from here on in order to check whether there is enough
	//available space for what the user is attempting to build.
	{
		//When a user builds a road, the spaces around the new road need to be examined, to
		//check whether the road needs to curve or intersect. The gridspace's directional variables
		//are set here accordingly; the act of actually deciding which image to draw is handled
		//in OnPaint().
		temp.bottom=point.y-(point.y%8)+8;
		temp.top=point.y-(point.y%8);
		temp.left=point.x-(point.x%8);
		temp.right=point.x-(point.x%8)+8;
		cursorsize=0;
		money-=10;
		everything[x][y].road=TRUE;
		if (everything[x+1][y].road)
		{
			everything[x][y].right=TRUE;
			everything[x+1][y].left=TRUE;
			temp.right+=8;
		}
		if (everything[x-1][y].road)
		{
			everything[x][y].left=TRUE;
			everything[x-1][y].right=TRUE;
			temp.left-=8;
		}
		if (everything[x][y-1].road)
		{
			everything[x][y].up=TRUE;
			everything[x][y-1].down=TRUE;
			temp.top-=8;
		}
		if (everything[x][y+1].road)
		{
			everything[x][y].down=TRUE;
			everything[x][y+1].up=TRUE;
			temp.bottom+=8;
		}
	}
	else if (cursor==RAIL && IsFree(x,y) && money>=20)
	{
		//Rails work in exactly the same way as roads; just the cost and appearance are
		//different.
		temp.bottom=point.y-(point.y%8)+8;
		temp.top=point.y-(point.y%8);
		temp.left=point.x-(point.x%8);
		temp.right=point.x-(point.x%8)+8;
		cursorsize=0;
		money-=20;
		everything[x][y].rail=TRUE;
		if (everything[x+1][y].rail)
		{
			everything[x][y].right=TRUE;
			everything[x+1][y].left=TRUE;
			temp.right+=8;
		}
		if (everything[x-1][y].rail)
		{
			everything[x][y].left=TRUE;
			everything[x-1][y].right=TRUE;
			temp.left-=8;
		}
		if (everything[x][y-1].rail)
		{
			everything[x][y].up=TRUE;
			everything[x][y-1].down=TRUE;
			temp.top-=8;
		}
		if (everything[x][y+1].rail)
		{
			everything[x][y].down=TRUE;
			everything[x][y+1].up=TRUE;
			temp.bottom+=8;
		}
	}
	else if (cursor==PLINE && (IsFree(x,y) || everything[x][y].road || everything[x][y].rail) && money>=5)
	{
		//These work the same way as roads, except that they use separate directional variables.
		//This is so that powerlines will be able to overlap roads and railways.
		temp.bottom=point.y-(point.y%8)+8;
		temp.top=point.y-(point.y%8);
		temp.left=point.x-(point.x%8);
		temp.right=point.x-(point.x%8)+8;
		cursorsize=0;
		money-=5;
		everything[x][y].pline=TRUE;
		if (everything[x+1][y].pline)
		{
			everything[x][y].pRight=TRUE;
			everything[x+1][y].pLeft=TRUE;
			temp.right+=8;
		}
		if (everything[x-1][y].pline)
		{
			everything[x][y].pLeft=TRUE;
			everything[x-1][y].pRight=TRUE;
			temp.left-=8;
		}
		if (everything[x][y-1].pline)
		{
			everything[x][y].pUp=TRUE;
			everything[x][y-1].pDown=TRUE;
			temp.top-=8;
		}
		if (everything[x][y+1].pline)
		{
			everything[x][y].pDown=TRUE;
			everything[x][y+1].pUp=TRUE;
			temp.bottom+=8;
		}
	}
	else if (cursor==PARK && IsFree(x,y) && money>=10)
	{
		//Wherever the user clicked, the landscaping changes...
		temp.bottom=point.y-(point.y%8)+8;
		temp.top=point.y-(point.y%8);
		temp.left=point.x-(point.x%8);
		temp.right=point.x-(point.x%8)+8;
		cursorsize=0;
		money-=10;
		everything[x][y].image=2;
	}
	else if (cursor==RES && IsFree(x,y,3) && money>=100)
	{
		//The construction of zones of all sizes work basically the same way. A bcenter
		//is made in the gridspace on which the user clicked. 'builparts' are made surrounding
		//the bcenter, depending on how big the zones need to be (the bcenter on 4x4 zones isn't
		//exactly in the middle, understandably). Then powerlines are assigned to be on the edges
		//of the building... So that nearby power lines will actually connect to the building when
		//they need to, rather than just sit adjacent to it.
		temp.bottom=point.y-(point.y%8)+16;
		temp.top=point.y-(point.y%8)-8;
		temp.left=point.x-(point.x%8)-8;
		temp.right=point.x-(point.x%8)+16;
		cursorsize=1;
		money-=100;
		everything[x][y].bcenter=1;
		everything[x+1][y].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x-1][y-1].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+1][y].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x][y+1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+1][y+1].pline=TRUE;
	}
	else if (cursor==COM && IsFree(x,y,3) && money>=100)
	{
		temp.bottom=point.y-(point.y%8)+16;
		temp.top=point.y-(point.y%8)-8;
		temp.left=point.x-(point.x%8)-8;
		temp.right=point.x-(point.x%8)+16;
		cursorsize=1;
		money-=100;
		everything[x][y].bcenter=18;
		everything[x+1][y].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x-1][y-1].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+1][y].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x][y+1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+1][y+1].pline=TRUE;
	}
	else if (cursor==IND && IsFree(x,y,3) && money>=100)
	{
		temp.bottom=point.y-(point.y%8)+16;
		temp.top=point.y-(point.y%8)-8;
		temp.left=point.x-(point.x%8)-8;
		temp.right=point.x-(point.x%8)+16;
		cursorsize=1;
		money-=100;
		everything[x][y].bcenter=35;
		everything[x+1][y].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x-1][y-1].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+1][y].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x][y+1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+1][y+1].pline=TRUE;
	}
	else if (cursor==POLICE && IsFree(x,y,3) && money>=500)
	{
		temp.bottom=point.y-(point.y%8)+16;
		temp.top=point.y-(point.y%8)-8;
		temp.left=point.x-(point.x%8)-8;
		temp.right=point.x-(point.x%8)+16;
		cursorsize=1;
		money-=500;
		everything[x][y].bcenter=52;
		everything[x+1][y].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x-1][y-1].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+1][y].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x][y+1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+1][y+1].pline=TRUE;
	}
	else if (cursor==FIREDEPT && IsFree(x,y,3) && money>=500)
	{
		temp.bottom=point.y-(point.y%8)+16;
		temp.top=point.y-(point.y%8)-16;
		temp.left=point.x-(point.x%8)-8;
		temp.right=point.x-(point.x%8)+16;
		cursorsize=1;
		money-=500;
		everything[x][y].bcenter=53;
		everything[x+1][y].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x-1][y-1].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+1][y].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x][y+1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+1][y+1].pline=TRUE;
	}
	else if (cursor==STADIUM && IsFree(x,y,4) && money>=2000)
	{
		temp.bottom=point.y-(point.y%8)+24;
		temp.top=point.y-(point.y%8)-16;
		temp.left=point.x-(point.x%8)-16;
		temp.right=point.x-(point.x%8)+24;
		cursorsize=2;
		money-=2000;
		everything[x][y].bcenter=54;
		everything[x-1][y-1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+2][y-1].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x+1][y].builpart=TRUE;
		everything[x+2][y].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+2][y+1].builpart=TRUE;
		everything[x-1][y+2].builpart=TRUE;
		everything[x][y+2].builpart=TRUE;
		everything[x+1][y+2].builpart=TRUE;
		everything[x+2][y+2].builpart=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+2][y-1].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x+2][y].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+2][y+1].pline=TRUE;
		everything[x-1][y+2].pline=TRUE;
		everything[x][y+2].pline=TRUE;
		everything[x+1][y+2].pline=TRUE;
		everything[x+2][y+2].pline=TRUE;
	}
	else if (cursor==SEAPORT && IsFree(x,y,4) && money>=2000)
	{
		temp.bottom=point.y-(point.y%8)+24;
		temp.top=point.y-(point.y%8)-16;
		temp.left=point.x-(point.x%8)-16;
		temp.right=point.x-(point.x%8)+24;
		everything[x][y].bcenter=55;
		money-=2000;
		cursorsize=2;
		everything[x-1][y-1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+2][y-1].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x+1][y].builpart=TRUE;
		everything[x+2][y].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+2][y+1].builpart=TRUE;
		everything[x-1][y+2].builpart=TRUE;
		everything[x][y+2].builpart=TRUE;
		everything[x+1][y+2].builpart=TRUE;
		everything[x+2][y+2].builpart=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+2][y-1].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x+2][y].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+2][y+1].pline=TRUE;
		everything[x-1][y+2].pline=TRUE;
		everything[x][y+2].pline=TRUE;
		everything[x+1][y+2].pline=TRUE;
		everything[x+2][y+2].pline=TRUE;
	}
	else if (cursor==COAL && IsFree(x,y,4) && money>=3000)
	{
		money-=3000;
		temp.bottom=point.y-(point.y%8)+24;
		temp.top=point.y-(point.y%8)-16;
		temp.left=point.x-(point.x%8)-16;
		temp.right=point.x-(point.x%8)+24;
		cursorsize=2;
		everything[x][y].bcenter=56;
		everything[x-1][y-1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+2][y-1].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x+1][y].builpart=TRUE;
		everything[x+2][y].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+2][y+1].builpart=TRUE;
		everything[x-1][y+2].builpart=TRUE;
		everything[x][y+2].builpart=TRUE;
		everything[x+1][y+2].builpart=TRUE;
		everything[x+2][y+2].builpart=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+2][y-1].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x+2][y].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+2][y+1].pline=TRUE;
		everything[x-1][y+2].pline=TRUE;
		everything[x][y+2].pline=TRUE;
		everything[x+1][y+2].pline=TRUE;
		everything[x+2][y+2].pline=TRUE;
	}
	else if (cursor==NUCLEAR && IsFree(x,y,4) && money>=5000)
	{
		money-=5000;
		temp.bottom=point.y-(point.y%8)+24;
		temp.top=point.y-(point.y%8)-16;
		temp.left=point.x-(point.x%8)-16;
		temp.right=point.x-(point.x%8)+24;
		cursorsize=2;
		everything[x][y].bcenter=57;
		everything[x-1][y-1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+2][y-1].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x+1][y].builpart=TRUE;
		everything[x+2][y].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+2][y+1].builpart=TRUE;
		everything[x-1][y+2].builpart=TRUE;
		everything[x][y+2].builpart=TRUE;
		everything[x+1][y+2].builpart=TRUE;
		everything[x+2][y+2].builpart=TRUE;
		everything[x-1][y-1].pline=TRUE;
		everything[x][y-1].pline=TRUE;
		everything[x+1][y-1].pline=TRUE;
		everything[x+2][y-1].pline=TRUE;
		everything[x-1][y].pline=TRUE;
		everything[x+2][y].pline=TRUE;
		everything[x-1][y+1].pline=TRUE;
		everything[x+2][y+1].pline=TRUE;
		everything[x-1][y+2].pline=TRUE;
		everything[x][y+2].pline=TRUE;
		everything[x+1][y+2].pline=TRUE;
		everything[x+2][y+2].pline=TRUE;
	}
	else if (cursor==AIRPORT && IsFree(x,y,5) && money>=10000)
	{
		//The airport is 6x6 squares so it requires a lot of code.
		money-=10000;
		temp.bottom=point.y-(point.y%8)+36;
		temp.top=point.y-(point.y%8)-24;
		temp.left=point.x-(point.x%8)-16;
		temp.right=point.x-(point.x%8)+36;
		everything[x][y].bcenter=58;
		cursorsize=3;
		everything[x-2][y-2].builpart=TRUE;
		everything[x-1][y-2].builpart=TRUE;
		everything[x][y-2].builpart=TRUE;
		everything[x+1][y-2].builpart=TRUE;
		everything[x+2][y-2].builpart=TRUE;
		everything[x+3][y-2].builpart=TRUE;
		everything[x-2][y-1].builpart=TRUE;
		everything[x-1][y-1].builpart=TRUE;
		everything[x][y-1].builpart=TRUE;
		everything[x+1][y-1].builpart=TRUE;
		everything[x+2][y-1].builpart=TRUE;
		everything[x+3][y-1].builpart=TRUE;
		everything[x-2][y].builpart=TRUE;
		everything[x-1][y].builpart=TRUE;
		everything[x+1][y].builpart=TRUE;
		everything[x+2][y].builpart=TRUE;
		everything[x+3][y].builpart=TRUE;
		everything[x-2][y+1].builpart=TRUE;
		everything[x-1][y+1].builpart=TRUE;
		everything[x][y+1].builpart=TRUE;
		everything[x+1][y+1].builpart=TRUE;
		everything[x+2][y+1].builpart=TRUE;
		everything[x+3][y+1].builpart=TRUE;
		everything[x-2][y+2].builpart=TRUE;
		everything[x-1][y+2].builpart=TRUE;
		everything[x][y+2].builpart=TRUE;
		everything[x+1][y+2].builpart=TRUE;
		everything[x+2][y+2].builpart=TRUE;
		everything[x+3][y+2].builpart=TRUE;
		everything[x-2][y+3].builpart=TRUE;
		everything[x-1][y+3].builpart=TRUE;
		everything[x][y+3].builpart=TRUE;
		everything[x+1][y+3].builpart=TRUE;
		everything[x+2][y+3].builpart=TRUE;
		everything[x+3][y+3].builpart=TRUE;
		everything[x-2][y-2].pline=TRUE;
		everything[x-1][y-2].pline=TRUE;
		everything[x][y-2].pline=TRUE;
		everything[x+1][y-2].pline=TRUE;
		everything[x+2][y-2].pline=TRUE;
		everything[x+3][y-2].pline=TRUE;
		everything[x-2][y-1].pline=TRUE;
		everything[x+3][y-1].pline=TRUE;
		everything[x-2][y].pline=TRUE;
		everything[x+3][y].pline=TRUE;
		everything[x-2][y+1].pline=TRUE;
		everything[x+3][y+1].pline=TRUE;
		everything[x-2][y+2].pline=TRUE;
		everything[x+3][y+2].pline=TRUE;
		everything[x-2][y+3].pline=TRUE;
		everything[x-1][y+3].pline=TRUE;
		everything[x][y+3].pline=TRUE;
		everything[x+1][y+3].pline=TRUE;
		everything[x+2][y+3].pline=TRUE;
		everything[x+3][y+3].pline=TRUE;
	}
	InvalidateRect(temp);
	temp.top=380;
	temp.bottom=420;
	temp.left=20;
	temp.right=60;
	InvalidateRect(temp);
	FindPowerStart(this->GetSafeHwnd(),hscrollpos,vscrollpos);
	CDialog::OnLButtonDown(nFlags, point);
}
//Whenever one of the toolbar buttons is pressed, one of these functions is executed
//in response to it. All these do is set the cursor appropriately depending on which
//control button was pressed.
void CSimCity2Dlg::OnTb1() 
{
	cursor=BULLDOZER;	
}

void CSimCity2Dlg::OnTb2() 
{
	cursor=ROAD;	
}

void CSimCity2Dlg::OnTb3() 
{
	cursor=RAIL;	
}

void CSimCity2Dlg::OnTb4() 
{
	cursor=PLINE;	
}

void CSimCity2Dlg::OnTb5() 
{
	cursor=PARK;	
}

void CSimCity2Dlg::OnTb6() 
{
	cursor=RES;	
}

void CSimCity2Dlg::OnTb7() 
{
	cursor=COM;	
}

void CSimCity2Dlg::OnTb8() 
{
	cursor=IND;	
}

void CSimCity2Dlg::OnTb9() 
{
	cursor=POLICE;	
}

void CSimCity2Dlg::OnTb10() 
{
	cursor=FIREDEPT;	
}

void CSimCity2Dlg::OnTb11() 
{
	cursor=STADIUM;	
}

void CSimCity2Dlg::OnTb12() 
{
	cursor=SEAPORT;	
}

void CSimCity2Dlg::OnTb13() 
{
	cursor=COAL;	
}

void CSimCity2Dlg::OnTb14() 
{
	cursor=NUCLEAR;	
}

void CSimCity2Dlg::OnTb15() 
{
	cursor=AIRPORT;	
}
void CSimCity2Dlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	//This allows rails, roads, and powerlines to be built through dragging the mouse.
	//Only these are allowed to built this way; it makes sense from a practical standpoint.
	//(i.e. probably no one will want to drag to make 5 airports in a row)
	if (nFlags==MK_LBUTTON) //This flag means that the left mouse button is pressed
	{
		CRect temp;
		xpos=point.x-(point.x%8);
		ypos=point.y-(point.y%8);	//A gridspace (x,y) needs to be interpreted based
		int x,y;					//on the co-ordinates of where the user clicked.
		x=point.x+(8*hscrollpos);
		y=point.y+(8*vscrollpos);
		x=x/8;
		y=y/8;
		temp.top=ypos;
		temp.bottom=ypos+8;
		temp.right=xpos+8;
		temp.left=xpos;
		//The code for park, roads, rails, and powerlines is the same as it is from
		//OnLButtonDown.
		//The 'fboxes' are used so that the label displaying the current amount of funds
		//will be updated each time something is built.
		if (cursor==PARK && IsFree(x,y) && money>=10)
			everything[x][y].image=2;
		else if (cursor==ROAD && IsFree(x,y) && money>=10) 
		{
			everything[x][y].road=TRUE;
			money-=10;
			if (everything[x+1][y].road)
			{
				everything[x][y].right=TRUE;
				everything[x+1][y].left=TRUE;
				temp.right+=8;
			}
			if (everything[x-1][y].road)
			{
				everything[x][y].left=TRUE;
				everything[x-1][y].right=TRUE;
				temp.left-=8;
			}
			if (everything[x][y-1].road)
			{
				everything[x][y].up=TRUE;
				everything[x][y-1].down=TRUE;
				temp.top-=8;
			}
			if (everything[x][y+1].road)
			{
				everything[x][y].down=TRUE;
				everything[x][y+1].up=TRUE;
				temp.bottom+=8;
			}
			CRect fbox;
			fbox.top=380;
			fbox.bottom=420;
			fbox.left=20;
			fbox.right=60;
			InvalidateRect(fbox);
		}
		else if (cursor==RAIL && IsFree(x,y) && money>=20)
		{
			everything[x][y].rail=TRUE;
			money-=20;
			if (everything[x+1][y].rail)
			{
				everything[x][y].right=TRUE;
				everything[x+1][y].left=TRUE;
				temp.right+=8;
			}
			if (everything[x-1][y].rail)
			{
				everything[x][y].left=TRUE;
				everything[x-1][y].right=TRUE;
				temp.left-=8;
			}
			if (everything[x][y-1].rail)
			{
				everything[x][y].up=TRUE;
				everything[x][y-1].down=TRUE;
				temp.top-=8;
			}
			if (everything[x][y+1].rail)
			{
				everything[x][y].down=TRUE;
				everything[x][y+1].up=TRUE;
				temp.bottom+=8;
			}
			CRect fbox;
			fbox.top=380;
			fbox.bottom=420;
			fbox.left=20;
			fbox.right=60;
			InvalidateRect(fbox);
		}
		else if (cursor==PLINE && IsFree(x,y) && money>=10)
		{
			everything[x][y].pline=TRUE;
			money-=20;
			if (everything[x+1][y].pline)
			{
				everything[x][y].pRight=TRUE;
				everything[x+1][y].pLeft=TRUE;
				temp.right+=8;
			}
			if (everything[x-1][y].pline)
			{
				everything[x][y].pLeft=TRUE;
				everything[x-1][y].pRight=TRUE;
				temp.left-=8;
			}
			if (everything[x][y-1].pline)
			{
				everything[x][y].pUp=TRUE;
				everything[x][y-1].pDown=TRUE;
				temp.top-=8;
			}
			if (everything[x][y+1].pline)
			{
				everything[x][y].pDown=TRUE;
				everything[x][y+1].pUp=TRUE;
				temp.bottom+=8;
			}
			CRect fbox;
			fbox.top=380;
			fbox.bottom=420;
			fbox.left=20;
			fbox.right=60;
			InvalidateRect(fbox);
		}
		//Power needs to be updated each time something is built, so...
		FindPowerStart(this->GetSafeHwnd(),hscrollpos,vscrollpos);			
		InvalidateRect(temp);
	}

}
/*
This checks whether the space (x,y) can have something built on it (i.e. if it has only
blank land, forest, or park). 
*/
bool CSimCity2Dlg::IsFree(int x, int y)
{
	if ((everything[x][y].image==0 || everything[x][y].image==1 || everything[x][y].image==2) && !everything[x][y].bcenter && !everything[x][y].builpart && !everything[x][y].road && !everything[x][y].rail)
		return TRUE;
	else
		return FALSE;
}


/*
This checks if a section of the grid can have something built on it. If 'size' is 3,
it checks if there is room for a 3x3 zone. If it's 4, it checks if there's room for a 4x4
zone. If it's 5, it checks if there's room for a 6x6 zone (...) 
*/
bool CSimCity2Dlg::IsFree(int x,int y,int size)
{
	if (size==3)
	{
		if(IsFree(x-1,y-1) && IsFree(x-1,y) && IsFree(x-1,y+1) && IsFree(x,y-1) && IsFree(x,y) && IsFree(x,y+1) && IsFree(x+1,y-1) && IsFree(x+1,y) && IsFree(x+1,y+1))
			return TRUE;
		else
			return FALSE;
	}
	else if (size==4)
	{
		if(IsFree(x,y) && IsFree(x,y-1) && IsFree(x,y-2) && IsFree(x,y-3) && IsFree(x+1,y) && IsFree(x+1,y-1) && IsFree(x+1,y-2) && IsFree(x+1,y-3) && IsFree(x+2,y) && IsFree(x+2,y-1) && IsFree(x+2,y-2) && IsFree(x+2,y-3) && IsFree(x+3,y) && IsFree(x+3,y-1) && IsFree(x+3,y-2) && IsFree(x+3,y-3)) 
			return TRUE;
		else
			return FALSE;
	}
	else if (size==5)
	{
		if(IsFree(x,y) && IsFree(x,y-1) && IsFree(x,y-2) && IsFree(x,y-3) && IsFree(x,y-4) && IsFree(x,y-5) && IsFree(x+1,y) && IsFree(x+1,y-1) && IsFree(x+1,y-2) && IsFree(x+1,y-3) && IsFree(x+1,y-4) && IsFree(x+1,y-5) && IsFree(x+2,y) && IsFree(x+2,y-1) && IsFree(x+2,y-2) && IsFree(x+2,y-3)  && IsFree(x+2,y-4) && IsFree(x+2,y-5) && IsFree(x+3,y) && IsFree(x+3,y-1) && IsFree(x+3,y-2) && IsFree(x+3,y-3) && IsFree(x+3,y-4) && IsFree(x+3,y-5) && IsFree(x+4,y) && IsFree(x+4,y-1) && IsFree(x+4,y-2) && IsFree(x+4,y-3) && IsFree(x+4,y-4) && IsFree(x+4,y-5)) 
			return TRUE;
		else
			return FALSE;
	}
	return FALSE;
}

/*
This function calculates land value throughout the grid. Forests, parks, water, and 
developed surrounding residential zones increase land value.
*/
void CSimCity2Dlg::CalcLandvalue()
{
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			everything[i][j].landvalue=0;
		}
	}
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			if (everything[i][j].image==1)
			{
				Raise(i,j,5,2,1);
			}
			else if (everything[i][j].image==2)
			{
				Raise(i,j,4,2,1);
			}
			else if (everything[i][j].image==3)
			{
				Raise(i,j,6,2,1);
			}
			else if (everything[i][j].bcenter && everything[i][j].bcenter<=17)
			{
				Raise(i,j,3,everything[i][j].bcenter*2,1);
			}
			if (everything[i][j].road || everything[i][j].rail)
			{
				Raise(i,j,3,2,1);
			}
		}
	}
	for (int i=1;i<99;i++) //But pollution negates land value...
	{
		for (int j=1;j<99;j++)
		{
			if (everything[i][j].pollution>100)//Make sure pollution isn't over 100
				everything[i][j].pollution=100;
			everything[j][j].landvalue-=everything[i][j].pollution;
			if (everything[i][j].landvalue<0)//Make sure land value hasn't gone less than 0
				everything[i][j].landvalue=0;
		}
	}
}

//This will raise the landvalue, pollution, or crime rate within the grid starting
//at point (x,y) and with radius 'radius'. Actually 'radius' is misleading since the
//stats are raised in a square with an odd number side length whose center is (x,y)...~

//The 'type' variable just refers to whether landvalue, pollution, or crime is to be
//raised. (numbers chosen arbitrarily)

void CSimCity2Dlg::Raise(int x,int y, int radius, int bywhat, int type)
{
	if (type==1) //Type 1 means land value is to be raised
	{
		for (int i=(-1)*radius+1;i<radius;i++)
		{
			for (int j=(-1)*radius+1;j<radius;j++)
			{
				everything[x+i][y+j].landvalue+=bywhat;
			}
					
		}
	}
	else if (type==2) //Type 2 refers to pollution
	{
		for (int i=(-1)*radius+1;i<radius;i++)
		{
			for (int j=(-1)*radius+1;j<radius;j++)
			{
				everything[x+i][y+j].pollution+=bywhat;
			}
				
		}
	}
	//There was once a type 3. But it was removed. It was too much of an unnecessary
	//hassle to change all the old type 4's back to type 3's.

	else if (type==4) //Type 4 refers to ResProxim (...residential proximity)
	{
		for (int i=(-1)*radius+1;i<radius;i++)
		{
			for (int j=(-1)*radius+1;j<radius;j++)
			{
				everything[x+i][y+j].resproxim+=bywhat;
			}
				
		}
	}
}

//This will adjust the zoning (Res,Com,Ind) throughout the grid depending
//on some different factors.
/*
The window handle is necessary so that InvalidateRect will be possible.
If the development level of a building changes, it needs to be drawn again.
*/
void CSimCity2Dlg::Develop(HWND window,int hscrollpos,int vscrollpos)
{
	CRect temp;
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			if (everything[i][j].bcenter && everything[i][j].bcenter<=17)
			//Residential zoning is affected just by land value.
			{
				int oldc=everything[i][j].bcenter;
				if (everything[i][j].landvalue>100)
					everything[i][j].landvalue=100;
				everything[i][j].bcenter=everything[i][j].landvalue/8+1;
				if (!everything[i][j].power) //Buildings don't develop if there's no power.
					everything[i][j].bcenter=1;
				if (everything[i][j].bcenter!=oldc)//An update needs to happen only if the
				{								   //the building's changed..
					temp.top=j*8-11-(8*vscrollpos);
					temp.bottom=j*8+16-(8*vscrollpos);
					temp.left=i*8-11-(8*hscrollpos);
					temp.right=i*8+16-(8*hscrollpos);
					InvalidateRect(temp);
				}
			}
			else if(everything[i][j].bcenter && everything[i][j].bcenter<=34)
			{
			//The development of a commercial zone depends on the value of resproxim.
			//The factors of resproxim are explained in CalcResProxim()...
				int oldc=everything[i][j].bcenter;
				if (everything[i][j].resproxim>100)
					everything[i][j].resproxim=100;
				everything[i][j].bcenter=everything[i][j].resproxim/8+19;
				if (!everything[i][j].power)
					everything[i][j].bcenter=18;
				if (everything[i][j].bcenter!=oldc)
				{
					temp.top=j*8-11-(8*vscrollpos);
					temp.bottom=j*8+16-(8*vscrollpos);
					temp.left=i*8-11-(8*hscrollpos);
					temp.right=i*8+16-(8*hscrollpos);
					InvalidateRect(temp);
				}
			}
			else if(everything[i][j].bcenter && everything[i][j].bcenter<=52)
			//The development of industrial zones depends on the ratio of powered residential
			//zones to currently built industrial zones. If there's a lot of residential zones
			//and relatively few existing industrial zones, the industrial zones will develop
			//by a greater amount. (This factor is made up.. i don't know how the SNES game
			//actually does it)
			{
				int oldc=everything[i][j].bcenter;
				int rescount=0;
				int indcount=1;
				for (int x=1;x<99;x++)
				{
					for (int y=1;y<99;y++)
					{
						if (everything[x][y].bcenter && everything[x][y].bcenter<=17 && everything[x][y].power)
							rescount++;
						else if (everything[x][y].bcenter>=35 && everything[x][y].bcenter<=52 && everything[x][y].power)
							indcount++;
					}
				}
				everything[i][j].bcenter=(rescount/indcount)*3+35;
				if (everything[i][j].bcenter>43)
					everything[i][j].bcenter=43;
				if (!everything[i][j].power) //And buildings don't develop if there's no power.
					everything[i][j].bcenter=35;
				if (everything[i][j].bcenter!=oldc)
				{
					temp.top=j*8-11-(8*vscrollpos);
					temp.bottom=j*8+16-(8*vscrollpos);
					temp.left=i*8-11-(8*hscrollpos);
					temp.right=i*8+16-(8*hscrollpos);
					InvalidateRect(temp);
				}
			}
		}
	}
}

/*
This is a recursive function that confirms whether zones have power or not. The
gridspace at which it is first called is always the center of the power plant.
The base case is when all the spaces adjacent to everything[x][y] are either 1) not
powerlines or parts of buildings, or 2) have already been checked.
If this base case isn't true, FindPower will call itself in whichever direction has
an unchecked powerline or building.  
This happens until all gridspaces which should have power, do. ~
*/

void CSimCity2Dlg::FindPower(int x,int y)
{
	everything[x][y].power=TRUE;
	everything[x][y].checked=TRUE;
	if ((everything[x][y-1].pline || everything[x][y-1].builpart || everything[x][y-1].bcenter) && !everything[x][y-1].checked)
		FindPower(x,y-1);
	if ((everything[x][y+1].pline || everything[x][y+1].builpart || everything[x][y+1].bcenter) && !everything[x][y+1].checked)
		FindPower(x,y+1);
	if ((everything[x+1][y].pline || everything[x+1][y].builpart || everything[x+1][y].bcenter) && !everything[x+1][y].checked)
		FindPower(x+1,y);
	if ((everything[x-1][y].pline || everything[x-1][y].builpart || everything[x-1][y].bcenter) && !everything[x-1][y].checked)
		FindPower(x-1,y);
}

/*
This function isn't totally necessary but it makes checking power easier. (a one-line operation)
A temporary boolean array called hadpower is used here. It keeps track of whether each space
on the grid had power before FindPower(...) was used. This is important because if it didn't have
power but now it does, (or vice-versa), the building center needs to be drawn again to get rid
of the no-power icon that appears.
The window handle and scroll positions have to be passed to this function so that
InvalidateRect will be possible. ~
*/
void CSimCity2Dlg::FindPowerStart(HWND window,int hscrollpos, int vscrollpos)
{
	for (int i=0;i<100;i++)
	{
		for (int j=0;j<100;j++)
		{
			//Every gridspace needs to start this way. Before FindPower is called, none
			//of the grid spaces have been checked. They also can't count as having power
			//because that can't be assumed true until FindPower is actually called. 
			hadpower[i][j]=everything[i][j].power;
			everything[i][j].checked=FALSE;
			everything[i][j].power=FALSE;
		}
	}
	for (int i=0;i<100;i++)
	{
		for (int j=0;j<100;j++)
		{
			if (everything[i][j].bcenter==56 || everything[i][j].bcenter==57)
			{
				//Finally, FindPower(...) is called.
				//These two for loops will search the grid and call it when it encounters a
				//power plant (if there is one).
				FindPower(i,j);
			}
		}
	}
	for (int i=0;i<100;i++)
	{
		for (int j=0;j<100;j++)
		{
			if (everything[i][j].bcenter && everything[i][j].power!=hadpower[i][j])
			{
				CRect temp;
				temp.top=j*8-(8*vscrollpos);
				temp.bottom=j*8+8-(8*vscrollpos);
				temp.left=i*8-(8*hscrollpos);
				temp.right=i*8+8-(8*hscrollpos);
				InvalidateRect(temp);
			}
			//Any buildings' centers which need to be updated, are. (because of adding/removing
			//the lightning-bolt icon).. The array 'hadpower' is all assigned to false too,
			//so that it will still be of use the next time FindPowerStart(...) is used.
			hadpower[i][j]=FALSE;
		}
	}
}

//This function is run every 5 seconds... It adjusts the zoning everywhere in the grid that needs
//to be. (If all city development happened immediately, the game would be strange-looking...)
void CSimCity2Dlg::OnTimer(UINT nIDEvent)
{
	CRect temp;
	CalcPollute();
	CalcLandvalue();
	CalcResProxim();
	Develop(this->GetSafeHwnd(),hscrollpos,vscrollpos);
	CalcPop();
	temp.top=440;
	temp.bottom=460;
	temp.left=20;
	temp.right=60;
	InvalidateRect(temp);
	if (counter==15) //When 15 of the game's 'time intervals' have elapsed, it counts as one
		//year, so taxes are collected. A counter seemed like the easiest way to do this
		//(rather than use multiple timers)
	{
		int tax;
		tax=population*.5;
		money+=tax;
		temp.top=380;
		temp.bottom=420;
		temp.left=20;
		temp.right=60;
		InvalidateRect(temp);
		CString t;
		t.Format("%i in taxes have been added to the city's funds.",tax);
		MessageBox(t);
		counter=0;
	}
	counter++;
	CDialog::OnTimer(nIDEvent);
}

void CSimCity2Dlg::CalcResProxim()
{		//Resproxim is a generic term that basically represents the factors that make
		//commercial zones develop. The most influential factor is the proximity to
		//residential zones, so it's called resproxim. But the presence of roads and
		//railways are also somewhat of a factor.
		//In addition: police/fire stations and air/sea ports will affect commercial
		//zone development since their full functionality isn't included in this game.
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			everything[i][j].resproxim=0; //Set all the resproxim's to 0
		}
	}
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			if (everything[i][j].bcenter && everything[i][j].bcenter<=17)
			{ //Raise values according to the location and development of residential zones
				Raise(i,j,6,everything[i][j].bcenter*10,4);
			}
			if (everything[i][j].road)
				Raise(i,j,4,1,4); //Roads increase rexproxim
			if (everything[i][j].rail)
				Raise(i,j,4,2,4); //So do rails
			//The next four cases are for police stations, fire stations, the stadium,
			//seaport, and airport, respectively..
			if (everything[i][j].bcenter==52 || everything[i][j].bcenter==53)
				Raise(i,j,12,30,4);
			else if (everything[i][j].bcenter==54)
				Raise(i,j,15,30,4);
			else if (everything[i][j].bcenter==55)
				Raise(i,j,17,35,4);
			else if (everything[i][j].bcenter==58)
				Raise(i,j,25,35,4);
		}
	}
}

void CSimCity2Dlg::CalcPop() //The population needs to be calculated so that taxes can be counted.
//It is based on the development of all residential zones in the grid.
{
	population=0;
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			if (everything[i][j].bcenter && everything[i][j].bcenter<=17)
			{
				population+=(everything[i][j].bcenter-1)*100;
			}
		}
	}
}

void CSimCity2Dlg::CalcPollute()
//Pollution in the game is calculated so that it can negate land value.
{
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			everything[i][j].pollution=0;
		}
	}
	for (int i=1;i<99;i++)
	{
		for (int j=1;j<99;j++)
		{
			if (everything[i][j].bcenter>=35 && everything[i][j].bcenter<=43)
				//Industrial zones affect pollution (higher developed zones increase pollution 
				//more
			{
				Raise(i,j,10,(everything[i][j].bcenter-34)*7,2);
			}
			else if(everything[i][j].bcenter==56)
				//Coal power plants increase pollution..
			{
				Raise(i,j,15,20,2);
			}
			else if(everything[i][j].bcenter==58)
			{
				//And so do airports
				Raise(i,j,20,30,2);
			}
				
		}
	}
}

//~-~ T h e   E n d  ~-~\\