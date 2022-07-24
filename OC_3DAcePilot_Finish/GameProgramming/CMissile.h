#ifndef CMISSILE_H
#define CMISSILE_H

#include "CCharacter.h"
#include "CCollider.h"
/*
ミサイルクラス
*/
class CMissile : public CCharacter {
public:
	int mLife;
	CCharacter *mpPoint;

	//ミサイルにコライダ
	CCollider mCollider;
	//コンストラクタ
	//CMissile(モデル, 位置, 回転, 拡縮)
	CMissile(CModel *model, CVector position, CVector rotation, CVector scale);
	//
	void Update();
	//衝突処理
	void Collision(CCollider *m, CCollider *y);
};

#endif
