#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
//
#include "CTaskManager.h"
//
#include "CCollisionManager.h"
////
#include "CRock.h"
//
#include "CObj.h"
//
#include "CItem.h"
//
#include "CKey.h"
//
#include "CBullet.h"
//
#include "CRoad.h"

extern CSound BGM;

CSceneGame::~CSceneGame() {
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}


void CSceneGame::Init() {
	//�V�[���̐ݒ�
	mScene = ESTAGE1;
	
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//�w�i�̓ǂݍ���
	mSky.Load("material\\racing_mat\\stage5\\cource05road2.obj", "material\\racing_mat\\stage5\\cource05road2.mtl");

	CRoadManager* r = new CRoadManager();
	r->Init(&mSky);

}


void CSceneGame::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
//	e = CVector(-2.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY + 90) * mPlayer->mMatrix;
	e = CVector(-2.0f, 1000.0f, -40.0f) ;
	//�����_�����߂�
//	c = mPlayer->mPosition;
	c = CVector();
	//����������߂�
//	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer->mMatrixRotate;
	u = CVector(0.0f, 1.0f, 0.0f) ;

	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//�w�i�̕`��
//	mSky.Render();

	////�^�X�N�}�l�[�W���̍X�V
	//TaskManager.Update();
	////�^�X�N�}�l�[�W���̕`��
	//TaskManager.Render();

	//�^�X�N�}�l�[�W���̍X�V�E�`��
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Render();


	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	CText::DrawString("STAGE 1", 20, 20, 10, 12);

	//2D�`��I��
	End2D();

	return;
}


//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene(){
	return mScene;
}

