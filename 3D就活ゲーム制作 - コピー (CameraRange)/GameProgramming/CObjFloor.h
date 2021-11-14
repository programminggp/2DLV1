#ifndef COBJFLOOR_H
#define COBJFLOOR_H
#include "CObj.h"

class CObjFloor :public CObj{
public:
	//コンストラクタで初期設定
	CObjFloor(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif
