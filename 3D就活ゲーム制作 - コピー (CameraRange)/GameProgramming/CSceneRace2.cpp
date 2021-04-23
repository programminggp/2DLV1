#include "CSceneRace2.h"
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

//�X�}�[�g�|�C���^�̐���
extern std::shared_ptr<CTexture> TextureExp;
extern std::shared_ptr<CTexture> TextureHit;

extern CSound BGM;
extern CSound SoundCountDown;
extern CSound SoundStart;
extern CSound SoundGoal;

CSceneRace2::~CSceneRace2() {
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}


void CSceneRace2::Init() {
	mMiami.Load("Miami\\miami 2526.obj", "Miami\\miami 2526.mtl");
	//�V�[���̐ݒ�
	mScene = ERACE1;

	//�I�̎c���̏�����
	CItem::mTargetAmount = 0;

	//�����e�N�X�`���̓ǂݍ���
	TextureExp->Load("exp.tga");
	//�Փ˃e�N�X�`���̓ǂݍ���
	TextureHit->Load("effect\\[Attack]Hit01_panop.tga");

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//�w�i�̓ǂݍ���
	mSky.Load("sky.obj", "sky.mtl");
	//�Ԃ̓ǂݍ���
	mRover.Load("Rover1.obj", "Rover1.mtl");
	mCarRed.Load("Rover1.obj", "material\\racing_mat\\red.mtl");
	mCarBlue.Load("Rover1.obj", "material\\racing_mat\\blue.mtl");
	
	//�n�ʂ̓ǂݍ���
	mPlane.Load("plane.obj", "plane.mtl");

	mCarsol.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol.mtl");
	mMiniGoal.Load("material\\racing_mat\\minigoal.obj", "material\\racing_mat\\minigoal.mtl");

	//�X�e�[�W1BGM�̓ǂݍ���
	BGM.Load("BGM\\(���ʒ�����)Pops�M�^�[_No.01.wav");
	SoundCountDown.Load("SE\\Countdown01-5.wav");
	SoundStart.Load("SE\\Countdown01-6.wav");
	SoundGoal.Load("SE\\tm2_whistle000.wav");

	new CObj(&mMiami, CVector(), CVector(), CVector(5.0f, 5.0f, 5.0f), 1);
	new CObj(&mPlane, CVector(), CVector(), CVector(100.0f, 1.0f, 100.0f), 1);

	mPlayer = new CPlayer();
	mPlayer->mpModel = &mRover;

	mEnemy1 = new CEnemy();
	mEnemy1->mpModel = &mCarRed;
	mEnemy1->mPosition = CVector(250.0f, -13.538f, -100.0f);
	mEnemy1->CCharacter::Update();

	mEnemy2 = new CEnemy();
	mEnemy2->mpModel = &mCarBlue;
	mEnemy2->mPosition = CVector(350.0f, -13.538f, -100.0f);
	mEnemy2->CCharacter::Update();

	
	mCamY = 0.0f;
	mPutCol = false;

	mFrame = 0;
	mCountDown = 3+1;

	//���[�X�̓J�E���g�_�E�����I����Ă���J�n
	isStartRace = false;
	//���Ԃ̃��Z�b�g
	mTime = 0;
	//�x�X�g�^�C���̐ݒ�
	mBestTime = 30000;
	//���b�v���̏�����
	mLap = 3;
	//�L�^�X�V���ĂȂ����
	isNewRecord = false;
	
	//�J�������_
	mCamPoV = 1;

	//TaskManager.ChangePriority(&mPlayer, 15);
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	//CTaskManager::Get()->ChangePriority(, 15);
	CTaskManager::Get()->ChangePriority(mEnemy1, 15);
	CTaskManager::Get()->ChangePriority(mEnemy2, 15);

	BGM.Repeat();
}


void CSceneRace2::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
//	e = CVector(-2.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrix   * mPlayer->mMatrixScale * mPlayer->mMatrixRotate * mPlayer->mMatrixTranslate;
//	e = CVector(-2.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale * mPlayer->mMatrixRotate * mPlayer->mMatrixTranslate;
	if (mCamPoV == 1){
		e = CVector(0.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale
			* CMatrix().RotateY(mPlayer->mRotation.mY)
			* mPlayer->mMatrixTranslate
			+ CVector(0.0f, 0.0f, 0.0f);
		////�����_�����߂�
		//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
		c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale
			* CMatrix().RotateY(mPlayer->mRotation.mY);
			//* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	}
	else if (mCamPoV == 2){
		e = CVector(0.0f, 0.0f + 0.5f, -40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale
			* CMatrix().RotateY(mPlayer->mRotation.mY)
			* mPlayer->mMatrixTranslate
			+ CVector(0.0f, 0.0f, 0.0f);
		////�����_�����߂�
		//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
		c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale
			* CMatrix().RotateY(mPlayer->mRotation.mY);
			//* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	}
	else if (mCamPoV == 3){//������f�����_
		e = CVector(0.0f, 17.0f, 40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale
			* CMatrix().RotateY(mPlayer->mRotation.mY)
			* mPlayer->mMatrixTranslate
			+ CVector(0.0f, 0.0f, 0.0f);
		////�����_�����߂�
		//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
		c = mPlayer->mPosition + CVector(0.0f, 0.0f, -40.0f)* mPlayer->mMatrixScale
			* CMatrix().RotateY(mPlayer->mRotation.mY);
			//* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	}

	//CMatrix().RotateZ(mRotation.mZ) *CMatrix().RotateX(mRotation.mX) *CMatrix().RotateY(mRotation.mY);

	//////�����_�����߂�
	////c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
	//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)
	//	* CMatrix().RotateY(mPlayer->mRotation.mY)
	//	* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);// *mPlayer->mMatrixRotate;
	


	//e = CVector(0.0f+mXXX, 5000.0f, mZZZ+0.0f);
	//	/*CVector(0.0f, 3000.0f, 0.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale
	//	* CMatrix().RotateY(mPlayer->mRotation.mY)
	//	* mPlayer->mMatrixTranslate
	//	+ CVector(0.0f, 0.0f, 0.0f);*/
	////�����_�����߂�
	//c = CVector(0.0f+mXXX, 0.0f, mZZZ+0.0001f);
	//	//mPlayer->mPosition + CVector(0.0f, 0.0f, 0.01f)*mPlayer->mMatrixRotate;
	////����������߂�
	//u = CVector(0.0f, 1.0f, 0.0f) * mPlayer->mMatrixRotate;

	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.mEye = e;

	////�w�i�̕`��
	//mSky.Render();
	////�^�X�N�}�l�[�W���̍X�V
	//TaskManager.Update();
	////�^�X�N�}�l�[�W���̕`��
	//TaskManager.Render();

	//mPlayer->mpModel = &mRover;
	mPlayer->mpModel = &mRover;
	mPlayer->mScale = CVector(2.5f, 2.5f, 2.5f);

	//�^�X�N�}�l�[�W���̍X�V�E�`��
	CTaskManager::Get()->Update();
	CTaskManager::Get()->TaskCollision();
	CTaskManager::Get()->Render();

	////��̕`��
	//mRock.Render(CMatrix().Scale(5.0f, 5.0f, 5.0f));
	////�Ԃ̕`��
	//mRover.Render(CMatrix().Translate(-20.0f, 0.0f, 10.0f));

	//���J
	//�R���W�����}�l�[�W���̏Փˏ���
//	CollisionManager.Collision();
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

	if (CKey::Once('0')){
		//mCamPoV = 1;
		if (mCamPoV == 1){
			mCamPoV = 2;
		}
		else if (mCamPoV == 2){
			mCamPoV = 3;
		}
		else if (mCamPoV == 3){
			mCamPoV = 1;
		}
	}


	if (isStartRace){
		//59:59:59���ő厞��
		if (mTime < 595959){
			if (mTime % 10000 == 5959){
				mTime += 1 + 40 + 4000;
			}
			else if (mTime % 100 == 59){
				mTime += 1 + 40;
			}
			else{
				mTime += 1;
			}
		}
	}
	
	RenderMiniMap();
	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	CText::DrawString("COURCE 1", 20, 20, 10, 12);

	//���Ԃ̕\��
	char mti[70];// :���܂߂��ő啶�����̐ݒ�
//	sprintf(mti, "%06d", mTime);
	sprintf(mti, "TIME:%02d:%02d:%02d", mTime / 10000 % 100, mTime / 100 % 100, mTime % 100);
	CText::DrawString(mti, 20, 530, 10, 12);
	//�x�X�g�^�C���̕\��
	char mbestti[70];// :���܂߂��ő啶�����̐ݒ�
	//	sprintf(mti, "%06d", mTime);
	sprintf(mbestti, "BEST:%02d:%02d:%02d", mBestTime / 10000 % 100, mBestTime / 100 % 100, mBestTime % 100);
	CText::DrawString(mbestti, 20, 580, 10, 12);
	
	//�J�E���g�_�E���J�n�AGO!�ő���̎�t�J�n
	if (mFrame < 60){
		mFrame++;
	}
	else{
		if (mCountDown >= 0){
			mCountDown--;
			if (mCountDown == 0){
				isStartRace = true;
				SoundStart.Play();
			}
			else if (mCountDown > 0){
				SoundCountDown.Play();
			}
		}
		mFrame = 0;
	}
	//�J�E���g�_�E���\��
	char mcountd[7];
	//�c��3�b�܂ł̎������\��
	sprintf(mcountd, "%d", mCountDown);
	if (mCountDown > 0 && mCountDown <= 3){
		CText::DrawString(mcountd, 400, 300, 25, 30);
	}
	else if (mCountDown == 0){
		CText::DrawString("GO!", 400-40, 300, 25, 30);
		CPlayer::mpPlayer->CanMove = true;
		mEnemy1->CanMove = true;
		mEnemy2->CanMove = true;
	}
	/*SoundCountDown.Play();
	SoundStart.Play();*/


	if (isStartRace == false){
		if (mCountDown > 0){
			//�J�E���g�_�E����(�S�[���ȑO�ɁA�X�^�[�g���炵�ĂȂ�)
		}
		else{
			CText::DrawString("FINISH!", 400 - 25 * 6, 300, 25, 30);
		}
	}

	char lap[19];
	sprintf(lap, "LAP %d", mLap);
	CText::DrawString(lap, 20, 500, 10, 12);

	//�S�[����A�p�����Ď��s���鏈��
	if (mLap == 3 && isStartRace == false){
		//�V�L�^���������o������
		if (isNewRecord){
			//CText::DrawString("FINISH!", 400 - 20 * 6, 300, 20, 24);
			CText::DrawString("NEW RECORD!", 55, 558, 8, 9);
		}
	}

	//�~�j�}�b�v�E���ݒn�̕\��
//	CText::DrawString("+", -(CPlayer::mpPlayer->mPosition.mX / 50)+600, CPlayer::mpPlayer->mPosition.mZ / 50 + 100, 10, 10);

	char carspeed[33];
	sprintf(carspeed, "SPEED:%4.1f", CPlayer::mpPlayer->mCarSpeed);
	CText::DrawString(carspeed, 20+560, 20, 10, 12);

	//2D�`��I��
	End2D();


	//CText::DrawString("PONG", 110, 80, 100, 100);
	//CText::DrawString("HEPPY", 110, 380, 70, 70);
	//CText::DrawString("MEW", 250, 230, 70, 70);
	//CText::DrawString("YEAH", 180, 80, 70, 70);


	if (CKey::Push('Y')){//�ł�
		mCamY += 1.0f;
	}
	if (CKey::Push('U')){//��
		mCamY += -1.0f;
	}


	if ((CPlayer::mpPlayer->mPosition.mX > 155.0f && CPlayer::mpPlayer->mPosition.mX < 975.0f)
		&& (CPlayer::mpPlayer->mPosition.mZ > -3.1f - 5.0f && CPlayer::mpPlayer->mPosition.mZ < -3.1f + 5.0f)
		&& (CPlayer::mpPlayer->mChecks == 3)
		&& (isStartRace)){
		//new CObj(&mCube, CVector(0.0f, 0.0f, 5700.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(100.0f, 13.0f, 211.0f), 1);//�S�[��
		//new CObj(&mTileBlack, CVector(170.0f + 20.0f * -1 + 5.0f, -13.1f + 10.0f, -10.0f), CVector(0.0f, 0.0f, 0.0f), CVector(5.0f, 64.0f, 5.0f), 99);//��
		//new CObj(&mTileBlack, CVector(170.0f + 20.0f * 40 + 5.0f, -13.1f + 10.0f, -10.0f), CVector(0.0f, 0.0f, 0.0f), CVector(5.0f, 64.0f, 5.0f), 99);//��

		if (mLap == 3){
			//�x�X�g�^�C���X�V��
			if (mTime < mBestTime){
				mBestTime = mTime;
				isNewRecord = true;
			}
			isStartRace = false;
			BGM.Stop();
			SoundGoal.Play();
			//CPlayer::mpPlayer->CanMove = false;//�����X�g�b�v
			CPlayer::mpPlayer->mChecks = 0;
		}
		else{
			mLap++;
			CPlayer::mpPlayer->mChecks = 0;
		}
	}
	

	//	new CObj(&mWarpPoint, CVector(-143.0f, 0.0f, 94.0f), CVector(0.0f, 0.0f, 0.0f), CVector(6.0f, 20.0f, 6.0f), 20);
	//����̒n�_(��(�̂���)�͈͓̔�)�ɍs����Stage2�ֈڍs
	/*if ((CPlayer::mpPlayer->mPosition.mX > -149.0f && CPlayer::mpPlayer->mPosition.mX < -137.0f)
		&& (CPlayer::mpPlayer->mPosition.mZ > 88.0f && CPlayer::mpPlayer->mPosition.mZ < 100.0f)
		&& (CPlayer::mpPlayer->mHaveBoat)){
		mScene = ESTAGE2;
	}*/
	////�f�o�b�O�R�}���h
	//if (CKey::Once(VK_RETURN)){
	//	mScene = ESTAGE2;
	//}

	if (CKey::Once('1')){
		printf("%d\n", CItem::mTargetAmount);
	}
	if (CKey::Once('2')){//Player�̍��W���o�͂���
		printf("X:%f Y:%f Z:%f\n", CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY, CPlayer::mpPlayer->mPosition.mZ);
	}
	if (CKey::Once('3')){//�����I�ɓI�̎c����0�ɂ���(�{���̓I�͏����Ȃ�)
		CItem::mTargetAmount = 0;
	}
	if (CKey::Once('4')){//�]��̌v�Z���A���鐔(�E�̐���)�͐��̒l�Ōv�Z�����H
		printf("%d\n", -13 % 5);//��%��=��
		printf("%d\n", -12 % -5);//��%��=��
		printf("%d\n", 14 % -5);//��%��=��
	}
	if (CKey::Push('5')){
		printf("%f:%f:%f\n", CPlayer::mpPlayer->mRotation.mX, CPlayer::mpPlayer->mRotation.mY, CPlayer::mpPlayer->mRotation.mZ);
	}
	if (CKey::Once('6')){
		printf("%d\n", CPlayer::mpPlayer->mChecks);
	}
	if (CKey::Once('7')){
		if (CPlayer::mpPlayer->mFlyingMode){
			CPlayer::mpPlayer->mFlyingMode = false;
		}
		else{
			CPlayer::mpPlayer->mFlyingMode = true;
		}
	}
	
	if (CKey::Once('M')){
		BGM.Stop();
	}

	if (CKey::Once(VK_RETURN)){
		//���̃V�[���̓Q�[��
		mScene = ETITLE;
	}


	return;
}

/* �}�b�v�ォ��̎��_ */
void CSceneRace2::RenderMiniMap() {
	glPushMatrix();
	glViewport(600 + 20-30, 450 - 440, 200, 150); //��ʂ̕`��G���A�̎w��
	glLoadIdentity();
	gluLookAt(0, 4800, 0, 0, 0, 0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
//	BackGround.Render(CMatrix());
	//�^�X�N�}�l�[�W���̕`��
//	TaskManager.Render();

//	mPlayer->mpModel = &mCarsol;
//	mPlayer->mScale = CVector(10.0f, 1.0f, 10.0f);
	CTaskManager::Get()->Render();
	//�~�j�}�b�v�ɃS�[���A�C�R����`��
	CMatrix matminig;
	matminig = CMatrix().Scale(20.0f, 1.0f, 20.0f)
		//* mPlayer->mMatrixRotate
		* CMatrix().RotateX(0)
		* CMatrix().RotateY(0)
		* CMatrix().RotateZ(0)
		* CMatrix().Translate(550.0f, 0.0f, -10.0f);
	mMiniGoal.Render(matminig);
	//�~�j�}�b�v�ɃJ�[�\����`��
	CMatrix mat;
	mat = CMatrix().Scale(35.0f, 1.0f, 35.0f) //* mPlayer->mMatrixScale
		//* mPlayer->mMatrixRotate
		* CMatrix().RotateX(0)
		* CMatrix().RotateY(mPlayer->mRotation.mY)
		* CMatrix().RotateZ(0)
		* mPlayer->mMatrixTranslate;
	mCarsol.Render(mat);
	//mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;
	


	glPopMatrix();
	glViewport(0, 0, 800, 600); //��ʂ̕`��G���A�̎w��
	glEnable(GL_DEPTH_TEST);
	
	//Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	
}


//���̃V�[���̎擾
CScene::EScene CSceneRace2::GetNextScene(){
	return mScene;
}

