//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include "CKey.h"
//
#include "CBullet.h"
//
#include "CTaskManager.h"
//
#include "CCollisionManager.h"
//
#include "CUtil.h"

CPlayer *CPlayer::spThis = 0;

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
{
	spThis = this;
	//
	mText.LoadTexture("FontWhite.tga", 1, 4096 / 64);
}

//�X�V����
void CPlayer::Update() {
	//A�L�[���͂ŉ�]
	if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation.mY += 1;
	}
	if (CKey::Push('D')) {
		//Y���̉�]�l�𑝉�
		mRotation.mY -= 1;
	}
	//����L�[���͂őO�i
	if (CKey::Push(VK_UP)) {
		//Z��������1�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	//S�L�[���͂ŏ����
	if (CKey::Push('S')) {
		//X���̉�]�l�����Z
		mRotation.mX -= 1;
	}
	//W�L�[���͂ŏ����
	if (CKey::Push('W')) {
		//X���̉�]�l�����Z
		mRotation.mX += 1;
	}

	//�X�y�[�X�L�[���͂Œe����
	if (CKey::Push(VK_SPACE)) {
		CBullet *bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
		bullet->mRotation = mRotation;
		bullet->Update();
//		TaskManager.Add(bullet);
	}

	//CTransform�̍X�V
	CTransform::Update();
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType) {
	case CCollider::ELINE://�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition - adjust * -1;
			//�s��̍X�V
			CTransform::Update();
		}
		break;
	}
}
//�Փˏ���
void CPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
}

void CPlayer::Render()
{
	//�e�̕`�揈��
	CCharacter::Render();

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�i�ΐF�̔������j
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	//������ҏW�G���A�̍쐬
	char buf[64];

	//X����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RX:%7.2f", mRotation.mX);
	//������̕`��
	mText.DrawString(buf, 100, 0, 8, 16);

	//Y����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RY:%7.2f", mRotation.mY);
	//������̕`��
	mText.DrawString(buf, 100, -100, 8, 16);

	//Y���W�̕\��
	//������̐ݒ�
	sprintf(buf, "PY:%7.2f", mPosition.mY);
	//������̕`��
	mText.DrawString(buf, 100, 30, 8, 16);

	CUtil::End2D();

}