#pragma once
#include "CCharacter.h"

class CItem : public CCharacter
{
private:
	static int mIh;
public:
	//コンストラクタ
	CItem(float x, float y, float w, float h, CTexture* pt);
	static int Ih();
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);

	//更新処理
	void Update();
};