#include "CXPlayer.h"
#include "CActionCamera.h"
#include "CTaskManager.h"

CXPlayer::CXPlayer()
	:
	mColBody(this, nullptr, CVector(0.0f,25.0f, 0.0f), CVector(0.0f, 150.0f, 0.0f), 0.5f)
	, mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr,
		CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereSword(this, nullptr,
		CVector(-10.0f, 10.0f, 50.0f), 0.3f, CCollider::ETag::ESWORD)
{
	//�^�O�Ƀv���C���[��ݒ肵�܂�
	mTag = EPLAYER;
	//mPriority = EPLAYER;
	//CTaskManager::Instance()->Remove(this);
	//CTaskManager::Instance()->Add(this);
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColBody.Matrix(&mpCombinedMatrix[1]);
	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);
}

void CXPlayer::Update()
{
//	mPosition.Y(mPosition.Y() - 0.1f);

	//�J�����̑O��
	CVector cameraZ = CActionCamera::Instance()->VectorZ();
	//�J�����̍�����
	CVector cameraX = CActionCamera::Instance()->VectorX();
	//�L�����N�^�̑O��
	CVector charZ = mMatrixRotate.VectorZ();
	//XZ���ʂɂ��Đ��K��
	cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
	cameraX.Y(0.0f); cameraX = cameraX.Normalize();
	charZ.Y(0.0f); charZ = charZ.Normalize();

	switch (AnimationIndex())
	{
	case 3:
		if (IsAnimationFinished())
		{
			ChangeAnimation(4, false, 30);
		}
		break;
	case 4:
		if (IsAnimationFinished())
		{
			ChangeAnimation(0, true, 60);
		}
		break;
	default:
		//�����̐ݒ�
		CVector move;
		if (mInput.Key('A')) {
			move = move + cameraX;
		}
		if (mInput.Key('D')) {
			move = move - cameraX;
		}
		if (mInput.Key('W')) {
			move = move + cameraZ;
		}
		if (mInput.Key('S')) {
			move = move - cameraZ;
		}
		//��������
		if (move.Length() > 0.0f)
		{
			//�V��
			const float MARGIN = 0.06f;
			//���K��
			move = move.Normalize();
			//�����̌����ƌ��������������ŊO��
			float cross = charZ.Cross(move).Y();
			//�����̌����ƌ��������������œ���
			float dot = charZ.Dot(move);
			//�O�ς��v���X�͍���]
			if (cross > MARGIN) {
				mRotation.Y(mRotation.Y() + 5.0f);
			}
			//�O�ς��}�C�i�X�͉E��]
			else if (cross < -MARGIN) {
				mRotation.Y(mRotation.Y() - 5.0f);
			}
			//�O��̌����������Ƃ����ς�1.0
			else if (dot < 1.0f - MARGIN) {
				mRotation.Y(mRotation.Y() - 5.0f);
			}
			ChangeAnimation(1, true, 60);
			mPosition = mPosition + move * 0.1f;
		}
		else
		{
			ChangeAnimation(0, true, 60);
		}

		if (mInput.Key(' '))
		{
			ChangeAnimation(3, false, 30);
		}


	}
	CXCharacter::Update();
	mColBody.Update();
}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::ECAPSULE:
		if (o->Type() == CCollider::ECAPSULE)
		{
			CVector adjust;
			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
			{
				mPosition = mPosition + adjust;
				CTransform::Update();
			}
		}
		else if (o->Type() == CCollider::ETRIANGLE)
		{
			CVector adjust;
			if (CCollider::CollisionCapsuleTriangle(m, o, &adjust))
			{
				mPosition = mPosition + adjust;
				CTransform::Update();
			}
		}
		break;
	}
}