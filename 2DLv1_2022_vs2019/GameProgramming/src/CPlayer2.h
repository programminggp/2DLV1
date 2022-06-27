#pragma once
#include "CCharacter.h"
#include "CInput.h"

class CPlayer2 : public CCharacter
{
public:
	int Hp();
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
	//CPlayer2(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CPlayer2(float x, float y, float w, float h, CTexture* pt);
	//更新処理
	void Update();
private:
	int mInvincble;
	int mHp;
	CInput mInput;
};