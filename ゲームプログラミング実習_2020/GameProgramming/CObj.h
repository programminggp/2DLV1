#ifndef COBJ_H
#define COBJ_H

#include "CCharacter.h"
//06
#include "CCollider.h"

class CObj : public CCharacter {
public:
	//コライダの追加
	CCollider *mpCollider;
	//コンストラクタで初期設定
	CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale);
	~CObj();

//	void Render() {}
};



#endif
