#ifndef CSPRING_H
#define CSPRING_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"

class CItem : public CCharacter{
public:
	//デフォルトコンストラクタ
	CItem();

	CItem(CModel *model, CVector position, CVector rotation, CVector scale, int itemnum);

	CCollider mColBody;

	//衝突処理
	void Collision(CCollider *m, CCollider *y);

	int mItemNumber;

	//static CItem *mpItem;

	//CSound SoundDest;//破壊音

	bool mBoatMove;

	void Update();
	float mADMoveX;
	float mWSMoveZ;
	static int mTargetAmount;//的の残数

	void TaskCollision();
};

#endif