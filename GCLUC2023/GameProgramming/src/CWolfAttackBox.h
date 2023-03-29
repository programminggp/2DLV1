#pragma once
#include "CCharacter.h"
#include "CTask.h"

class CWolfAttackBox : public CCharacter
{
private:
public:
	//コンストラクタ
	CWolfAttackBox(float x, float y, float w, float h, CTexture* pt);
	//デストラクタ
	~CWolfAttackBox();

	//更新処理
	void Update();

};