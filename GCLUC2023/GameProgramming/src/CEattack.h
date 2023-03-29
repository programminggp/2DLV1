#pragma once
#include "CCharacter.h"

class CEattack : public CCharacter
{
private:
public:
	//コンストラクタ
	CEattack(float x, float y, float w, float h, CTexture* pt);
	//デストラクタ
	~CEattack();

	//更新処理
	void Update();

};