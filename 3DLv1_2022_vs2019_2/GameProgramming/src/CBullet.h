#pragma once
#include "CCharacter.h"

class CBullet : public CCharacter
{
public:
	//衝突処理２
	void Collision();
	//衝突処理４
	//Collision(自分のポインタ, 衝突相手のポインタ)
	void Collision(CCharacter* m, CCharacter* o);
	//CBullet(X座標,Y座標,幅,高さ,画像右,画像左,画像下,画像上,テクスチャのポインタ)
	CBullet(float x, float y, float w, float h,float l, float r, float b, float t, CTexture* pt);
	CBullet();
	void Update();
	//void Render();
	bool Collision(CRectangle* rect);
};