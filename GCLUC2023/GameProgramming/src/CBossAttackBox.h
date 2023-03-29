#pragma once
#include "CCharacter.h"
#include "CTask.h"

class CBossAttackBox : public CCharacter
{
private:
public:
	//コンストラクタ
	CBossAttackBox(float x, float y, float w, float h, CTexture* pt);
	//デストラクタ
	~CBossAttackBox();

	//更新処理
	void Update();

};