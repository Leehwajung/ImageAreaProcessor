// BMPDoc.h : CBMPDoc Ŭ������ �������̽��Դϴ�.
//

#pragma once

using Gdiplus::Bitmap;

// CBMPDoc �����Դϴ�.

class CBMPDoc : public CDocument
{
protected:	// serialization������ ��������ϴ�.
	CBMPDoc();
	DECLARE_DYNCREATE(CBMPDoc)

// Ư���Դϴ�.
public:
	Bitmap* m_bitmap;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);	// ���� ��/����� ���� �����ǵǾ����ϴ�.
#endif
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
	virtual void OnFinalRelease();

// �����Դϴ�.
public:
	virtual ~CBMPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	
// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void copyFrom(const CBMPDoc* bmpDoc);
	BYTE* getData(BitmapData* bitmapData, const PixelFormat pixelFormat);
	void clearData(BitmapData* bitmapData);

	// Histogram Equalization
	void HistogramEqualization();

	// Basic Contrast Stretching
	void BasicContrastStretching();

	// Ends-in Contrast Stretching
	void EndsinContrastStretching(const BYTE low, const BYTE high);

	// Gaussian Noise
	void CBMPDoc::GaussianNoise(const DOUBLE snr);

	// Roberts Masking
	void CBMPDoc::RobertsMasking();

	// Sobel Masking
	void CBMPDoc::SobelMasking();

	// Prewitt Masking
	void CBMPDoc::PrewittMasking();

	// Stochastic Gradient Masking
	void CBMPDoc::StochasticGradientMasking();

	// Low-pass Filtering
	void CBMPDoc::LowPassFiltering();

	// Median Filtering
	void CBMPDoc::MedianFiltering();
};
