#ifndef CAIRBASE_H
#define CAIRBASE_H

#include "CCharacter.h"
#include "CCollider.h"
/*
航空基地クラス
*/
class CAirBase : public CCharacter {
public:
	//ダメージ
	int mDamage;

	//管制塔にコライダ
	CCollider mCollider;
	//コンストラクタ
	//CAirBase(モデル, 位置, 回転, 拡縮)
	CAirBase(CModel *model, CVector position, CVector rotation, CVector scale);
	//衝突処理
	void Collision(CCollider *m, CCollider *y);
};


#endif
