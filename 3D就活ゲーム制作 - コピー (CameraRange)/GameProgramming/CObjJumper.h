#ifndef COBJJUMPER_H
#define COBJJUMPER_H
#include "CObj.h"

class CObjJumper :public CObj{
public:
	//コンストラクタで初期設定
	CObjJumper(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif
