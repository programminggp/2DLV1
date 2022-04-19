#include "CTank.h"
#include "CKey.h"

#define OBJTANK1 "res\\tank1.obj"	//���f���̃t�@�C��
#define MTLTANK1 "res\\tank1.mtl"	//���f���̃}�e���A���t�@�C��
#define ROTATEY CVector(0.0f, 1.0f, 0.0f) //��]���x
#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //�ړ����x

CModel CTank::mModel;	//���f���f�[�^�쐬

CTank::CTank()
{
	//���f�����ǂ܂�ĂȂ����͓ǂ�
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK1, MTLTANK1);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
}

CTank::CTank(const CVector& position, const CVector& rotation,
	const CVector& scale)
	: CTank()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
	new CTank2(this);

}

void CTank::Update()
{
	//A�L�[���͂ō���]
	if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation = mRotation + ROTATEY;
	}
	//D�L�[���͂ŉE��]
	if (CKey::Push('D')) {
		//Y���̉�]�l������
		mRotation = mRotation - ROTATEY;
	}
	//W�L�[���͂őO�i
	if (CKey::Push('W')) {
		//X���̉�]�l�����Z
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//S�L�[���͂Ō��
	if (CKey::Push('S')) {
		//X���̉�]�l�����Z
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	CTransform::Update();
}

#define OBJTANK2 "res\\tank2.obj"	//���f���̃t�@�C��
#define MTLTANK2 "res\\tank2.mtl"	//���f���̃}�e���A���t�@�C��
CModel CTank2::mModel;	//���f���f�[�^�쐬

CTank2::CTank2(CCharacter* parent)
	: mpParent(parent)
{
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK2, MTLTANK2);
	}
	mpModel = &mModel;
	mScale.Set(1.0f, 1.0f, 1.0f);	
}

void CTank2::Update()
{
	if (CKey::Push('J'))
	{
		mRotation = mRotation + ROTATEY;
	}
	if (CKey::Push('L'))
	{
		mRotation = mRotation - ROTATEY;
	}
	CTransform::Update();
	//���g�̍s��~�e�̍s��
	mMatrix = mMatrix * mpParent->Matrix();
}
