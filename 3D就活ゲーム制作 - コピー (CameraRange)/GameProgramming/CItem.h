#ifndef CSPRING_H
#define CSPRING_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"

class CItem : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^
	CItem();

	CItem(CModel *model, CVector position, CVector rotation, CVector scale, int itemnum);

	CCollider mColBody;

	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);

	int mItemNumber;

	//static CItem *mpItem;

	//CSound SoundDest;//�j��

	bool mBoatMove;

	void Update();
	float mADMoveX;
	float mWSMoveZ;
	static int mTargetAmount;//�I�̎c��

	void TaskCollision();
};

#endif