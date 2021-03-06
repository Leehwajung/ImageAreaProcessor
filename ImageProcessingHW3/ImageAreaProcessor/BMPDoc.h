// BMPDoc.h : CBMPDoc 클래스의 인터페이스입니다.
//

#pragma once

#include "ImageProcessorUtil.h"

using Gdiplus::Bitmap;

// CBMPDoc 문서입니다.

class CBMPDoc : public CDocument
{
protected:	// serialization에서만 만들어집니다.
	CBMPDoc();
	DECLARE_DYNCREATE(CBMPDoc)

// 특성입니다.
public:
	Bitmap* m_bitmap;

// 작업입니다.
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

	// Edge Detection
	void CBMPDoc::detectEdge(const Mask::Type maskType);

	// Low-pass Filtering
	void CBMPDoc::LowPassFiltering(const UINT filterWidth);

	// Median Filtering
	void CBMPDoc::MedianFiltering(const UINT windowWidth);

	// 에러율 계산
	DOUBLE getErrorRate(const Mask::Type maskType, const DOUBLE snr);

	// MSE (filterType: 0 = Low-Pass, 1 = Median)
	DOUBLE getMSE(const INT filterType, const DOUBLE snr, const UINT filterWidth);

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);	// 문서 입/출력을 위해 재정의되었습니다.
#endif
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
	virtual void OnFinalRelease();

// 구현입니다.
public:
	virtual ~CBMPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	
// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

class CRAWDoc : public CBMPDoc {
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};