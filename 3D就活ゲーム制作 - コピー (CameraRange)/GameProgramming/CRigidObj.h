#ifndef CRIGIDOBJ_H
#define CRIGIDOBJ_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"

class CRigidObj :public CCharacter{
public:
	static CRigidObj*mpRigObj;
	
	//�R���C�_�̒ǉ�
	CCollider *mpCollider;
	
	//�R���X�g���N�^�ŏ����ݒ�
	CRigidObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
	~CRigidObj();
	////�f�t�H���g�R���X�g���N�^
	//CRigidObj();

	//�X�V
	void Update();

	//�v���C���[�̑̂̓����蔻��
	CCollider mColBody;
	CCollider mColBody2nd;

	//�Փˏ���
	void Collision(CCollider *mc, CCollider *yc);

	//�W�����v���x�̕ϐ�
	float mVelocity;
	int mJumpPrio;
	
	//�R���C�_�̍X�V
	void TaskCollision();
};


#endif