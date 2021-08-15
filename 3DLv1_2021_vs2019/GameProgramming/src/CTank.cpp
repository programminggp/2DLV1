#include "CTank.h"
#include "CKey.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"

#include "CBullet.h"

#define OBJTANK1 "res\\tank1.obj"	//���f���̃t�@�C��
#define MTLTANK1 "res\\tank1.mtl"	//���f���̃}�e���A���t�@�C��
#define OBJTANK2 "res\\tank2.obj"	//���f���̃t�@�C��
#define MTLTANK2 "res\\tank2.mtl"	//���f���̃}�e���A���t�@�C��
#define OBJTANK3 "res\\tank3.obj"	//���f���̃t�@�C��
#define MTLTANK3 "res\\tank3.mtl"	//���f���̃}�e���A���t�@�C��

#define ROTATEY CVector(0.0f, 1.0f, 0.0f)
#define ROTATEX CVector(1.0f, 0.0f, 0.0f)
#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //��]���x

#define HP 3	//�ϋv�l
//#define VELOCITY 0.11f	//���x

CModel CTank::mModel;	//���f���f�[�^�쐬
CModel CTank2::mModel;	//���f���f�[�^�쐬
CModel CTank3::mModel;	//���f���f�[�^�쐬


#define FIRECOUNT 15	//���ˊԊu


CTank::CTank()
	: mCollider(this, &mMatrix, CVector(0.0f, 1.0f, 0.0f), 0.2f)
	, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 100.0f), 30.0f)
	, mpPlayer(0)
	, mHp(HP)
	, mFireCount(0)
//	, mTank2(this)
{
	mTag = EENEMY;
	mColSearch.Tag(CCollider::ESEARCH);	//�^�O�ݒ�
	//���f�����ǂ܂�ĂȂ����͓ǂ�
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK1, MTLTANK1);
		//���f���̃|�C���^�ݒ�
		mpModel = &mModel;
	}
	mpTank2 = new CTank2(this);
}

CTank::CTank(const CVector& position, const CVector& rotation, const CVector& scale)
	: CTank()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
	//�D��x��1�ɕύX����
	//mPriority = 1;
	//CTaskManager::Get()->Remove(this); //�폜����
	//CTaskManager::Get()->Add(this); //�ǉ�����
	//�ڕW�n�_�̐ݒ�
	//mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}


void CTank::Update()
{
	//A�L�[���͂ŉ�]
	if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation = mRotation + ROTATEY;
	}
	if (CKey::Push('D')) {
		//Y���̉�]�l������
		mRotation = mRotation - ROTATEY;
	}
	//S�L�[���͂ŏ����
	if (CKey::Push('S')) {
		//X���̉�]�l�����Z
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//W�L�[���͂ŏ����
	if (CKey::Push('W')) {
		//X���̉�]�l�����Z
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	CTransform::Update();
//	mTank2.Update();
}

//void CTank::Render()
//{
//	CCharacter::Render();
////	mTank2.Render();
//}

void CTank::Collision(CCollider* m, CCollider* o)
{
}

void CTank::TaskCollision()
{
}

CCharacter* CTank::Tank()
{
	return mpTank2;
}

#define OFFSETTANK2 0.0f, -1.2f, 0.34f

CTank2::CTank2(CCharacter* parent)
	: mpParent(parent)
{
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK2, MTLTANK2);
		mpModel = &mModel;
	}
	mScale.Set(1.0f, 1.0f, 1.0f);
	new CTank3(this);
	mOffset.Translate(OFFSETTANK2);
	mPosition = CVector(OFFSETTANK2) * -1.0f;
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
	mMatrix = mOffset * mMatrix * mpParent->Matrix();
}

//void CTank2::Render()
//{
//	mModel.Render(mMatrix);
//}

#define OFFSETTANK3 0.0f, -1.7f, -0.43f


CTank3::CTank3(CCharacter* parent)
	: mpParent(parent)
{
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK3, MTLTANK3);
		mpModel = &mModel;
	}
	mScale.Set(1.0f, 1.0f, 1.0f);
	mOffset.Translate(OFFSETTANK3);
	mPosition = CVector(OFFSETTANK3) * -1.0f;
}

void CTank3::Update()
{
	int mFireCount = 0;
	if (CKey::Push('K'))
	{
		mRotation = mRotation + ROTATEX;
	}
	if (CKey::Push('I'))
	{
		mRotation = mRotation - ROTATEX;
	}
	CTransform::Update();
	mMatrix = mOffset * mMatrix * mpParent->Matrix();
	if (CKey::Push(VK_SPACE) && mFireCount == 0) {
		mFireCount = FIRECOUNT;
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		CVector f = CVector(0.0f, 0.0f, 1.0f) * mMatrix - CVector(0.0f, 0.0f, 0.0f) * mMatrix;
		CVector u = CVector(0.0f, 1.0f, 0.0f) * mMatrix - CVector(0.0f, 0.0f, 0.0f) * mMatrix;
		f.Set(f.GetRotationX(u), f.GetRotationY(), 0.0f);
		bullet->Rotation(f);
		bullet->Update();
		//		TaskManager.Add(bullet);
	}
}

//void CTank3::Render()
//{
//	mModel.Render(mMatrix);
//}
