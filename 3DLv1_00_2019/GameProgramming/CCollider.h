#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
/*
コライダクラス
衝突判定データ
*/
class CCollider : public CCharacter {
public:
	float mRadius;	//半径
	//コンストラクタ
	//CCollider(親, 位置, 回転, 拡縮, 半径)
	CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius);
	//描画
	void Render();
};

#endif
