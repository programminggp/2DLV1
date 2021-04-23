#ifndef COBJBOOST_H
#define COBJBOOST_H

#include "CObj.h"

class CObjBoost :public CObj{
public:
	//コンストラクタで初期設定
	CObjBoost(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif