#pragma once
#include "CCharacter.h"

class CEnemy2 : public CCharacter
{
public:
	//敵の数を設定
	static void Num(int num);
	//敵の数を取得
	static int Num();
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
	//CEnemy2(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CEnemy2(float x, float y, float w, float h, CTexture* pt);
	//更新処理
	void Update();
private:
	static int sNum;	//敵の数
};