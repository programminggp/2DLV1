#include "CEnemy3.h"
#include "CEffect.h"
#include "CApplication.h"

#define OBJ "res\\f16.obj" //���f���̃t�@�C��
#define MTL "res\\f16.mtl" //���f���̃}�e���A���t�@�C��
#define HP 3 //�ϋv�l
#define VELOCITY 0.11f //���x

CModel CEnemy3::sModel; //���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy3::CEnemy3()
	:CCharacter3(1)
	,mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.4f)
	,mHp(HP)
{
	//���f���������Ƃ��͓ǂݍ���
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &sModel;
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

//�R���X�g���N�^
//CEnemy3(�ʒu�A��]�A�g�k)
CEnemy3::CEnemy3(const CVector& position, const CVector& rotation,
	const CVector& scale)
	:CEnemy3() //�f�t�H���g�R���X�g���N�^�����s����
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
	CTransform::Update();
}

//�X�V����
void CEnemy3::Update()
{
	//�v���C���[�̃|�C���^���O�ȊO�̎�
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - mPosition;
		//���x�N�g���Ƃ̓��ς����߂�
		float dx = vp.Dot(mMatrixRotate.VectorX());
		//��x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(mMatrixRotate.VectorY());
		float dz = vp.Dot(mMatrixRotate.VectorZ());

		if (0.0f < dz && dz <= 30.0f)
		{
			//X���̂��ꂪ2.0�ȉ�
			if (-2.0f < dx && dx < 2.0f)
			{
				//Y���̂��ꂪ�Q�D�O�ȉ�
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

	//HP���O�̎��@���j
	if (mHp <= 0)
	{
		mHp--;
		//�P�T�t���[�����ɃG�t�F�N�g
		if (mHp % 15 == 0)
		{
			//�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//�~��������
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}

	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	//�ۑ�
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(mMatrixRotate.VectorX());
    //��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(mMatrixRotate.VectorY());
	const float margin = 0.1f;
	//���E�����։�]
	if (dx > margin)
	{
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f); //���։�]
	}
	else if (dx < -margin)
	{
		//�ۑ�
		mRotation = mRotation - CVector(0.0f, 1.0f, 0.0f); //�E�։�]
	}
	//�㉺�����։�]
	if (dy > margin)
	{
		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f); //��։�]
	}
	else if (dy < -margin)
	{
		//�ۑ�
		mRotation = mRotation - CVector(-1.0f, 0.0f, 0.0f); //���։�]
	}

	//�@�̑O���ֈړ�����
	mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
	CTransform::Update(); // �s��X�V

	//���悻�R�b���ɖڕW�n�_���X�V
	int r = rand() % 180; //rand()�͐����̗�����Ԃ�
	                      //% 180��180�Ŋ������]������߂�
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
//Collision(�R���C�_1�A�R���C�_2)
void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̍쐬
	switch (o->Type())
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă��鎞�͖����ɂ���
			//mEnabled = false;
			mHp--; //�q�b�g�|�C���g�̌��Z
		}
		break;
	case ETag::EBULLETENEMY:
	{
		break;
	}
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փˏ���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{   //�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
			//���j�Œn�ʂɏՓ˂���Ɩ���
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		//�G�t�F�N�g����
		new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		//�Փ˂��Ă��鎞�͖����ɂ���
		//mEnabled = false;
	}
}

void CEnemy3::Collision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mCollider, 30);
}