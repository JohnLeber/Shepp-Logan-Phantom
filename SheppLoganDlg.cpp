
// SheppLogonDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SheppLogan.h"
#include "SheppLoganDlg.h"
#include "SheppLoganPhantom.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//--------------------------------------------------------------------//
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------//
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
//--------------------------------------------------------------------//
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//--------------------------------------------------------------------//
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//--------------------------------------------------------------------//
// CSheppLogonDlg dialog
CSheppLogonDlg::CSheppLogonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHEPPLOGAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
//--------------------------------------------------------------------//
CSheppLogonDlg::~CSheppLogonDlg()
{
	if (m_pImage)
	{
		delete  m_pImage;
		m_pImage = 0;
	}
}
//--------------------------------------------------------------------//
void CSheppLogonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//--------------------------------------------------------------------//
BEGIN_MESSAGE_MAP(CSheppLogonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GENERATE, &CSheppLogonDlg::OnBnClickedGenerate)
	ON_BN_CLICKED(IDC_COPY_IMAGE, &CSheppLogonDlg::OnBnClickedCopyImage)
	ON_BN_CLICKED(IDC_AUTO, &CSheppLogonDlg::OnBnClickedAuto)
END_MESSAGE_MAP()
//--------------------------------------------------------------------//
// CSheppLogonDlg message handlers
BOOL CSheppLogonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	SetDlgItemInt(IDC_WIDTH, 512);
	
	SetDlgItemText(IDC_BLACK, L"0.98");
	SetDlgItemText(IDC_WHITE, L"1.05");

	OnBnClickedAuto();
	OnBnClickedGenerate();

	return TRUE;
}
//--------------------------------------------------------------------//
void CSheppLogonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
//--------------------------------------------------------------------//
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CSheppLogonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (m_pImage)
		{
			DrawImage(m_pImage);
		}
		CDialogEx::OnPaint();
	}
}
//--------------------------------------------------------------------//
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSheppLogonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//--------------------------------------------------------------------//
void CSheppLogonDlg::OnBnClickedGenerate()
{
	CWaitCursor wait;
	if (m_pImage)
	{
		delete m_pImage;
		m_pImage = 0;
	}
	long nWidth = GetDlgItemInt(IDC_WIDTH);
	long nHeight = nWidth;
	CString strBlack, strWhite;
	GetDlgItemText(IDC_BLACK, strBlack);
	GetDlgItemText(IDC_WHITE, strWhite);
	float nBlack = _ttof(strBlack);
	float nWhite = _ttof(strWhite);

	float* pBytes = 0;
 
	//Pass the array of bytes to the Shepp-Logon code and copy them into the bitmap.
	//An array of float is passed back and we scale them between a whiote/black range 
	//so we can visualize them more easily
	if (CSLP::Render(nWidth, nHeight, &pBytes))
	{
		m_pImage = new CImage(); 
		m_pImage->Create(nWidth, nHeight, 24, 0);
		if (m_bAutoScale)
		{
			float nLowestIntensity = 99999;
			float nHighestIntensity = 0;
			for (int h = 0; h < nHeight; h++)
			{
				for (int j = 0; j < nWidth; j++)
				{
					float clr = pBytes[h * nWidth + j];
					if (clr > 0.000001 && clr < nLowestIntensity) nLowestIntensity = clr;
					if (clr < 1.999999 && clr > nHighestIntensity) nHighestIntensity = clr;
				}
			}
			nBlack = nLowestIntensity;
			nWhite = nHighestIntensity; 
		}
		for (int h = 0; h < nHeight; h++)
		{
			for (int j = 0; j < nWidth; j++)
			{
				float clr = pBytes[h * nWidth + j];
				if (clr < nBlack) clr = nBlack;
				if (clr > nWhite) clr = nWhite;
				clr = static_cast<BYTE>((clr - nBlack) / (nWhite - nBlack) * 255);
				m_pImage->SetPixel(j, nHeight - h - 1, RGB(clr, clr, clr));
			}
		}
		delete[] pBytes;
		DrawImage(m_pImage);
	}
	else
	{
		AfxMessageBox(L"An error occurred. Check input values");
	}	
}
//--------------------------------------------------------------------// 
void CSheppLogonDlg::DrawImage(CImage* pImage)
{
	if (!pImage) return;
	CDC* pDC = GetDC();
	if (pDC == 0)
	{
		ATLASSERT(0);
		return;
	}
	CRect rtClient;
	GetDlgItem(IDC_FRAME)->GetWindowRect(&rtClient);
	ScreenToClient(&rtClient);
	pDC->FillSolidRect(rtClient, RGB(192, 192, 192));
	long nImageWidth = pImage->GetWidth();
	long nImageHeight = pImage->GetHeight();
	if (nImageWidth > rtClient.Width())
	{
		pImage->Draw(pDC->m_hDC, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), 0, 0, nImageWidth, nImageHeight);
	}
	else
	{
		pImage->Draw(pDC->m_hDC, rtClient.left, rtClient.top, nImageWidth, nImageHeight, 0, 0, nImageWidth, nImageHeight);
	}
		  
	ReleaseDC(pDC);
}
//--------------------------------------------------------------------// 
void CSheppLogonDlg::OnBnClickedCopyImage()
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		CBitmap* pTempBitmap = new CBitmap();
		if (pTempBitmap)
		{
			CClientDC cdc(this);
			CDC dc;
			dc.CreateCompatibleDC(&cdc);

			long nHeight = m_pImage->GetWidth();
			long nWidth = m_pImage->GetHeight();
 
			BYTE* pBMP = new BYTE[nWidth * nHeight * 4]; 
			for (int h = 0; h < nHeight; h++) {
				for (int j = 0; j < nWidth; j++) { 
					COLORREF clr = m_pImage->GetPixel(j, h);
					BYTE b = GetRValue(clr);//assum rgb and all the same
					pBMP[h * nWidth * 4 + j * 4 + 0] = b;
					pBMP[h * nWidth * 4 + j * 4 + 1] = b;
					pBMP[h * nWidth * 4 + j * 4 + 2] = b;
					pBMP[h * nWidth * 4 + j * 4 + 3] = 255;
				}
			}
			CRect client(0, 0, nWidth, nHeight);
			pTempBitmap->CreateCompatibleBitmap(&cdc, nWidth, nHeight);
			dc.SelectObject(pTempBitmap);
			//call draw routine here that makes GDI calls
			pTempBitmap->SetBitmapBits(nWidth * nHeight * 4, pBMP);
			//put the data on the clipboard
			SetClipboardData(CF_BITMAP, pTempBitmap->m_hObject);
			CloseClipboard();
			//copy has been made on clipboard so we can delete
			delete pTempBitmap;
		}
	}
}
//--------------------------------------------------------------------// 
void CSheppLogonDlg::OnBnClickedAuto()
{
	m_bAutoScale = IsDlgButtonChecked(IDC_AUTO) == BST_CHECKED;
	GetDlgItem(IDC_WHITE)->EnableWindow(m_bAutoScale == false);
	GetDlgItem(IDC_BLACK)->EnableWindow(m_bAutoScale == false);
}
