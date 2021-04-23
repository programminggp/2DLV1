#include "CSceneGameStage2.h"
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

extern CSound BGM;

CSceneGameStage2::~CSceneGameStage2() {
	CTaskManager::Get()->Disabled();

	CTaskManager::Get()->Delete();
}


void CSceneGameStage2::Init() {
	//�V�[���̐ݒ�
	mScene = ESTAGE2;

	//�I�̎c���̏�����
	CItem::mTargetAmount = 0;

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//�w�i�̓ǂݍ���
	mSky.Load("sky.obj", "sky.mtl");
	//��̓ǂݍ���
	mRock.Load("Rock1.obj", "Rock1.mtl");
	//�Ԃ̓ǂݍ���
	mRover.Load("untitled.obj", "cube.mtl");
	//�����̂̓ǂݍ���
	mCube.Load("cube.obj", "material\\cube.mtl");
	//�n�ʂ̓ǂݍ���
	mPlane.Load("plane.obj", "plane.mtl");

	mItem.Load("Rock1.obj", "Rock1.mtl");
	//�e�̓ǂݍ���
	mItemGun.Load("�e.obj", "Rover1.mtl");
	mSpring.Load("�΂ːL��.obj", "cube.mtl");

	mCube2.Load("cube.obj", "cube2.mtl");
	mCube3.Load("cube.obj", "cube3.mtl");

	mGrass.Load("cube.obj", "material\\grass.mtl");
	mSoil.Load("cube.obj", "material\\soil.mtl");

	mWater.Load("cube.obj", "material\\clearwater.mtl");

	mBridge.Load("cube.obj", "material\\bridge.mtl");

	mInvWall.Load("cube.obj", "cube2.mtl");

	mRoof.Load("cube.obj", "material\\roof.mtl");
	mHouseWall.Load("cube.obj", "material\\housewall.mtl");
	mDoor.Load("cube.obj", "material\\door.mtl");
	mKey.Load("cube.obj", "material\\key.mtl");
	mWindow.Load("cube.obj", "material\\window.mtl");

	

	//�{�[�g�̓ǂݍ���
	mBoat.Load("�ӂ�.obj", "cube.mtl");

	//�X�e�[�W2BGM�̓ǂݍ���
	BGM.Load("BGM\\game_maoudamashii_4_field02.wav");

	////�����ȓz���ɕ`�悷��H
	//new CObj(&mInvWall, CVector(0.0f, 6.1f, 57.0f-14.4f), CVector(0.0f, 0.0f, 0.0f), CVector(14.5f, 1.1f, 31.8f-13.6f), 1);//���̓����蔻��A�����x100%

	//new CObj(&mInvWall, CVector(0.0f, 6.1f, 57.0f - 242.4f), CVector(0.0f, 0.0f, 0.0f), CVector(14.5f, 1.1f, 31.8f - 13.6f), 1);//������A�����x100%�A���Ȃ��O�̕�
	//new CObj(&mInvWall, CVector(2.0f, 4.0f, -213.0f), CVector(0.0f, 0.0f, 0.0f), CVector(15.0f, 2.5f, 6.5f), 1);//�{�[�g�̓����蔻��
	//
	////new CObj(&mCube3, CVector(-73.0f, 5.0f, 100.0f), CVector(0.0f, 0.0f, 0.0f), CVector(30.0f, 45.0f, 1.0f), 9);

	//new CObj(&mWindow, CVector(27.0f, 16.0f, 320.1f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 8.0f, 1.0f), 0);//���A�����x30%

	//new CObj(&mWater, CVector(0.0f, -4.0f, -57.0f), CVector(0.0f, 0.0f, 0.0f), CVector(199.9f, 1.0f, 320.0f), 20);//��

	mPlayer = new CPlayer();
	mPlayer->mpModel = &mRover;

	//��̐����@���f��mRock�@�ʒu|-20.0 0.0 20.0|
	//��]|0.0 0.0 0.0|�@�g��|5.0 5.0 5.0|
//	new CRock(&mRock, CVector(-20.0f, 0.0f, 20.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//��̐����@���f��mRock�@�ʒu|-20.0 0.0 20.0|
	//��]|0.0 0.0 0.0|�@�g��|5.0 5.0 5.0|
//	new CRock(&mRock, CVector(20.0f, 0.0f, 40.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//�����̂̐���
	//	new CObj(&mCube, CVector(0.0f, 0.0f, 60.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 10.0f, 1.0f), 1);
	////�n�ʂ̐���
	//new CObj(&mPlane, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(200.0f, 1.0f, 200.0f), 1);
	/*for (int i = 0; i < 30; i++){
		new CObj(&mWater, CVector(0.0f, 40.0f, 0.0f + i), CVector(i * 3, i * 3, i * 3), CVector(5.0f, 5.0f, 1.0f), 1);
	}*/

//	//���̐���
////	new CObj(&mWater, CVector(0.0f, -35.0f, 0.0f), CVector(), CVector(199.8f, 16.0f, 25.0f), 20);
//	//�����E�y�̐���
////	new CObj(&mGrass, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(200.0f, 1.0f, 200.0f), 1);
//	//new CObj(&mGrass, CVector(0.0f, 3.0f, 284.0f), CVector(), CVector(200.0f, 1.5f, 200.0f), 1);
//	new CObj(&mGrass, CVector(0.0f, 3.0f, -70.0f), CVector(), CVector(200.0f, 1.5f, 100.0f), 1);
//	//new CObj(&mSoil, CVector(0.0f, -35.0f, 284.0f), CVector(), CVector(200.0f, 19.0f, 200.0f), 1);
//	new CObj(&mSoil, CVector(0.0f, -35.0f, -70.0f), CVector(), CVector(200.0f, 19.0f, 100.0f), 1);
//
//	new CObj(&mGrass, CVector(0.0f, 3.0f, 334.0f), CVector(), CVector(200.0f, 1.5f, 100.0f), 1);
//	new CObj(&mSoil, CVector(0.0f, -35.0f, 334.0f), CVector(), CVector(200.0f, 19.0f, 100.0f), 1);
//
//
//
//	//for (int i = 0; i < 3; i++){
//	//	for (int j = 0; j < 3; j++){
//	//		for (int k = 0; k < 3; k++){
//	//			if ((i == 1 && j == 1) || (j == 1 && k == 1) || (k == 1 && i == 1) || (k == 2 && j != 1)) {
//	//			}
//	//			else{
//	//				new CObj(&mCube, CVector(-20.0f + 20.0f * i, 0.0f + 20.0f * k - 2.0f, 80.0f + 20.0f * j), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 10.0f, 10.0f), 1);
//	//			}
//	//		}
//	//	}
//	//}
//
//	//new CObj(&mCube, CVector(0.0f, 60.0f, 100.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 10.0f, 10.0f), 1);
//	//new CItem(&mItemGun, CVector(0.0f, 80.0f, 100.0f), CVector(), CVector(2.0f, 2.0f, 2.0f), 4);//�e
//	//for (int i = 0; i < 5; i++){
//	//	new CItem(&mItem, CVector(-10.0f + i * 7.5f, 93.0f, 150.0f), CVector(), CVector(2.1f, 2.1f, 2.1), 1);//����
//	//}
//
//
//
////	new CItem(&mItem, CVector(43.0f, 111.0f, 118.0f), CVector(), CVector(2.0f, 2.0f, 2.0f), 3);//�X�N�����[
//
//	for (int l = 0; l < 5; l++){
//		new CObj(&mBridge, CVector(0.0f, 6.1f, 28.0f + l * 7.2f), CVector(0.0f, 0.0f, 0.0f), CVector(14.0f, 1.0f, 3.3f), 20);//��
//	}
//	//new CObj(&mCube, CVector(0.0f, -26.0f, 5.0f), CVector(-25.0f, 0.0f, 0.0f), CVector(15.0f, 16.0f, 36.0f), 1);
//
//	new CItem(&mSpring, CVector(0.0f, 10.0f, 40.0f), CVector(), CVector(5.0f, 5.0f, 5.0f), 2);//�o�l
//
////	new CItem(&mBoat, CVector(30.0f, 7.0f, 30.0f), CVector(), CVector(3.0f, 3.0f, 3.0f), 1);//�{�[�g
//	
//
//	//new CObj(&mCube, CVector(30.0f, 0.0f, 30.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 2.0f, 10.0f), 2);
//
//	//�Ƃ̍쐬
//	new CObj(&mRoof, CVector(-6.4f, 54.4f, 346.1f), CVector(0.0f, 0.0f, 30.0f), CVector(23.5f, 2.0f, 33.3f), 0);////����
//	new CObj(&mRoof, CVector(30.4f, 54.4f, 346.1f), CVector(0.0f, 0.0f, -30.0f), CVector(23.5f, 2.0f, 33.3f), 0);////����
//
//	new CObj(&mHouseWall, CVector(12.0f, 5.1f, 346.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 0.5f, 25.0f), 20);//�Ƃ̏�
//
//	//new CObj(&mHouseWall, CVector(27.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(20.0f, 20.0f, 2.0f), 0);//��O���̕�
//	
//	new CObj(&mHouseWall, CVector(42.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(5.0f, 13.0f, 2.0f), 0);//��O�E���t�ߍ�
//	new CObj(&mHouseWall, CVector(12.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(5.0f, 13.0f, 2.0f), 0);//��O�E���t�߉E
//	new CObj(&mHouseWall, CVector(27.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 5.0f, 2.0f), 0);//��O�E���t�߉�
//
//	new CObj(&mHouseWall, CVector(-15.5f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(7.5f, 13.0f, 2.0f), 0);//��O���̕�
//	new CObj(&mHouseWall, CVector(12.0f, 32.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 8.1f, 2.0f), 0);//��O�E���̏キ�炢�̕�
//
//	//new CObj(&mHouseWall, CVector(12.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 20.0f, 2.0f), 0);//��O���̕�
//	new CObj(&mHouseWall, CVector(20.0f, 43.5f, 321.1f), CVector(0.0f, 0.0f, -30.0f), CVector(21.0f, 8.0f, 2.0f), 0);////��O��
//	new CObj(&mHouseWall, CVector(4.0f, 43.5f, 321.1f), CVector(0.0f, 0.0f, 30.0f), CVector(21.0f, 8.0f, 2.0f), 0);////��O��
//
//	new CObj(&mHouseWall, CVector(12.0f, 6.0f, 371.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 20.0f, 2.0f), 0);//��둤�̕�
//	new CObj(&mHouseWall, CVector(19.0f, 41.5f, 371.1f), CVector(0.0f, 0.0f, -30.0f), CVector(20.0f, 10.0f, 2.0f), 0);////��둤
//	new CObj(&mHouseWall, CVector(5.0f, 41.5f, 371.1f), CVector(0.0f, 0.0f, 30.0f), CVector(20.0f, 10.0f, 2.0f), 0);////��둤
//	new CObj(&mHouseWall, CVector(-21.0f, 6.0f, 346.1f), CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 20.0f, 25.0f), 0);//�E��
//	new CObj(&mHouseWall, CVector(45.0f, 6.0f, 346.1f), CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 20.0f, 25.0f), 0);//����
//	new CObj(&mDoor, CVector(-0.5f, 6.0f, 320.0f), CVector(0.0f, 0.0f, 0.0f), CVector(7.5f, 13.0f, 1.0f), 22);//��
//	new CItem(&mKey, CVector(38.0f, 60.0f, 321.0f), CVector(), CVector(2.5f, 2.5f, 2.5f), 5);//��
//
//	new CObj(&mBridge, CVector(-11.0f, 6.0f, 394.0f), CVector(0.0f, 0.0f, 0.0f), CVector(11.0f, 11.0f, 11.0f), 0);//�ؔ�(�H)
//
//
//	new CObj(&mCube, CVector(100.0f, 0.0f, 80.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 21);//��𗬂�镨��
//	new CObj(&mCube, CVector(-100.0f, 0.0f, 80.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 21);//��𗬂�镨��
//
//	//new CObj(&mCube, CVector(-100.0f, 15.0f, 62.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//���ԁH�H�H
//	//new CObj(&mCube, CVector(0.0f, 15.0f, 62.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//���ԁH�H�H
//	//new CObj(&mCube, CVector(100.0f, 15.0f, 62.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//���ԁH�H�H
//
//	new CObj(&mCube, CVector(100.0f, 15.0f, 117.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 0);//���ԁH�H�H
//	for (int i = 0; i < 7; i++){
//		new CObj(&mCube, CVector(70.0f-30.0*i, 30.0f+ 15.0f *i, 117.0f), CVector(0.0f + 90.0f*i , 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//���ԁH�H�H
//	}
//	new CObj(&mCube, CVector(100.0f - 245.0f, 15.0f + 105.0f, 157.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 50.0f), 0);//���邮��̐�̑���
//
//	for (int l = 0; l < 5; l++){
//		new CObj(&mBridge, CVector(0.0f, 6.1f, -200.0f + l * 7.2f), CVector(0.0f, 0.0f, 0.0f), CVector(14.0f, 1.0f, 3.3f), 20);//��
//	}
//	new CItem(&mBoat, CVector(0.0f, 6.0f, -213.0f), CVector(0.0f, 0.0f, 0.0f), CVector(2.5f, 2.5f, 2.5f), 0);//�{�[�g�c���̃X�e�[�W�ł͎g���Ȃ�


	mCamY = 0.0f;
	mPutCol = false;

	//TaskManager.ChangePriority(&mPlayer, 15);
	CTaskManager::Get()->ChangePriority(mPlayer, 15);

	//CPlayer::mpPlayer->mPosition.mX = 0.0f; CPlayer::mpPlayer->mPosition.mY = 21.3f; CPlayer::mpPlayer->mPosition.mZ = -189.2f;
	
	////�X�e�[�W2���y�����[�v�Đ�����
	BGM.Repeat();
}


void CSceneGameStage2::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(-2.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY + 90) * mPlayer->mMatrix;
	//�����_�����߂�
	c = mPlayer->mPosition;
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer->mMatrixRotate;

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


	////��̕`��
	//mRock.Render(CMatrix().Scale(5.0f, 5.0f, 5.0f));
	////�Ԃ̕`��
	//mRover.Render(CMatrix().Translate(-20.0f, 0.0f, 10.0f));

	//���J
	//�R���W�����}�l�[�W���̏Փˏ���
	CollisionManager.Collision();
	//TaskManager.Delete();
	CTaskManager::Get()->Delete();


	//�f�o�b�O�p
#ifdef _DEBUG
	if (CKey::Once('9')){
		if (mPutCol){
			mPutCol = false;
		}
		else{
			mPutCol = true;
		}
	}
	if (mPutCol){
		//�Փ˔���̕`��
		CollisionManager.Render();
	}
#endif


	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	

	if ((CPlayer::mpPlayer->mPosition.mX > -21.0f && CPlayer::mpPlayer->mPosition.mX < 45.0f)
		&& (CPlayer::mpPlayer->mPosition.mY > 5.9f +13.0f && CPlayer::mpPlayer->mPosition.mY < 46.1f +13.0f)
		&& (CPlayer::mpPlayer->mPosition.mZ > 321.1f && CPlayer::mpPlayer->mPosition.mZ < 371.1f)){
		CText::DrawString("STAGE CLEAR !", 300, 300, 10, 12);
	}
	
	CText::DrawString("STAGE 2", 20, 20, 10, 12);

	//2D�`��I��
	End2D();


	//if (CKey::Push('Q')){//�ł�
	//	mCamY += 1.0f;
	//}
	//if (CKey::Push('E')){//��
	//	mCamY += -1.0f;
	//}




	if (CKey::Once(VK_RETURN)){
		mScene = ESTAGE1;
	}

	if (CKey::Once('1')){//�I�̎c�����o�͂���
		printf("%d\n", CItem::mTargetAmount);
	}
	if (CKey::Once('2')){//Player�̍��W���o�͂���
		printf("X:%f Y:%f Z:%f\n", CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY, CPlayer::mpPlayer->mPosition.mZ);
	}
	if (CKey::Once('3')){//�����J����or�߂�(����Stage2��p�̃f�o�b�O�p�R�}���h)
		if (CPlayer::mpPlayer->mIsGetKey){
			CPlayer::mpPlayer->mIsGetKey = false;
		}
		else{
			CPlayer::mpPlayer->mIsGetKey = true;
		}
	}
	if (CKey::Once('5')){//��s���[�h��ON�EOFF�؂�ւ�(�f�o�b�O�p)
		if (CPlayer::mpPlayer->mFlyingMode){
			CPlayer::mpPlayer->mFlyingMode = false;
		}
		else{
			CPlayer::mpPlayer->mFlyingMode = true;
		}
	}

	return;
}


//���̃V�[���̎擾
CScene::EScene CSceneGameStage2::GetNextScene(){
	return mScene;
}