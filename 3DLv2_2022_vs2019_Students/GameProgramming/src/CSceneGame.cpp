#include "CSceneGame.h"
#include "CModelX.h"
#include "CCollisionManager.h"

//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CUtil.h"

#include "CKey.h"

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

}

void CSceneGame::Update() {
	////�ŏ��̃A�j���[�V�����̌��ݎ��Ԃ�45�ɂ���
	//gModelX.AnimationSet()[0]->Time(0);
	////�ŏ��̃A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	//gModelX.AnimationSet()[0]->Weight(1.0f);
	////�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	//gModelX.AnimateFrame();
	////�t���[���̍����s����v�Z����
	//gModelX.Frames()[0]->AnimateCombined(&gMatrix);

	//�L�����N�^�[�N���X�̍X�V
	mPlayer.Update();
	mEnemy.Update();

//	gModelX.AnimationSet()[0]->Time(
//		gModelX.AnimationSet()[0]->Time() + 1.0f);
//	gModelX.AnimationSet()[0]->Time(
//		(int)gModelX.AnimationSet()[0]->Time() %
//		(int)(gModelX.AnimationSet()[0]->MaxTime() + 1));
//

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
	//�Փˏ���
	CCollisionManager::Get()->Collision();

	//X���{��]
	if (CKey::Push('K')) {
		gMatrix = gMatrix * CMatrix().RotateX(1);
	}
	//Y���{��]
	if (CKey::Push('L')) {
		gMatrix = gMatrix * CMatrix().RotateY(1);
	}
	//X��-��]
	if (CKey::Push('I')) {
		gMatrix = gMatrix * CMatrix().RotateX(-1);
	}
	//Y��-��]
	if (CKey::Push('J')) {
		gMatrix = gMatrix * CMatrix().RotateY(-1);
	}
	//�s��ݒ�
	glMultMatrixf(gMatrix.M());

	//���_�ɃA�j���[�V������K�p����
//	gModelX.AnimateVertex();
	//���f���`��
	//gModelX.Render();
	mPlayer.Render();
	mEnemy.Render();
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
}

