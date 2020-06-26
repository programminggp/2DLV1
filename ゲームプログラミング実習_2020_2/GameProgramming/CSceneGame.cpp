#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
//
#include "CRes.h"

#include "glut.h"
#include <Windows.h>
#include "CMaterial.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	CRes::sModelX.Load(MODEL_FILE);
	//�L�����N�^�[�Ƀ��f����ݒ�
	mPlayer.Init(&CRes::sModelX);

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
}


void CSceneGame::Update() {
	////�����A�j���[�V�����ɐ؂�ւ���
	//if (mPlayer.mAnimationFrame >= mPlayer.mAnimationFrameSize) {
	//	mPlayer.ChangeAnimation(mPlayer.mAnimationIndex + 1, true, 60);
	//}

	//�L�����N�^�[�N���X�̍X�V
	mPlayer.Update();

//	//�ŏ��̃A�j���[�V�����̌��ݎ��Ԃ�45�ɂ���
//	CRes::sModelX.mAnimationSet[0]->mTime += 1.0f;
//	CRes::sModelX.mAnimationSet[0]->mTime =
//		(int)CRes::sModelX.mAnimationSet[0]->mTime %
//		(int)(CRes::sModelX.mAnimationSet[0]->mMaxTime + 1);
////	CRes::sModelX.mAnimationSet[0]->mTime = 0;
//
//	//�ŏ��̃A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
//	CRes::sModelX.mAnimationSet[0]->mWeight = 1.0f;
//	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
//	CRes::sModelX.AnimateFrame();
//	//�t���[���̍����s����v�Z����
//	CRes::sModelX.mFrame[0]->AnimateCombined(&CMatrix());
//
//
//	//���_�ɃA�j���[�V������K�p����
//	CRes::sModelX.AnimateVertex();


	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//X���{��]
	if (GetKeyState('K') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateX(1);
	}
	//Y���{��]
	if (GetKeyState('L') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateY(1);
	}
	//X��-��]
	if (GetKeyState('I') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateX(-1);
	}
	//Y��-��]
	if (GetKeyState('J') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateY(-1);
	}

	//�s��ݒ�
	glMultMatrixf(Matrix.mF);
	//���f���`��
//	CRes::sModelX.Render();
	mPlayer.Render();

	//�e�N�X�`���e�X�g
//	CRes::sModelX.mMaterial[0]->mpTexture->DrawImage(-5, 5, -5, 5, 0, 128, 128, 0);

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�`��I��
	End2D();

	return;
}

