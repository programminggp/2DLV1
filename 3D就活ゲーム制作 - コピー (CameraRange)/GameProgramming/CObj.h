#ifndef COBJ_H
#define COBJ_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CObj :public CCharacter{
public:
	//コライダの追加
	CCollider *mpCollider;
	//コンストラクタで初期設定
	CObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider = true);
	~CObj();

	int mObjNumber;

	void Update();
};

#endif