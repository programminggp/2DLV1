#pragma once
#include "CRectangle.h"
#include "CTexture.h"

class CCharacter : public CRectangle
{
protected:
	enum EState	//ó‘Ô
	{
		EMOVE,	//ˆÚ“®
		ESTOP	//’â~
	};
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	CCharacter();
	CTexture* Texture();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	void Render();
	void Move();
};