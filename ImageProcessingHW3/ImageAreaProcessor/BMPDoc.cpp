// BMPDoc.cpp : CBMPDoc Ŭ������ ���� �����Դϴ�.
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageAreaProcessor.h"
#endif

#include "ImageProcessorUtil.h"

#include "BMPDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include <gdiplus.h>
using namespace Gdiplus;

// CBMPDoc

IMPLEMENT_DYNCREATE(CBMPDoc, CDocument)

BEGIN_MESSAGE_MAP(CBMPDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBMPDoc, CDocument)
END_DISPATCH_MAP()

// ����: IID_IBMPDoc�� ���� ������ �߰��Ͽ�
//  VBA���� ���� ���� ���ε��� �����մϴ�. 
//  �� IID�� .IDL ���Ͽ� �ִ� dispinterface�� GUID�� ��ġ�ؾ� �մϴ�.

// {56F902D5-BA11-4E73-9A1D-C873816130E7}
static const IID IID_IBMPDoc =
{ 0x56F902D5, 0xBA11, 0x4E73,{ 0x9A, 0x1D, 0xC8, 0x73, 0x81, 0x61, 0x30, 0xE7 } };

BEGIN_INTERFACE_MAP(CBMPDoc, CDocument)
	INTERFACE_PART(CBMPDoc, IID_IBMPDoc, Dispatch)
END_INTERFACE_MAP()


// CBMPDoc ����/�Ҹ��Դϴ�.

CBMPDoc::CBMPDoc()
{
	EnableAutomation();
	m_bitmap = NULL;
}

CBMPDoc::~CBMPDoc()
{
	//if (m_bitmap) {
	//	delete m_bitmap;
	//}
}

BOOL CBMPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

BOOL CBMPDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	//m_bitmap.LoadBitmapW(lpszPathName);
	m_bitmap = Bitmap::FromFile(lpszPathName);

	return TRUE;
}

//int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
//{
//	UINT  num = 0;          // number of image encoders
//	UINT  size = 0;         // size of the image encoder array in bytes
//
//	ImageCodecInfo* pImageCodecInfo = NULL;
//
//	GetImageEncodersSize(&num, &size);
//	if (size == 0)
//		return -1;  // Failure
//
//	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
//	if (pImageCodecInfo == NULL)
//		return -1;  // Failure
//
//	GetImageEncoders(num, size, pImageCodecInfo);
//
//	for (UINT j = 0; j < num; ++j)
//	{
//		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
//		{
//			*pClsid = pImageCodecInfo[j].Clsid;
//			free(pImageCodecInfo);
//			return j;  // Success
//		}
//	}
//
//	free(pImageCodecInfo);
//	return -1;  // Failure
//}

BOOL CBMPDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	//CLSID bmpClsid;
	//GetEncoderClsid(L"image/png", &bmpClsid);
	//m_bitmap->Save(lpszPathName, &bmpClsid, NULL);

	return CDocument::OnSaveDocument(lpszPathName);
}

void CBMPDoc::OnCloseDocument()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (m_bitmap) delete m_bitmap;

	CDocument::OnCloseDocument();
}

#ifndef _WIN32_WCE
// CBMPDoc serialization�Դϴ�.

void CBMPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.

	}
}
#endif

void CBMPDoc::OnFinalRelease()
{
	// �ڵ�ȭ ��ü�� ���� ������ ������ �����Ǹ�
	// OnFinalRelease�� ȣ��˴ϴ�.  �⺻ Ŭ�������� �ڵ����� ��ü�� �����մϴ�.
	// �⺻ Ŭ������ ȣ���ϱ� ���� ��ü�� �ʿ��� �߰� ���� �۾���
	// �߰��Ͻʽÿ�.

	CDocument::OnFinalRelease();
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CBMPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CBMPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBMPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBMPDoc �����Դϴ�.

#ifdef _DEBUG
void CBMPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CBMPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG


// CBMPDoc ����Դϴ�.

void CBMPDoc::copyFrom(const CBMPDoc* bmpDoc)
{
	Bitmap *src = bmpDoc->m_bitmap;
	this->m_bitmap = src->Clone(0, 0, src->GetWidth(), src->GetHeight(), PixelFormat8bppIndexed);

	CString newTitle("copied_");
	newTitle.Append(bmpDoc->GetTitle());
	this->SetTitle(newTitle);
}

BYTE* CBMPDoc::getData(BitmapData* bitmapData, const PixelFormat pixelFormat)
{
	Rect imageArea(0, 0, m_bitmap->GetWidth(), m_bitmap->GetHeight());
	m_bitmap->LockBits(
		&imageArea,
		pixelFormat,
		PixelFormat8bppIndexed,
		bitmapData);

	return (BYTE*)bitmapData->Scan0;
}

void CBMPDoc::clearData(BitmapData* bitmapData)
{
	m_bitmap->UnlockBits(bitmapData);
}

// Histogram Equalization
void CBMPDoc::HistogramEqualization()
{
	// ������ histogram�� ���
	BitmapData bitmapData;
	BYTE *pixelData = getData(&bitmapData, ImageLockModeRead | ImageLockModeWrite);	//������ �ȼ� �����͸� ������
	UINT pixelDataSize = bitmapData.Width * bitmapData.Height;
	UINT histogramData[HTGSIZE];
	CImageProcessorUtil::generateHistogram(
		pixelData,
		pixelDataSize,
		histogramData);

	// Histogram�� ������ �� ����ȭ�� �� ���
	UINT accruedSum = 0;
	DOUBLE normalizedSum[HTGSIZE];
	FLOAT scaleFactor = (FLOAT)INTENSITYMAX / (FLOAT)pixelDataSize;
	for (UINT i = 0; i < HTGSIZE; i++) {
		accruedSum += histogramData[i];
		normalizedSum[i] = accruedSum * scaleFactor;
	}

	// Histogram Equalization (��Ȱȭ): normalizedSum�� LUT�� ���
	for (UINT i = 0; i < pixelDataSize; i++) {
		pixelData[i] = (BYTE)(normalizedSum[pixelData[i]] + 0.5);
	}

	clearData(&bitmapData);
}

// Basic Contrast Stretching
void CBMPDoc::BasicContrastStretching()
{
	// ������ pixel data�� ������
	BitmapData bitmapData;
	BYTE *pixelData = getData(&bitmapData, ImageLockModeRead | ImageLockModeWrite);	//������ �ȼ� �����͸� ������
	UINT pixelDataSize = bitmapData.Width * bitmapData.Height;

	// ���� �۰ų� ū ��Ⱚ�� ����
	UINT low = (UINT)INTENSITYMAX;
	UINT high = (UINT)INTENSITYMIN;
	for (UINT i = 0; i < pixelDataSize; i++) {
		if (pixelData[i] < low) {
			low = pixelData[i];
		}
		else if (pixelData[i] > high) {
			high = pixelData[i];
		}
	}

	// Basic Contrast Stretching
	CImageProcessorUtil::stretchContrast(pixelData, pixelDataSize, low, high);

	clearData(&bitmapData);
}

// Ends-in Contrast Stretching
void CBMPDoc::EndsinContrastStretching(const BYTE low, const BYTE high)
{
	// ������ pixel data�� ������
	BitmapData bitmapData;
	BYTE *pixelData = getData(&bitmapData, ImageLockModeRead | ImageLockModeWrite);	//������ �ȼ� �����͸� ������
	UINT pixelDataSize = bitmapData.Width * bitmapData.Height;

	// Ends-in Contrast Stretching
	CImageProcessorUtil::stretchContrast(pixelData, pixelDataSize, low, high);

	clearData(&bitmapData);
}

// Gaussian Noise
void CBMPDoc::GaussianNoise(const DOUBLE snr)
{
	// ������ pixel data�� ������
	BitmapData bitmapData;
	BYTE *pixelData = getData(&bitmapData, ImageLockModeRead | ImageLockModeWrite);	//������ �ȼ� �����͸� ������
	UINT pixelDataSize = bitmapData.Width * bitmapData.Height;

	// Add Gaussian Noise
	CImageProcessorUtil::addGaussianNoise(pixelData, pixelDataSize, snr);

	clearData(&bitmapData);
}

// Roberts Masking
void CBMPDoc::RobertsMasking()
{
	// ������ pixel data�� ������
	BitmapData bitmapData;
	BYTE *pixelData = getData(&bitmapData, ImageLockModeRead | ImageLockModeWrite);	//������ �ȼ� �����͸� ������
	UINT pixelDataSize = bitmapData.Width * bitmapData.Height;

	// Roberts Mask
	int MaskRobertsX[3][3] = {
		{ 0,  0, -1 },
		{ 0,  1,  0 },
		{ 0,  0,  0 }
	};
	int MaskRobertsY[3][3] = {
		{ -1,  0,  0 },
		{  0,  1,  0 },
		{  0,  0,  0 }
	};

	// Magnitude Gradient
	double *g = new double[pixelDataSize];

	// Get Magnitude Gradient
	for (UINT i = 0; i < bitmapData.Height; i++) {
		for (UINT j = 0; j < bitmapData.Width; j++) {
			int newValX = 0;
			int newValY = 0;
			for (int r = 0; r < 3; r++) {
				for (int c = 0; c < 3; c++) {
					int mi = i + r - 1;
					int mj = j + c - 1;
					mi = mi >= bitmapData.Width ? bitmapData.Width - 1 : mi < 0 ? 0 : mi;
					mj = mj >= bitmapData.Height ? bitmapData.Height - 1 : mj < 0 ? 0 : mj;

					UINT where = mi * bitmapData.Width + mj;
					newValX += MaskRobertsX[r][c] * pixelData[where];
					newValY += MaskRobertsY[r][c] * pixelData[where];
				}
			}

			g[i * bitmapData.Width + j] = sqrt(pow(newValX, 2.0) + pow(newValY, 2.0));
		}
	}

	// ����ȭ�� ���� ���� �۰ų� ū ���� ����
	double min = INT_MAX;
	double max = INT_MIN;
	for (UINT i = 1; i < pixelDataSize; i++) {
		if (g[i] < min) {
			min = g[i];
		}
		else if (g[i] > max) {
			max = g[i];
		}
	}
	
	// [min, max] ������ [0, 255]������ ��ȯ
	double scaleFactor = (double)INTENSITYMAX / (max - min);
	double translator = -(double)INTENSITYMAX * min / (max - min);
	for (UINT i = 0; i < pixelDataSize; i++) {
		pixelData[i] = (BYTE)(scaleFactor * g[i] + translator + 0.5);
	}

	// ���� �Ҵ� �޸� ����
	delete[] g;

	clearData(&bitmapData);
}

// Sobel Masking
void CBMPDoc::SobelMasking()
{

}

// Prewitt Masking
void CBMPDoc::PrewittMasking()
{

}

// Stochastic Gradient Masking
void CBMPDoc::StochasticGradientMasking()
{

}

// Low-pass Filtering
void CBMPDoc::LowPassFiltering()
{

}

// Median Filtering
void CBMPDoc::MedianFiltering()
{

}