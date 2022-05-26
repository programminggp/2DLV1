#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include <stdio.h>
class CCharacter : public CRectangle
{
public:
	enum class ETag
	{
		EZERO,		//‰Šú’l
		EBULLET,	//’e
		EENEMY,		//“I
		EPLAYER		//ƒvƒŒƒCƒ„[
	};
	enum class EState	//ó‘Ô
	{
		EMOVE,	//ˆÚ“®
		ESTOP	//’âŽ~
	};
protected:
	bool mEnabled;
	ETag mTag;
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	bool Enabled();
	ETag Tag();
	//Õ“Ëˆ—‚Q
	virtual void Collision() {};
	//Õ“Ëˆ—‚S
	//Collision(Ž©•ª‚Ìƒ|ƒCƒ“ƒ^, Õ“Ë‘ŠŽè‚Ìƒ|ƒCƒ“ƒ^)
	virtual void Collision(CCharacter* m, CCharacter* o) {};
	virtual void Update() = 0;
	CCharacter();
	CTexture* Texture();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	virtual void Render();
	void Move();


};