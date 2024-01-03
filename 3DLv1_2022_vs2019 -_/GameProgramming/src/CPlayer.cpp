//�v���C���[�N���X�̃C���N���[�h
#include <math.h>
#include "CPlayer.h"
#include "CApplication.h"
#include "CColliderManager.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f) //��]���x
#define VELOCITY CVector(0.0f,0.0f,0.5f) //�ړ����x
#define VELOCITY2 CVector(0.5f,0.0f,0.0f) //�ړ����x�i��)
#define ROTATION_XV CVector(1.0f,0.0f,0.0f) //��]���x
#define MOS_POS_X 400 //�}�E�X���W��X�␳
#define MOS_POS_Y 300 //�}�E�X���W��Y�␳

CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::sBotan = 0;

int CPlayer::Botan()
{
	return sBotan;
}

int CPlayer::sGate = 0;

int CPlayer::Gate()
{
	return sGate = 0;
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}


//CPlayer(�ʒu�A��]�A�X�P�[��)
CPlayer::CPlayer(const CVector& pos, const CVector& rot, const CVector& scale)
{
	CTransform::Update(pos, rot, scale); //�s��̍X�V
}

void CPlayer::Collision()
{
	//�R���C�_�̗D��x�ύX
	mLine1.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//�Փˏ��������s
	//CCollisionManager::Instance()->Collision(&mLine1, COLLISIONRANGE);
	//CCollisionManager::Instance()->Collision(&mLine2, COLLISIONRANGE);
	//CCollisionManager::Instance()->Collision(&mLine3, COLLISIONRANGE);
	CColliderManager::Instance()->Collision(&mLine1);
	CColliderManager::Instance()->Collision(&mLine2);
	CColliderManager::Instance()->Collision(&mLine3);
}

void CPlayer::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ELINE://�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
			}
		}
		break;
	
	case CCollider::EBOTAN://�{�^���R���C�_
	    //����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����x�N�g��
			//�{�^���Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleBotan(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
				sBotan = 1;
			}
		}
		break;
	}
	
}

//�X�V����
void CPlayer::Update() {
	if (sBotan > 0)
	{
		sBotan--;
	}
	//W�L�[�őO�i
	if (mInput.Key('W')) {
		//Z�������̒l����]�����ړ�������
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//S�L�[�Ō��
	if (mInput.Key('S')) {
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//A�L�[�ō�
	if (mInput.Key('A')) {
		//Z�������̒l����]�����ړ�������
		mPosition = mPosition + VELOCITY2 * mMatrixRotate;
	}
	//D�L�[�ŉE
	if (mInput.Key('D')) {
		mPosition = mPosition - VELOCITY2 * mMatrixRotate;
	}
	if (sBotan == 1) {
		if (mInput.Key('F')) {
			sGate++;
		}
	}
	////S�L�[���͂ŉ�����
	//if (mInput.Key('S')) {
	//	//X���̉�]�l�팸�Z
	//	mRotation = mRotation - ROTATION_XV;
	//}
	////W�L�[���͂ŏ����
	//if (mInput.Key('W')) {
	//	//X���̉�]�l����Z
	//	mRotation = mRotation + ROTATION_XV;
	//}
	////�X�y�[�X�L�[���͂Œe����
	//if (mInput.Key(VK_SPACE)) {
	//	CBullet* bullet = new CBullet();
	//	bullet->Set(0.1f, 1.5f);
	//	bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
	//	bullet->Rotation(mRotation);
	//	bullet->Update();
	//	/*CApplication::TaskManager()->Add(bullet);*/
	//}
	//�ϊ��s��̍X�V
	CTransform::Update();
	//UI�ݒ�
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());
}