#pragma once
#include "CCharacter.h"

class CBullet : public CCharacter
{
public:
	//CBullet(X座標,Y座標,幅,高さ,画像右,画像左,画像下,画像上,テクスチャのポインタ)
	CBullet(float x, float y, float w, float h,float l, float r, float b, float t, CTexture* pt);
	CBullet();
	void Update();
	//void Render();
	bool Collision(CRectangle* rect);
	//void Collision();
};