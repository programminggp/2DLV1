#pragma once
#include "CRectangle.h"
#include "CTexture.h"

class CCharacter : public CRectangle
{
public:
	enum class ETag
	{
		EINIT,
		EENEMY,
		EMISS,
		EBULLET,
	};
	enum class EState	//èÛë‘
	{
		EMOVE,	//à⁄ìÆ
		ESTOP	//í‚é~
	};
protected:
	bool mEnabled;
	ETag mTag;
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
	virtual bool Collision(CCharacter* m, CCharacter* o);
	ETag Tag();
	bool Enabled();
};