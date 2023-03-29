#pragma once
#include "CCharacter.h"
#include "CTask.h"

class CSlimeAttackBox : public CCharacter
{
private:
public:
	//コンストラクタ
	CSlimeAttackBox(float x, float y, float w, float h, CTexture* pt);
	//デストラクタ
	~CSlimeAttackBox();

	//更新処理
	void Update();

};