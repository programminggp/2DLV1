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

//スマートポインタの生成
std::shared_ptr<CTexture> TextureExp(new CTexture());
std::shared_ptr<CTexture> TextureHit(new CTexture());
std::shared_ptr<CTexture> TextureBoost(new CTexture());

extern CSound BGM;
extern CSound SoundCountDown;
extern CSound SoundStart;
extern CSound SoundGoal;

//ここのmBestTimeの値は関係ない(mRecord_ の値を入れるため)
int CSceneRace::mBestTime = 0;
int CSceneRace::mRecord_A = 10000;
int CSceneRace::mRecord_B = 13000;
int CSceneRace::mRecord_C = 22000;
int CSceneRace::mRecord_D = 30000;
int CSceneRace::mRecord_E = 40000;
int CSceneRace::mRecord_F = 43300;

//画面サイズは800x600を想定
#define SCREENSIZE_X 800
#define SCREENSIZE_Y 600
//描画エリアの指定(左端のX座標,下端のY座標,幅,高さ)
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

bool CSceneRace::mPutCol;//当たり判定の描画のON・OFF

CSceneRace::~CSceneRace() {
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}


void CSceneRace::Init() {

	//レンダーテクスチャの初期設定
	mRenderTexture.Init();

	//的の残数の初期化
	CItem::mTargetAmount = 0;

	//爆発テクスチャの読み込み
	TextureExp->Load("exp.tga");
	//衝突テクスチャの読み込み
	TextureHit->Load("effect\\[Attack]Hit01_panop.tga");
	//加速テクスチャの読み込み
	TextureBoost->Load("effect\\boost01.tga");

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	CText::mFont2.Load("font2nd.tga");
	CText::mFont2.SetRowCol(8, 256 / 16);
	//mFont3:最後にmFont3に設定したシーンでのフォント(=Title画面のフォント)
	
	/*全コース共通のマテリアル*/
	mSky.Load("sky.obj", "sky.mtl");//背景
	mRock.Load("Rock1.obj", "Rock1.mtl");//岩
	//車の読み込み
	mRover.Load("Rover1.obj", "material\\racing_mat\\single_color\\white.mtl");//プレイヤー
	mCarRed.Load("Rover1.obj", "material\\racing_mat\\single_color\\red.mtl");//以下敵の車
	mCarBlue.Load("Rover1.obj", "material\\racing_mat\\single_color\\blue.mtl");
	mCarGreen.Load("Rover1.obj", "material\\racing_mat\\single_color\\green.mtl");
	mCarYellow.Load("Rover1.obj", "material\\racing_mat\\single_color\\yellow.mtl");
	mCarPink.Load("Rover1.obj", "material\\racing_mat\\single_color\\pink.mtl");
	mCarCyan.Load("Rover1.obj", "material\\racing_mat\\single_color\\cyan.mtl");
	mCarWhite.Load("Rover1.obj", "material\\racing_mat\\single_color\\white.mtl");
	mCarBlack.Load("Rover1.obj", "material\\racing_mat\\single_color\\black.mtl");
	mCarGray.Load("Rover1.obj", "material\\racing_mat\\single_color\\gray.mtl");
	mCheckPoint.Load("cube.obj", "cube2.mtl");//中間地点(透明、ポリゴン1枚)
	//床タイルの読み込み
	mTileBlack.Load("cube.obj", "material\\racing_mat\\tile_black.mtl");
	mTileWhite.Load("cube.obj", "material\\racing_mat\\tile_white.mtl");
	mRWTile.Load("material\\racing_mat\\NewNewR-W.obj", "material\\racing_mat\\NewNewR-W.mtl");
	//立方体の読み込み
	mCube.Load("cube.obj", "material\\cube.mtl");//白
	mCube2.Load("cube.obj", "cube2.mtl");//透明
	mCube3.Load("cube.obj", "cube3.mtl");//?
	//地面の読み込み
	mPlane.Load("plane.obj", "plane.mtl");
	//階段の読み込み
	mStairs.Load("cube.obj", "material\\stairs.mtl");
	//的の読み込み
	mTarget.Load("Rock1.obj", "material\\target.mtl");
	//ONブロック(？)の読み込み
	mOnBlock.Load("cube.obj", "material\\on.mtl");
	mSign_Left.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnLeft.mtl");//標識:左折
	mSign_Right.Load("material\\racing_mat\\stage5\\Sign_TurnLeft.obj", "material\\racing_mat\\stage5\\Sign_TurnRight.mtl");//標識:右折
	//ミニマップ上でのプレイヤー・敵のカーソル、ゴール地点の読み込み
	mCarsol.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol.mtl");//プレイヤー
	mCarsol_Enemy.Load("material\\racing_mat\\minicarsol.obj", "material\\racing_mat\\minicarsol_enemy.mtl");//敵
	mMiniGoal.Load("material\\racing_mat\\minigoal.obj", "material\\racing_mat\\minigoal.mtl");
	mPole.Load("cube.obj", "material\\soil.mtl");//ポール(木製)
	mDashBoard.Load("material\\racing_mat\\dashboard.obj", "material\\racing_mat\\dashboard.mtl");//加速床
	mJumper01.Load("cube.obj", "cube.mtl");//ジャンプ台
	/*コース個別に読み込むマテリアル*/
	if (CSceneTitle::mMode == 1){
		mCource01.Load("material\\racing_mat\\CourceNew01.obj", "material\\racing_mat\\CourceNew01.mtl");//路面
		mGrass01.Load("material\\racing_mat\\GrassNew01.obj", "material\\racing_mat\\GrassNew01.mtl");//芝生
		mFenceTop.Load("material\\racing_mat\\FenceTopNew.obj", "material\\racing_mat\\FenceTopNew.mtl");//柵(上面)
		mFenceSide.Load("material\\racing_mat\\FenceSideNew.obj", "material\\racing_mat\\FenceSideNew.mtl");//柵(壁)
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
	else if (CSceneTitle::mMode == 5){
		//コース05の読み込み
		mCource05Wall.Load("material\\racing_mat\\stage5\\cource05wall.obj", "material\\racing_mat\\stage5\\cource05wall.mtl");
		mCource05Mountain.Load("material\\racing_mat\\stage5\\cource05mountain.obj", "material\\racing_mat\\stage5\\cource05mountain.mtl");//全ての山共通
		mCource05Road.Load("material\\racing_mat\\stage5\\cource05road2.obj", "material\\racing_mat\\stage5\\cource05road2.mtl");
		mCource05Lake.Load("material\\racing_mat\\stage5\\cource05_lake.obj", "material\\racing_mat\\stage5\\cource05_lake.mtl");
		mCource05Grass_Floor.Load("material\\racing_mat\\stage5\\cource05grassF03.obj", "material\\racing_mat\\stage5\\cource05grassF03.mtl");
		mCource05Grass_Wall.Load("material\\racing_mat\\stage5\\cource05grass_wall.obj", "material\\racing_mat\\stage5\\cource05grass_wall.mtl");
		mCource05GoalTile.Load("material\\racing_mat\\stage5\\Checker_Tile.obj", "material\\racing_mat\\stage5\\Checker_Tile.mtl");
	}
	else if (CSceneTitle::mMode == 6){
		//
	}


	//ステージ1BGMの読み込み
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

	//レースのカウントダウン関連
	mFrame = 0;
	mCountDown = 3+1;
	//レースはカウントダウンが終わってから開始
	isStartRace = isGoal = false;
	//時間のリセット
	mTime = 0;
	mTime_Output = 0;
		
	//ラップ数の初期化
	mLap = 1;
	//？周でゴール(基本は3周)
	mMaxLap = 3;
	if (CSceneTitle::mMode == 5){
		mMaxLap = 2;//コース5は2周
	}
	//記録更新してない状態
	isNewRecord = false;
	
	//※最終順位の初期化
	mRanking = 1;
	//プレイヤーがゴール後の経過時間
	mAfterGoalTime = 0;

	//カメラ視点
	mCamPoV = 1;

	//バックミラーの描画
	isRender_BackMirror = true;

	//初期状態では敵の目標地点は描画しない
	isRendPoint = false;
	//初期状態ではポーズ状態無効
	isPause = false;

	//BGMはループ
	BGM.Repeat();

	//Shadow Map

	/* テクスチャユニット１に切り替える */
//	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &dtex);
	glBindTexture(GL_TEXTURE_2D, dtex);

	/* テクスチャの割り当て */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, TEXWIDTH, TEXHEIGHT, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	/* テクスチャを拡大・縮小する方法の指定 */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* テクスチャの繰り返し方法の指定 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	/* 書き込むポリゴンのテクスチャ座標値のＲとテクスチャとの比較を行うようにする */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	/* もしＲの値がテクスチャの値以下なら真（つまり日向） */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	/* 比較の結果を輝度値として得る */
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

	if(false)
	{
		/* テクスチャ座標に視点座標系における物体の座標値を用いる */
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

		/* 生成したテクスチャ座標をそのまま (S, T, R, Q) に使う */
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
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向

	////視点を求める
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
	//	////注視点を求める
	//	//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
	//	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)* mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY);
	//		//* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	//}
	//else if (mCamPoV == 3){//後方を映す視点
	//	e = CVector(0.0f, 17.0f, 40.0f) * CMatrix().RotateY(mCamY) * mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY)
	//		* mPlayer->mMatrixTranslate
	//		+ CVector(0.0f, 0.0f, 0.0f);
	//	////注視点を求める
	//	//c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f)*mPlayer->mMatrixRotate;
	//	c = mPlayer->mPosition + CVector(0.0f, 0.0f, -40.0f)* mPlayer->mMatrixScale
	//		* CMatrix().RotateY(mPlayer->mRotation.mY);
	//		//* CMatrix().RotateZ(mPlayer->mRotation.mZ);
	//}
	//else{//1～3以外の数値が入っている時はとりあえず前方視点(1と同じ)
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
	////上方向を求める
	//u = CVector(0.0f, 1.0f, 0.0f);// *mPlayer->mMatrixRotate;

	e = CCameraPos::mpCamera->mPosition;

	c = mPlayer->mPosition + CVector(0.0f, 0.0f, 40.0f) * mPlayer->mMatrixScale   //* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);//*mPlayer->mMatrixRotate;
	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.mEye = e;

	//タスクマネージャの更新・描画
	if (isPause == false) {
		CTaskManager::Get()->Update();
	}

	//Shadow Map

	const int FRAMES(600);
	GLint viewport[4];       /* ビューポートの保存用　　　　 */
	//GLdouble modelview[16];  /* モデルビュー変換行列の保存用 */
	CMatrix modelview;  /* モデルビュー変換行列の保存用 */
//	GLdouble modelviewCamera[16];  /* モデルビュー変換行列の保存用 */
	CMatrix modelviewCamera;  /* モデルビュー変換行列の保存用 */
//	GLdouble projection[16]; /* 透視変換行列の保存用　　　　 */
	CMatrix projection; /* 透視変換行列の保存用　　　　 */
	//GLdouble projectionDepth[16]; /* 透視変換行列の保存用　　　　 */
	CMatrix projectionDepth; /* 透視変換行列の保存用　　　　 */
	static int frame = 0;    /* フレーム数のカウント　　　　 */
	double t = (double)frame / (double)FRAMES; /* 経過時間　 */

	if (++frame >= FRAMES) frame = 0;

	/*
	 ** 第１ステップ：デプステクスチャの作成
	 */

	 /* デプスバッファをクリアする */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* ビューポートをテクスチャのサイズに設定する */
	glViewport(0, 0, TEXWIDTH, TEXHEIGHT);

	/* 現在の透視変換行列を保存しておく */
//	glGetDoublev(GL_PROJECTION_MATRIX, projectionDepth.mM[0]);
	glGetFloatv(GL_PROJECTION_MATRIX, projection.mM[0]);

	/* 透視変換行列を単位行列に設定する */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 100000.0);
	//	gluPerspective(75.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 20000.0);
//	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetFloatv(GL_PROJECTION_MATRIX, projectionDepth.mM[0]);

	GLfloat lightpos[] = { 0.0f, 49000.0f, 100.0f, 0.0f };

//	glGetDoublev(GL_MODELVIEW_MATRIX, modelviewCamera);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewCamera.mM[0]);

	/* 光源位置を視点としシーンが視野に収まるようモデルビュー変換行列を設定する */
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(lightpos[0], lightpos[1], lightpos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* 設定したモデルビュー変換行列を保存しておく */
//	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview.mM[0]);

	if(true)
	{
		// 合成された変換行列を取得する。
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

			// 合成した変換行列をオブジェクトの頂点に掛ければ画面を覆うようにUVが自動計算される。
			glTexGenfv(GL_S, GL_OBJECT_PLANE, vs);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, vt);
			glTexGenfv(GL_R, GL_OBJECT_PLANE, vr);
			glTexGenfv(GL_Q, GL_OBJECT_PLANE, vq);
		}

		// UVの自動生成を有効化する。
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);
		glEnable(GL_TEXTURE_GEN_Q);

		// 自動生成の計算式にオブジェクト空間の頂点座標を使う。
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	}

	/* デプスバッファの内容だけを取得するのでフレームバッファには書き込まない */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* したがって陰影付けも不要なのでライティングをオフにする */
	glDisable(GL_LIGHTING);

	/* デプスバッファには背面のポリゴンの奥行きを記録するようにする */
	glCullFace(GL_FRONT);

	CTaskManager::Get()->Render();

	/* テクスチャユニット１に切り替える */
//	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dtex);
	/* デプスバッファの内容をテクスチャメモリに転送する */
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, TEXWIDTH, TEXHEIGHT);

	/* 通常の描画の設定に戻す */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
//	glLoadMatrixd(projection);
	glLoadMatrixf(projection.mM[0]);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);

	/*
	** 第２ステップ：全体の描画
	*/

	/* フレームバッファとデプスバッファをクリアする */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glPopMatrix();

	/* 視点の位置を設定する（物体の方を奥に移動する）*/
//	glTranslated(0.0, 0.0, -10.0);

	/* トラックボール式の回転を与える */
//	glMultMatrixd(trackballRotation());

	/* 光源の位置を設定する */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	/* テクスチャ変換行列を設定する */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* テクスチャのモデルビュー変換行列と透視変換行列の積をかける */
//	glMultTransposeMatrixd(modelviewCamera);
//	glMultMatrixd(modelview);
	/* テクスチャ座標の [-1,1] の範囲を [0,1] の範囲に収める */
//	glScaled(0.5, 0.5, 0.5);
//	glTranslated(0.5, 0.5, 0.5);

	/* テクスチャ座標の [-1,1] の範囲を [0,1] の範囲に収める */
	glTranslated(0.5, 0.5, 0.5);
	glScaled(0.5, 0.5, 0.5);
	/* テクスチャのモデルビュー変換行列と透視変換行列の積をかける */
	//glMultMatrixf(modelview.mM[0]);
	//glMultMatrixf(projectionDepth.mM[0]);
	//glMultMatrixf(modelviewCamera.GetInverse().mM[0]);

	glMultMatrixf(projectionDepth.mM[0]);
//	glMultMatrixf(modelview.mM[0]);
//	glMultMatrixf(modelviewCamera.GetInverse().mM[0]);


	//glMultTransposeMatrixd(modelviewCamera);


	/* 現在のモデルビュー変換の逆変換をかけておく */
	//glMultTransposeMatrixd(trackballRotation());
	//	glTranslated(0.0, 0.0, 10.0);

	/* モデルビュー変換行列に戻す */
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	/* テクスチャマッピングとテクスチャ座標の自動生成を有効にする */
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glEnable(GL_TEXTURE_GEN_R);
	//glEnable(GL_TEXTURE_GEN_Q);

	const GLfloat lightcol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	/* 光源の明るさを日向の部分での明るさに設定 */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
	
	CTaskManager::Get()->Render();

	/* テクスチャマッピングとテクスチャ座標の自動生成を無効にする */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_2D);

	//	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);


	/* テクスチャ変換行列を設定する */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);


	//衝突処理
	CTaskManager::Get()->TaskCollision();
	//削除処理
	CTaskManager::Get()->Delete();
	if (CKey::Once('9')) {
		if (mPutCol) {
			mPutCol = false;
		}
		else {
			mPutCol = true;
		}
	}
	//デバッグ用
#ifdef _DEBUG
	if (CKey::Once('1')){
		printf("%d\n", CItem::mTargetAmount);
		printf("ベストタイム:%d\n", mBestTime);
	}
	if (CKey::Once('2')){//Playerの座標を出力する
		printf("X:%f Y:%f Z:%f\n", CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY, CPlayer::mpPlayer->mPosition.mZ);
	}
	if (CKey::Once('3')){//強制的に的の残数を0にする(本来の的は消えない)
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			printf("X:%f Y:%f Z:%f\n", mEnemys[i]->mPosition.mX, mEnemys[i]->mPosition.mY, mEnemys[i]->mPosition.mZ);
		}
		//CItem::mTargetAmount = 0;
	}
	if (CKey::Once('4')){//バックミラーのON・OFF切り替え
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
		//敵車すべてのmVPointの値を出力
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			//printf("mEnemys[%d]->mVPoint…X:%.1f Y:%.1f Z:%.1f\n", i, mEnemys[i]->mVPoint.mX, mEnemys[i]->mVPoint.mX, mEnemys[i]->mVPoint.mZ);
			printf("mEnemys[%d]の中間地点…%d  %d週目\n", i, mEnemys[i]->mChecks, mEnemys[i]->mEnemyLap);
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
//		CollisionManager.Render();
	}

	//敵の中継地点の表示ON・OFF切り替え
	if (CKey::Once('O')){		
		/*if (isRendPoint){
			isRendPoint = false;
		}
		else{
			isRendPoint = true;
		}*/
		//もっと簡潔に切り替える方法
		isRendPoint = !isRendPoint;
	}
	//BGMを停止する
	if (CKey::Once('M')){
		BGM.Stop();
	}
	//Bキーを押している間、メイン画面も後方視点になる
	if (CKey::Push('B')){
		mCamPoV = 3;
	}
	else{
		mCamPoV = 1;
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

	//ポーズ画面に入っていない時
	if (isPause == false){
		if (isStartRace || isGoal){
			//mTime:ゴール後も内部的にタイマーは作動し続ける
			//59:59:59が最大時間
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
			//mTime_Output:レース中に表示されるタイム(ゴール後にタイマー停止)
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
	
	//ミニマップの描画
	RenderMiniMap();
	//バックミラーの描画
	if (isRender_BackMirror){
		RenderBackMirror();
	}

	//2D描画開始
	Start2D(0, 800, 0, 600);

	//順位の描画
	float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//コース名を左下に表示
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

	//時間の表示
	char mti[20];// :も含めた最大文字数の設定
	sprintf(mti, "TIME:%02d:%02d:%02d", mTime_Output / 10000 % 100, mTime_Output / 100 % 100, mTime_Output % 100);
	CText::DrawString(mti, 20, 530, 10, 12);
	//ベストタイムの表示
	char mbestti[20];// :も含めた最大文字数の設定
	//	sprintf(mti, "%06d", mTime);
	sprintf(mbestti, "BEST:%02d:%02d:%02d", mBestTime / 10000 % 100, mBestTime / 100 % 100, mBestTime % 100);
	CText::DrawString(mbestti, 20, 580, 10, 12);
	
	//カウントダウン開始、GO!で操作の受付開始
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
	//カウントダウン表示
	char mcountd[7];
	//残り3秒までの間、表示
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

	//ゴール後、継続して実行する処理
	if (mLap == mMaxLap && isStartRace == false && isGoal){
		//60fで一巡
		if (mTextBlinkTime < 60){
			mTextBlinkTime++;
		}
		else{
			mTextBlinkTime = 0;
		}
		//Enterキー入力でタイトル画面に戻れることを伝えるテキスト
		if (mTextBlinkTime < 30){
			CText::DrawString("Press Enter to Title", 222, 77, 10, 12, 2);
		}
		//新記録をたたき出した時
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
	////敵の速度表示(デバッグ用)
	//char enecarspeed[33];
	//sprintf(enecarspeed, "SPEED:%4.1f", mEnemys[0]->mCarSpeed);
	//CText::DrawString(enecarspeed, 20 + 560, 20+25, 10, 12);
	
	//ゴール後に表示される文字
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

		//ゴール済みのプレイヤー、ライバルの記録を表示
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
				//色を一旦、白に戻す
				color[0] = color[1] = color[2] = 1.0f;
				glColor4fv(color);
				CText::DrawString(goaltime, 270, 285 - mEnemys[i]->mRank * 17, 10, 12, 2);
			}			
		}
	}
	//色合いを元に戻す
	color[3] = 1.0f;
	glColor4fv(color);
	
	//ポーズ中に表示される文字
	if (isPause){
		CText::DrawString("PAUSE", 280, 300, 10*3, 12*3, 3);		
		CText::DrawString("P - Resume", 290, 200, 10, 12, 2);
		CText::DrawString("Esc - Back to Title", 250, 170, 10, 12, 2);
	}
	//2D描画終了
	End2D();
	
	//ゴール地点通過時の処理
	if (CSceneTitle::mMode == 2){
		if ((CPlayer::mpPlayer->mPosition.mX > 2216.0f - 222.0f && CPlayer::mpPlayer->mPosition.mX < 2216.0f + 222.0f)
			&& (CPlayer::mpPlayer->mPosition.mZ > -2300.0f - 30.0f && CPlayer::mpPlayer->mPosition.mZ < -2300.0f + 30.0f)
			&& (CPlayer::mpPlayer->mChecks == 3)
			&& (isStartRace)){
			if (mLap == mMaxLap){
				//ベストタイム更新時
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//コースによって新しく記録する
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
				//CPlayer::mpPlayer->CanMove = false;//動きストップ
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->mGoalTime = mTime;
			}
			else{
				mLap++;
				CPlayer::mpPlayer->mChecks = 0;
			}
		}
		//CPUの車がゴール地点を通過した時の処理
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->mPosition.mX>2216.0f - 222.0f && mEnemys[i]->mPosition.mX < 2216.0f + 222.0f
				&& (mEnemys[i]->mPosition.mZ > -2300.0f - 30.0f && mEnemys[i]->mPosition.mZ < -2300.0f + 30.0f)
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//その敵が最終ラップだった場合
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//まだ最終ラップでない場合
				else{
					//チェックポイントをリセットし、次の周スタート
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
				//ベストタイム更新時
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//コースによって新しく記録する
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
				//CPlayer::mpPlayer->CanMove = false;//動きストップ
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->mGoalTime = mTime;
			}
			else{
				mLap++;
				CPlayer::mpPlayer->mChecks = 0;
			}
		}
		//CPUの車がゴール地点を通過した時の処理
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->mPosition.mX>100.0f && mEnemys[i]->mPosition.mX < 180.0f
				&& (mEnemys[i]->mPosition.mZ > -222.0f && mEnemys[i]->mPosition.mZ < 222.0f)
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//その敵が最終ラップだった場合
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//まだ最終ラップでない場合
				else{
					//チェックポイントをリセットし、次の周スタート
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
				//ベストタイム更新時
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//コースによって新しく記録する
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
				//CPlayer::mpPlayer->CanMove = false;//動きストップ
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
		//CPUの車がゴール地点を通過した時の処理
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->isTouchGoal
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//その敵が最終ラップだった場合
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isTouchGoal = false;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//まだ最終ラップでない場合
				else{
					//チェックポイントをリセットし、次の周スタート
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
				//ベストタイム更新時
				if (mTime < mBestTime){
					mBestTime = mTime;
					isNewRecord = true;
					//コースによって新しく記録する
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
				//CPlayer::mpPlayer->CanMove = false;//false:ゴール後も走行は可能
				CPlayer::mpPlayer->mChecks = 0;
				CPlayer::mpPlayer->mGoalTime = mTime;
			}
			else{
				mLap++;
				CPlayer::mpPlayer->mChecks = 0;
			}
		}
		//CPUの車がゴール地点を通過した時の処理
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			if (mEnemys[i]->mPosition.mX>-55.0f && mEnemys[i]->mPosition.mX < 1400.0f
				&& (mEnemys[i]->mPosition.mZ > -3.1f - 5.0f && mEnemys[i]->mPosition.mZ < -3.1f + 5.0f + 20.0f)
				&& (mEnemys[i]->mChecks == 3)
				&& (mEnemys[i]->isEnemyGoaled == false)){
				//その敵が最終ラップだった場合
				if (mEnemys[i]->mEnemyLap == mMaxLap){
					mEnemys[i]->mRank = mRanking;
					mRanking++;
					mEnemys[i]->isEnemyGoaled = true;
					mEnemys[i]->mGoalTime = mTime;
				}
				//まだ最終ラップでない場合
				else{
					//チェックポイントをリセットし、次の周スタート
					mEnemys[i]->mChecks = 0;
					mEnemys[i]->mEnemyLap++;
				}
			}
		}
	}

	if (CKey::Once('P')){
		//カウントダウン終了後、ポーズの切り替えが可能になる。
		if (mCountDown < 0){
			//ゴール後は切り替え不可
			if (isGoal)return;

			//ポーズのON・OFF切り替え
			isPause = !isPause;
		}		
	}

	/*シーン切り替え系の処理*/
	//ゴール後Enterキー押下→タイトル画面移行
	if (isGoal){
		if (CKey::Once(VK_RETURN)){
			//次のシーンはゲーム
			mScene = ETITLE;
		}
	}
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
void CSceneRace::RenderMiniMap() {
	glPushMatrix();
	glLoadIdentity();
	//一時的に2D視点に変更する
	glViewport(MINIMAP_AREA);//画面の描画エリアの指定
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	//行列退避
	glPushMatrix();
	glLoadIdentity();				//行列を初期化
	//2D画面の設定変更
	float size = 20000.0f;//コースの縮尺設定
	bool canscrollmap = false;//プレイヤーに合わせたマップ移動の有無
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
		
	if (CSceneTitle::mMode == 3){
		if (isRendPoint == true){
			/*デバッグ用*/
			//設定した敵の目標地点すべてをミニマップ上に描画する
			CMatrix point;
			for (int i = 1; i <= 12; i++){//ポイントの数だけ処理実行
				point = CMatrix().Scale(150.0f, 1.0f, 150.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1より小さい時は即やめ
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
		//ミニマップにゴールアイコンを描画
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
		//ミニマップ状にプレイヤーを示すカーソルを描画
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
			/*デバッグ用*/
			//設定した敵の目標地点すべてをミニマップ上に描画する
			CMatrix point;
			for (int i = 1; i <= 12; i++){//ポイントの数だけ処理実行
				point = CMatrix().Scale(111.0f, 1.0f, 111.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1より小さい時は即やめ
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
		//ミニマップにゴールアイコンを描画
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
		//ミニマップ状にプレイヤーを示すカーソルを描画
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
			/*デバッグ用*/
			//設定した敵の目標地点すべてをミニマップ上に描画する
			CMatrix point;
			for (int i = 1; i <= 12; i++){//ポイントの数だけ処理実行
				point = CMatrix().Scale(111.0f, 1.0f, 111.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1より小さい時は即やめ
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
		//ミニマップにゴールアイコンを描画
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
		//ミニマップ状にプレイヤーを示すカーソルを描画
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
			/*デバッグ用*/
			//設定した敵の目標地点すべてをミニマップ上に描画する
			CMatrix point;
			for (int i = 1; i <= 12; i++){//ポイントの数だけ処理実行
				point = CMatrix().Scale(111.0f, 1.0f, 111.0f)
					* CMatrix().RotateY(45);
				//* CEnemy::mPoint->mMatrixTranslate;
				//1より小さい時は即やめ
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
		//ミニマップにゴールアイコンを描画
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

		//ミニマップ状にプレイヤーを示すカーソルを描画
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
//バックミラーを表示
void CSceneRace::RenderBackMirror(){

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	e = CVector(0.0f, 17.0f + 13.0f, 40.0f - 41.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY)
		* mPlayer->mMatrixTranslate;
	c = mPlayer->mPosition + CVector(0.0f, 17.0f + 12.8f, 40.0f - 42.0f)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);

	//行列を退避させる
	glPushMatrix();
	//行列を単位行列にする
	glLoadIdentity();

	//バックミラーのカメラの設定
	gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//レンダーテクスチャ開始
	mRenderTexture.Start();

	//バックミラー画面描画
	CTaskManager::Get()->Render();

	//レンダーテクスチャ終了
	mRenderTexture.End();

	//バックミラー描画エリアの指定
	glViewport(BACKMIRROR_BG_WHITE_AREA);

	//2D描画開始
	Start2D(-1, 1, -1, 1);

	// テクスチャマッピングを有効にする
	glEnable(GL_TEXTURE_2D);
	//レンダーテクスチャのテクスチャをバインドする
	glBindTexture(GL_TEXTURE_2D, mRenderTexture.GetTexture());

	// 正方形を描く
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

	//2D描画終了
	End2D();

	// テクスチャマッピングを無効にする
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glViewport(0, 0, SCREENSIZE_X, SCREENSIZE_Y); //画面の描画エリアをメインの画面に戻す

	//行列を戻す
	glPopMatrix();

	return;

	glDisable(GL_CULL_FACE);//一時的に両面を描画可能にする
	glDisable(GL_DEPTH_TEST);
	glViewport(BACKMIRROR_FRAME_AREA);
	//2D描画開始
	Start2D(0, 800, 0, 600);
	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glColor4fv(color);
	//上記の2D描画範囲の指定値より大きめに白背景を描画する
	int expand = 100; color[3] = 0.0f;
	//白背景のよりも先に黒枠となるものを描画する
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
	//2D描画終了
	End2D();

	glViewport(BACKMIRROR_BG_WHITE_AREA);
	//2D描画開始
	Start2D(0, SCREENSIZE_X, 0, SCREENSIZE_Y);
	color[0] = color[1] = color[2] = 0.8f; color[3] = 0.0f;
	glColor4fv(color);
	//上記の2D描画範囲の指定値より大きめに白背景を描画する
	expand = 100;
	//白背景を"先に"描画する
	glBegin(GL_TRIANGLES);//久しぶり
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
	//2D描画終了
	End2D();
		
	//行列を退避させる
	glPushMatrix();
	//行列を単位行列にする
	glLoadIdentity();
	glViewport(BACKMIRROR_VIEW_AREA);
	//カメラのパラメータを作成する
//	CVector e, c, u;//視点、注視点、上方向
	e = CVector(0.0f, 17.0f + 13.0f, 40.0f - 41.0f) * CMatrix().RotateY(mCamY)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY)
		* mPlayer->mMatrixTranslate;
	c = mPlayer->mPosition + CVector(0.0f, 17.0f + 12.8f, 40.0f - 42.0f)* mPlayer->mMatrixScale
		* CMatrix().RotateY(mPlayer->mRotation.mY);
	u = CVector(0.0f, 1.0f, 0.0f);
	//カメラののX座標を反転させる	
	e = e * CMatrix().Scale(-1.0f, 1.0f, 1.0f);
	c = c * CMatrix().Scale(-1.0f, 1.0f, 1.0f);
	u = u * CMatrix().Scale(-1.0f, 1.0f, 1.0f);
	//バックミラーのカメラの設定
	gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);	
	GLfloat translate[] = {
		-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	glMultMatrixf(translate);
	CTaskManager::Get()->Render();

	//黒枠の見切れの補完
	glViewport(BACKMIRROR_EXTRAFRAME_AREA);
	//2D描画開始
	Start2D(0, SCREENSIZE_X, 0, SCREENSIZE_Y);
	color[0] = color[1] = color[2] = 0.0f;
	glColor4fv(color);
	//上記の2D描画範囲の指定値より大きめに白背景を描画する
	expand = 100;
	//風景の上に黒枠を描画する
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
	//2D描画終了
	End2D();

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, SCREENSIZE_X, SCREENSIZE_Y); //画面の描画エリアをメインの画面に戻す
	glEnable(GL_CULL_FACE);//表面のみの描画に戻す

	//行列を戻す
	glPopMatrix();
}
//次のシーンの取得
CScene::EScene CSceneRace::GetNextScene(){
	return mScene;
}