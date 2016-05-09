// ImageProcessorUtil.h : CImageProcessorUtil Ŭ������ �������̽��Դϴ�.
//

#pragma once

#define HTGSIZE			256	// histogram ������ �ʺ�
#define INTENSITYMAX	255	// intensity �ִ�
#define INTENSITYMIN	0	// intensity �ּڰ�


// CImageProcessorUtil ��� ����Դϴ�.

class CImageProcessorUtil : public CObject
{
public:
	// �ȼ� �����Ϳ� ���� histogram ����
	static void generateHistogram(IN const BYTE pixelData[], IN const UINT pixelDataSize, OUT UINT histogramData[HTGSIZE]);
	// Ends-in Contrast Stretching
	static void stretchContrast(OUT BYTE pixelData[], IN const UINT pixelDataSize, IN const BYTE low, IN const BYTE high);
	// Get Variance of Pixels
	static double getImagePower(IN const BYTE pixelData[], IN const UINT pixelDataSize);
	// Get Standard Deviation of Noise
	static double getStandardDeviationOfNoise(IN const BYTE pixelData[], IN const UINT pixelDataSize, IN const double snr);
	// Add Gaussian Noise
	static void addGaussianNoise(OUT BYTE pixelData[], IN const UINT pixelDataSize, IN const double sigma);
	// get gaussian
	static double gaussian(IN const double sd);
};
