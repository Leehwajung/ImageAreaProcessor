// ImageProcessorUtil.h : CImageProcessorUtil Ŭ������ �������̽��Դϴ�.
//

#pragma once

#define HTGSIZE			256	// histogram ������ �ʺ�
#define INTENSITYMAX	255	// intensity �ִ�
#define INTENSITYMIN	0	// intensity �ּڰ�


// CImageProcessorUtil ��� ����Դϴ�.

class Mask;

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
	// mask
	static void mask(OUT BYTE pixelData[], IN const UINT pixelDataWidth,IN const UINT pixelDataHeight, IN Mask& mask);
};

class Mask
{
public:
	enum Type {
		Roberts,
		Sobel,
		Prewitt,
		StochasticGradient
	};

	Mask();
	Mask(Type type);
	const int getLength();
	double* getMaskX();
	double* getMaskY();

private:
	int m_Length;
	double *m_MaskX;
	double *m_MaskY;

private:
	// Roberts Mask
	static const int RobertsLength = 3;
	static const double RobertsX[RobertsLength][RobertsLength];
	static const double RobertsY[RobertsLength][RobertsLength];

	// Sobel Mask
	static const int SobelLength = 3;
	static const double SobelX[SobelLength][SobelLength];
	static const double SobelY[SobelLength][SobelLength];

	// Prewitt Mask
	static const int PrewittLength = 3;
	static const double PrewittX[PrewittLength][PrewittLength];
	static const double PrewittY[PrewittLength][PrewittLength];

	// 5*5 Stochastic Gradient Mask
	static const int StochasticGradientLength = 5;
	static const double StochasticGradientX[StochasticGradientLength][StochasticGradientLength];
	static const double StochasticGradientY[StochasticGradientLength][StochasticGradientLength];
};
