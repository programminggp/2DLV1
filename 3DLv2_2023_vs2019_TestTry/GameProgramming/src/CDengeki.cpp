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
	if (!sMaterial.Texture()->IsLoaded())
	{
		sMaterial.Texture()->Load(EFFECT_IMAGE);
		sMaterial.Diffuse(RGBA);
	}
}

CDengeki::CDengeki()
	: mSize(0)
	, mState(0)
{

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

		mState++;
		const int cycle = 12;
		if (mState > cycle)
			mState = 0;
		if (mState < cycle/2)
		{
			mUV[0][0] = 0.0f;
			mUV[0][1] = 1.0f;
			mUV[1][0] = 0.0f;
			mUV[1][1] = 0.6f;
			mUV[2][0] = 1.0f;
			mUV[2][1] = 0.6f;
			mUV[3][0] = 1.0f;
			mUV[3][1] = 1.0f;
		}
		else if(mState < cycle)
		{
			mUV[0][0] = 0.0f;
			mUV[0][1] = 0.55f;
			mUV[1][0] = 0.0f;
			mUV[1][1] = 0.0f;
			mUV[2][0] = 1.0f;
			mUV[2][1] = 0.0f;
			mUV[3][0] = 1.0f;
			mUV[3][1] = 0.55f;
		}
		glBegin(GL_QUADS);
		glTexCoord2f(mUV[0][0], mUV[0][1]);
		glVertex3f(mStartPoint.X(), mStartPoint.Y() + mSize, mStartPoint.Z());
		glTexCoord2f(mUV[1][0], mUV[1][1]);
		glVertex3f(mStartPoint.X(), mStartPoint.Y() - mSize, mStartPoint.Z());
		glTexCoord2f(mUV[2][0], mUV[2][1]);
		glVertex3f(mEndPoint.X(), mEndPoint.Y() - mSize, mEndPoint.Z());
		glTexCoord2f(mUV[3][0], mUV[3][1]);
		glVertex3f(mEndPoint.X(), mEndPoint.Y() + mSize, mEndPoint.Z());

		glTexCoord2f(mUV[0][0], mUV[0][1]);
		glVertex3f(mStartPoint.X()-mSize, mStartPoint.Y(), mStartPoint.Z());
		glTexCoord2f(mUV[1][0], mUV[1][1]);
		glVertex3f(mStartPoint.X()+mSize, mStartPoint.Y(), mStartPoint.Z());
		glTexCoord2f(mUV[2][0], mUV[2][1]);
		glVertex3f(mEndPoint.X()+mSize, mEndPoint.Y(), mEndPoint.Z());
		glTexCoord2f(mUV[3][0], mUV[3][1]);
		glVertex3f(mEndPoint.X()-mSize, mEndPoint.Y(), mEndPoint.Z());
		glEnd();

		sMaterial.Disabled();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
	}
}
