#include "CSceneTest.h"
#include "CInput.h"
#include "CKey.h"

//���f���̃t�@�C����
//#define MODELX_FILE "res\\felguard\\felguard-X.X"
#define MODELX_FILE "res\\paladin\\Paladin.X"
#define ANIMATION_ATTACKSP1 "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Attack.x"

void CSceneTest::Init() {
	//���f���f�[�^�ǂݍ���
	mModelX.Load(MODELX_FILE);
	//���f���f�[�^�ݒ�
	mXCharacter.Init(&mModelX);
	//�X�P�[���𓙔{�ɐݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	mTransform.Scale(mScale);
	//�}�E�X����n�ϐ��̏�����
	mPushFlg = false;
	mOldMousePosX = 0;

	//�A�j���[�V�����̒ǉ�
	mModelX.AddAnimationSet(ANIMATION_ATTACKSP1);
	//�A�j���[�V������؂�ւ�
	mXCharacter.ChangeAnimation(1, true, 120);
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

	//�J�����ݒ�
	gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);

	//��]�Ȃ�
	mTransform.Update();
	glMultMatrixf(mTransform.Matrix().M());

	//�L�����N�^�X�V�E�`��
	mXCharacter.Update();
	mXCharacter.Render();
}

