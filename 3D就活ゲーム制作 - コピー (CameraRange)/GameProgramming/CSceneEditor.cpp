#include "CSceneEditor.h"
#include "CSceneTitle.h"
#include "CCamera.h"
#include "CText.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CKey.h"
#include "CRaceCourceD.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CObjGrass.h"
#include "CObjBoost.h"
#include "CObjNonCol.h"

extern CSound BGM;
extern CSound SoundCountDown;
extern CSound SoundStart;
extern CSound SoundGoal;

//��ʃT�C�Y��800x600��z��
#define SCREENSIZE_X 800
#define SCREENSIZE_Y 600
//�`��G���A�̎w��(���[��X���W,���[��Y���W,��,����)
#define MINIMAP_AREA 590,10,200,150
#define MINIMAP_AREA_EDITMODE 0,0,800,600
#define BACKMIRROR_FRAME_AREA 286,491,229,154
#define BACKMIRROR_BG_WHITE_AREA 288,493,225,150
#define BACKMIRROR_VIEW_AREA 288,493,225,150
#define BACKMIRROR_EXTRAFRAME_AREA 286,598,228,5

CSceneEditor::~CSceneEditor() {
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}

void CSceneEditor::Init() {
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("font\\FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	CText::mFont2.Load("font\\font2nd.tga");
	CText::mFont2.SetRowCol(8, 256 / 16);
	CText::mFont3.Load("font\\FontDIY.tga");
	CText::mFont3.SetRowCol(8, 176 / 11);

	/*�S�R�[�X���ʂ̃}�e���A��*/
	//�Ԃ̓ǂݍ���
	mRover.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\white.mtl");//�v���C���[
	mCarRed.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\red.mtl");//�ȉ��G�̎�
	mCarBlue.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\blue.mtl");
	mCarGreen.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\green.mtl");
	mCarYellow.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\yellow.mtl");
	mCarPink.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\pink.mtl");
	mCarCyan.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\cyan.mtl");
	mCarWhite.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\white.mtl");
	mCarBlack.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\black.mtl");
	mCarGray.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\gray.mtl");
	mCheckPoint.Load("material\\common_mat\\cube.obj", "material\\single_color\\invisible.mtl");//���Ԓn�_(�����A�|���S��1��)
	//���^�C���̓ǂݍ���
	mTileBlack.Load("material\\common_mat\\cube.obj", "material\\racing_mat\\tile_black.mtl");
	mTileWhite.Load("material\\common_mat\\cube.obj", "material\\racing_mat\\tile_white.mtl");
	mRWTile.Load("material\\racing_mat\\NewNewR-W.obj", "material\\racing_mat\\NewNewR-W.mtl");
	//�n�ʂ̓ǂݍ���
	mPlane.Load("material\\common_mat\\plane.obj", "material\\common_mat\\plane.mtl");
	mSign_Left.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnLeft.mtl");//�W��:����
	mSign_Right.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnRight.mtl");//�W��:�E��
	//�~�j�}�b�v��ł̃v���C���[�E�G�̃J�[�\���A�S�[���n�_�̓ǂݍ���
	mCarsol.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol.mtl");//�v���C���[
	mCarsol_Enemy.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol_enemy.mtl");//�G
	mMiniGoal.Load("material\\racing_mat\\minigoal.obj", "material\\racing_mat\\minigoal.mtl");
	mPole.Load("material\\common_mat\\cube.obj", "material\\common_mat\\soil.mtl");//�|�[��(�ؐ�)
	mDashBoard.Load("material\\racing_mat\\dashboard.obj", "material\\racing_mat\\dashboard.mtl");//������
	mJumper01.Load("material\\common_mat\\cube.obj", "material\\common_mat\\on.mtl");//�W�����v��
	/*�R�[�X�ʂɓǂݍ��ރ}�e���A��*/
	if (CSceneTitle::mCource == 1){
		mCource01.Load("material\\racing_mat\\CourceNew01.obj", "material\\racing_mat\\CourceNew01.mtl");//�H��
		mGrass01.Load("material\\racing_mat\\GrassNew01.obj", "material\\racing_mat\\GrassNew01.mtl");//�Ő�
		mFenceTop.Load("material\\racing_mat\\FenceTopNew.obj", "material\\racing_mat\\FenceTopNew.mtl");//��(���)
		mFenceSide.Load("material\\racing_mat\\FenceSideNew.obj", "material\\racing_mat\\FenceSideNew.mtl");//��(��)
	}
	else if (CSceneTitle::mCource == 2){
		mCource02Road.Load("material\\racing_mat\\cource2nd\\cource02road.obj", "material\\racing_mat\\cource2nd\\cource02road.mtl");
		mCource02Wall.Load("material\\racing_mat\\cource2nd\\cource02wall.obj", "material\\racing_mat\\cource2nd\\cource02wall.mtl");
		mCource02Jump.Load("material\\racing_mat\\cource2nd\\cource02jumper.obj", "material\\racing_mat\\cource2nd\\cource02jumper.mtl");
	}
	else if (CSceneTitle::mCource == 3){
		mCource03Road.Load("material\\racing_mat\\stage3\\cource03road.obj", "material\\racing_mat\\stage3\\cource03road.mtl");
		mCource03Wall.Load("material\\racing_mat\\stage3\\cource03wall.obj", "material\\racing_mat\\stage3\\cource03wall.mtl");
		mCource03Fence.Load("material\\racing_mat\\stage3\\cource03fence.obj", "material\\racing_mat\\stage3\\cource03fence.mtl");
	}
	else if (CSceneTitle::mCource == 4){
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
	else if (CSceneTitle::mCource == 5){
		//�R�[�X05�̓ǂݍ���
		mCource05Wall.Load("material\\racing_mat\\stage5\\cource05wall.obj", "material\\racing_mat\\stage5\\cource05wall.mtl");
		mCource05Mountain.Load("material\\racing_mat\\stage5\\cource05mountain.obj", "material\\racing_mat\\stage5\\cource05mountain.mtl");//�S�Ă̎R����
		mCource05Road.Load("material\\racing_mat\\stage5\\cource05road2.obj", "material\\racing_mat\\stage5\\cource05road2.mtl");
		mCource05Lake.Load("material\\racing_mat\\stage5\\cource05_lake.obj", "material\\racing_mat\\stage5\\cource05_lake.mtl");
		mCource05Grass_Floor.Load("material\\racing_mat\\stage5\\cource05grassF03.obj", "material\\racing_mat\\stage5\\cource05grassF03.mtl");
		mCource05Grass_Wall.Load("material\\racing_mat\\stage5\\cource05grass_wall.obj", "material\\racing_mat\\stage5\\cource05grass_wall.mtl");
		mCource05GoalTile.Load("material\\racing_mat\\stage5\\Checker_Tile.obj", "material\\racing_mat\\stage5\\Checker_Tile.mtl");
	}

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

	BGM.Load("BGM\\revolumed_PopsGuitar_No.01.wav");
	
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
	
	//������Ԃł̓|�[�Y��Ԗ���
	isPause = false;

	//BGM�̓��[�v
	BGM.Repeat();


	//�V�[���̐ݒ�
	mScene = EEDIT;
	//�v���C���[�̐���
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//�J�����̐���
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();


	int ess[3][4][5] = {
		{
			{ 00, 00, 00, 00, 21 },
			{ 00, 24, 00, 00, 00 },
			{ 00, 00, 00, 00, 00 },
			{ 00, 00, 00, 00, 00 },
		},
		{
			{ 00, 00, 00, 32, 00 },
			{ 00, 00, 34, 21, 33 },
			{ 00, 33, 00, 00, 00 },
			{ 00, 23, 22, 00, 00 },
		},
		{
			{ 24, 12, 32, 00, 00 },
			{ 31, 24, 21, 00, 00 },
			{ 33, 11, 31, 33, 33 },
			{ 23, 22, 00, 23, 22 },
		}
	};
	int size = 10;//�R�[�X�̏k��
	//for (int i = 3-1; i >= 0; i--){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 5; k++){
				if (ess[i][j][k] == 11){//����:I��
					new CObjFloor(&mTile_Straight01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Straight01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 12){//����:�ꎚ
					new CObjFloor(&mTile_Straight02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Straight02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 21){//�J�[�u:0���`3��
					new CObjFloor(&mTile_Curve03_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve03_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 22){//�J�[�u:3���`6��
					new CObjFloor(&mTile_Curve04_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve04_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 23){//�J�[�u:6���`9��
					new CObjFloor(&mTile_Curve01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 24){//�J�[�u:9���`12��
					new CObjFloor(&mTile_Curve02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 31){//��:
					new CObjFloor(&mTile_Slope01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 32){//��:
					new CObjFloor(&mTile_Slope02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 33){//��:
					new CObjFloor(&mTile_Slope03_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope03_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 34){//��:
					new CObjFloor(&mTile_Slope04_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope04_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 91){//�L����
					new CObjFloor(&mTile_Wide_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Wide_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 99){//�ł����u���b�N
					new CObjFloor(&mBlock_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mBlock_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
			}
		}
	}


	//�D��x�ύX
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
}


void CSceneEditor::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����

	//e = CCameraPos::mpCamera->mPosition;
	e = CVector(0.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale   // * mPlayer->mMatrixScale
				* CMatrix().RotateY(mPlayer->mRotation.mY)
				* mPlayer->mMatrixTranslate
				+ CVector(0.0f, 0.0f, 0.0f);

	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);//*mPlayer->mMatrixRotate;
	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.mEye = e;

	//�^�X�N�}�l�[�W���̍X�V�E�`��
	if (isPause == false){
		CTaskManager::Get()->Update();
	}
	CTaskManager::Get()->Render();
	//�Փˏ���
	CTaskManager::Get()->TaskCollision();
	//�폜����
	CTaskManager::Get()->Delete();

	//�f�o�b�O�p
#ifdef _DEBUG
	if (CKey::Once('2')){//Player�̍��W���o�͂���
		printf("X:%f Y:%f Z:%f\n", CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY, CPlayer::mpPlayer->mPosition.mZ);
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

	//BGM���~����
	if (CKey::Once('M')){
		BGM.Stop();
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

	if (CKey::Once('P')){
		isPause = !isPause;
	}
	//�~�j�}�b�v�̕`��
	RenderMiniMap();


	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	//���ʂ̕`��
	float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�R�[�X���������ɕ\��
	CText::DrawString("COURCE EDIT", 20, 20, 10, 12);
		
	CPlayer::mpPlayer->CanMove = true;

	//�|�[�Y���\������镶��
	if (isPause){
		CText::DrawString("PAUSE", 280, 300, 10 * 3, 12 * 3, 3);
		CText::DrawString("P - Resume", 290, 200, 10, 12, 2);
		CText::DrawString("Esc - Back to Title", 250, 170, 10, 12, 2);
	}
	//2D�`��I��
	End2D();
		
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
void CSceneEditor::RenderMiniMap() {
	glPushMatrix();
	glLoadIdentity();
	//�ꎞ�I��2D���_�ɕύX����
	glViewport(MINIMAP_AREA);//��ʂ̕`��G���A�̎w��
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	//�s��ޔ�
	glPushMatrix();
	glLoadIdentity();				//�s���������
	//2D��ʂ̐ݒ�ύX
	float size = 4000.0f;//�R�[�X�̏k�ڐݒ�
	bool canscrollmap = false;//�v���C���[�ɍ��킹���}�b�v�ړ��̗L��
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

	//�~�j�}�b�v�ɃS�[���A�C�R����`��
	CMatrix matminig;
	matminig = CMatrix().Scale(20.0f, 1.0f, 20.0f)
		//* mPlayer->mMatrixRotate
		* CMatrix().RotateX(0)
		* CMatrix().RotateY(0)
		* CMatrix().RotateZ(0)
		* CMatrix().Translate(550.0f, 0.0f, -10.0f);
	mMiniGoal.Render(matminig);
	//�~�j�}�b�v��Ƀv���C���[�������J�[�\����`��
	CMatrix matplayer;
	matplayer = CMatrix().Scale(35.0f, 1.0f, 35.0f) //* mPlayer->mMatrixScale
		//* mPlayer->mMatrixRotate
		* CMatrix().RotateX(0)
		* CMatrix().RotateY(mPlayer->mRotation.mY)
		* CMatrix().RotateZ(0)
		* mPlayer->mMatrixTranslate;
	mCarsol.Render(matplayer);




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
CScene::EScene CSceneEditor::GetNextScene(){
	return mScene;
}