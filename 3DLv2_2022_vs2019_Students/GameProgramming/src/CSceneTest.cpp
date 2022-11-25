#include "CSceneTest.h"
#include "CInput.h"
#include "CKey.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CXEnemy.h"


//���f���̃t�@�C����
//#define MODELX_FILE "res\\felguard\\felguard-X.X"
//#define MODELX_FILE "res\\paladin\\Paladin.X"
#define MODELX_FILE "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"
//�A�j���[�V�����f�[�^�ǉ�
#define ANIMATION_ATTACKSP1 "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Attack.x"
#define ANIMATION_ATTACK "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Slash.fbx.x"
#define ANIMATION_JUMP "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Jump.fbx.x"
#define ANIMATION_RUN "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Run.fbx.x"
#define ANIMATION_WALK "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Walk.fbx.x"
//�n�`���f���f�[�^
#define MODEL_GROUND "res\\forest-terrain\\TerrainNew1000.obj","res\\forest-terrain\\TerrainNew1000.mtl"

CMatrix mMatrixGround;

CText CSceneTest::sText;

CText* CSceneTest::Text()
{
	return &sText;
}

void CSceneTest::Init() {
	sText.LoadTexture("FontG.png", 1, 4096 / 64);
	//���f���f�[�^�ǂݍ���
	mModelX.Load(MODELX_FILE);
	//���f���f�[�^�ݒ�
	//mXCharacter.Init(&mModelX);
	//�X�P�[���𓙔{�ɐݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	mTransform.Scale(mScale);
	//�}�E�X����n�ϐ��̏�����
	mPushFlg = false;
	mOldMousePosX = 0;

	//�A�j���[�V�����̒ǉ�ANIMATION_RUN
	mModelX.AddAnimationSet(ANIMATION_WALK);
	mModelX.AddAnimationSet(ANIMATION_RUN);
	mModelX.AddAnimationSet(ANIMATION_ATTACK);
	mModelX.AddAnimationSet(ANIMATION_ATTACKSP1);
	mModelX.AddAnimationSet(ANIMATION_JUMP);


	//�n�`�f�[�^�ǂݍ���
	mGround.Load(MODEL_GROUND);
	mMatrixGround = CMatrix().Scale(150, 150, 150) * CMatrix().Translate(0, 0, -10);
	mColliderMesh.Set(nullptr, &mMatrixGround, &mGround);

	mpPlayer = new CPaladin(CVector(0.0f, 0.0f, 2.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	mpPlayer->Init(&mModelX);
	//�A�j���[�V������؂�ւ�
	mpPlayer->ChangeAnimation(1, true, 120);

	CXEnemy* penemy = new CXEnemy(CVector(0.0f, -2.0f, 8.0f), CVector(), CVector(0.4f, 0.4f, 0.4f));

	mActionCamera.Position(mpPlayer->Position()+CVector(0.0f, 2.0f, 0.0f));
}

void CSceneTest::Update() 
{
	//Mouse Right Drag Turn
	float x, y;
	//�}�E�X�J�[�\�����W�̎擾
	CInput::GetMousePosWin(&x, &y);
	if (mPushFlg)
	{
		//�}�E�X�E�{�^���N���b�N
		if (CKey::Push(VK_RBUTTON))
		{
			if (mOldMousePosX < x)
			{
				//Turn Right
				CVector v = mTransform.Rotation();
				v.Y(v.Y() + x - mOldMousePosX);
				mTransform.Rotation(v);
				mOldMousePosX = x;
			}
			else if(x < mOldMousePosX)
			{
				//Turn Left
				CVector v = mTransform.Rotation();
				v.Y(v.Y() - mOldMousePosX + x);
				mTransform.Rotation(v);
				mOldMousePosX = x;
			}
		}
		else
		{
			mPushFlg = false;
		}
	}
	else
	{
		//�}�E�X�E�{�^���N���b�N
		if (CKey::Push(VK_RBUTTON))
		{
			mPushFlg = true;
			mOldMousePosX = x;
		}
	}

	//Wheel Change Scale
	//�}�E�X�z�C�[����Ԃ̎擾
	//-1:���։�]�@0:��]�Ȃ��@1:��ɉ�]
	int w = CInput::Wheel();
	if (w != 0)
	{
		if (w > 0)
		{
			//Big
			mScale.X(mScale.X() + 0.1f);
			mScale.Y(mScale.Y() + 0.1f);
			mScale.Z(mScale.Z() + 0.1f);
		}
		else
		{
			//Small
			mScale.X(mScale.X() - 0.1f);
			mScale.Y(mScale.Y() - 0.1f);
			mScale.Z(mScale.Z() - 0.1f);
		}
		mTransform.Scale(mScale);
	}
//	mTransform.Position(mpPlayer->Position()*-1);

	//�J�����ݒ�
//	gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);


	//��]�Ȃ�
	mTransform.Update();
//	glMultMatrixf((CMatrix().Translate(mpPlayer->Position().X() * -1.0f, mpPlayer->Position().Y() * -1.0f, mpPlayer->Position().Z() * -1.0f) * mTransform.Matrix()).M());
	glMultMatrixf(mTransform.Matrix().M());

//	mGround.Render(CMatrix().Scale(150, 150, 150) * CMatrix().Translate(-150, 0, -250));

	//�L�����N�^�X�V�E�`��
	//mXCharacter.Update();
	//mXCharacter.Render

	CTaskManager::Get()->Update();
	mActionCamera.Position(mpPlayer->Position() + CVector(0.0f, 2.0f, 0.0f));
	mActionCamera.Update();

	CTaskManager::Get()->TaskCollision();

	mActionCamera.Render();
	CVector screen, world(1.0f, 1.0f, 1.0f);
	mActionCamera.WorldToScreen(&screen, world);

	//�n�`�f�[�^�`��
	mGround.Render(mMatrixGround);
	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();
}

