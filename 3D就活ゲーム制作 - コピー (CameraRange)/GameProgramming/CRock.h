#ifndef CROCK_H
#define CROCK_H
#include "CCharacter.h"
#include "CCollider.h"

class CRock : public CCharacter{
public:
	//デフォルトコンストラクタ
	CRock();

	CRock(CModel *model, CVector position, CVector rotation, CVector scale);

	CCollider mColBody;

	//衝突処理
	void Collision(CCollider *m, CCollider *y);
};

#endif