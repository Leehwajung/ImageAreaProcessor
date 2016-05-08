// ImageProcessorUtil.h : CImageProcessorUtil Ŭ������ �������̽��Դϴ�.
//

#pragma once

#define HTGSIZE	256		// histogram ������ �ʺ�
#define HTGMAX	255.0f	// histogram ������ �ִ�
#define HTGMIN	0.0f	// histogram ������ �ּڰ�

// CImageProcessorUtil ��� ����Դϴ�.

class CImageProcessorUtil : public CObject
{
public:
	static void generateHistogram(IN const BYTE pixelData[], IN const UINT pixelDataSize, OUT UINT histogramData[HTGSIZE]);
};
