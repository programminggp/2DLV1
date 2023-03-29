#pragma once
#include "CCharacter.h"

class CMagicBullet : public CCharacter
{
private:
public:
	//コンストラクタ
	CMagicBullet(float x, float y, float w, float h, CTexture* pt);
	//デストラクタ
	~CMagicBullet();
 
	//更新処理
	void Update();

};