#ifndef COBJ_H
#define COBJ_H

#include "CCharacter.h"
#include "CCollider.h"

class CObj : public CCharacter {
public:
	//コライダの追加
	CCollider *mpCollider;
	CObj()
		: mpCollider(nullptr)
	{}
	//コンストラクタで初期設定
	CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale);
	~CObj();
};

#endif
