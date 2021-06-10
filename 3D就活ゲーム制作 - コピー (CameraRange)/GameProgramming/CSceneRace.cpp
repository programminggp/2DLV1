#include "glew.h"

#include "CSceneRace.h"
//
#include "CSceneTitle.h"
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
#include "CObjWall.h"
//
#include "CItem.h"
//
#include "CKey.h"
//
#include "CBullet.h"

//�X�}�[�g�|�C���^�̐���
std::shared_ptr<CTexture> TextureExp(new CTexture());
std::shared_ptr<CTexture> TextureHit(new CTexture());
std::shared_ptr<CTexture> TextureBoost(new CTexture());

extern CSound BGM;
extern CSound SoundCountDown;
extern CSound SoundStart;
extern CSound SoundGoal;

//������mBestTime�̒l�͊֌W�Ȃ�(mRecord_ �̒l�����邽��)
int CSceneRace::mBestTime = 0;
int CSceneRace::mRecord_A = 10000;
int CSceneRace::mRecord_B = 13000;
int CSceneRace::mRecord_C = 22000;
int CSceneRace::mRecord_D = 30000;
int CSceneRace::mRecord_E = 40000;
int CSceneRace::mRecord_F = 43300;

//��ʃT�C�Y��800x600��z��
#define SCREENSIZE_X 800
#define SCREENSIZE_Y 600
//�`��G���A�̎w��(���[��X���W,���[��Y���W,��,����)
#define MINIMAP_AREA 590,10,200,150
#define BACKMIRROR_FRAME_AREA 286,491,229,154
#define BACKMIRROR_BG_WHITE_AREA 288,493,225,150
#define BACKMIRROR_VIEW_AREA 288,493,225,150
#define BACKMIRROR_EXTRAFRAME_AREA 286,598,228,5

//GLuint gFb;
//GLuint gCb;
//GLuint gRb;
//#define FBOWIDTH 512
//#define FBOHEIGHT 512

#define TEXWIDTH (1024)
#define TEXHEIGHT (1024)

bool CSceneRace::mPutCol;//�����蔻��̕`���ON�EOFF

CSceneRace::~CSceneRace() {
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}


void CSceneRace::Init() {

	//�����_�[�e�N�X�`���̏����ݒ�
	mRenderTexture.Init();

	//�I�̎c���̏�����
	CItem::mTargetAmount = 0;

	//�����e�N�X�`���̓ǂݍ���
	TextureExp->Load("exp.tga");
	//�Փ˃e�N�X�`���̓ǂݍ���
	TextureHit->Load("effect\\[Attack]Hit01_panop.tga");
	//�����e�N�X�`���̓ǂݍ���
	TextureBoost->Load("effect\\boost01.tga");

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	CText::mFont2.Load("font2nd.tga");
	CText::mFont2.SetRowCol(8, 256 / 16);
	//mFont3:�Ō��mFont3�ɐݒ肵���V�[���ł̃t�H���g(=Title��ʂ̃t�H���g)
	
	/*�S�R�[�X���ʂ̃}�e���A��*/
	mSky.Load("sky.obj", "sky.mtl");//�w�i
	mRock.Load("Rock1.obj", "Rock1.mtl");//��
	//�Ԃ̓ǂݍ���
	mRover.Load("Rover1.obj", "material\\racing_mat\\single_color\\white.mtl");//�v���C���[
	mCarRed.Load("Rover1.obj", "material\\racing_mat\\single_color\\red.mtl");//�ȉ��G�̎�
	mCarBlue.Load("Rover1.obj", "material\\racing_mat\\single_color\\blue.mtl");
	mCarGreen.Load("Rover1.obj", "material\\racing_mat\\single_color\\green.mtl");
	mCarYellow.Load("Rover1.obj", "material\\racing_mat\\single_color\\yellow.mtl");
	mCarPink.Load("Rover1.obj", "material\\racing_mat\\single_color\\pink.mtl");
	mCarCyan.Load("Rover1.obj", "material\\racing_mat\\single_color\\cyan.mtl");
	mCarWhite.Load("Rover1.obj", "material\\racing_mat\\single_color\\white.mtl");
	mCarBlack.Load("Rover1.obj", "material\\racing_mat\\single_color\\black.mtl");
	mCarGray.Load("Rover1.obj", "material\\racing_mat\\single_color\\gray.mtl");
	mCheckPoint.Load("cube.obj", "cube2.mtl");//���Ԓn�_(�����A�|���S��1��)
	//���^�C���̓ǂݍ���
	mTileBlack.Load("cube.obj", "material\\racing_mat\\tile_black.mtl");
	mTileWhite.Load("cube.obj", "material\\racing_mat\\tile_white.mtl");
	mRWTile.Load("material\\racing_mat\\NewNewR-W.obj", "material\\racing_mat\\NewNewR-W.mtl");
	//�����̂̓ǂݍ���
	mCube.Load("cube.obj", "material\\cube.mtl");//��
	mCube2.Load("cube.obj", "cube2.mtl");//����
	mCube3.Load("cube.obj", "cube3.mtl");//?
	//�n�ʂ̓ǂݍ���
	mPlane.Load("plane.obj", "plane.mtl");
	//�K�i�̓ǂݍ���
	mStairs.Load("cube.obj", "material\\stairs.mtl");
	//�I�̓ǂݍ���
	mTarget.Load("Rock1.obj", "material\\target.mtl");
	//ON�u���b�N(�H)�̓ǂݍ���
	mOnBlock.Load("cube.obj", "material\\on.mtl");
	mSign_Left.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnLeft.mtl");//�W��:����
	mSign_Right.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnRight.mtl");//�W��:�E��
	//�~�j�}�b�v��ł̃v���C���[�E�G�̃J�[�\���A�S�[���n�_�̓ǂݍ���
	mCarsol.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol.mtl");//�v���C���[
	mCarsol_Enemy.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol_enemy.mtl");//�G
	mMiniGoal.Load("material\\racing_mat\\minigoal.obj", "material\\racing_mat\\minigoal.mtl");
	mPole.Load("cube.obj", "material\\soil.mtl");//�|�[��(�ؐ�)
	mDashBoard.Load("material\\racing_mat\\dashboard.obj", "material\\racing_mat\\dashboard.mtl");//������
	mJumper01.Load("cube.obj", "cube.mtl");//�W�����v��
	/*�R�[�X�ʂɓǂݍ��ރ}�e���A��*/
	if (CSceneTitle::mMode == 1){
		mCource01.Load("material\\racing_mat\\CourceNew01.obj", "material\\racing_mat\\CourceNew01.mtl");//�H��
		mGrass01.Load("material\\racing_mat\\GrassNew01.obj", "material\\racing_mat\\GrassNew01.mtl");//�Ő�
		mFenceTop.Load("material\\racing_mat\\FenceTopNew.obj", "material\\racing_mat\\FenceTopNew.mtl");//��(���)
		mFenceSide.Load("material\\racing_mat\\FenceSideNew.obj", "material\\racing_mat\\FenceSideNew.mtl");//��(��)
	}
	else if (CSceneTitle::mMode == 2){
		mCource02Road.Load("material\\racing_mat\\cource2nd\\cource02road.obj", "material\\racing_mat\\cource2nd\\cource02road.mtl");
		mCource02Wall.Load("material\\racing_mat\\cource2nd\\cource02wall.obj", "material\\racing_mat\\cource2nd\\cource02wall.mtl");
		mCource02Jump.Load("material\\racing_mat\\cource2nd\\cource02jumper.obj", "material\\racing_mat\\cource2nd\\cource02jumper.mtl");
	}
	else if (CSceneTitle::mMode == 3){
		mCource03Road.Load("material\\racing_mat\\stage3\\cource03road.obj", "material\\racing_mat\\stage3\\cource03road.mtl");
		mCource03Wall.Load("material\\racing_mat\\stage3\\cource03wall.obj", "material\\racing_mat\\stage3\\cource03wall.mtl");
		mCource03Fence.Load("material\\racing_mat\\stage3\\cource03fence.obj", "material\\racing_mat\\stage3\\cource03fence.mtl");
	}
	else if (CSceneTitle::mMode == 4){
		//�R�[�X�G�f�B�^�[�̃^�C���̓ǂݍ���
		mTile_Curve01_Floor.Load("material\\racing_mat\\stage_edit\\Curve01_floor.obj", "material\\racing_mat\\stage_edit\\Curve01_floor.mtl");
		mTile_Curve01_Wall.Load("material\\racing_mat\\stage_edit\\Curve01_wall.obj", "material\\racing_mat\\stage_edit\\Curve01_wall.mtl");
		mTile_Curve02_Floor.Load("material\\racing_mat\\stage_edit\\Curve02_floor.obj", "material\\racing_mat\\stage_edit\\Curve02_floor.mtl");
		mTile_Curve02_Wall.Load("material\\racing_mat\\stage_edit\\Curve02_wall.obj", "material\\racing_mat\\stage_edit\\Curve02_wall.mtl");
		mTile_Curve03_Floor.Load("material\\racing_mat\\stage_edit\\Curve03_floor.obj", "material\\racing_mat\\stage_edit\\Curve03_floor.mtl");
		mTile_Curve03_Wall.Load("material\\racing_mat\\stage_edit\\Curve03_wall.obj", "material\\racing_mat\\stage_edit\\Curve03_wall.mtl");
		mTile_Curve04_Floor.Load("material\\racing_mat\\stage_edit\\Curve04_floor.obj", "material\\racing_mat\\stage_edit\\Curve04_floor.mtl");
		mTile_Curve04_Wall.Load("material\\racing_mat\\stage_edit\\Curve04_wall.obj", "material\\racing_mat\\stage_edit\\Curve04_wall.mtl");
		mTile_Straight01_Floor.Load("material\\racing_mat\\stage_edit\\Straight01_floor.obj", "material\\racing_mat\\stage_edit\\Straight01_floor.mtl");
		mTile_Straight01_Wall.Load("material\\racing_mat\\stage_edit\\Straight01_wall.obj", "material\\racing_mat\\stage_edit\\Straight01_wall.mtl");
		mTile_Straight02_Floor.Load("material\\racing_mat\\stage_edit\\Straight02_floor.obj", "material\\racing_mat\\stage_edit\\Straight02_floor.mtl");
		mTile_Straight02_Wall.Load("material\\racing_mat\\stage_edit\\Straight02_wall.obj", "material\\racing_mat\\stage_edit\\Straight02_wall.mtl");
		mTile_Slope01_Floor.Load("material\\racing_mat\\stage_edit\\Slope01_floor.obj", "material\\racing_mat\\stage_edit\\Slope01_floor.mtl");
		mTile_Slope01_Wall.Load("material\\racing_mat\\stage_edit\\Slope01_wall.obj", "material\\racing_mat\\stage_edit\\Slope01_wall.mtl");
		mTile_Slope02_Floor.Load("material\\racing_mat\\stage_edit\\Slope02_floor.obj", "material\\racing_mat\\stage_edit\\Slope02_floor.mtl");
		mTile_Slope02_Wall.Load("material\\racing_mat\\stage_edit\\Slope02_wall.obj", "material\\racing_mat\\stage_edit\\Slope02_wall.mtl");
		mTile_Slope03_Floor.Load("material\\racing_mat\\stage_edit\\Slope03_floor.obj", "material\\racing_mat\\stage_edit\\Slope03_floor.mtl");
		mTile_Slope03_Wall.Load("material\\racing_mat\\stage_edit\\Slope03_wall.obj", "material\\racing_mat\\stage_edit\\Slope03_wall.mtl");
		mTile_Slope04_Floor.Load("material\\racing_mat\\stage_edit\\Slope04_floor.obj", "material\\racing_mat\\stage_edit\\Slope04_floor.mtl");
		mTile_Slope04_Wall.Load("material\\racing_mat\\stage_edit\\Slope04_wall.obj", "material\\racing_mat\\stage_edit\\Slope04_wall.mtl");
		mTile_Wide_Floor.Load("material\\racing_mat\\stage_edit\\Tile_WideF.obj", "material\\racing_mat\\stage_edit\\Tile_WideF.mtl");
		mTile_Wide_Wall.Load("material\\racing_mat\\stage_edit\\Tile_WideW.obj", "material\\racing_mat\\stage_edit\\Tile_WideW.mtl");
		mBlock_Floor.Load("material\\racing_mat\\stage_edit\\BlockF.obj", "material\\racing_mat\\stage_edit\\BlockF.mtl");
		mBlock_Wall.Load("material\\racing_mat\\stage_edit\\BlockW.obj", "material\\racing_mat\\stage_edit\\BlockW.mtl");
	}
	else if (CSceneTitle::mMode == 5){
		//�R�[�X05�̓ǂݍ���
		mCource05Wall.Load("material\\racing_mat\\stage5\\cource05wall.obj", "material\\racing_mat\\stage5\\cource05wall.mtl");
		mCource05Mountain.Load("material\\racing_mat\\stage5\\cource05mountain.obj", "material\\racing_mat\\stage5\\cource05mountain.mtl");//�S�Ă̎R����
		mCource05Road.Load("material\\racing_mat\\stage5\\cource05road2.obj", "material\\racing_mat\\stage5\\cource05road2.mtl");
		mCource05Lake.Load("material\\racing_mat\\stage5\\cource05_lake.obj", "material\\racing_mat\\stage5\\cource05_lake.mtl");
		mCource05Grass_Floor.Load("material\\racing_mat\\stage5\\cource05grassF03.obj", "material\\racing_mat\\stage5\\cource05grassF03.mtl");
		mCource05Grass_Wall.Load("material\\racing_mat\\stage5\\cource05grass_wall.obj", "material\\racing_mat\\stage5\\cource05grass_wall.mtl");
		mCource05GoalTile.Load("material\\racing_mat\\stage5\\Checker_Tile.obj", "material\\racing_mat\\stage5\\Checker_Tile.mtl");
	}
	else if (CSceneTitle::mMode == 6){
		//
	}


	//�X�e�[�W1BGM�̓ǂݍ���
	if (CSceneTitle::mMode == 1){
		BGM.Load("BGM\\revolumed_PopsGuitar_No.01.wav");
		mBestTime = mRecord_A;
	}
	else if (CSceneTitle::mMode == 2){
		BGM.Load("BGM\\revolumed_game_maoudamashii_1_battle34.wav");
		mBestTime = mRecord_B;
	}
	else if (CSceneTitle::mMode == 3){
		BGM.Load("BGM\\revolumed_bgm_maoudamashii_neorock33.wav");
		mBestTime = mRecord_C;
	}
	else if (CSceneTitle::mMode == 4){
		BGM.Load("BGM\\revolumed_Spring_Breeze.wav");
		mBestTime = mRecord_D;
	}
	else if (CSceneTitle::mMode == 5){
		BGM.Load("BGM\\Go_on_the_mountain_road.wav");
		mBestTime = mRecord_E;
	}
	else if (CSceneTitle::mMode == 6){
		BGM.Load("BGM\\game_maoudamashii_7_event46.wav");
		mBestTime = mRecord_F;
	}
	//���ʉ��̓ǂݍ���
	SoundCountDown.Load("SE\\Countdown01-5.wav");
	SoundStart.Load("SE\\Countdown01-6.wav");
	SoundGoal.Load("SE\\tm2_whistle000.wav");

	//�J�������_��Y���W
	mCamY = 0.0f;
	//�Փ˔���̕`��(�f�o�b�O�p)
	mPutCol = false;

	//�ꕔ�e�L�X�g���_�ł��鎞��
	mTextBlinkTime = 0;

	//���[�X�̃J�E���g�_�E���֘A
	mFrame = 0;
	mCountDown = 3+1;
	//���[�X�̓J�E���g�_�E�����I����Ă���J�n
	isStartRace = isGoal = false;
	//���Ԃ̃��Z�b�g
	mTime = 0;
	mTime_Output = 0;
		
	//���b�v���̏�����
	mLap = 1;
	//�H���ŃS�[��(��{��3��)
	mMaxLap = 3;
	if (CSceneTitle::mMode == 5){
		mMaxLap = 2;//�R�[�X5��2��
	}
	//�L�^�X�V���ĂȂ����
	isNewRecord = false;
	
	//���ŏI���ʂ̏�����
	mRanking = 1;
	//�v���C���[���S�[����̌o�ߎ���
	mAfterGoalTime = 0;

	//�J�������_
	mCamPoV = 1;

	//�o�b�N�~���[�̕`��
	isRender_BackMirror = true;

	//������Ԃł͓G�̖ڕW�n�_�͕`�悵�Ȃ�
	isRendPoint = false;
	//������Ԃł̓|�[�Y��Ԗ���
	isPause = false;

	//BGM�̓��[�v
	BGM.Repeat();

	//Shadow Map

	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
//	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &dtex);
	glBindTexture(GL_TEXTURE_2D, dtex);

	/* �e�N�X�`���̊��蓖�� */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, TEXWIDTH, TEXHEIGHT, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	/* �e�N�X�`�����g��E�k��������@�̎w�� */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* �e�N�X�`���̌J��Ԃ����@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	/* �������ރ|���S���̃e�N�X�`�����W�l�̂q�ƃe�N�X�`���Ƃ̔�r���s���悤�ɂ��� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	/* �����q�̒l���e�N�X�`���̒l�ȉ��Ȃ�^�i�܂�����j */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	/* ��r�̌��ʂ��P�x�l�Ƃ��ē��� */
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

	if(false)
	{
		/* �e�N�X�`�����W�Ɏ��_���W�n�ɂ����镨�̂̍��W�l��p���� */
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

		/* ���������e�N�X�`�����W�����̂܂� (S, T, R, Q) �Ɏg�� */
		static const GLdouble genfunc[][4] = {
		  { 1.0, 0.0, 0.0, 0.0 },
		  { 0.0, 1.0, 0.0, 0.0 },
		  { 0.0, 0.0, 1.0, 0.0 },
		  { 0.0, 0.0, 0.0, 1.0 },
		};

		glTexGendv(GL_S, GL_EYE_PLANE, genfunc[0]);
		glTexGendv(GL_T, GL_EYE_PLANE, genfunc[1]);
		glTexGendv(GL_R, GL_EYE_PLANE, genfunc[2]);
		glTexGendv(GL_Q, GL_EYE_PLANE, genfunc[3]);

		glBindTexture(GL_TEXTURE_2D, 0);

		//	glActiveTexture(GL_TEXTURE0);
	}

//	glDisable(GL_TEXTURE_2D);

}


void CSceneRace::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����

	////���_�����߂�
	//if (mCamPoV == 1){
	//	e = CVector(0.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale   // * mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY)
	//		* mPlayer->mMatrixTranslate
	//		+ CVector(0.0f, 0.0f, 0.0f);
	//	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY);
	//	//e = CVector(0.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale   // * mPlayer->mMatrixScale
	//	//	* CMatrix().RotateY(mPlayer->mRotation.mY)
	//	//	//* mPlayer->mMatrixTranslate
	//	//	*CCameraPos::mpCamera->mMatrixTranslate
	//	//	+ CVector(0.0f, 0.0f, 0.0f);
	//	//c = CCameraPos::mpCamera->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
	//	//	* CMatrix().RotateY(mPlayer->mRotation.mY);
	//	//e = CVector(0.0f, 0.0f, 0.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale   // * mPlayer->mMatrixScale
	//	//	* CMatrix().RotateY(mPlayer->mRotation.mY)
	//	//	*CCameraPos::mpCamera->mMatrixTranslate;
	//	//c = CCameraPos::mpCamera->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
	//	//	* CMatrix().RotateY(mPlayer->mRotation.mY);
	//	
	//}
	//else if (mCamPoV == 2){
	//	e = CVector(0.0f, 0.0f + 0.5f, -40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY)
	//		* mPlayer->mMatrixTranslate
	//		+ CVector(0.0f, 0.0f, 0.0f);
	//	////�����_�����߂�
	//	//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
	//	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY);
	//		//* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	//}
	//else if (mCamPoV == 3){//������f�����_
	//	e = CVector(0.0f, 17.0f, 40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY)
	//		* mPlayer->mMatrixTranslate
	//		+ CVector(0.0f, 0.0f, 0.0f);
	//	////�����_�����߂�
	//	//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
	//	c = mPlayer->mPosition + CVector(0.0f, 0.0f, -40.0f)* mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY);
	//		//* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	//}
	//else{//1�`3�ȊO�̐��l�������Ă��鎞�͂Ƃ肠�����O�����_(1�Ɠ���)
	//	e = CVector(0.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale   // * mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY)
	//		* mPlayer->mMatrixTranslate
	//		+ CVector(0.0f, 0.0f, 0.0f);
	//	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY);
	//}
	////e = CVector(0.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale   // * mPlayer->mMatrixScale
	////	* CMatrix().RotateY(mPlayer->mRotation.mY)
	////	*mCam->mMatrixTranslate
	////	//* mPlayer->mMatrixTranslate
	////	+ CVector(0.0f, 0.0f, 0.0f);
	////c = mCam->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
	////	* CMatrix().RotateY(mPlayer->mRotation.mY);
	///*printf("X:%f\n", mPlayer->mColBody.mPosition.mX);
	//printf("Y:%f\n", mPlayer->mColBody.mPosition.mY);
	//printf("Z:%f\n", mPlayer->mColBody.mPosition.mZ);*/
	////����������߂�
	//u = CVector(0.0f, 1.0f, 0.0f);// *mPlayer->mMatrixRotate;

	e = CCameraPos::mpCamera->mPosition;

	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f) * mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);//*mPlayer->mMatrixRotate;
	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.mEye = e;

	//�^�X�N�}�l�[�W���̍X�V�E�`��
	if (isPause == false) {
		CTaskManager::Get()->Update();
	}

	//Shadow Map

	const int FRAMES(600);
	GLint viewport[4];       /* �r���[�|�[�g�̕ۑ��p�@�@�@�@ */
	//GLdouble modelview[16];  /* ���f���r���[�ϊ��s��̕ۑ��p */
	CMatrix modelview;  /* ���f���r���[�ϊ��s��̕ۑ��p */
//	GLdouble modelviewCamera[16];  /* ���f���r���[�ϊ��s��̕ۑ��p */
	CMatrix modelviewCamera;  /* ���f���r���[�ϊ��s��̕ۑ��p */
//	GLdouble projection[16]; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
	CMatrix projection; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
	//GLdouble projectionDepth[16]; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
	CMatrix projectionDepth; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
	static int frame = 0;    /* �t���[�����̃J�E���g�@�@�@�@ */
	double t = (double)frame / (double)FRAMES; /* �o�ߎ��ԁ@ */

	if (++frame >= FRAMES) frame = 0;

	/*
	 ** ��P�X�e�b�v�F�f�v�X�e�N�X�`���̍쐬
	 */

	 /* �f�v�X�o�b�t�@���N���A���� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* �r���[�|�[�g���e�N�X�`���̃T�C�Y�ɐݒ肷�� */
	glViewport(0, 0, TEXWIDTH, TEXHEIGHT);

	/* ���݂̓����ϊ��s���ۑ����Ă��� */
//	glGetDoublev(GL_PROJECTION_MATRIX, projectionDepth.mM[0]);
	glGetFloatv(GL_PROJECTION_MATRIX, projection.mM[0]);

	/* �����ϊ��s���P�ʍs��ɐݒ肷�� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 100000.0);
	//	gluPerspective(75.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 20000.0);
//	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetFloatv(GL_PROJECTION_MATRIX, projectionDepth.mM[0]);

	GLfloat lightpos[] = { 0.0f, 49000.0f, 100.0f, 0.0f };

//	glGetDoublev(GL_MODELVIEW_MATRIX, modelviewCamera);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewCamera.mM[0]);

	/* �����ʒu�����_�Ƃ��V�[��������Ɏ��܂�悤���f���r���[�ϊ��s���ݒ肷�� */
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(lightpos[0], lightpos[1], lightpos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* �ݒ肵�����f���r���[�ϊ��s���ۑ����Ă��� */
//	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview.mM[0]);

	if(true)
	{
		// �������ꂽ�ϊ��s����擾����B
		float m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);

		{
			float vs[] = { m[0], m[4], m[8],  m[12] };
			float vt[] = { m[1], m[5], m[9],  m[13] };
			float vr[] = { m[2], m[6], m[10], m[14] };
			float vq[] = { m[3], m[7], m[11], m[15] };

			//float vs[] = { m[0], m[1], m[2],  m[3] };
			//float vt[] = { m[4], m[5], m[6],  m[7] };
			//float vr[] = { m[8], m[9], m[10], m[11] };
			//float vq[] = { m[12], m[13], m[14], m[15] };

			// ���������ϊ��s����I�u�W�F�N�g�̒��_�Ɋ|����Ή�ʂ𕢂��悤��UV�������v�Z�����B
			glTexGenfv(GL_S, GL_OBJECT_PLANE, vs);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, vt);
			glTexGenfv(GL_R, GL_OBJECT_PLANE, vr);
			glTexGenfv(GL_Q, GL_OBJECT_PLANE, vq);
		}

		// UV�̎���������L��������B
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);
		glEnable(GL_TEXTURE_GEN_Q);

		// ���������̌v�Z���ɃI�u�W�F�N�g��Ԃ̒��_���W���g���B
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	}

	/* �f�v�X�o�b�t�@�̓��e�������擾����̂Ńt���[���o�b�t�@�ɂ͏������܂Ȃ� */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* ���������ĉA�e�t�����s�v�Ȃ̂Ń��C�e�B���O���I�t�ɂ��� */
	glDisable(GL_LIGHTING);

	/* �f�v�X�o�b�t�@�ɂ͔w�ʂ̃|���S���̉��s�����L�^����悤�ɂ��� */
	glCullFace(GL_FRONT);

	CTaskManager::Get()->Render();

	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
//	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dtex);
	/* �f�v�X�o�b�t�@�̓��e���e�N�X�`���������ɓ]������ */
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, TEXWIDTH, TEXHEIGHT);

	/* �ʏ�̕`��̐ݒ�ɖ߂� */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
//	glLoadMatrixd(projection);
	glLoadMatrixf(projection.mM[0]);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);

	/*
	** ��Q�X�e�b�v�F�S�̂̕`��
	*/

	/* �t���[���o�b�t�@�ƃf�v�X�o�b�t�@���N���A���� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���f���r���[�ϊ��s��̐ݒ� */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glPopMatrix();

	/* ���_�̈ʒu��ݒ肷��i���̂̕������Ɉړ�����j*/
//	glTranslated(0.0, 0.0, -10.0);

	/* �g���b�N�{�[�����̉�]��^���� */
//	glMultMatrixd(trackballRotation());

	/* �����̈ʒu��ݒ肷�� */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* �e�N�X�`���̃��f���r���[�ϊ��s��Ɠ����ϊ��s��̐ς������� */
//	glMultTransposeMatrixd(modelviewCamera);
//	glMultMatrixd(modelview);
	/* �e�N�X�`�����W�� [-1,1] �͈̔͂� [0,1] �͈̔͂Ɏ��߂� */
//	glScaled(0.5, 0.5, 0.5);
//	glTranslated(0.5, 0.5, 0.5);

	/* �e�N�X�`�����W�� [-1,1] �͈̔͂� [0,1] �͈̔͂Ɏ��߂� */
	glTranslated(0.5, 0.5, 0.5);
	glScaled(0.5, 0.5, 0.5);
	/* �e�N�X�`���̃��f���r���[�ϊ��s��Ɠ����ϊ��s��̐ς������� */
	//glMultMatrixf(modelview.mM[0]);
	//glMultMatrixf(projectionDepth.mM[0]);
	//glMultMatrixf(modelviewCamera.GetInverse().mM[0]);

	glMultMatrixf(projectionDepth.mM[0]);
//	glMultMatrixf(modelview.mM[0]);
//	glMultMatrixf(modelviewCamera.GetInverse().mM[0]);


	//glMultTransposeMatrixd(modelviewCamera);


	/* ���݂̃��f���r���[�ϊ��̋t�ϊ��������Ă��� */
	//glMultTransposeMatrixd(trackballRotation());
	//	glTranslated(0.0, 0.0, 10.0);

	/* ���f���r���[�ϊ��s��ɖ߂� */
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎���������L���ɂ��� */
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glEnable(GL_TEXTURE_GEN_R);
	//glEnable(GL_TEXTURE_GEN_Q);

	const GLfloat lightcol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	/* �����̖��邳������̕����ł̖��邳�ɐݒ� */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
	
	CTaskManager::Get()->Render();

	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎��������𖳌��ɂ��� */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_2D);

	//	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);


	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);


	//�Փˏ���
	CTaskManager::Get()->TaskCollision();
	//�폜����
	CTaskManager::Get()->Delete();
	if (CKey::Once('9')) {
		if (mPutCol) {
			mPutCol = false;
		}
		else {
			mPutCol = true;
		}
	}
	//�f�o�b�O�p
#ifdef _DEBUG
	if (CKey::Once('1')){
		printf("%d\n", CItem::mTargetAmount);
		printf("�x�X�g�^�C��:%d\n", mBestTime);
	}
	if (CKey::Once('2')){//Player�̍��W���o�͂���
		printf("X:%f Y:%f Z:%f\n", CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY, CPlayer::mpPlayer->mPosition.mZ);
	}
	if (CKey::Once('3')){//�����I�ɓI�̎c����0�ɂ���(�{���̓I�͏����Ȃ�)
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			printf("X:%f Y:%f Z:%f\n", mEnemys[i]->mPosition.mX, mEnemys[i]->mPosition.mY, mEnemys[i]->mPosition.mZ);
		}
		//CItem::mTargetAmount = 0;
	}
	if (CKey::Once('4')){//�o�b�N�~���[��ON�EOFF�؂�ւ�
		isRender_BackMirror = !isRender_BackMirror;
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
	if (CKey::Once('8')){
		//�G�Ԃ��ׂĂ�mVPoint�̒l���o��
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			//printf("mEnemys[%d]->mVPoint�cX:%.1f Y:%.1f Z:%.1f\n", i, mEnemys[i]->mVPoint.mX, mEnemys[i]->mVPoint.mX, mEnemys[i]->mVPoint.mZ);
			printf("mEnemys[%d]�̒��Ԓn�_�c%d  %d�T��\n", i, mEnemys[i]->mChecks, mEnemys[i]->mEnemyLap);
		}
	}
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
//		CollisionManager.Render();
	}

	//�G�̒��p�n�_�̕\��ON�EOFF�؂�ւ�
	if (CKey::Once('O')){		
		/*if (isRendPoint){
			isRendPoint = false;
		}
		else{
			isRendPoint = true;
		}*/
		//�����ƊȌ��ɐ؂�ւ�����@
		isRendPoint = !isRendPoint;
	}
	//BGM���~����
	if (CKey::Once('M')){
		BGM.Stop();
	}
	//B�L�[�������Ă���ԁA���C����ʂ�������_�ɂȂ�
	if (CKey::Push('B')){
		mCamPoV = 3;
	}
	else{
		mCamPoV = 1;
	}
	//�����g�b�v�X�s�[�h��
	if (CKey::Once('G')){
		mPlayer->mCarSpeed = 20.0f;
	}
	//
	if (CKey::Once('V')){
		mPlayer->mChecks = 3;
	}
#endif	

	//�|�[�Y��ʂɓ����Ă��Ȃ���
	if (isPause == false){
		if (isStartRace || isGoal){
			//mTime:�S�[����������I�Ƀ^�C�}�[�͍쓮��������
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
			for (int i = 0; i < ENEMYS_AMOUNT; i++){				
				if (mEnemys[i]->isEnemyGoaled == false){
					mEnemys[i]->mPointTime++;
				}
			}
		}
		if (isStartRace){
			//mTime_Output:���[�X���ɕ\�������^�C��(�S�[����Ƀ^�C�}�[��~)
			if (mTime_Output < 595959){
				if (mTime_Output % 10000 == 5959){
					mTime_Output += 1 + 40 + 4000;
				}
				else if (mTime_Output % 100 == 59){
					mTime_Output += 1 + 40;
				}
				else{
					mTime_Output += 1;
				}
			}
		}		
	}
	
	//�~�j�}�b�v�̕`��
	RenderMiniMap();
	//�o�b�N�~���[�̕`��
	if (isRender_BackMirror){
		RenderBackMirror();
	}

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	//���ʂ̕`��
	float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�R�[�X���������ɕ\��
	if (CSceneTitle::mMode == 1){
		CText::DrawString("COURCE 1", 20, 20, 10, 12);
	}
	else if (CSceneTitle::mMode == 2){
		CText::DrawString("COURCE 2", 20, 20, 10, 12);
	}
	else if (CSceneTitle::mMode == 3){
		CText::DrawString("COURCE 3", 20, 20, 10, 12);
	}
	else if (CSceneTitle::mMode == 4){
		CText::DrawString("COURCE 4", 20, 20, 10, 12);
	}

	//���Ԃ̕\��
	char mti[20];// :���܂߂��ő啶�����̐ݒ�
	sprintf(mti, "TIME:%02d:%02d:%02d", mTime_Output / 10000 % 100, mTime_Output / 100 % 100, mTime_Output % 100);
	CText::DrawString(mti, 20, 530, 10, 12);
	//�x�X�g�^�C���̕\��
	char mbestti[20];// :���܂߂��ő啶�����̐ݒ�
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
	//�c��3�b�܂ł̊ԁA�\��
	sprintf(mcountd, "%d", mCountDown);
	if (mCountDown > 0 && mCountDown <= 3){
		CText::DrawString(mcountd, 400, 300, 25, 30);
	}
	else if (mCountDown == 0){
		CText::DrawString("GO!", 400-40, 300, 25, 30);
		CPlayer::mpPlayer->CanMove = true;
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			mEnemys[i]->CanMove = true;
		}
	}

	char lap[19];
	sprintf(lap, "LAP%d/%d", mLap, mMaxLap);
	CText::DrawString(lap, 20, 500, 10, 12, 2);

	//�S�[����A�p�����Ď��s���鏈��
	if (mLap == mMaxLap && isStartRace == false && isGoal){
		//60f�ňꏄ
		if (mTextBlinkTime < 60){
			mTextBlinkTime++;
		}
		else{
			mTextBlinkTime = 0;
		}
		//Enter�L�[���͂Ń^�C�g����ʂɖ߂�邱�Ƃ�`����e�L�X�g
		if (mTextBlinkTime < 30){
			CText::DrawString("Press Enter to Title", 222, 77, 10, 12, 2);
		}
		//�V�L�^���������o������
		if (isNewRecord){
			//CText::DrawString("FINISH!", 400 - 20 * 6, 300, 20, 24);
			if (mTextBlinkTime < 15 || mTextBlinkTime >= 30 && mTextBlinkTime < 45){
				CText::DrawString("NEW RECORD!", 55, 551, 8, 9, 2);
			}
		}
	}
	char carspeed[33];
	sprintf(carspeed, "SPEED:%4.1f", CPlayer::mpPlayer->mCarSpeed);
	CText::DrawString(carspeed, 20+580, 20, 10, 12);
	////�G�̑��x�\��(�f�o�b�O�p)
	//char enecarspeed[33];
	//sprintf(enecarspeed, "SPEED:%4.1f", mEnemys[0]->mCarSpeed);
	//CText::DrawString(enecarspeed, 20 + 560, 20+25, 10, 12);
	
	//�S�[����ɕ\������镶��
	if (isGoal){
		if (mAfterGoalTime < 999){
			mAfterGoalTime++;
		}
		if (mAfterGoalTime > 85){
			color[3] = 1.0f - 0.1f * (mAfterGoalTime - 85);
			glColor4fv(color);
		}
		CText::DrawString("FINISH!", 400 - 25 * 6, 300, 25, 30);

		color[3] = 0.05f * (mAfterGoalTime - 100);
		glColor4fv(color);
		char rank[8];
		if (mPlayer->mRank == 1){      //1st
			sprintf(rank, "%dst", mPlayer->mRank);
		}
		else if (mPlayer->mRank == 2){ //2nd
			sprintf(rank, "%dnd", mPlayer->mRank);
		}
		else if (mPlayer->mRank == 3){ //3rd
			sprintf(rank, "%drd", mPlayer->mRank);
		}
		else{ //4th,5th,...
			sprintf(rank, "%dth", mPlayer->mRank);
		}
		CText::DrawString(rank, 357, 310, 10 * 2, 12 * 2, 2);

		//�S�[���ς݂̃v���C���[�A���C�o���̋L�^��\��
		char goaltime[30];
		char name[8];
		sprintf(goaltime, "%d YOU  %02d:%02d:%02d", mPlayer->mRank, mPlayer->mGoalTime / 10000 % 100, mPlayer->mGoalTime / 100 % 100, mPlayer->mGoalTime % 100);
		if (isGoal){
			CText::DrawString(goaltime, 270, 285 - mPlayer->mRank * 17, 10, 12, 2);
		}
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			sprintf(goaltime, "%d      %02d:%02d:%02d", mEnemys[i]->mRank, mEnemys[i]->mGoalTime / 10000 % 100, mEnemys[i]->mGoalTime / 100 % 100, mEnemys[i]->mGoalTime % 100);
			sprintf(name, "CPU%d", i + 1);
			if (mEnemys[i]->isEnemyGoaled){
				if (mEnemys[i]->mpModel == &mCarRed){
					color[0] = 1.0f, color[1] = 0.0f, color[2] = 0.0f;
				}
				else if (mEnemys[i]->mpModel == &mCarGreen){
					color[0] = 0.0f, color[1] = 1.0f, color[2] = 0.0f;
				}
				else if (mEnemys[i]->mpModel == &mCarBlue){
					color[0] = 0.0f, color[1] = 0.0f, color[2] = 1.0f;
				}
				else if (mEnemys[i]->mpModel == &mCarYellow){
					color[0] = 1.0f, color[1] = 1.0f, color[2] = 0.0f;
				}
				else if (mEnemys[i]->mpModel == &mCarCyan){
					color[0] = 0.0f, color[1] = 1.0f, color[2] = 1.0f;
				}								
				else if (mEnemys[i]->mpModel == &mCarPink){
					color[0] = 1.0f, color[1] = 0.0f, color[2] = 1.0f;
				}
				else if (mEnemys[i]->mpModel == &mCarWhite){
					color[0] = color[1] = color[2] = 1.0f;
				}
				else if (mEnemys[i]->mpModel == &mCarGray){
					color[0] = color[1] = color[2] = 0.5f;
				}
				else if (mEnemys[i]->mpModel == &mCarBlack){
					color[0] = color[1] = color[2] = 0.0f;
				}
				else {
					color[0] = color[1] = color[2] = 0.75f;
				}
				glColor4fv(color);
				CText::DrawString(name, 270+40, 285 - mEnemys[i]->mRank * 17, 10, 12, 2);
				//�F����U�A���ɖ߂�
				color[0] = color[1] = color[2] = 1.0f;
				glColor4fv(color);
				CText::DrawString(goaltime, 270, 285 - mEnemys[i]->mRank * 17, 10, 12, 2);
			}			
		}
	}
	//�F���������ɖ߂�
	color[3] = 1.0f;
	glColor4fv(color);
	
	//�|�[�Y���ɕ\������镶��
	if (isPause){
		CText::DrawString("PAUSE", 280, 300, 10*3, 12*3, 3);		
		CText::DrawString("P - Resume", 290, 200, 10, 12, 2);
		CText::DrawString("Esc - Back to Title", 250, 170, 10, 12, 2);
	}
	//2D�`��I��
	End2D();
	
	//�S�[���n�_�ʉߎ��̏���
	if (CSceneTitle::mMode == 2){
		if ((CPlayer::mpPlayer->mPosition.mX > 2216.0f - 222.0f && CPlayer::mpPlayer->mPosition.mX < 2216.0f + 222.0f)
			&& (CPlayer::mpPlayer->mPosition.mZ > -2300.0f - 30.0f && CPlayer::mpPlayer->mPosition.mZ < -2300.0f + 30.0f)
			&& (CPlayer::mpPlayer->mChecks == 3)
			&& (isStartRace)){
			if (mLap == mMaxLap){
				//�x�X�g�^�C���X�V��
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//�R�[�X�ɂ���ĐV�����L�^����
					if (CSceneTitle::mMode == 1){
						mRecord_A = mBestTime;
					}
					else if (CSceneTitle::mMode == 2){
						mRecord_B = mBestTime;
					}
					else if (CSceneTitle::mMode == 3){
						mRecord_C = mBestTime;
					}
					else if (CSceneTitle::mMode == 4){
						mRecord_D = mBestTime;
					}
					else if (CSceneTitle::mMode == 5){
						mRecord_E = mBestTime;
					}
					else if (CSceneTitle::mMode == 6){
						mRecord_F = mBestTime;
					}
				}
				mPlayer->mRank = mRanking;
				mRanking++;
				isStartRace = false;
				isGoal = true;
				BGM.Stop();
				SoundGoal.Play();
				//CPlayer::mpPlayer->CanMove = false;//�����X�g�b�v
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->mGoalTime = mTime;
			}
			else{
				mLap++;
				CPlayer::mpPlayer->mChecks = 0;
			}
		}
		//CPU�̎Ԃ��S�[���n�_��ʉ߂������̏���
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->mPosition.mX>2216.0f - 222.0f && mEnemys[i]->mPosition.mX < 2216.0f + 222.0f
				&& (mEnemys[i]->mPosition.mZ > -2300.0f - 30.0f && mEnemys[i]->mPosition.mZ < -2300.0f + 30.0f)
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//���̓G���ŏI���b�v�������ꍇ
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//�܂��ŏI���b�v�łȂ��ꍇ
				else{
					//�`�F�b�N�|�C���g�����Z�b�g���A���̎��X�^�[�g
					mEnemys[i]->mChecks = 0;
					mEnemys[i]->mEnemyLap++;
				}
			}
		}
	}
	else if (CSceneTitle::mMode == 3){
		if ((CPlayer::mpPlayer->mPosition.mX > 140.0f - 30.0f && CPlayer::mpPlayer->mPosition.mX < 140.0f + 30.0f)
			&& (CPlayer::mpPlayer->mPosition.mZ > -222.0f && CPlayer::mpPlayer->mPosition.mZ < 222.0f)
			&& (CPlayer::mpPlayer->mChecks == 3)
			&& (isStartRace)){
			if (mLap == mMaxLap){
				//�x�X�g�^�C���X�V��
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//�R�[�X�ɂ���ĐV�����L�^����
					if (CSceneTitle::mMode == 1){
						mRecord_A = mBestTime;
					}
					else if (CSceneTitle::mMode == 2){
						mRecord_B = mBestTime;
					}
					else if (CSceneTitle::mMode == 3){
						mRecord_C = mBestTime;
					}
					else if (CSceneTitle::mMode == 4){
						mRecord_D = mBestTime;
					}
					else if (CSceneTitle::mMode == 5){
						mRecord_E = mBestTime;
					}
					else if (CSceneTitle::mMode == 6){
						mRecord_F = mBestTime;
					}
				}
				mPlayer->mRank = mRanking;
				mRanking++;
				isStartRace = false;
				isGoal = true;
				BGM.Stop();
				SoundGoal.Play();
				//CPlayer::mpPlayer->CanMove = false;//�����X�g�b�v
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->mGoalTime = mTime;
			}
			else{
				mLap++;
				CPlayer::mpPlayer->mChecks = 0;
			}
		}
		//CPU�̎Ԃ��S�[���n�_��ʉ߂������̏���
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->mPosition.mX>100.0f && mEnemys[i]->mPosition.mX < 180.0f
				&& (mEnemys[i]->mPosition.mZ > -222.0f && mEnemys[i]->mPosition.mZ < 222.0f)
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//���̓G���ŏI���b�v�������ꍇ
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//�܂��ŏI���b�v�łȂ��ꍇ
				else{
					//�`�F�b�N�|�C���g�����Z�b�g���A���̎��X�^�[�g
					mEnemys[i]->mChecks = 0;
					mEnemys[i]->mEnemyLap++;
				}
			}
		}
	}
	else if (CSceneTitle::mMode == 5){
		if ((CPlayer::mpPlayer->isTouchGoal)
			&& (CPlayer::mpPlayer->mChecks == 3)
			&& (isStartRace)){
			if (mLap == mMaxLap){
				//�x�X�g�^�C���X�V��
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//�R�[�X�ɂ���ĐV�����L�^����
					if (CSceneTitle::mMode == 1){
						mRecord_A = mBestTime;
					}
					else if (CSceneTitle::mMode == 2){
						mRecord_B = mBestTime;
					}
					else if (CSceneTitle::mMode == 3){
						mRecord_C = mBestTime;
					}
					else if (CSceneTitle::mMode == 4){
						mRecord_D = mBestTime;
					}
					else if (CSceneTitle::mMode == 5){
						mRecord_E = mBestTime;
					}
					else if (CSceneTitle::mMode == 6){
						mRecord_F = mBestTime;
					}
				}
				mPlayer->mRank = mRanking;
				mRanking++;
				isStartRace = false;
				isGoal = true;
				BGM.Stop();
				SoundGoal.Play();
				//CPlayer::mpPlayer->CanMove = false;//�����X�g�b�v
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->mGoalTime = mTime;
				CPlayer::mpPlayer->isTouchGoal = false;
			}
			else{
				mLap++;
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->isTouchGoal = false;
			}
		}
		//CPU�̎Ԃ��S�[���n�_��ʉ߂������̏���
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->isTouchGoal
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//���̓G���ŏI���b�v�������ꍇ
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isTouchGoal = false;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//�܂��ŏI���b�v�łȂ��ꍇ
				else{
					//�`�F�b�N�|�C���g�����Z�b�g���A���̎��X�^�[�g
					mEnemys[i]->mChecks = 0;
					mEnemys[i]->isTouchGoal = false;
					mEnemys[i]->mEnemyLap++;
				}
			}
		}
	}
	else{
		if ((CPlayer::mpPlayer->mPosition.mX > -55.0f && CPlayer::mpPlayer->mPosition.mX < 1400.0f)
			&& (CPlayer::mpPlayer->mPosition.mZ > -3.1f - 5.0f && CPlayer::mpPlayer->mPosition.mZ < -3.1f + 5.0f + 20.0f)
			&& (CPlayer::mpPlayer->mChecks == 3)
			&& (isStartRace)){
			if (mLap == mMaxLap){
				//�x�X�g�^�C���X�V��
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//�R�[�X�ɂ���ĐV�����L�^����
					if (CSceneTitle::mMode == 1){
						mRecord_A = mBestTime;
					}
					else if (CSceneTitle::mMode == 2){
						mRecord_B = mBestTime;
					}
					else if (CSceneTitle::mMode == 3){
						mRecord_C = mBestTime;
					}
					else if (CSceneTitle::mMode == 4){
						mRecord_D = mBestTime;
					}
					else if (CSceneTitle::mMode == 5){
						mRecord_E = mBestTime;
					}
					else if (CSceneTitle::mMode == 6){
						mRecord_F = mBestTime;
					}
				}
				mPlayer->mRank = mRanking;
				mRanking++;
				isStartRace = false;
				isGoal = true;
				BGM.Stop();
				SoundGoal.Play();
				//CPlayer::mpPlayer->CanMove = false;//false:�S�[��������s�͉\
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->mGoalTime = mTime;
			}
			else{
				mLap++;
				CPlayer::mpPlayer->mChecks = 0;
			}
		}
		//CPU�̎Ԃ��S�[���n�_��ʉ߂������̏���
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->mPosition.mX>-55.0f && mEnemys[i]->mPosition.mX < 1400.0f
				&& (mEnemys[i]->mPosition.mZ > -3.1f - 5.0f && mEnemys[i]->mPosition.mZ < -3.1f + 5.0f + 20.0f)
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//���̓G���ŏI���b�v�������ꍇ
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//�܂��ŏI���b�v�łȂ��ꍇ
				else{
					//�`�F�b�N�|�C���g�����Z�b�g���A���̎��X�^�[�g
					mEnemys[i]->mChecks = 0;
					mEnemys[i]->mEnemyLap++;
				}
			}
		}
	}

	if (CKey::Once('P')){
		//�J�E���g�_�E���I����A�|�[�Y�̐؂�ւ����\�ɂȂ�B
		if (mCountDown < 0){
			//�S�[����͐؂�ւ��s��
			if (isGoal)return;

			//�|�[�Y��ON�EOFF�؂�ւ�
			isPause = !isPause;
		}		
	}

	/*�V�[���؂�ւ��n�̏���*/
	//�S�[����Enter�L�[�������^�C�g����ʈڍs
	if (isGoal){
		if (CKey::Once(VK_RETURN)){
			//���̃V�[���̓Q�[��
			mScene = ETITLE;
		}
	}
	//�|�[�Y��Esc�L�[�������^�C�g����ʈڍs
	if (isPause){
		if (CKey::Once(VK_BACK) || CKey::Once(VK_ESCAPE)){
			//���̃V�[���̓Q�[��
			mScene = ETITLE;
		}
	}

	return;
}

/* �}�b�v�ォ��̎��_ */
void CSceneRace::RenderMiniMap() {
	glPushMatrix();
	glLoadIdentity();
	//�ꎞ�I��2D���_�ɕύX����
	glViewport(MINIMAP_AREA);//��ʂ̕`��G���A�̎w��
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	//�s��ޔ�
	glPushMatrix();
	glLoadIdentity();				//�s���������
	//2D��ʂ̐ݒ�ύX
	float size = 20000.0f;//�R�[�X�̏k�ڐݒ�
	bool canscrollmap = false;//�v���C���[�ɍ��킹���}�b�v�ړ��̗L��
	if (CSceneTitle::mMode == 1){
		size = 3600.0f;
	}
	else if (CSceneTitle::mMode == 2){
		size = 5600.0f;
	}
	else if (CSceneTitle::mMode == 3){
		size = 7600.0f;
	}
	else if (CSceneTitle::mMode == 4){
		size = 3600.0f;
	}
	else if (CSceneTitle::mMode == 5){
		size = 5500.0f;
		canscrollmap = true;
	}
	//��ʔ䗦��800x600��4:3��1.33:1
	float ratio = 1.33f;
	if (canscrollmap){
		glOrtho(-size*ratio + mPlayer->mPosition.mX, size*ratio + mPlayer->mPosition.mX, -size - mPlayer->mPosition.mZ, size - mPlayer->mPosition.mZ, -size, size);//glOrtho(���A�E�A���A��A��O�A��)
	}
	else{
		glOrtho(-size*ratio, size*ratio, -size, size, -size, size);//glOrtho(���A�E�A���A��A��O�A��)
	}	
	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();				//�s���������
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);	//X-Z���ʂ�X-Y���ʂ�
		
	glDisable(GL_DEPTH_TEST);
	CTaskManager::Get()->Render();
		
	if (CSceneTitle::mMode == 3){
		if (isRendPoint == true){
			/*�f�o�b�O�p*/
			//�ݒ肵���G�̖ڕW�n�_���ׂĂ��~�j�}�b�v��ɕ`�悷��
			CMatrix point;
			for (int i = 1; i <= 12; i++){//�|�C���g�̐������������s
				point = CMatrix().Scale(150.0f, 1.0f, 150.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1��菬�������͑����
				if (i < 1){
					break;
				}
				if (i == 1){
					point = point * CEnemy::mPoint->mMatrixTranslate;
				}
				else if (i == 2){
					point = point * CEnemy::mPoint2->mMatrixTranslate;
				}
				else if (i == 3){
					point = point * CEnemy::mPoint3->mMatrixTranslate;
				}
				else if (i == 4){
					point = point * CEnemy::mPoint4->mMatrixTranslate;
				}
				else if (i == 5){
					point = point * CEnemy::mPoint5->mMatrixTranslate;
				}
				else if (i == 6){
					point = point * CEnemy::mPoint6->mMatrixTranslate;
				}
				else if (i == 7){
					point = point * CEnemy::mPoint7->mMatrixTranslate;
				}
				else if (i == 8){
					point = point * CEnemy::mPoint8->mMatrixTranslate;
				}
				else if (i == 9){
					point = point * CEnemy::mPoint9->mMatrixTranslate;
				}
				else if (i == 10){
					point = point * CEnemy::mPoint10->mMatrixTranslate;
				}
				else if (i == 11){
					point = point * CEnemy::mPoint11->mMatrixTranslate;
				}
				else if (i == 12){
					point = point * CEnemy::mPoint12->mMatrixTranslate;
				}
				else{
					break;
				}
				mTileWhite.Render(point);
			}
		}
		//�~�j�}�b�v�ɃS�[���A�C�R����`��
		CMatrix matminig;
		matminig = CMatrix().Scale(25.0f, 1.0f, 25.0f)
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(90)
			* CMatrix().RotateZ(0)
			* CMatrix().Translate(140.0f, 0.0f, 60.0f);
		mMiniGoal.Render(matminig);
		CMatrix matenemys[ENEMYS_AMOUNT];
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			matenemys[i] = CMatrix().Scale(70.0f, 1.0f, 70.0f) //* mPlayer->mMatrixScale
				* CMatrix().RotateX(0)
				* CMatrix().RotateY(mEnemys[i]->mRotation.mY)
				* CMatrix().RotateZ(0)
				* mEnemys[i]->mMatrixTranslate;
			mCarsol_Enemy.Render(matenemys[i]);
		}
		//�~�j�}�b�v��Ƀv���C���[�������J�[�\����`��
		CMatrix matplayer;
		matplayer = CMatrix().Scale(70.0f, 1.0f, 70.0f) //* mPlayer->mMatrixScale
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(mPlayer->mRotation.mY)
			* CMatrix().RotateZ(0)
			* mPlayer->mMatrixTranslate;
		mCarsol.Render(matplayer);
	}
	else if (CSceneTitle::mMode == 2){
		if (isRendPoint == true){
			/*�f�o�b�O�p*/
			//�ݒ肵���G�̖ڕW�n�_���ׂĂ��~�j�}�b�v��ɕ`�悷��
			CMatrix point;
			for (int i = 1; i <= 12; i++){//�|�C���g�̐������������s
				point = CMatrix().Scale(111.0f, 1.0f, 111.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1��菬�������͑����
				if (i < 1){
					break;
				}
				if (i == 1){
					point = point * CEnemy::mPoint->mMatrixTranslate;
				}
				else if (i == 2){
					point = point * CEnemy::mPoint2->mMatrixTranslate;
				}
				else if (i == 3){
					point = point * CEnemy::mPoint3->mMatrixTranslate;
				}
				else if (i == 4){
					point = point * CEnemy::mPoint4->mMatrixTranslate;
				}
				else if (i == 5){
					point = point * CEnemy::mPoint5->mMatrixTranslate;
				}
				else if (i == 6){
					point = point * CEnemy::mPoint6->mMatrixTranslate;
				}
				else if (i == 7){
					point = point * CEnemy::mPoint7->mMatrixTranslate;
				}
				else if (i == 8){
					point = point * CEnemy::mPoint8->mMatrixTranslate;
				}
				else if (i == 9){
					point = point * CEnemy::mPoint9->mMatrixTranslate;
				}
				else if (i == 10){
					point = point * CEnemy::mPoint10->mMatrixTranslate;
				}
				else if (i == 11){
					point = point * CEnemy::mPoint11->mMatrixTranslate;
				}
				else if (i == 12){
					point = point * CEnemy::mPoint12->mMatrixTranslate;
				}
				else{
					break;
				}
				mTileWhite.Render(point);
			}
		}
		//�~�j�}�b�v�ɃS�[���A�C�R����`��
		CMatrix matminig;
		matminig = CMatrix().Scale(25.0f, 1.0f, 25.0f)
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(0)
			* CMatrix().RotateZ(0)
			* CMatrix().Translate(2211.0f, 0.0f, -2300.0f);
			//* CMatrix().Translate(-3200.0f, 0.0f, 341.7f);
		mMiniGoal.Render(matminig);
		CMatrix matenemys[ENEMYS_AMOUNT];
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			matenemys[i] = CMatrix().Scale(35.0f, 1.0f, 35.0f) //* mPlayer->mMatrixScale
				* CMatrix().RotateX(0)
				* CMatrix().RotateY(mEnemys[i]->mRotation.mY)
				* CMatrix().RotateZ(0)
				* mEnemys[i]->mMatrixTranslate;
			mCarsol_Enemy.Render(matenemys[i]);
		}
		//�~�j�}�b�v��Ƀv���C���[�������J�[�\����`��
		CMatrix matplayer;
		matplayer = CMatrix().Scale(35.0f, 1.0f, 35.0f) //* mPlayer->mMatrixScale
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(mPlayer->mRotation.mY)
			* CMatrix().RotateZ(0)
			* mPlayer->mMatrixTranslate;
		mCarsol.Render(matplayer);
	}
	else if (CSceneTitle::mMode == 5){
		if (isRendPoint == true){
			/*�f�o�b�O�p*/
			//�ݒ肵���G�̖ڕW�n�_���ׂĂ��~�j�}�b�v��ɕ`�悷��
			CMatrix point;
			for (int i = 1; i <= 12; i++){//�|�C���g�̐������������s
				point = CMatrix().Scale(111.0f, 1.0f, 111.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1��菬�������͑����
				if (i < 1){
					break;
				}
				if (i == 1){
					point = point * CEnemy::mPoint->mMatrixTranslate;
				}
				else if (i == 2){
					point = point * CEnemy::mPoint2->mMatrixTranslate;
				}
				else if (i == 3){
					point = point * CEnemy::mPoint3->mMatrixTranslate;
				}
				else if (i == 4){
					point = point * CEnemy::mPoint4->mMatrixTranslate;
				}
				else if (i == 5){
					point = point * CEnemy::mPoint5->mMatrixTranslate;
				}
				else if (i == 6){
					point = point * CEnemy::mPoint6->mMatrixTranslate;
				}
				else if (i == 7){
					point = point * CEnemy::mPoint7->mMatrixTranslate;
				}
				else if (i == 8){
					point = point * CEnemy::mPoint8->mMatrixTranslate;
				}
				else if (i == 9){
					point = point * CEnemy::mPoint9->mMatrixTranslate;
				}
				else if (i == 10){
					point = point * CEnemy::mPoint10->mMatrixTranslate;
				}
				else if (i == 11){
					point = point * CEnemy::mPoint11->mMatrixTranslate;
				}
				else if (i == 12){
					point = point * CEnemy::mPoint12->mMatrixTranslate;
				}
				else{
					break;
				}
				mTileWhite.Render(point);
			}
		}
		//�~�j�}�b�v�ɃS�[���A�C�R����`��
		CMatrix matminig;
		matminig = CMatrix().Scale(25.0f, 100.0f, 25.0f)
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(-145.3)
			* CMatrix().RotateZ(0)
			* CMatrix().Translate(-3862.5f, 30.0f, 15925.0f);
		mMiniGoal.Render(matminig);

		CMatrix matenemys[ENEMYS_AMOUNT];
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			matenemys[i] = CMatrix().Scale(45.0f, 1.0f, 45.0f) //* mPlayer->mMatrixScale
				* CMatrix().RotateX(0)
				* CMatrix().RotateY(mEnemys[i]->mRotation.mY)
				* CMatrix().RotateZ(0)
				* mEnemys[i]->mMatrixTranslate;
			mCarsol_Enemy.Render(matenemys[i]);
		}
		//�~�j�}�b�v��Ƀv���C���[�������J�[�\����`��
		CMatrix matplayer;
		matplayer = CMatrix().Scale(45.0f, 1.0f, 45.0f) //* mPlayer->mMatrixScale
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(mPlayer->mRotation.mY)
			* CMatrix().RotateZ(0)
			* mPlayer->mMatrixTranslate;
		mCarsol.Render(matplayer);
	}
	else{
		if (isRendPoint == true){
			/*�f�o�b�O�p*/
			//�ݒ肵���G�̖ڕW�n�_���ׂĂ��~�j�}�b�v��ɕ`�悷��
			CMatrix point;
			for (int i = 1; i <= 12; i++){//�|�C���g�̐������������s
				point = CMatrix().Scale(111.0f, 1.0f, 111.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1��菬�������͑����
				if (i < 1){
					break;
				}
				if (i == 1){
					point = point * CEnemy::mPoint->mMatrixTranslate;
				}
				else if (i == 2){
					point = point * CEnemy::mPoint2->mMatrixTranslate;
				}
				else if (i == 3){
					point = point * CEnemy::mPoint3->mMatrixTranslate;
				}
				else if (i == 4){
					point = point * CEnemy::mPoint4->mMatrixTranslate;
				}
				else if (i == 5){
					point = point * CEnemy::mPoint5->mMatrixTranslate;
				}
				else if (i == 6){
					point = point * CEnemy::mPoint6->mMatrixTranslate;
				}
				else if (i == 7){
					point = point * CEnemy::mPoint7->mMatrixTranslate;
				}
				else if (i == 8){
					point = point * CEnemy::mPoint8->mMatrixTranslate;
				}
				else if (i == 9){
					point = point * CEnemy::mPoint9->mMatrixTranslate;
				}
				else if (i == 10){
					point = point * CEnemy::mPoint10->mMatrixTranslate;
				}
				else if (i == 11){
					point = point * CEnemy::mPoint11->mMatrixTranslate;
				}
				else if (i == 12){
					point = point * CEnemy::mPoint12->mMatrixTranslate;
				}
				else{
					break;
				}
				mTileWhite.Render(point);
			}
		}
		//�~�j�}�b�v�ɃS�[���A�C�R����`��
		CMatrix matminig;
		matminig = CMatrix().Scale(20.0f, 1.0f, 20.0f)
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(0)
			* CMatrix().RotateZ(0)
			* CMatrix().Translate(550.0f, 0.0f, -10.0f);
		mMiniGoal.Render(matminig);

		CMatrix matenemys[ENEMYS_AMOUNT];
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			matenemys[i] = CMatrix().Scale(35.0f, 1.0f, 35.0f) //* mPlayer->mMatrixScale
				* CMatrix().RotateX(0)
				* CMatrix().RotateY(mEnemys[i]->mRotation.mY)
				* CMatrix().RotateZ(0)
				* mEnemys[i]->mMatrixTranslate;
			mCarsol_Enemy.Render(matenemys[i]);
		}

		//�~�j�}�b�v��Ƀv���C���[�������J�[�\����`��
		CMatrix matplayer;
		matplayer = CMatrix().Scale(35.0f, 1.0f, 35.0f) //* mPlayer->mMatrixScale
			//* mPlayer->mMatrixRotate
			* CMatrix().RotateX(0)
			* CMatrix().RotateY(mPlayer->mRotation.mY)
			* CMatrix().RotateZ(0)
			* mPlayer->mMatrixTranslate;
		mCarsol.Render(matplayer);
	}
	
	glPopMatrix();
	glViewport(0, 0, 800, 600); //��ʂ̕`��G���A�̎w��
	glEnable(GL_DEPTH_TEST);

	//3D���_�ɖ߂�
	glViewport(0, 0, 800, 600);	//��ʂ̕`��G���A�̎w��
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
	//gluOrtho2D(-200 / 2, 200 / 2, -150 / 2, 150 / 2);	//2D�̉�ʂ�ݒ�
	gluPerspective(75.0, 800.0 / 600.0, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�
	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();
}
//�o�b�N�~���[��\��
void CSceneRace::RenderBackMirror(){

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	e = CVector(0.0f, 17.0f + 13.0f, 40.0f - 41.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY)
		* mPlayer->mMatrixTranslate;
	c = mPlayer->mPosition + CVector(0.0f, 17.0f + 12.8f, 40.0f - 42.0f)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);

	//�s���ޔ�������
	glPushMatrix();
	//�s���P�ʍs��ɂ���
	glLoadIdentity();

	//�o�b�N�~���[�̃J�����̐ݒ�
	gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//�����_�[�e�N�X�`���J�n
	mRenderTexture.Start();

	//�o�b�N�~���[��ʕ`��
	CTaskManager::Get()->Render();

	//�����_�[�e�N�X�`���I��
	mRenderTexture.End();

	//�o�b�N�~���[�`��G���A�̎w��
	glViewport(BACKMIRROR_BG_WHITE_AREA);

	//2D�`��J�n
	Start2D(-1, 1, -1, 1);

	// �e�N�X�`���}�b�s���O��L���ɂ���
	glEnable(GL_TEXTURE_2D);
	//�����_�[�e�N�X�`���̃e�N�X�`�����o�C���h����
	glBindTexture(GL_TEXTURE_2D, mRenderTexture.GetTexture());

	// �����`��`��
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(-1.0, -1.0);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(1.0, -1.0);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(1.0, 1.0);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(-1.0, 1.0);
	glEnd();

	//2D�`��I��
	End2D();

	// �e�N�X�`���}�b�s���O�𖳌��ɂ���
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glViewport(0, 0, SCREENSIZE_X, SCREENSIZE_Y); //��ʂ̕`��G���A�����C���̉�ʂɖ߂�

	//�s���߂�
	glPopMatrix();

	return;

	glDisable(GL_CULL_FACE);//�ꎞ�I�ɗ��ʂ�`��\�ɂ���
	glDisable(GL_DEPTH_TEST);
	glViewport(BACKMIRROR_FRAME_AREA);
	//2D�`��J�n
	Start2D(0, 800, 0, 600);
	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glColor4fv(color);
	//��L��2D�`��͈͂̎w��l���傫�߂ɔ��w�i��`�悷��
	int expand = 100; color[3] = 0.0f;
	//���w�i�̂�����ɍ��g�ƂȂ���̂�`�悷��
	glBegin(GL_TRIANGLES);
	glVertex2d(0 - expand, 0 - expand);
	glVertex2d(800 + expand, 600 + expand);
	glVertex2d(0 - expand, 600 + expand);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2d(0 - expand, 0 - expand);
	glVertex2d(800 + expand, 0 - expand);
	glVertex2d(800 + expand, 600 + expand);
	glEnd();
	color[0] = color[1] = color[2] = color[3] = 1.0f;
	glColor4fv(color);
	//2D�`��I��
	End2D();

	glViewport(BACKMIRROR_BG_WHITE_AREA);
	//2D�`��J�n
	Start2D(0, SCREENSIZE_X, 0, SCREENSIZE_Y);
	color[0] = color[1] = color[2] = 0.8f; color[3] = 0.0f;
	glColor4fv(color);
	//��L��2D�`��͈͂̎w��l���傫�߂ɔ��w�i��`�悷��
	expand = 100;
	//���w�i��"���"�`�悷��
	glBegin(GL_TRIANGLES);//�v���Ԃ�
	glVertex2d(0 - expand, 0 - expand);
	glVertex2d(SCREENSIZE_X + expand, SCREENSIZE_Y + expand);
	glVertex2d(0 - expand, 600 + expand);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2d(0 - expand, 0 - expand);
	glVertex2d(SCREENSIZE_X + expand, 0 - expand);
	glVertex2d(SCREENSIZE_X + expand, SCREENSIZE_Y + expand);
	glEnd();
	color[0] = color[1] = color[2] = color[3] = 1.0f;
	glColor4fv(color);
	//2D�`��I��
	End2D();
		
	//�s���ޔ�������
	glPushMatrix();
	//�s���P�ʍs��ɂ���
	glLoadIdentity();
	glViewport(BACKMIRROR_VIEW_AREA);
	//�J�����̃p�����[�^���쐬����
//	CVector e, c, u;//���_�A�����_�A�����
	e = CVector(0.0f, 17.0f + 13.0f, 40.0f - 41.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY)
		* mPlayer->mMatrixTranslate;
	c = mPlayer->mPosition + CVector(0.0f, 17.0f + 12.8f, 40.0f - 42.0f)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);
	//�J�����̂�X���W�𔽓]������	
	e = e * CMatrix().Scale(-1.0f, 1.0f, 1.0f);
	c = c * CMatrix().Scale(-1.0f, 1.0f, 1.0f);
	u = u * CMatrix().Scale(-1.0f, 1.0f, 1.0f);
	//�o�b�N�~���[�̃J�����̐ݒ�
	gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);	
	GLfloat translate[] = {
		-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	glMultMatrixf(translate);
	CTaskManager::Get()->Render();

	//���g�̌��؂�̕⊮
	glViewport(BACKMIRROR_EXTRAFRAME_AREA);
	//2D�`��J�n
	Start2D(0, SCREENSIZE_X, 0, SCREENSIZE_Y);
	color[0] = color[1] = color[2] = 0.0f;
	glColor4fv(color);
	//��L��2D�`��͈͂̎w��l���傫�߂ɔ��w�i��`�悷��
	expand = 100;
	//���i�̏�ɍ��g��`�悷��
	glBegin(GL_TRIANGLES);
	glVertex2d(0 - expand, 0 - expand);
	glVertex2d(SCREENSIZE_X + expand, SCREENSIZE_Y + expand);
	glVertex2d(0 - expand, SCREENSIZE_Y + expand);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2d(0 - expand, 0 - expand);
	glVertex2d(SCREENSIZE_X + expand, 0 - expand);
	glVertex2d(SCREENSIZE_X + expand, SCREENSIZE_Y + expand);
	glEnd();
	color[0] = color[1] = color[2] = color[3] = 1.0f;
	glColor4fv(color);
	//2D�`��I��
	End2D();

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, SCREENSIZE_X, SCREENSIZE_Y); //��ʂ̕`��G���A�����C���̉�ʂɖ߂�
	glEnable(GL_CULL_FACE);//�\�ʂ݂̂̕`��ɖ߂�

	//�s���߂�
	glPopMatrix();
}
//���̃V�[���̎擾
CScene::EScene CSceneRace::GetNextScene(){
	return mScene;
}