// ImageProcessorUtil.cpp : CImageProcessorUtil Ŭ������ ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessorUtil.h"


// CImageProcessorUtil

// CImageProcessorUtil ��� �Լ�

// �ȼ� �����Ϳ� ���� histogram ����
void CImageProcessorUtil::generateHistogram(IN const BYTE pixelData[], IN const UINT pixelDataSize, OUT UINT histogramData[HTGSIZE])
{
	for (UINT i = 0; i < HTGSIZE; i++) {
		histogramData[i] = 0;					// histogram �迭 �ʱ�ȭ
	}

	for (UINT i = 0; i < pixelDataSize; i++) {
		if (pixelData[i] >= 0 && pixelData[i] < HTGSIZE) {
			histogramData[pixelData[i]]++;	// ��Ⱚ �� ����
		}
		else {	// �߸��� �ȼ� �������̸� ����
			return;
		}
	}
}