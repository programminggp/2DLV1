#ifndef CCAMERARANGE_H
#define CCAMERARANGE_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CCameraRange :public CCharacter{
public:
	static CCameraRange*mpCameraRange;
	//�f�t�H���g�R���X�g���N�^
	CCameraRange();

	//�X�V
	void Update();

	//�J�����̓����蔻��
	CCollider mColRange;

	//�R���C�_�̍X�V
	void TaskCollision();
};


#endif