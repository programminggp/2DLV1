#include "CSceneTest.h"
#include "CInput.h"
#include "CKey.h"

//���f���̃t�@�C����
#define MODELX_FILE "res\\felguard\\felguard-X.X"

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
}
void CSceneTest::Update()
{
	//�}�E�X�̉E�N���b�N�h���b�O�Ń��f����]
	float x, y;
	//�}�E�X�J�[�\�����W�̎擾
	CInput::GetMousePosWin(&x, &y);
	if (mPushFlg)
	{
		//�}�E�X�E�{�^���N���b�N�@���N���b�N��VK_LBUTTON
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
			else if (x < mOldMousePosX)
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
	//�}�E�X�̃z�C�[���Ŋg��k��
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

	//�g��k���E��]�Ȃ�
	mTransform.Update();
	glMultMatrixf(mTransform.Matrix().M());

	//�L�����N�^�X�V�E�`��
	mXCharacter.Update();
	mXCharacter.Render();


}
