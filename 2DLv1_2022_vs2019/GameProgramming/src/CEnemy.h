#pragma once
#include "CCharacter.h"

class CEnemy : public CCharacter
{
public:
	//CEnemy(X座標,Y座標,幅,高さ,画像右,画像左,画像下,画像上,テクスチャのポインタ)
	CEnemy(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt);
	void Update();
	bool Collision(CRectangle* rect);
	void Collision();
	void Collision(CCharacter* m, CCharacter* o);
};