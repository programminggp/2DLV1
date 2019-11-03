#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//
#include "CTransform.h"
/*
コライダクラス
衝突判定データ
*/
class CCollider : public CTask, public CTransform {
public:
	CCharacter *mpParent;
	float mRadius;	//半径
	//コンストラクタ
	//CCollider(親, 位置, 回転, 拡縮, 半径)
	CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius);
	~CCollider();
	//描画
	void Render();
};

#endif
