#include"CXMutant.h"
#include"CXCharacter.h"
#include"CMatrix.h"
#include"CVector.h"
#include"CTransform.h"
#include"CCollisionManager.h"
#include"CTaskManager.h"
#include"CColliderCapsule.h"
#include"CXPlayer.h"
#include"CCollision.h"

//int CXMutant::MutantHp = 5;

CXMutant::CXMutant()
	: mColCapBody(this, nullptr, CVector(0.0f, -110.0f, 40.0f), CVector(0.0f, 65.0f, 0.0f), 0.8f)
	, mColSphereArm(this, nullptr, CVector(0.0f, 40.0f, 0.0f), 0.5f)
	, mCore(this, nullptr, CVector(0.0f, 0.0f,10.0f), 0.9f)
	, MutantHp(5)
{
	mTag = EMUTANT;
}

void CXMutant::Init(CModelX* model)
{
	CXCharacter::Init(model);
	mColCapBody.Matrix(&mpCombinedMatrix[14]);//����
	mColSphereArm.Matrix(&mpCombinedMatrix[20]);//�r
	mCore.Matrix(&mpCombinedMatrix[14]);//�R�A
	mColSphereArm.Tag(CCollider::EMUTANTARM);
	mCore.Tag(CCollider::ECORE);
}

void CXMutant::Update()
{
	//������(X��)�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//�����(Y��)�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O����(Z��)�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	CXPlayer* player = CXPlayer::Get();
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	float dx = vp.Dot(vx);//���x�N�g���̓��ς����߂�
	float dy = vp.Dot(vy);//��x�N�g�����ς����߂�
	float margin = 0.1f;
	//�������։�]
	if (dx > margin){
		//CXMutant::ChangeAnimation(2, true, 45);
		mRotation = mRotation + CVector(0.0f, 2.0f, 0.0f);//���։�]
	}
	else if (dx < -margin){
		//CXMutant::ChangeAnimation(2, true, 45);
		mRotation = mRotation + CVector(0.0f, -2.0f, 0.0f);//�E�ɉ�]
	}
	////�㉺�ɉ�]
	//if (dy > margin)
	//{
	//	mRotation = mRotation + CVector(-2.0f, 0.0f, 0.0f);//��։�]
	//}
	//else if (dy < -margin)
	//{
	//	mRotation = mRotation + CVector(2.0f, 0.0f, 0.0f);//���ɉ�]
	//}
	//�ړ�����
	mPosition = mPosition + CVector(0.0f, -0.0f, 0.0f) * mMatrixRotate;
	CTransform::Update();//�s��X�V
	//���悻3�b���ƂɖڕW�n�_���X�V
	int r = rand() % 50;//rand()�͐����̗�����Ԃ�
						 //%180��180�Ŋ������]������߂�
	if (r == 0)
		//if (mPoint.X() == 0.0f && mPoint.Y() == 0.0f && mPoint.Z() == 0.0f)
	{
		if (player != nullptr){
			mPoint = player->Position();
		}
		else{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}

	//CXMutant::ChangeAnimation(3, true, 160);

	if (MutantHp <= 0) {
		CXMutant::ChangeAnimation(4, false, 70);
	}

	CXCharacter::Update();
	CTransform::Update();
}

void CXMutant::Collision(CCollider* m, CCollider* o){
	////���g�̃R���C�_�^�C�v�̔���
	//switch (m->Type()) {
	//case CCollider::ECAPSULE:
	//	//����̃R���C�_���O�p�R���C�_�̎�
	//	if (o->Type() == CCollider::ETRIANGLE) {
	//		CVector adjust;//�����p�x�N�g��
	//		//�O�p�`�Ɛ����̏Փ˔���
	//		if (CCollider::CollisionTriangleLine(o, m, &adjust)){
	//			mPosition = mPosition + adjust;//�ʒu�̍X�V(mPosition + adjust)
	//			CTransform::Update();//�s��̍X�V
	//		}
	//	}
	//	break;
	//case CCollider::ESPHERE:
	//	//�R���C�_��m��y���Փ˂��Ă��邩����
	//	if (m->Tag() == CCollider::ECORE){
	//		if (o->Tag() == CCollider::ESWORD) {
	//			if (CCollider::Collision(m, o)) {
	//				MutantHp--;
	//			}
	//		}
	//		if (o->Tag()== CCollider::EPLAYERSMAGIC) {
	//			if (CCollider::Collision(m, o)) {
	//				MutantHp -= 2;
	//			}
	//		}
	//		if (o->Tag() == CCollider::EPLAYERAMAGIC) {
	//			if (CCollider::Collision(m, o)) {
	//				MutantHp -= 2;
	//			}
	//		}
	//	}
	//	break;
	//}
		//case CCollider::ESPHERE://���R���C�_�̎�
		////�R���C�_��m��y���Փ˂��Ă��邩����
		//	if (o->Type() == CCollider::ESPHERE && CCollider::Collision(m, o)) {
		//		//�Փ˂��Ă��鎞�͖����ɂ���
		//		//�폜mEnabled = false;
		//		/*PlayerHp--;
		//		if (PlayerHp <= 0)
		//		{
		//			mEnabled = false;
		//		}*/
		//	}
		//	break;

	CVector adjust;
	if (CCollision::CollisionAll(m, o, &adjust)) {
		if (o->Type() == CCollider::ETRIANGLE) {
			mPosition = mPosition + adjust;
		}
		if (o->Type() == CCollider::ECAPSULE) {
			mPosition = mPosition + adjust;
		}
		if (CXPlayer::BattleSwitch == true) {
			if (o->Tag() == CCollider::ESWORD) {
				MutantHp--;
			}
		}
		if (o->Tag() == CCollider::EPLAYERSMAGIC) {
			MutantHp -= 2;
		}
		if (o->Tag() == CCollider::EPLAYERAMAGIC) {
			MutantHp -= 2;
		}
	}
}

void CXMutant::TaskCollision()
{
	mColCapBody.ChangePriority();
	mColSphereArm.ChangePriority();
	mCore.ChangePriority();
	CCollisionManager::Get()->Collision(&mColCapBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereArm, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCore, COLLISIONRANGE);
}




