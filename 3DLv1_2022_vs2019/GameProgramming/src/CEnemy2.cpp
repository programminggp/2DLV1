#include "CEnemy2.h"
#include "CEffect.h"
#include "CPlayer.h"

#define OBJ "res\\f16.obj"	//���f���̃t�@�C��
#define MTL "res\\f16.mtl"	//���f���̃}�e���A���t�@�C��
#define HP 3	//�ϋv�l
#define VELOCITY 0.11f	//���x

CModel CEnemy2::mModel;	//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy2::CEnemy2()
	: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
	, mHp(HP)
{
	//���f���������Ƃ��͓ǂݍ���
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
}


//CEnemy(�ʒu, ��], �g�k)
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation,
	const CVector& scale)
	: CEnemy2()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
	//�ڕW�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

//�X�V����
void CEnemy2::Update() {
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Get();
	if (player != nullptr)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - mPosition;
		float dx = vp.Dot(vx);	//���x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(vy);	//��x�N�g���Ƃ̓��ς����߂�
		//X���̃Y����2.0�ȉ�
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y���̃Y����2.0�ȉ�
			if (-2.0f < dy && dy < 2.0f)
			{
				float dz = vp.Dot(vz);
				if (dz > 0.0f
					&& vp.Length() <= 30.0f)
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
	//HP��0�ȉ��̎��@���j
	if (mHp <= 0)
	{
		mHp--;
		//15�t���[�����ɃG�t�F�N�g
		if (mHp % 15 == 0)
		{
			//�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//���~������
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	//�ۑ�
	float dx = vp.Dot(vx);	//���x�N�g���Ƃ̓��ς����߂�

	float dy = vp.Dot(vy);	//��x�N�g���Ƃ̓��ς����߂�
	float margin = 0.1f;
	//���E�����։�]
	if (dx > margin)
	{
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f); //���։�]
	}
	else if (dx < -margin)
	{
		//�ۑ�
		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f); //�E�։�]
	}
	//�㉺�����։�]
	if (dy > margin)
	{
		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f); //��։�]
	}
	else if (dy < -margin)
	{
		//�ۑ�
		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f); //���։�]
	}

	//�ړ�����
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	CTransform::Update();	//�s��X�V

	//���悻3�b���ɖڕW�n�_���X�V
	int r = rand() % 180;	//rand()�͐����̗�����Ԃ�
							//% 180 ��180�Ŋ������]������߂�
	if (r == 0)
	{
		if (player != nullptr)
		{
			mPoint = player->Position();
		}
		else
		{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy2::Collision(CCollider* m, CCollider* o)
{
	//�R���C�_��m��o���Փ˂��Ă��邩�̔���
	if (CCollider::Collision(m, o)) {
		//�G�t�F�N�g����
		new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		mHp--;	//�q�b�g�|�C���g�̌��Z
		//�Փ˂��Ă��鎞�͖����ɂ���
		//�폜mEnabled = false;
	}
}
