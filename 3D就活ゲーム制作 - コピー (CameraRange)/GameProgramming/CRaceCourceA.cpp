#include "CRaceCourceA.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CObjCheckPoint.h"
#include "CObjNonCol.h"
#include "CObjBoost.h"
#include "CObjGrass.h"
#include "CObjJumper.h"
#include "CSceneTitle.h"

void CRaceCourceA::Init(){
	//シーンの設定
	mScene = ERACE1;

	CSceneRace::Init();
	
	//敵のポイント(目的地)の設定
	//if (CSceneTitle::mDifficulty == 1){//難易度：EASY
	//	CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 500.0f);
	//	CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 500.0f);
	//	CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 500.0f);
	//	CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 500.0f);
	//	CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 500.0f);
	//	CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 500.0f);
	//	CEnemy::mPoint7 = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 500.0f);
	//	CEnemy::mPoint8 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 500.0f);
	//	CEnemy::mPoint9 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 500.0f);
	//	CEnemy::mPoint10 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 500.0f);
	//	CEnemy::mPoint11 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 500.0f);
	//	CEnemy::mPoint12 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 500.0f);
	//}
	//else if (CSceneTitle::mDifficulty == 2){//難易度：NORMAL
	//	CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 500.0f);
	//	CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 500.0f);
	//	CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 500.0f);
	//	CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 500.0f);
	//	CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 500.0f);
	//	CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 500.0f);
	//	CEnemy::mPoint7 = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 500.0f);
	//	CEnemy::mPoint8 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 500.0f);
	//	CEnemy::mPoint9 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 500.0f);
	//	CEnemy::mPoint10 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 500.0f);
	//	CEnemy::mPoint11 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 500.0f);
	//	CEnemy::mPoint12 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 500.0f);
	//}
	//else if (CSceneTitle::mDifficulty == 3){//難易度：HARD
	//	CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 500.0f);
	//	CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 500.0f);
	//	CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 500.0f);
	//	CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 500.0f);
	//	CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 500.0f);
	//	CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 500.0f);
	//	CEnemy::mPoint7 = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 500.0f);
	//	CEnemy::mPoint8 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 500.0f);
	//	CEnemy::mPoint9 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 500.0f);
	//	CEnemy::mPoint10 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 500.0f);
	//	CEnemy::mPoint11 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 500.0f);
	//	CEnemy::mPoint12 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 500.0f);
	//}
	//else{
	//	//隠しHARDの予定
	//}
	//プレイヤーの生成
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//カメラの生成
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();

	//new CObjFloor(&mCource01, CVector(-360.0f, 5.0f - 33.0f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f));
	mpRoadManager = new CRoadManager(&mCource01, CVector(-360.0f, 5.0f - 33.0f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f), mPlayer->mPosition, CVector(0.0f, 0.0f, 1.0f));//

	//mCam->mpModel = &mCarYellow;
	//敵車の生成
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		mEnemys[i] = new CEnemy();
		if (i % 8 == 0){
			mEnemys[i]->mpModel = &mCarBlue;
		}
		else if (i % 8 == 1){
			mEnemys[i]->mpModel = &mCarPink;
		}
		else if (i % 8 == 2){
			mEnemys[i]->mpModel = &mCarRed;
		}
		else if (i % 8 == 3){
			mEnemys[i]->mpModel = &mCarGreen;
		}
		else if (i % 8 == 4){
			mEnemys[i]->mpModel = &mCarYellow;
		}
		else if (i % 8 == 5){
			mEnemys[i]->mpModel = &mCarBlack;
		}
		else if (i % 8 == 6){
			mEnemys[i]->mpModel = &mCarGray;
		}
		else if (i % 8 == 7){
			mEnemys[i]->mpModel = &mCarCyan;
		}
		//初期の配置座標を設定する
		mEnemys[i]->mPosition = CVector(350.0f, -13.538f, -130.0f - 80.0f*i);
		if (i % 2 == 0){
			mEnemys[i]->mPosition.mX -= 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}
	/*透明度の高い物から先に描画する*/
	//中間地点(順に通らないと1周したことにならないし、順番を飛ばしてもいけない)
	new CObjCheckPoint(&mCheckPoint, CVector(50.0f, 15.0f, 2500.0f), CVector(-90.0f, 0.0f, -50.0f), CVector(2000.0f, 31.0f, 255.0f), 1);
	new CObjCheckPoint(&mCheckPoint, CVector(-1800.0f, 15.0f, 20.0f), CVector(-90.0f, 180.0f, 0.0f), CVector(750.0f, 31.0f, 255.0f), 2);
	new CObjCheckPoint(&mCheckPoint, CVector(-1100.0f, 15.0f, -2000.0f), CVector(-90.0f, 0.0f, 110.0f), CVector(750.0f, 31.0f, 255.0f), 3);
	//新・コースの生成
	for (int i = 0; i < 1; i++){
		//コースの生成//ここを床と壁で分割して処理を分ける予定
//		new CObjFloor(&mCource01, CVector(-360.0f, 5.0f - 33.0f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f));
		//芝生の生成(通行中は速度低下)
		new CObjGrass(&mGrass01, CVector(-360.0f, 5.0f - 33.0f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f));
		//コースに柵の配置(壁扱い)
		new CObjFloor(&mFenceTop, CVector(-360.0f, -70.0f - 35.0f, 230.0f), CVector(), CVector(50.0f, 5.5f + 1.5f, 50.0f));
		new CObjWall(&mFenceSide, CVector(-360.0f, -70.0f - 35.0f, 230.0f), CVector(), CVector(50.0f, 5.5f + 1.5f, 50.0f));
		//道路と芝生の境目のタイルを生成(当たり判定無し)
		new CObjNonCol(&mRWTile, CVector(-360.0f, 5.0f - 33.0f + 0.05f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f));
	}
	//白・黒タイルでゴール示唆
	for (int i = 0; i < 40; i++){
		if (i % 2 == 0){
			new CObjNonCol(&mTileBlack, CVector(170.0f + 20.0f*i, -13.1f + 0.5f, -20.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.0f, 10.0f));//黒タイル
			new CObjNonCol(&mTileWhite, CVector(170.0f + 20.0f*i, -13.1f + 0.5f, -20.0f + 20.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.0f, 10.0f));//白タイル
		}
		else{
			new CObjNonCol(&mTileBlack, CVector(170.0f + 20.0f*i, -13.1f + 0.5f, -20.0f + 20.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.0f, 10.0f));//黒タイル
			new CObjNonCol(&mTileWhite, CVector(170.0f + 20.0f*i, -13.1f + 0.5f, -20.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.0f, 10.0f));//白タイル
		}
	}	
	
	//加速床
	//new CObj(&mDashBoard, CVector(260.0f, -13.1f + 3.0f, 800.0f), CVector(0.0f, 180.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f), 111);//保留
	new CObjBoost(&mDashBoard, CVector(234.0f, -13.1f + 3.0f, -980.0f), CVector(0.0f, 180.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));
	new CObjBoost(&mDashBoard, CVector(-1500.0f, -13.1f + 3.0f, -50.0f), CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	//ジャンプ台
	new CObjJumper(&mOnBlock, CVector(240.0f, -13.1f + 3.0f, 1110.0f), CVector(-30.0f, 0.0f, 0.0f), CVector(77.0f, 5.0f, 50.0f));


	//優先度変更
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}

	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		if (mEnemys[i]->mpModel==&mCarRed){
			printf("CPU%d RED\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarBlue){
			printf("CPU%d BLUE\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarBlack){
			printf("CPU%d BLACK\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarCyan){
			printf("CPU%d CYAN\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarGreen){
			printf("CPU%d GREEN\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarGray){
			printf("CPU%d GRAY\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarPink){
			printf("CPU%d PINK\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarWhite){
			printf("CPU%d WHITE\n", i + 1);
		}
		else if (mEnemys[i]->mpModel == &mCarYellow){
			printf("CPU%d YELLOW\n", i + 1);
		}
	}
	
}
void CRaceCourceA::Update(){
	CSceneRace::Update();
}