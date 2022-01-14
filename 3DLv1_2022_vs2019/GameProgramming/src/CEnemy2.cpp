#include "CEnemy2.h"
#include "CEffect.h"

#define OBJ "res\\f16.obj"	//���f���̃t�@�C��
#define MTL "res\\f16.mtl"	//���f���̃}�e���A���t�@�C��

CModel CEnemy2::mModel;	//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy2::CEnemy2()
	: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
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
}

//�X�V����
void CEnemy2::Update() {
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy2::Collision(CCollider* m, CCollider* o)
{
	//�R���C�_��m��o���Փ˂��Ă��邩�̔���
	if (CCollider::Collision(m, o)) {
		//�G�t�F�N�g����
		new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		//�Փ˂��Ă��鎞�͖����ɂ���
		//�폜mEnabled = false;
	}
}
