#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
//4
#include "CTaskManager.h"
//06
#include "CCollisionManager.h"
//07
#include "CRock.h"
//10
#include "CObj.h"
//
#include "CImage.h"
//
#include "CSound.h"

#include "CKey.h"
//
#include "CSlope.h"
//
#include "CSphere.h"

CSound Sound;
CSound Bgm;

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//1
	mSky.Load("sky.obj", "sky.mtl");
	mRock.Load("Rock1.obj", "Rock1.mtl");
	mRover.Load("Rover1.obj", "Rover1.mtl");
	//10
	mCube.Load("cube.obj", "cube.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");
//	mPlane.Load("plane.obj", "plane.mtl");
	mPlane.Load("plane.obj", "plane.mtl");
	//4
	mPlayer.mpModel = &mRover;
	mPlayer.mPosition = CVector(0.0f, 0.0f, -10.0f);
	//07
	//��̐����@���f��mRock�@�ʒu|-20.0 0.0 20.0|
	//��]|0.0 0.0 0.0|�@�g��|5.0 5.0 5.0|
//	new CRock(&mRock, CVector(-20.0f, 0.0f, 20.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//��̐����@���f��mRock�@�ʒu|20.0 0.0 40.0|
	//��]|0.0 0.0 0.0|�@�g��|5.0 5.0 5.0|
//	new CRock(&mRock, CVector(20.0f, 0.0f, 40.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//10
//	new CObj(&mCube, CVector(0.0f, 0.0f, 60.0f), CVector(), CVector(10.0f, 10.0f, 1.0f));
	//12
	new CObj(&mPlane, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(200.0f, 1.0f, 200.0f));
	//
	new CSlope(&mPlane, CVector(0.0f, 5.0f, 0.0f), CVector(), CVector(10.0f, 1.0f, 10.0f));
	//
	new CSphere(&mSphere, CVector(0.0f, 20.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//13
	std::shared_ptr<CTexture> grass(new CTexture("brick.tga"));
//	new CImage(grass, CVector(30.0f, 10.0f, 30.0f), CVector(-120.0f, 0.0f, 0.0f), CVector(10.0f, 20.0f, 1.0f));

	//Sound.Load("jump.wav");
	//Bgm.Load("mario.wav");
	//Bgm.Repeat();
}


void CSceneGame::Update() {
	//if (CKey::Push('B')) {
	//	Bgm.Repeat();
	//}
	//if (CKey::Push('S')) {
	//	Bgm.Stop();
	//}


	//4
	TaskManager.Update();
	//06
	CollisionManager.Collision();
	//07
	TaskManager.Delete();


	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	//09
	e = CVector(-2.0f, 10.0f, -30.0f) * mPlayer.mMatrix;
	//�����_�����߂�
	c = CVector() * mPlayer.mMatrix;
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.mMatrixRotate;

	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);


	//1
	mSky.Render();
//	mRock.Render(CMatrix().Scale(5.0f, 5.0f, 5.0f));
//	mRover.Render(CMatrix().Translate(-20.0f, 0.0f, 10.0f));

	//4
	TaskManager.Render();
	//06
//	CollisionManager.Render();

	////10
	//mCube.Render(CMatrix().Translate(15, 0, 0));
	//mCube.Render(CMatrix().Scale(100, 0.1, 100));
	//mSphere.Render(CMatrix().Translate(15, 10, 0));

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�`��I��
	End2D();

	return;
}

