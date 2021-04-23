#ifndef COBJFLOOR_H
#define COBJFLOOR_H
#include "CObj.h"

class CObjFloor :public CObj{
public:
	//コンストラクタで初期設定
	CObjFloor(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);

	////CObj側で衝突処理…は以前、処理が爆重になったのでやらない、やれない、やりたくない
	//void Collision(CCollider *m, CCollider *y);
	////更新処理のオーバーライド
	//void Update();
};
#endif
