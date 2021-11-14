#ifndef COBJWALL_H
#define COBJWALL_H
#include "CObj.h"

class CObjWall :public CObj{
public:
	//コンストラクタで初期設定
	CObjWall(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif


