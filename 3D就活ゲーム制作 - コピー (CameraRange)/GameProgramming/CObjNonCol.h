#ifndef COBJNONCOL_H
#define COBJNONCOL_H
#include "CObj.h"

class CObjNonCol :public CObj{
public:
	//コンストラクタで初期設定
	CObjNonCol(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, bool hasshadow = true);
};
#endif

