// BMPFrm.h : CBMPFrame Ŭ������ �������̽��Դϴ�.
//

#pragma once

#include "BMPView.h"
#include "BMPDoc.h"

// CBMPFrame

class CBMPView;

class CBMPFrame : public CMDIChildWndEx
{
public:
	CBMPFrame();
	DECLARE_DYNCREATE(CBMPFrame)

// Ư���Դϴ�.
public:
//	virtual CBMPView* GetActiveView();
	virtual CBMPDoc* GetActiveDocument();
	BYTE m_bEcsHighEnd;
	BYTE m_bEcsLowEnd;
	UINT m_InitW = 552;
	UINT m_InitH = 555;

// �۾��Դϴ�.
public:
	void Duplicate(OUT CBMPFrame** frame, OUT CBMPView** view, OUT CBMPDoc** document);

// �������Դϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnFinalRelease();
	virtual void ActivateFrame(int nCmdShow = -1);

// �����Դϴ�.
public:
	virtual ~CBMPFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnIpHistogramEqualization();
	afx_msg void OnIpBasicContrastStretching();
	afx_msg void OnIpEndsinContrastStretching();
	afx_msg void OnIpEcsHighEnd();
	afx_msg void OnIpEcsLowEnd();
	afx_msg void OnViewOriginSize();
};
