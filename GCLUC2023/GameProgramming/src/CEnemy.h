#pragma once
#include "CCharacter.h"

class CEnemy : public CCharacter
{
private:
	static int mNum;	//敵の数

public:
	//コンストラクタ
	CEnemy(float x, float y, float w, float h, CTexture* pt);
	//デストラクタ
	~CEnemy();

	//敵の数を設定
	static void Num(int num);
	//敵の数を取得
	static int Num();

	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);

	//更新処理
	void Update();
};