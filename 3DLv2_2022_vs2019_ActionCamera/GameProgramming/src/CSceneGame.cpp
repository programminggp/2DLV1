#include "CSceneGame.h"
#include "CModelX.h"
#include "CCollisionManager.h"

//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CActionCamera.h"
#include "CUtil.h"

#include "CKey.h"
#include "CXTest.h"

//�m�F�p�C���X�^���X
CModelX gModelX;
CMatrix gMatrix;

CModelX gKnight;

void CSceneGame::Init() {
	gKnight.Load("res\\knight\\knight_low.X");
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:�ړ�
	gKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:�ҋ@
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:�_�~�[
	gKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	gKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:�_�~�[
	gKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:�_�E��

	//3D���f���t�@�C���̓ǂݍ���
	gModelX.Load(MODEL_FILE);
	//�L�����N�^�[�Ƀ��f����ݒ�
	mPlayer.Init(&gModelX);

	mFont.LoadTexture("FontG.png", 1, 4096 / 64);
	//�G�̏����ݒ�
//	mEnemy.Init(&gModelX);
	mEnemy.Init(&gKnight);
	//�G�̔z�u
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	mEnemy.ChangeAnimation(2, true, 200);

	new CXTest();
//	new CActionCamera(5.0f, -15.0f, 180.0f);
}

void CSceneGame::Update() {

	//�X�V
	CTaskManager::Get()->Update();
	CActionCamera::Instance()->Update();

	//�Փˏ���
	CCollisionManager::Get()->Collision();

	CActionCamera::Instance()->Render();
	CTaskManager::Get()->Render();

	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
}

