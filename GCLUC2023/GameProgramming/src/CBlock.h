#pragma once
#include "CCharacter.h"

class CBlock: public CCharacter
{
private:
public:
	//コンストラクタ
	CBlock(float x, float y, float w, float h, CTexture* pt);
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);

	//更新処理
	void Update();
};