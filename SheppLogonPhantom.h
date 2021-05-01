
#include "math.h"
const long MaxEllipses = 10;
const long MaxImageDim = 4096;
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
		bool bValid = false;
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
	bool bValid;
	double nCenterX;
	double nCenterY;
	double nMajorAxis;
	double nMinorAxis;
	double nTheta;
	double nGrayLevel;
};
//--------------------------------------------------------------------//
class CSLP
{
	static void CSLP::ClearBackground(float* pImage, long nWidth, long nHeight, float clr)
	{
		for (int h = 0; h < nHeight; h++) {
			for (int j = 0; j < nWidth; j++) {
				pImage[h * nWidth + j] = clr;
			}
		}
	}

	static void CSLP::FillEllipse(float* pImage, long nWidth, long nHeight, const CSLPEllipse& ellipse)
	{
		double nCenterX = nWidth / 2;
		double nCenterY = nHeight / 2;
		for (int h = 0; h < nHeight; h++) {
			for (int j = 0; j < nWidth; j++) {
				double nAngle = ellipse.nTheta * 3.14159267 / 180.0;
				double x = j;
				double y = h;
				double rx = ellipse.nMajorAxis * nWidth / 2;
				double ry = ellipse.nMinorAxis * nHeight / 2;
				double nEllipseCenterX = nCenterX + ellipse.nCenterX * nWidth / 2;
				double nEllipseCenterY = nCenterY + ellipse.nCenterY * nHeight / 2;
				if (nAngle != 0)
				{
					nAngle = -nAngle;//reverse angle because we are keeping the ellipse unrotated and are rotating elverything else around it
					x = x - nEllipseCenterX;
					y = y - nEllipseCenterY;
					// rotate point around ellipse center
					double xnew = x * cos(nAngle) - y * sin(nAngle);
					double ynew = x * sin(nAngle) + y * cos(nAngle);
					//and translate point back
					x = xnew + nEllipseCenterX;
					y = ynew + nEllipseCenterY;
				}
				//check to see if the point is contained in the ellipse
				if ((x - nEllipseCenterX) * (x - nEllipseCenterX) / rx / rx +
					(y - nEllipseCenterY) * (y - nEllipseCenterY) / ry / ry <= 1)
				{
					pImage[h * nWidth + j] = pImage[h * nWidth + j] + ellipse.nGrayLevel;
				}
			}
		}
	}
public:
 
	static bool Render(long nWidth, long nHeight, float** ppImage, float nBackgroundColour = 0, CSLPEllipse* pEllipse = 0, long nNumEllipse = 0)
	{
		CSLPEllipse ellipse[MaxEllipses];

		//perform simple check on input parameters
		if (pEllipse != 0 && (nNumEllipse <= 0 || nNumEllipse > MaxEllipses)) return false;
		if (nWidth < 0 || nWidth > MaxImageDim) return false;
		if (nHeight < 0 || nHeight > MaxImageDim) return false;

		//allocate enough space for a greyscale image
		(*ppImage) = new float[nWidth * nHeight];
		//set background to black
		ClearBackground(*ppImage, nWidth, nHeight, nBackgroundColour);
		//prepare the ellipse data
		if (pEllipse == 0)
		{
			//see  https://en.wikipedia.org/wiki/Shepp%E2%80%93Logan_phantom
			ellipse[0] = CSLPEllipse(0, 0, 0.69f, 0.92f, 0, 2);//a
			ellipse[1] = CSLPEllipse(0, -0.0184, 0.6624, 0.874, 0, -0.98);//b
			ellipse[2] = CSLPEllipse(0.22, 0, 0.11, 0.31, -18.0, -0.02);//c
			ellipse[3] = CSLPEllipse(-0.22, 0, 0.15, 0.41, 18.0, -0.02);//d
			ellipse[4] = CSLPEllipse(0, 0.35, 0.21, 0.25, 0, 0.01);//e
			ellipse[5] = CSLPEllipse(0, 0.1, 0.046, 0.046, 0, 0.01); //f
			ellipse[6] = CSLPEllipse(0, -0.1, 0.046, 0.046, 0, 0.02);//g
			ellipse[7] = CSLPEllipse(-0.08, -0.605, 0.046, 0.023, 0, 0.01);//h
			ellipse[8] = CSLPEllipse(0, -0.605, 0.023, 0.023, 0, 0.01);//i
			ellipse[9] = CSLPEllipse(0.06, -0.605, 0.023, 0.046, 0, 0.01);//j
		}
		else
		{
			for (int h = 0; h < nNumEllipse; h++)
			{
				ellipse[h] = pEllipse[h];
				ellipse[h].bValid = true;
			}
		}
		//draw the ellipses
		for (int h = 0; h < 10; h++)
		{
			if (!ellipse[h].bValid) continue;
			FillEllipse(*ppImage, nWidth, nHeight, ellipse[h]);
		}
		return true;
	}
	 
};

