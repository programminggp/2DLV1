#include "CXPlayer.h"
#include "CActionCamera.h"

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColBody.Matrix(&mpCombinedMatrix[1]);

	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	//��
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	//��
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);
}

void CXPlayer::Update()
{
	switch (mAnimationIndex)
	{
	case 3:
		if (IsAnimationFinished())
		{
			ChangeAnimation(4, false, 30);
		}
		break;
	case 4:
		if (IsAnimationFinished())
		{
			ChangeAnimation(0, true, 60);
		}
		break;
	default:
		/*if (mInput.Key('A'))
		{
			mRotation.Y(mRotation.Y() + 2.0f);
		}
		if (mInput.Key('D'))
		{
			mRotation.Y(mRotation.Y() - 2.0f);
		}
		if (mInput.Key('W'))
		{
			ChangeAnimation(1, true, 60);
			Position(Position() + mMatrixRotate.VectorZ() * 0.1);
		}*/

		//�J�����̑O��
		CVector cameraZ = CActionCamera::Instance()->VectorZ();
		//�J�����̍�����
		CVector cameraX = CActionCamera::Instance()->VectorX();
		//�L�����N�^�̑O��
		CVector charZ = mMatrixRotate.VectorZ();
		//XZ���ʂɂ��Đ��K��
		cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
		cameraX.Y(0.0f); cameraX = cameraX.Normalize();
		charZ.Y(0.0f); charZ = charZ.Normalize();
		//�ړ������̐ݒ�
		CVector move;
		if (mInput.Key('A')) {
			move = move + cameraX;
		}
		if (mInput.Key('D')) {
			move = move - cameraX;
		}
		if (mInput.Key('W')) {
			move = move + cameraZ;
		}
		if (mInput.Key('S')) {
			move = move - cameraZ;
		}

		//�ړ�����
		if (move.Length() > 0.0f)
		{
			//�V��
			const float MARGIN = 0.06f;
			//���K��
			move = move.Normalize();
			//�����̌����ƌ��������������ŊO��
			float cross = charZ.Cross(move).Y();
			//�����̌����ƌ��������������œ���
			float dot = charZ.Dot(move);
			//�O�ς��v���X�͍���]
			if (cross > MARGIN) {
				mRotation.Y(mRotation.Y() + 5.0f);
			}
			//�O�ς��}�C�i�X�͉E��]
			else if (cross < -MARGIN) {
				mRotation.Y(mRotation.Y() - 5.0f);
			}
			//�O��̌����������Ƃ����ς�1.0
			else if (dot < 1.0f - MARGIN) {
				mRotation.Y(mRotation.Y() - 5.0f);
			}
			//�ړ������ֈړ�
			mPosition = mPosition + move * 0.1f;
			ChangeAnimation(1, true, 60);
		}
		else
		{
			ChangeAnimation(0, true, 60);
		}
		if (mInput.Key(VK_SPACE))
		{
			ChangeAnimation(3, false, 30);
		}
	}
	CXCharacter::Update();
	mColBody.Update();
}
