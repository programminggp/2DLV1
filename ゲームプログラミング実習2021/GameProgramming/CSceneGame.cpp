#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "Ckey.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);

	CRes::sModelX.Load(MODEL_FILE);

}


void CSceneGame::Update() {
	//�ŏ��̃A�j���[�V�����̌��ݎ��Ԃ�45�ɂ���
	//CRes::sModelX.mAnimationSet[0]->mTime = 0;
	CRes::sModelX.mAnimationSet[0]->mTime += 1.0f;
	CRes::sModelX.mAnimationSet[0]->mTime =
		(int)CRes::sModelX.mAnimationSet[0]->mTime %
		(int)(CRes::sModelX.mAnimationSet[0]->mMaxTime + 1);

	//�ŏ��̃A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	CRes::sModelX.mAnimationSet[0]->mWeight = 1.0f;
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	CRes::sModelX.AnimateFrame();
	//�t���[���̍����s����v�Z����
	CRes::sModelX.mFrame[0]->AnimateCombined(&Matrix);

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//X���{��]
	if (CKey::Push('K')) {
		Matrix = Matrix * CMatrix().RotateX(1);
	}
	if (CKey::Push('I')) {
		Matrix = Matrix * CMatrix().RotateX(-1);
	}
	//Y���{��]
	if (CKey::Push('L')) {
		Matrix = Matrix * CMatrix().RotateY(1);
	}
	if (CKey::Push('J')) {
		Matrix = Matrix * CMatrix().RotateY(-1);
	}

	//�s��ݒ�
	glMultMatrixf(Matrix.mF);
	//���_�ɃA�j���[�V������K�p����
	CRes::sModelX.AnimateVertex();
	//���f���`��
	CRes::sModelX.Render();

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

	return;
}

