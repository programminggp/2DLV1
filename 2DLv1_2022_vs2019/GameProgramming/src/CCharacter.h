#pragma once
#include "CRectangle.h"
#include "CTexture.h"

class CCharacter : public CRectangle
{
protected:
	enum class ETag
	{
		EINIT,
		EENEMY,
		EMISS,
	};
	ETag mTag;
	enum class EState	//èÛë‘
	{
		EMOVE,	//à⁄ìÆ
		ESTOP	//í‚é~
	};
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	CCharacter();
	CTexture* Texture();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	virtual void Render();
	void Move();
	virtual void Update() = 0;
};