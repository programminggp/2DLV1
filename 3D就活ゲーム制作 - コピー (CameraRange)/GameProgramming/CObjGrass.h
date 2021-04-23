#ifndef COBJGRASS_H
#define COBJGRASS_H
#include "CObj.h"

class CObjGrass :public CObj{
public:
	//コンストラクタで初期設定
	CObjGrass(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);

	////CObj側で衝突処理…は以前、処理が爆重になったのでやらない、やれない、やりたくない
	//void Collision(CCollider *m, CCollider *y);
	////更新処理のオーバーライド
	//void Update();
};
#endif
