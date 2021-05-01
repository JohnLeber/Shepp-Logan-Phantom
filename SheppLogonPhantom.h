#pragma once
//--------------------------------------------------------------------//
struct CSLPEllipse
{
	CSLPEllipse()
	{
		nCenterX = 0;
		nCenterY = 0;
		nMajorAxis = 0;
		nMinorAxis = 0;
		nTheta = 0;
		nGrayLevel = 0;
	}	
	CSLPEllipse(double centerX, double centerY, double majorAxis, double minorAxis, double theta, double grayLevel)
	{
		nCenterX = centerX;
		nCenterY = centerY;
		nMajorAxis = majorAxis;
		nMinorAxis = minorAxis;
		nTheta = theta;
		nGrayLevel = grayLevel;
		bValid = true;
	}
	bool bValid = false;
	double nCenterX = 0;
	double nCenterY = 0;
	double nMajorAxis = 0;
	double nMinorAxis = 0;
	double nTheta = 0;
	double nGrayLevel = 0;
};
//--------------------------------------------------------------------//
class CSLP
{
	static void ClearBackground(float* pImag, long nWidth, long nHeight, float clr);
	static void FillEllipse(float* pImage, long nWidth, long nHeight, const CSLPEllipse& ellipse);
public:
	CSLP()
	{

	}
	static bool Render(long nWidth, long nHeight, float** ppImage, float nBackgroundColour = 0, CSLPEllipse* pEllipse = 0, long nNumEllipse = 0);
};
//--------------------------------------------------------------------//

