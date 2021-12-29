#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CKey.h"
#include "CMatrix.h"
#include "CTaskManager.h"
#include "CUtil.h"
//
#include "CCollisionManager.h"
//
#include "CCamera.h"
//
#include "CXPlayer.h"
//
#include "CFelguard.h"

////���f���f�[�^�̎w��
//#define MODEL_X "res\\knight\\knight_low.X"
//
//CMatrix Matrix;
//
//CModelX ModelSample;

void CSceneGame::Init() {
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);
	//Camera.Set(CVector(1.0f, 6.0f, 7.0f), CVector(0.0f, 4.0f, 0.0f), CVector(0.0f, 1.0f, 0.0f));
	//ModelSample.Load(MODEL_X);
	////�ŏ��̃A�j���[�V�����̌��ݎ��Ԃ�45�ɂ���
	//ModelSample.AnimationSets()[0]->Time(45);
	////�ŏ��̃A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	//ModelSample.AnimationSets()[0]->Weight(1.0f);
	new CXPlayer(CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CFelguard();
	new CCamera(CVector(0.0f, 4.0f, 0.0f), CVector(20.0f, 180.0f, 0.0f), 7.0f);
}

void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	CTaskManager::Get()->TaskCollision();
	//Camera.Render();

	////X���{��]
	//if (CKey::Push('K')) {
	//	Matrix = Matrix * CMatrix().RotateX(1);
	//}
	////Y���{��]
	//if (CKey::Push('L')) {
	//	Matrix = Matrix * CMatrix().RotateY(1);
	//}

	//ModelSample.AnimationSets()[0]->Time(
	//	ModelSample.AnimationSets()[0]->Time() + 1.0f);
	//ModelSample.AnimationSets()[0]->Time(
	//	(int)ModelSample.AnimationSets()[0]->Time() %
	//	(int)(ModelSample.AnimationSets()[0]->MaxTime() + 1));
	////�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	//ModelSample.AnimateFrame();
	////�t���[���̍����s����v�Z����
	//ModelSample.Frames()[0]->AnimateCombined(&Matrix);

	////���_�ɃA�j���[�V������K�p����
	//ModelSample.AnimateVertex();
	//ModelSample.Render();

	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	CTaskManager::Get()->Render();

#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
#endif

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
}

