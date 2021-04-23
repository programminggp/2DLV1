#ifndef COBJ_H
#define COBJ_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CObj :public CCharacter{
public:
	//�R���C�_�̒ǉ�
	CCollider *mpCollider;
	//�R���X�g���N�^�ŏ����ݒ�
	CObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider = true);
	~CObj();

	int mObjNumber;
	
	////�Փˏ���
	//void Collision(CCollider *m, CCollider *y);

	void Update();//virtual�c�Ē�`�\�ɂȂ�?

	//bool mDeleteFlag;

	////�R���C�_�̍X�V
	//void TaskCollision();

	////�W�����v���x�̕ϐ�
	//float mVelocity;
};

//class CObjection :public CObj{
//public:
//	//�R���C�_�̍X�V
//	void TaskCollision();
//};
#endif