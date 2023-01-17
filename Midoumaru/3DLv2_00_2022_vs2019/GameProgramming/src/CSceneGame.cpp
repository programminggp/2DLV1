#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include"CMatrix.h"
#include "CUtil.h"
#include"CModelX.h"
#include"CKey.h"
#include"CXCharacter.h"
#include"CCollisionManager.h"
#include"CColliderMesh.h"
#include"CColliderTriangle.h"
#include"CTaskManager.h"
#include"CInput.h"
#include"CActionCamera.h"
#include"CBillBoard.h"

//#define MODEL_P_TURNR "res\\PaladinTurnRight.x"
//#define MODEL_P_TURNL "res\\PaladinTurnLeft.x"
//#define MODEL_P_ROLL1 "res\\PaladinRoll1.x"
//#define MODEL_P_ROLL2 "res\\PaladinRoll2.x"
//#define MODEL_P_SHIELD2 "res\\PaladinShield2.x"

CModelX Player;
CModelX Mutant;
CMatrix gMatrix;
CModelX gKnight;
CVector mEye;
CMatrix matrix;
CMatrix UndergroundMatrix;
CColliderMesh mColliderMesh;

CSceneGame::CSceneGame()
	: mActionCamera(6.0f, -15.0f, 180.0f)
	, mPlayer(0)
	, mMutant(0)
{
}

void CSceneGame::Init() {

	UndergroundMatrix.Translate(0.0f, 0.0f, -50.0f);
	UndergroundMatrix.Scale(7.0f, 7.0f, 7.0f);

	//3D���f���t�@�C����ǂݍ���
	Player.Load("res\\PaladinStand1.x");
	//�A�j���[�V�����̒ǉ�
	Player.AddAnimationSet("res\\PaladinStand1.x");//1
	Player.AddAnimationSet("res\\PaladinStand2.x");//2
	Player.AddAnimationSet("res\\PaladinRun.x");//3
	Player.AddAnimationSet("res\\PaladinSlash1.x");//4
	Player.AddAnimationSet("res\\PaladinSlash2.x");//5
	Player.AddAnimationSet("res\\PaladinSlash3.x");//6
	Player.AddAnimationSet("res\\PaladinDeath.x");//7
	Player.AddAnimationSet("res\\PaladinBack.x");//8
	Player.AddAnimationSet("res\\PaladinShield1.x");//9
	Player.AddAnimationSet("res\\PaladinMagic1.x");//10
	Player.AddAnimationSet("res\\PaladinMagic2.x");//11
	Player.AddAnimationSet("res\\PaladinMagicStand.x");//12

	//Player.AddAnimationSet(MODEL_P_SHIELD2);
	//Player.AddAnimationSet(MODEL_P_ROLL1); //33
	//Player.AddAnimationSet(MODEL_P_ROLL2);
	//Player.AddAnimationSet(MODEL_P_TURNR); //23
	//Player.AddAnimationSet(MODEL_P_TURNL); //26

	Mutant.Load("res\\MutantStand.x");
	Mutant.AddAnimationSet("res\\MutantStand.x");//1
	Mutant.AddAnimationSet("res\\MutantRun.x");//2
	Mutant.AddAnimationSet("res\\MutantAttack.x");//3
	Mutant.AddAnimationSet("res\\MutantDeath.x");//4

	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	mPlayer = new CXPlayer();
	mPlayer->Init(&Player);
	mPlayer->Position(CVector(-38.0f, 1.5f, -45.0f));
	mPlayer->Scale(CVector(2.0f, 2.0f, 2.0f));

	mMutant = new CXMutant();
	mMutant->Init(&Mutant);
	mMutant->Position(CVector(-38.0f, 1.5f, -30.0f));
	mMutant->Rotation(CVector(1.0f, 200.0f, 0.0f));
	mMutant->Scale(CVector(2.1f, 2.1f, 2.1f));


    Underground.Load("res\\Underground.obj", "res\\Underground.mtl");
	//�r���{�[�h�̐���
//	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	new CBillBoard(CVector(-36.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	mColliderMesh.Set(nullptr, &UndergroundMatrix, &Underground);
	
	matrix.Print();
	//�G�̏����ݒ�
	//�G�̔z�u
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	gKnight.Load("res\\knight\\knight_low.X");
	mEnemy.Init(&gKnight);
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
	mEnemy.ChangeAnimation(2, true, 200);

}

void CSceneGame::Update() {
	/*�g��k���E��]�Ȃ�
	mTransform.Update();
	glMultMatrixf(mTransform.Matrix().M());*/
	/*�����A�j���[�V�����ɐ؂�ւ���
	mCharacter.ChangeAnimation(1, false, 60);
	if (mCharacter.IsAnimationFinished() == true)
	{
		mCharacter.ChangeAnimation(mCharacter.AnimationIndex()+1,true, 60);
	}*/

	CTaskManager::Get()->Update();
	//�L�����N�^�[�N���X�̍X�V
	//mPlayer->Update();
	//�G�̍X�V
	//mEnemy.Update();
	//�~���[�^���g�̍X�V
	//mMutant->Update();

	/*�ŏ��̃A�j���[�V�����̌��ݎ��Ԃ�45�ɂ���
	gModelX.AnimationSet()[0]->Time(gModelX.AnimationSet()[0]->Time() + 1.0f);
	gModelX.AnimationSet()[0]->Time((int)gModelX.AnimationSet()[0]->Time() % (int)(gModelX.AnimationSet()[0]->MaxTime() + 1));
	�ŏ��̃A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	gModelX.AnimationSet()[0]->Weight(1.0f);
	�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	gModelX.AnimateFrame();
	�t���[���̍����s����v�Z����
	gModelX.Frames()[0]->AnimateCombined(&gMatrix);*/

	CActionCamera::Instance()->Position(mPlayer->Position() + (CVector(0.0f, 3.0f, 0.0f)));
	CActionCamera::Instance()->Update();
	CActionCamera::Instance()->Render();


	////X��+��]
	//if (CKey::Push('K')) {
	//	gMatrix = gMatrix * CMatrix().RotateX(1);
	//}
	////Y��+��]
	//if (CKey::Push('L')) {
	//	gMatrix = gMatrix * CMatrix().RotateY(1);
	//}
	////X��-��]
	//if (CKey::Push('I')) {
	//	gMatrix = gMatrix * CMatrix().RotateX(-1);
	//}
	////Y��-��]
	//if (CKey::Push('J')) {
	//	gMatrix = gMatrix * CMatrix().RotateY(-1);
	//}
	//�s��ݒ�
//	glMultMatrixf(gMatrix.M());

	//���_�ɃA�j���[�V������K�p����
	//gModelX.AnimateVertex();
	//���f���`��
	//gModelX.Render();
	//gModelX Render
	// 
	//�^�X�N���X�g�̍폜

	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();

	//�w�i�`��
	Underground.Render(UndergroundMatrix);
	//�v���C���[�`��
	//mPlayer->Render();
	//�G�`��
	//mEnemy.Render();
	//�^�X�N�}�l�[�W���̕`��	
	CTaskManager::Get()->Render();
	 
	
	//�R���C�_�`��
	CCollisionManager::Get()->Render();

	//�Փˏ���
	CTaskManager::Get()->TaskCollision();

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
}

