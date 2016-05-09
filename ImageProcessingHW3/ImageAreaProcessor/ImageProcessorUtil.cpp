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

// Ends-in Contrast Stretching
void CImageProcessorUtil::stretchContrast(OUT BYTE pixelData[], IN const UINT pixelDataSize, IN const BYTE low, IN const BYTE high)
{
	float scaleFactor = (FLOAT)INTENSITYMAX / (FLOAT)(high - low);
	for (UINT i = 0; i < pixelDataSize; i++) {
		if (pixelData[i] <= low) {
			pixelData[i] = (BYTE)INTENSITYMIN;
		}
		else if (pixelData[i] > high) {
			pixelData[i] = (BYTE)INTENSITYMAX;
		}
		else {
			pixelData[i] = (BYTE)((pixelData[i] - low) * scaleFactor);
		}
	}
}

// Get Power of Pixels
double CImageProcessorUtil::getImagePower(IN const BYTE pixelData[], IN const UINT pixelDataSize)
{
	return DOUBLE();
}

// Get Standard Deviation of Noise
double CImageProcessorUtil::getStandardDeviationOfNoise(IN const BYTE pixelData[], IN const UINT pixelDataSize, IN const double snr)
{
	double variance = getImagePower(pixelData, pixelDataSize);
	return sqrt(variance / pow(10.0, snr / 10.0));
}

// Add Gaussian Noise
void CImageProcessorUtil::addGaussianNoise(OUT BYTE pixelData[], IN const UINT pixelDataSize, IN const double sigma)
{
	for (UINT i = 0; i < pixelDataSize; i++) {
		double s = (double)pixelData[i] + gaussian(sigma);
		pixelData[i] = (BYTE)(s > INTENSITYMAX ? INTENSITYMAX : s < INTENSITYMIN ? INTENSITYMIN : s);
	}
}

// get gaussian
double CImageProcessorUtil::gaussian(IN const double sd)
{
	static int ready = 0;
	static float gstore;
	float v1, v2, r, fac, gaus;
	int r1, r2;

	if (ready == 0) {
		do {
			r1 = rand();
			r2 = rand();
			v1 = (float)(2.f * ((float)r1 / (float)RAND_MAX - 0.5));
			v2 = (float)(2.f * ((float)r2 / (float)RAND_MAX - 0.5));
			r = v1 * v1 + v2 * v2;
		} while (r > 1.0);
		fac = (float)sqrt((double)(-2 * log(r) / r));
		gstore = v1 * fac;
		gaus = v2 * fac;
		ready = 1;
	}
	else {
		ready = 0;
		gaus = gstore;
	}

	return (gaus * sd);
}

// mask
void CImageProcessorUtil::mask(OUT BYTE pixelData[], IN const UINT pixelDataWidth, IN const UINT pixelDataHeight, IN Mask& mask) {
	
	UINT pixelDataSize = pixelDataWidth * pixelDataHeight;

	// Magnitude Gradient
	double *g = new double[pixelDataSize];

	// Get Magnitude Gradient
	for (UINT i = 0; i < pixelDataHeight; i++) {
		for (UINT j = 0; j < pixelDataWidth; j++) {
			double newValX = 0;
			double newValY = 0;
			int length = mask.getLength();
			for (int r = 0; r < length; r++) {
				for (int c = 0; c < length; c++) {
					int mi = i + r - length / 2;
					int mj = j + c - length / 2;
					mi = mi >= (int)pixelDataWidth ? (int)pixelDataWidth - 1 : mi < 0 ? 0 : mi;
					mj = mj >= (int)pixelDataHeight ? (int)pixelDataHeight - 1 : mj < 0 ? 0 : mj;

					UINT where = mi * pixelDataWidth + mj;
					newValX += mask.getMaskX()[r * length + c] * (double)pixelData[where];
					newValY += mask.getMaskY()[r * length + c] * (double)pixelData[where];
				}
			}

			g[i * pixelDataWidth + j] = sqrt(pow(newValX, 2.0) + pow(newValY, 2.0));
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
}


Mask::Mask()
{
	Mask(Roberts);
}

Mask::Mask(Type type)
{
	switch (type)
	{
	case Mask::Roberts:
		m_Length = RobertsLength;
		m_MaskX = (double*)RobertsX;
		m_MaskY = (double*)RobertsY;
		break;
	case Mask::Sobel:
		m_Length = SobelLength;
		m_MaskX = (double*)SobelX;
		m_MaskY = (double*)SobelY;
		break;
	case Mask::Prewitt:
		m_Length = PrewittLength;
		m_MaskX = (double*)PrewittX;
		m_MaskY = (double*)PrewittY;
		break;
	case Mask::StochasticGradient:
		m_Length = StochasticGradientLength;
		m_MaskX = (double*)StochasticGradientX;
		m_MaskY = (double*)StochasticGradientY;
		break;
	}
}

const int Mask::getLength()
{
	return m_Length;
}

double* Mask::getMaskX()
{
	return m_MaskX;
}

double* Mask::getMaskY()
{
	return m_MaskY;
}


// Roberts Mask
const double Mask::RobertsX[RobertsLength][RobertsLength] = {
	{  0,  0, -1 },
	{  0,  1,  0 },
	{  0,  0,  0 }
};

const double Mask::RobertsY[RobertsLength][RobertsLength] = {
	{ -1,  0,  0 },
	{  0,  1,  0 },
	{  0,  0,  0 }
};

// Sobel Mask
const double Mask::SobelX[SobelLength][SobelLength] = {
	{  1,  0, -1 },
	{  2,  0, -2 },
	{  1,  0, -1 }
};

const double Mask::SobelY[SobelLength][SobelLength] = {
	{ -1, -2, -1 },
	{  0,  0,  0 },
	{  1,  2,  1 }
};

// Prewitt Mask
const double Mask::PrewittX[PrewittLength][PrewittLength] = {
	{  1,  0, -1 },
	{  1,  0, -1 },
	{  1,  0, -1 }
};

const double Mask::PrewittY[PrewittLength][PrewittLength] = {
	{ -1, -1, -1 },
	{  0,  0,  0 },
	{  1,  1,  1 }
};

// 5*5 Stochastic Gradient Mask
const double Mask::StochasticGradientX[StochasticGradientLength][StochasticGradientLength] = {
	{  0.267,  0.364,  0.000, -0.364, -0.267 },
	{  0.373,  0.562,  0.000, -0.562, -0.373 },
	{  0.463,  1.000,  0.000, -1.000, -0.463 },
	{  0.373,  0.562,  0.000, -0.562, -0.373 },
	{  0.267,  0.364,  0.000, -0.364, -0.267 }
};

const double Mask::StochasticGradientY[StochasticGradientLength][StochasticGradientLength] = {
	{  0.267,  0.373,  0.463,  0.373,  0.267 },
	{  0.364,  0.562,  1.000,  0.562,  0.364 },
	{  0.000,  0.000,  0.000,  0.000,  0.000 },
	{ -0.267, -0.373, -0.463, -0.373, -0.267 },
	{ -0.364, -0.562, -1.000, -0.562, -0.364 }
};