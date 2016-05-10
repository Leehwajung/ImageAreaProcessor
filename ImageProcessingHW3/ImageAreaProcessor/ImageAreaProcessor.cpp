// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ImageAreaProcessor.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ImageAreaProcessor.h"
#include "MainFrm.h"

#include "HistogramFrm.h"
#include "HistogramDoc.h"
#include "HistogramView.h"
#include "BMPFrm.h"
#include "BMPDoc.h"
#include "BMPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PFX_HISTOGRAM	L"histogram_of_"


// CImageAreaProcessorApp

BEGIN_MESSAGE_MAP(CImageAreaProcessorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CImageAreaProcessorApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� �����Դϴ�.
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� �����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_HTG_PLOT, &CImageAreaProcessorApp::OnHtgPlot)
END_MESSAGE_MAP()


// CImageAreaProcessorApp ����

CImageAreaProcessorApp::CImageAreaProcessorApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���� ���α׷��� ���� ��� ��Ÿ�� ������ ����Ͽ� ������ ���(/clr):
	//     1) �� �߰� ������ �ٽ� ���� ������ ������ ����� �۵��ϴ� �� �ʿ��մϴ�.
	//     2) ������Ʈ���� �����Ϸ��� System.Windows.Forms�� ���� ������ �߰��ؾ� �մϴ�.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ImageAreaProcessor.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CImageAreaProcessorApp ��ü�Դϴ�.

CImageAreaProcessorApp theApp;


// CImageAreaProcessorApp �ʱ�ȭ

BOOL CImageAreaProcessorApp::InitInstance()
{
	CWinAppEx::InitInstance();


	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(10);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�.  ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_BMPFileTYPE,
		RUNTIME_CLASS(CBMPDoc),
		RUNTIME_CLASS(CBMPFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CBMPView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_HistogramFileTYPE,
		RUNTIME_CLASS(CHistogramDoc),
		RUNTIME_CLASS(CHistogramFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CHistogramView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �� MDI ������ â�� ����ϴ�.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  MDI ���� ���α׷������� m_pMainWnd�� ������ �� �ٷ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	// ��� ���⿡ ���� ���⸦ Ȱ��ȭ�մϴ�.
	m_pMainWnd->DragAcceptFiles();

	// ǥ�� �� ����, DDE, ���� ���⿡ ���� �������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// DDE Execute ���⸦ Ȱ��ȭ�մϴ�.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// �����ٿ� ������ ������ ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// GDI plus�� �����մϴ�.
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// �ð��� �õ�� ����Ͽ� �������� ����ϴ�.
	srand((UINT)time(NULL));

	// ���� ���� ���̾�α׸� Ȱ��ȭ�մϴ�.
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_OPEN);

	return TRUE;
}

int CImageAreaProcessorApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);
	GdiplusShutdown(gdiplusToken);

	return CWinAppEx::ExitInstance();
}

// CImageAreaProcessorApp �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� �����Դϴ�.
void CImageAreaProcessorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CImageAreaProcessorApp ����� ���� �ε�/���� �޼���

void CImageAreaProcessorApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CImageAreaProcessorApp::LoadCustomState()
{
}

void CImageAreaProcessorApp::SaveCustomState()
{
}


// CImageAreaProcessorApp �޽��� ó����

void CImageAreaProcessorApp::OnHtgPlot()
{
	// TODO: ���⿡ ���� ó���� �ڵ带 �߰��մϴ�.

	// Source(image)�� ������
	CMainFrame *pMainFrm = (CMainFrame*)(AfxGetMainWnd());		// Main Frame
	CBMPDoc *pBMPDoc = ((CBMPFrame*)pMainFrm->MDIGetActive())->GetActiveDocument();

	// �ű� Historam ���� (CHistogramDoc) ����
	POSITION pos = GetFirstDocTemplatePosition();
	CDocTemplate *pTml;
	for (int i = 0; i < 2; i++) {
		pTml = GetNextDocTemplate(pos);
	}
	pTml->OpenDocumentFile(NULL);

	// Destination(histogram)�� ������
	CHistogramFrame *pHtgFrm = (CHistogramFrame*)pMainFrm->MDIGetActive();	// Histogram Frame
	CHistogramView *pHtgView = (CHistogramView*)(pHtgFrm->GetActiveView());	// Histogram View
	CHistogramDoc *pHtgDoc = pHtgView->GetDocument();						// Histogram Document

	// Source�� �ȼ� �����͸� ��������Ͽ� Destination�� histogram ����
	BitmapData bitmapData;
	BYTE* pixelData = pBMPDoc->getData(&bitmapData, ImageLockModeRead);
	pHtgDoc->plotHistogram(pixelData, bitmapData.Width * bitmapData.Height);
	pHtgView->plotHistogramImage();
	pBMPDoc->clearData(&bitmapData);

	// ���� ����
	CString newTitle(PFX_HISTOGRAM);
	newTitle.Append(pBMPDoc->GetTitle());
	pHtgDoc->SetTitle(newTitle);

	// Histogram�� �°� �ٽ� �׸���
	pHtgFrm->ActivateFrame();
	pHtgView->Invalidate();
}