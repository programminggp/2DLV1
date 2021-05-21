#include "CRigidObj.h"
#include "CTaskManager.h"

CRigidObj *CRigidObj::mpRigObj = 0;

#define G (9.8f / 120.0f)//�d�͉����x//60.0f

//CRigidObj::CRigidObj()
////:mColBody(this, CVector(0.0f, 4.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f)
//{
//	mpRigObj = this;
//
//	//mScale = CVector(2.5f, 2.5f, 2.5f);
//	mVelocity = 0.0f;
//	mJumpPrio = 0;
//	//CanMove = false;
//
//	//mTag = EPLAYER;
//	//CCharacter::Update();
//
//	//mColBody.mTag = CCollider::EBODY;
//
//}


//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k
CRigidObj::CRigidObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:mpCollider(0)
, mColBody(this, CVector(0.0f, 0.0f - 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 21.0f)
, mColBody2nd(this, CVector(0.0f, 0.0f + 3.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 31.0f)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;

	mpRigObj = this;
	mVelocity = 0.0f;
	mJumpPrio = 0;

	CCharacter::Update();
	//���f���̎O�p�`�̐����A�R���C�_�̔z����쐬���܂�
	mpCollider = new CCollider[model->mTriangles.size()];
	for (int i = 0; i < model->mTriangles.size(); i++){
		//�R���C�_���O�p�`�R���C�_�Őݒ肵�Ă����܂�
		mpCollider[i].SetTriangle(this,
			model->mTriangles[i].mV[0],
			model->mTriangles[i].mV[1],
			model->mTriangles[i].mV[2]);
		mpCollider[i].ChangePriority();
	}
	//mEnabled = false;
}
//�f�X�g���N�^
CRigidObj::~CRigidObj(){
	//�R���C�_������΍폜
	if (mpCollider){
		//delete[] �z����폜
		delete[] mpCollider;
	}
}

void CRigidObj::Update(){
	mPosition = CVector(0.0f, mVelocity*2.0f, 0.0f) * //mMatrixScale * 
		CMatrix().RotateZ(0) *
		CMatrix().RotateX(0) *
		CMatrix().RotateY(0)
		*mMatrixTranslate;
	CCharacter::Update();
	//�]�����Ă��܂�����(R�L�[�ő����X�^�[�g)
	if (mPosition.mY < -150.0f){
		//�����̐�����0�ɂ���
		mVelocity = 0.0f;
		mPosition.mY = 30.0f;
		CCharacter::Update();
	}	
	//�d�͂̉e���𔽉f����
	mVelocity -= G;

	if (mJumpPrio > 0){
		mJumpPrio--;
	}
}

void CRigidObj::Collision(CCollider *mc, CCollider *yc){
	//���g�̃R���C�_�^�C�v�̔���
	switch (mc->mType){
	case CCollider::ETRIANGLE://�O�p�R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (yc->mType == CCollider::ETRIANGLE){
			mVelocity = 0;
		}
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (yc->mType == CCollider::ETRIANGLE){
			//�������g�ƏՓ˂���̋֎~
			if (mc != yc){
				CVector aiueo;//�Ƃ�܃x�N�g��
				if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
					mVelocity = 1.0f;
				}
			}			
		}
	}
}


void CRigidObj::TaskCollision()
{
	mColBody.ChangePriority();
	CollisionManager.Collision(&mColBody);
	mColBody2nd.ChangePriority();
	CollisionManager.Collision(&mColBody2nd);
}