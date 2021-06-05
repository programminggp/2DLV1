#include "CXCharacter.h"

//�L�����N�^����̃J�����̑��Έʒu
#define CAMERA_POSITION 0.0f, 4.0f, -6.0f
#define TARGET_POSITION 0.0f, 3.0f, 6.0f

/*
Init
����������
*/
void CXCharacter::Init(CModelX *model) {
	mpModel = model;
	//�����s��ޔ��G���A�̊m��
	mpCombinedMatrix = new CMatrix44[model->mFrame.size()];
	//�ŏ��̃A�j���[�V�����ɂ���
	mAnimationIndex = 0;
	//�J��Ԃ��Đ�����
	mAnimationLoopFlg = true;
	//1�A�j���[�V����60�t���[��
	mAnimationFrameSize = 60.0f;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationFrame;
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
	mState = EIDLE;
	mScale = CVector3(1.0f, 1.0f, 1.0f);
}

/*
ChangeAnimation
�A�j���[�V������؂�ւ���
index:�A�j���[�V�����̔ԍ�
loop:true �J��Ԃ�
framesize�F�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//�����ꍇ�͐؂�ւ��Ȃ�
	if (mAnimationIndex == index) return;
	//���̃A�j���[�V�����̏d�݂�0.0�i0%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 0.0f;
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index % mpModel->mAnimationSet.size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationFrame;
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
}

/*
Update
�X�V����
matrix�F�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(CMatrix44 &matrix, bool addframe = true) {
	//24 �A�j���[�V�����Z�b�g�̃��Z�b�g
	for (int i = 0; i < mpModel->mAnimationSet.size(); i++) {
		mpModel->mAnimationSet[i]->mWeight = 0.0f;
	}
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;

	//�Ō�܂ōĐ����Ă��Ȃ�
	if (mAnimationFrame < mAnimationFrameSize) {
		//�A�j���[�V�����̎��Ԃ��v�Z
		if (addframe)
			//�t���[����i�߂�
			mAnimationFrame++;
	}
	else {
		//�J��Ԃ��̏ꍇ�́A�t���[����0�ɖ߂�
		if (mAnimationLoopFlg) {
			//�A�j���[�V�����̃t���[�����ŏ��ɂ���
			mAnimationFrame = 0.0f;
		}
	}
	//�A�j���[�V�����̎��Ԃ��v�Z
	mpModel->mAnimationSet[mAnimationIndex]->mTime =
		mpModel->mAnimationSet[mAnimationIndex]->mMaxTime * mAnimationFrame / mAnimationFrameSize;
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->mFrame[0]->Animate(&matrix);
	//�����s��̑ޔ�
	for (int i = 0; i < mpModel->mFrame.size(); i++) {
		mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
}

/*
�`�悷��
*/
void CXCharacter::Render() {
	//�ʒu����
	mPosition = mPosition + mAdjust;
	//�`�悷��
	mpModel->RenderShader(mpCombinedMatrix);
}
//�X�V����
void CXCharacter::Update() {
	CMatrix44 pos, rot, rotx, rotz, scale;;
	//�ʒu�̍s����擾
	pos.translate(mPosition);
	//��]�iY���j�̍s����擾
	rot.rotationY(mRotation.y);
	rotx.rotationX(mRotation.x);
	rotz.rotationZ(mRotation.z);
	scale.scale(mScale);
	//�ʒu��]�s��v�Z
	mMatrix = pos * rot * rotx * rotz * scale;
	//�A�j���[�V�������X�V����
	Update(mMatrix);
}
//�d�͏���
void CXCharacter::Gravity() {
	//���x���ړ�
	mPosition.y += mVelocityG;
	//���x������
	mVelocityG -= 0.01f;
}
//�J�����ʒu�̎擾
CVector3 CXCharacter::GetCameraPosition() {
	CMatrix44 pos, rot, rotx, Matrix;
	//�ʒu�̍s����擾
	pos.translate(mPosition);
	//��]�iY���j�̍s����擾
	rot.rotationY(mRotation.y);
	rotx.rotationX(mRotation.x);
	//�ʒu��]�s��v�Z
	Matrix = pos * rot * rotx;
	CMatrix44 crot;
	//��]�iY���j�̍s����擾
	crot.rotationY(mCameraRotation.y);
	return CVector3(CAMERA_POSITION) * crot * Matrix;
}
//�J�����ʒu�̎擾
CVector3 CXCharacter::GetTargetPosition() {
	CMatrix44 pos, rot, rotx, Matrix;
	//�ʒu�̍s����擾
	pos.translate(mPosition);
	//��]�iY���j�̍s����擾
	rot.rotationY(mRotation.y);
	rotx.rotationX(mRotation.x);
	//�ʒu��]�s��v�Z
	Matrix = pos * rot * rotx;
	CMatrix44 crot;
	//��]�iY���j�̍s����擾
	crot.rotationY(mCameraRotation.y);
	return CVector3(TARGET_POSITION) * crot * Matrix;
}

void CXCharacter::UpdateAdjust(const CVector3 v) {
	if (mAdjust.x < abs(v.x))
		mAdjust.x = v.x;
	if (mAdjust.y < abs(v.y))
		mAdjust.y = v.y;
	if (mAdjust.z < abs(v.z))
		mAdjust.z = v.z;
}
