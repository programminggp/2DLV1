#ifndef COBJWATER_H
#define COBJWATER_H
#include "CObj.h"

class CObjWater :public CObj{
public:
	//コンストラクタで初期設定
	CObjWater(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif