#pragma once
#include "CRectangle.h"
#include "CTexture.h"

class CCharacter : public CRectangle
{
protected:
	enum EState
	{
		EMOVE,
		ESTOP
	};
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	CCharacter();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	void Render();
	CTexture* Texture();
};