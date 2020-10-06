#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
//
#include "CRes.h"

#include <Windows.h>
#include "CMaterial.h"
//
#include "CCollisionManager.h"
//
#include "glut.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {
	// Free Monster 
	mFMonster.Set(CVector(-5.0f, 0.0f, 0.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	mFMonster2.Set(CVector(-5.0f, 0.0f, -5.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	// Felguard
	mFelguard.Set(CVector(-3.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	mFelguard.mAnimationFrameSize = 700;

	//3D���f���t�@�C���̓ǂݍ���
	CRes::sKnight.Load("knight\\knight_low.x");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:�ړ�
	CRes::sKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:�ҋ@
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	CRes::sKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:�_�E��

	//3D���f���t�@�C���̓ǂݍ���
	CRes::sModelX.Load(MODEL_FILE);
	//�L�����N�^�[�Ƀ��f����ݒ�
	mPlayer.Init(&CRes::sModelX);
	//�G�̏����ݒ�
//	mEnemy.Init(&CRes::sModelX);
	mEnemy.Init(&CRes::sKnight);
	//�G�̔z�u
	mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
	mEnemy.mScale = CVector(1.0f, 1.0f, 1.0f);
	mEnemy.mAnimationFrameSize = 1024;
	//
	mEnemy.ChangeAnimation(2, true, 200);

	mDummy[0].Init(&CRes::sKnight);
	mDummy[0].mPosition = CVector(7.0f, 0.0f, 4.0f);
	mDummy[0].mScale = CVector(1.0f, 1.0f, 1.0f);
	mDummy[0].mAnimationFrameSize = 1024;
	mDummy[1].Init(&CRes::sKnight);
	mDummy[1].mPosition = CVector(5.0f, 0.0f, 2.0f);
	mDummy[1].mScale = CVector(1.0f, 1.0f, 1.0f);
	mDummy[1].mAnimationFrameSize = 1024;
	mDummy[2].Init(&CRes::sKnight);
	mDummy[2].mPosition = CVector(3.0f, 0.0f, 0.0f);
	mDummy[2].mScale = CVector(1.0f, 1.0f, 1.0f);
	mDummy[2].mAnimationFrameSize = 1024;
	mDummy[0].ChangeAnimation(1, true, 200);
	mDummy[1].ChangeAnimation(2, true, 200);
	mDummy[2].ChangeAnimation(3, true, 200);

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
}


void CSceneGame::Update() {

	//�L�����N�^�[�N���X�̍X�V
	mPlayer.Update();
	//�G�̍X�V
	mEnemy.Update();

	mDummy[0].Update();
	mDummy[1].Update();
	mDummy[2].Update();

	mFMonster.Update();
	mFMonster2.Update();

	mFelguard.Update();

	//�Փˏ���
	CollisionManager.Collision();

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

	mPlayer.Render();
	//�G�`��
	mEnemy.Render();
	//
	mFMonster.Render();
	mFMonster2.Render();

	mFelguard.Render();

	mDummy[0].Render();
	mDummy[1].Render();
	mDummy[2].Render();


	//�R���C�_�̕`��
	CollisionManager.Render();


	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�`��I��
	End2D();

	return;
}

