#pragma once
#include "CCharacter.h"
#include "CTask.h"

#define BOAX 1.5f 
#define BOAY 1.5f

class CBossAttackBox2 : public CCharacter
{
private:
	float mBAx;
	float mBAy;
public:
	//コンストラクタ
	CBossAttackBox2(float x, float y, float w, float h, CTexture* pt);
	//デストラクタ
	~CBossAttackBox2();

	//更新処理
	void Update();

};