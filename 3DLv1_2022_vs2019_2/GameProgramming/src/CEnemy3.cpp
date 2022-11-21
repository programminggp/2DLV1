#include "CEnemy3.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CPlayer.h"

#define OBJ "res\\f16.obj"	//���f���̃t�@�C��
#define MTL "res\\f16.mtl"	//���f���̃}�e���A���t�@�C��

CModel CEnemy3::sModel;	//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy3::CEnemy3()
	: CCharacter3(1)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
{
	//���f���������Ƃ��͓ǂݍ���
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &sModel;
}


//CEnemy(�ʒu, ��], �g�k)
CEnemy3::CEnemy3(const CVector& position, const CVector& rotation,const CVector& scale)
	: CEnemy3()	//�f�t�H���g�R���X�g���N�^�����s����
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
}

//�X�V����
void CEnemy3::Update()
{
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - mPosition;
		float dx = vp.Dot(vx);	//���x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(vy);	//��x�N�g���Ƃ̓��ς����߂�
		float dz = vp.Dot(vz);	//�O�x�N�g���Ƃ̓��ς����߂�
		//X���̃Y����2.0�ȉ�
		if (-2.0f < dx && dx < 2.0f && 0.0f < dz && dz <= 30.0f)
		{
			//Y���̃Y����2.0�ȉ�
			if (-2.0f < dy && dy < 2.0f)
			{
				//�e�𔭎˂��܂�
				CBullet* bullet = new CBullet();
				bullet->Set(0.1f, 1.5f);
				bullet->Position(
					CVector(0.0f, 0.0f, 10.0f) * mMatrix);
				bullet->Rotation(mRotation);
				bullet->Update();
			}
		}
	}
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă��鎞�͖����ɂ���
			//mEnabled = false;
		}
		break;
	}
}

void CEnemy3::Collision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

