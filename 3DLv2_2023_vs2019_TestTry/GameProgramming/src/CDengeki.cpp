#include "CDengeki.h"

#define EFFECT_IMAGE "Effect\\ElectricShock.png"
#define RGBA 1.0f,1.0f,0.0f,0.5f


CMaterial CDengeki::sMaterial;

CDengeki::CDengeki(
	  const CVector& startPoint
	, const CVector& endPoint
	, float size
)
	:mStartPoint(startPoint)
	,mEndPoint(mEndPoint)
	,mSize(size)
{
	if (sMaterial.Texture()->IsLoaded())
	{
		sMaterial.Texture()->Load("");
		sMaterial.Diffuse(RGBA);
	}
}
