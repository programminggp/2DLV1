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

//画面サイズは800x600を想定
#define SCREENSIZE_X 800
#define SCREENSIZE_Y 600
//描画エリアの指定(左端のX座標,下端のY座標,幅,高さ)
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
	//テキストフォントの読み込みと設定
	CText::mFont.Load("font\\FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	CText::mFont2.Load("font\\font2nd.tga");
	CText::mFont2.SetRowCol(8, 256 / 16);
	CText::mFont3.Load("font\\FontDIY.tga");
	CText::mFont3.SetRowCol(8, 176 / 11);

	/*全コース共通のマテリアル*/
	//車の読み込み
	mRover.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\white.mtl");//プレイヤー
	mCarRed.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\red.mtl");//以下敵の車
	mCarBlue.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\blue.mtl");
	mCarGreen.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\green.mtl");
	mCarYellow.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\yellow.mtl");
	mCarPink.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\pink.mtl");
	mCarCyan.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\cyan.mtl");
	mCarWhite.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\white.mtl");
	mCarBlack.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\black.mtl");
	mCarGray.Load("material\\common_mat\\Rover1.obj", "material\\single_color\\gray.mtl");
	mCheckPoint.Load("material\\common_mat\\cube.obj", "material\\single_color\\invisible.mtl");//中間地点(透明、ポリゴン1枚)
	//床タイルの読み込み
	mTileBlack.Load("material\\common_mat\\cube.obj", "material\\racing_mat\\tile_black.mtl");
	mTileWhite.Load("material\\common_mat\\cube.obj", "material\\racing_mat\\tile_white.mtl");
	mRWTile.Load("material\\racing_mat\\NewNewR-W.obj", "material\\racing_mat\\NewNewR-W.mtl");
	//地面の読み込み
	mPlane.Load("material\\common_mat\\plane.obj", "material\\common_mat\\plane.mtl");
	mSign_Left.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnLeft.mtl");//標識:左折
	mSign_Right.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnRight.mtl");//標識:右折
	//ミニマップ上でのプレイヤー・敵のカーソル、ゴール地点の読み込み
	mCarsol.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol.mtl");//プレイヤー
	mCarsol_Enemy.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol_enemy.mtl");//敵
	mMiniGoal.Load("material\\racing_mat\\minigoal.obj", "material\\racing_mat\\minigoal.mtl");
	mPole.Load("material\\common_mat\\cube.obj", "material\\common_mat\\soil.mtl");//ポール(木製)
	mDashBoard.Load("material\\racing_mat\\dashboard.obj", "material\\racing_mat\\dashboard.mtl");//加速床
	mJumper01.Load("material\\common_mat\\cube.obj", "material\\common_mat\\on.mtl");//ジャンプ台
	/*コース個別に読み込むマテリアル*/
	if (CSceneTitle::mCource == 1){
		mCource01.Load("material\\racing_mat\\CourceNew01.obj", "material\\racing_mat\\CourceNew01.mtl");//路面
		mGrass01.Load("material\\racing_mat\\GrassNew01.obj", "material\\racing_mat\\GrassNew01.mtl");//芝生
		mFenceTop.Load("material\\racing_mat\\FenceTopNew.obj", "material\\racing_mat\\FenceTopNew.mtl");//柵(上面)
		mFenceSide.Load("material\\racing_mat\\FenceSideNew.obj", "material\\racing_mat\\FenceSideNew.mtl");//柵(壁)
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
		//コースエディターのタイルの読み込み
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
		//コース05の読み込み
		mCource05Wall.Load("material\\racing_mat\\stage5\\cource05wall.obj", "material\\racing_mat\\stage5\\cource05wall.mtl");
		mCource05Mountain.Load("material\\racing_mat\\stage5\\cource05mountain.obj", "material\\racing_mat\\stage5\\cource05mountain.mtl");//全ての山共通
		mCource05Road.Load("material\\racing_mat\\stage5\\cource05road2.obj", "material\\racing_mat\\stage5\\cource05road2.mtl");
		mCource05Lake.Load("material\\racing_mat\\stage5\\cource05_lake.obj", "material\\racing_mat\\stage5\\cource05_lake.mtl");
		mCource05Grass_Floor.Load("material\\racing_mat\\stage5\\cource05grassF03.obj", "material\\racing_mat\\stage5\\cource05grassF03.mtl");
		mCource05Grass_Wall.Load("material\\racing_mat\\stage5\\cource05grass_wall.obj", "material\\racing_mat\\stage5\\cource05grass_wall.mtl");
		mCource05GoalTile.Load("material\\racing_mat\\stage5\\Checker_Tile.obj", "material\\racing_mat\\stage5\\Checker_Tile.mtl");
	}

	//コースエディターのタイルの読み込み
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
	
	//効果音の読み込み
	SoundCountDown.Load("SE\\Countdown01-5.wav");
	SoundStart.Load("SE\\Countdown01-6.wav");
	SoundGoal.Load("SE\\tm2_whistle000.wav");

	//カメラ視点のY座標
	mCamY = 0.0f;
	//衝突判定の描画(デバッグ用)
	mPutCol = false;

	//一部テキストが点滅する時間
	mTextBlinkTime = 0;
	
	//初期状態ではポーズ状態無効
	isPause = false;

	//BGMはループ
	BGM.Repeat();


	//シーンの設定
	mScene = EEDIT;
	//プレイヤーの生成
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//カメラの生成
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
	int size = 10;//コースの縮尺
	//for (int i = 3-1; i >= 0; i--){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 5; k++){
				if (ess[i][j][k] == 11){//直線:I字
					new CObjFloor(&mTile_Straight01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Straight01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 12){//直線:一字
					new CObjFloor(&mTile_Straight02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Straight02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 21){//カーブ:0時～3時
					new CObjFloor(&mTile_Curve03_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve03_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 22){//カーブ:3時～6時
					new CObjFloor(&mTile_Curve04_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve04_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 23){//カーブ:6時～9時
					new CObjFloor(&mTile_Curve01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 24){//カーブ:9時～12時
					new CObjFloor(&mTile_Curve02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 31){//坂:
					new CObjFloor(&mTile_Slope01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 32){//坂:
					new CObjFloor(&mTile_Slope02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 33){//坂:
					new CObjFloor(&mTile_Slope03_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope03_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 34){//坂:
					new CObjFloor(&mTile_Slope04_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope04_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 91){//広い床
					new CObjFloor(&mTile_Wide_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Wide_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 99){//でかいブロック
					new CObjFloor(&mBlock_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mBlock_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
			}
		}
	}


	//優先度変更
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
}


void CSceneEditor::Update() {
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向

	//e = CCameraPos::mpCamera->mPosition;
	e = CVector(0.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale   // * mPlayer->mMatrixScale
				* CMatrix().RotateY(mPlayer->mRotation.mY)
				* mPlayer->mMatrixTranslate
				+ CVector(0.0f, 0.0f, 0.0f);

	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);//*mPlayer->mMatrixRotate;
	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.mEye = e;

	//タスクマネージャの更新・描画
	if (isPause == false){
		CTaskManager::Get()->Update();
	}
	CTaskManager::Get()->Render();
	//衝突処理
	CTaskManager::Get()->TaskCollision();
	//削除処理
	CTaskManager::Get()->Delete();

	//デバッグ用
#ifdef _DEBUG
	if (CKey::Once('2')){//Playerの座標を出力する
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
		//衝突判定の描画
		CollisionManager.Render();
	}

	//BGMを停止する
	if (CKey::Once('M')){
		BGM.Stop();
	}
	//即時トップスピードに
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
	//ミニマップの描画
	RenderMiniMap();


	//2D描画開始
	Start2D(0, 800, 0, 600);

	//順位の描画
	float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//コース名を左下に表示
	CText::DrawString("COURCE EDIT", 20, 20, 10, 12);
		
	CPlayer::mpPlayer->CanMove = true;

	//ポーズ中表示される文字
	if (isPause){
		CText::DrawString("PAUSE", 280, 300, 10 * 3, 12 * 3, 3);
		CText::DrawString("P - Resume", 290, 200, 10, 12, 2);
		CText::DrawString("Esc - Back to Title", 250, 170, 10, 12, 2);
	}
	//2D描画終了
	End2D();
		
	//ポーズ中Escキー押下→タイトル画面移行
	if (isPause){
		if (CKey::Once(VK_BACK) || CKey::Once(VK_ESCAPE)){
			//次のシーンはゲーム
			mScene = ETITLE;
		}
	}
	return;
}

/* マップ上からの視点 */
void CSceneEditor::RenderMiniMap() {
	glPushMatrix();
	glLoadIdentity();
	//一時的に2D視点に変更する
	glViewport(MINIMAP_AREA);//画面の描画エリアの指定
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	//行列退避
	glPushMatrix();
	glLoadIdentity();				//行列を初期化
	//2D画面の設定変更
	float size = 4000.0f;//コースの縮尺設定
	bool canscrollmap = false;//プレイヤーに合わせたマップ移動の有無
	//画面比率は800x600→4:3→1.33:1
	float ratio = 1.33f;
	if (canscrollmap){
		glOrtho(-size*ratio + mPlayer->mPosition.mX, size*ratio + mPlayer->mPosition.mX, -size - mPlayer->mPosition.mZ, size - mPlayer->mPosition.mZ, -size, size);//glOrtho(左、右、下、上、手前、奥)
	}
	else{
		glOrtho(-size*ratio, size*ratio, -size, size, -size, size);//glOrtho(左、右、下、上、手前、奥)
	}
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);	//X-Z平面をX-Y平面へ

	glDisable(GL_DEPTH_TEST);
	CTaskManager::Get()->Render();

	//ミニマップにゴールアイコンを描画
	CMatrix matminig;
	matminig = CMatrix().Scale(20.0f, 1.0f, 20.0f)
		//* mPlayer->mMatrixRotate
		* CMatrix().RotateX(0)
		* CMatrix().RotateY(0)
		* CMatrix().RotateZ(0)
		* CMatrix().Translate(550.0f, 0.0f, -10.0f);
	mMiniGoal.Render(matminig);
	//ミニマップ状にプレイヤーを示すカーソルを描画
	CMatrix matplayer;
	matplayer = CMatrix().Scale(35.0f, 1.0f, 35.0f) //* mPlayer->mMatrixScale
		//* mPlayer->mMatrixRotate
		* CMatrix().RotateX(0)
		* CMatrix().RotateY(mPlayer->mRotation.mY)
		* CMatrix().RotateZ(0)
		* mPlayer->mMatrixTranslate;
	mCarsol.Render(matplayer);




	glPopMatrix();
	glViewport(0, 0, 800, 600); //画面の描画エリアの指定
	glEnable(GL_DEPTH_TEST);

	//3D視点に戻す
	glViewport(0, 0, 800, 600);	//画面の描画エリアの指定
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	//gluOrtho2D(-200 / 2, 200 / 2, -150 / 2, 150 / 2);	//2Dの画面を設定
	gluPerspective(75.0, 800.0 / 600.0, 1.0, 10000.0);	//3Dの画面を設定
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();
}
CScene::EScene CSceneEditor::GetNextScene(){
	return mScene;
}