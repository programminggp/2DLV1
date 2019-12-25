#ifndef CAIRBASE_H
#define CAIRBASE_H

#include "CCharacter.h"
#include "CCollider.h"

class CAirBase : public CCharacter {
public:
	//コライダ
	CCollider mCollider;
	//コンストラクタ
	//CAirBase(モデル, 位置, 回転, 拡縮)
	CAirBase(CModel *model, CVector position, CVector rotation, CVector scale);
	//衝突処理
	void Collision(CCollider *m, CCollider *y);
};


#endif
