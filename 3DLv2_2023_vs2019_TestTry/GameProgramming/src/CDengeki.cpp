#include "CDengeki.h"

#define EFFECT_IMAGE "Effect\\ElectricShock.png"
#define RGBA 1.0f,1.0f,0.0f,0.5f


CMaterial CDengeki::sMaterial;

void CDengeki::Set(
	  const CVector& startPoint
	, const CVector& endPoint
	, float size
)
{
	mStartPoint = (startPoint);
	mEndPoint = (endPoint);
	mSize = (size);
	mState = (0);
}

CDengeki::CDengeki()
	: mSize(0)
	, mState(0)
{
	if (!sMaterial.Texture()->IsLoaded())
	{
		sMaterial.Texture()->Load(EFFECT_IMAGE);
		sMaterial.Diffuse(RGBA);
	}
}

void CDengeki::Update()
{
}

void CDengeki::Render()
{
	if (mInput.Key(VK_SPACE))
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);

		sMaterial.Enabled();

		glBegin(GL_QUADS);
		glVertex3f(mStartPoint.X(), mStartPoint.Y() + mSize, mStartPoint.Z());
		glVertex3f(mStartPoint.X(), mStartPoint.Y() - mSize, mStartPoint.Z());
		glVertex3f(mEndPoint.X(), mEndPoint.Y() - mSize, mEndPoint.Z());
		glVertex3f(mEndPoint.X(), mEndPoint.Y() + mSize, mEndPoint.Z());
		glVertex3f(mStartPoint.X()-mSize, mStartPoint.Y(), mStartPoint.Z());
		glVertex3f(mStartPoint.X()+mSize, mStartPoint.Y(), mStartPoint.Z());
		glVertex3f(mEndPoint.X()+mSize, mEndPoint.Y(), mEndPoint.Z());
		glVertex3f(mEndPoint.X()-mSize, mEndPoint.Y(), mEndPoint.Z());
		glEnd();

		sMaterial.Disabled();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
	}
}
