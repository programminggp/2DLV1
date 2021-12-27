#include "CXCharacter.h"
CXCharacter::CXCharacter()
	: mpCombinedMatrix(nullptr)
	, mAnimationFrame(0.0f)
	, mAnimationFrameSize(0.0f)
	, mAnimationIndex(0)
	, mAnimationLoopFlg(false)
	, mpModel(nullptr)
{
	mScale = CVector(1.0f, 1.0f, 1.0f);
}
/*
 Init
 ����������
*/
void CXCharacter::Init(CModelX* model) {
	mpModel = model;
	//�ŏ��̃A�j���[�V�����ɂ���
	mAnimationIndex = 0;
	//�J��Ԃ��Đ�����
	mAnimationLoopFlg = true;
	//1�A�j���[�V�����ڂ̍ő�t���[����
	mAnimationFrameSize =
		model->AnimationSets()[0]->MaxTime();
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSets()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->AnimationSets()[mAnimationIndex]->Weight(1.0f);
	// �����s��ޔ��G���A�̊m��
	mpCombinedMatrix = new CMatrix[model->Frames().size()];
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
	mpModel->AnimationSets()[mAnimationIndex]->Weight(0.0f);
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index % mpModel->AnimationSets().size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSets()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->AnimationSets()[mAnimationIndex]->Weight(1.0f);
}
/*
 Update
 �X�V����
 matrix�F�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(CMatrix& matrix) {
	for (size_t i = 0; i < mpModel->AnimationSets().size(); i++)
	{
		mpModel->AnimationSets()[i]->Weight(0.0f);
	}
	mpModel->AnimationSets()[mAnimationIndex]->Weight(1.0f);
	//�Ō�܂ōĐ����Ă��Ȃ�
	if (mAnimationFrame < mAnimationFrameSize) {
		//�A�j���[�V�����̎��Ԃ��v�Z
		mpModel->AnimationSets()[mAnimationIndex]->Time(
			mpModel->AnimationSets()[mAnimationIndex]->MaxTime() *
			mAnimationFrame / mAnimationFrameSize);
		//�t���[����i�߂�
		mAnimationFrame++;
	}
	else {
		//�J��Ԃ��̏ꍇ�́A�t���[����0�ɖ߂�
		if (mAnimationLoopFlg) {
			//�A�j���[�V�����̃t���[�����ŏ��ɂ���
			mAnimationFrame = 0.0f;
			mpModel->AnimationSets()[mAnimationIndex]->Time(mAnimationFrame);
		}
		else {
			mpModel->AnimationSets()[mAnimationIndex]->Time(
				mpModel->AnimationSets()[mAnimationIndex]->MaxTime());
		}
	}
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->Frames()[0]->AnimateCombined(&matrix);
	// �����s��̑ޔ�
	for (size_t i = 0; i < mpModel->Frames().size(); i++) {
		mpCombinedMatrix[i] =
			mpModel->Frames()[i]->CombinedMatrix();
	}
	//���_�ɃA�j���[�V������K�p����
	//mpModel->AnimateVertex();
}
/*
 �`�悷��
*/
void CXCharacter::Render() {
	mpModel->RenderShader(mpCombinedMatrix);
	//mpModel->Render();
}
//�X�V����
void CXCharacter::Update() {
	//�ϊ��s��̍X�V
	CTransform::Update();
	//�A�j���[�V�������X�V����
	Update(mMatrix);
}
