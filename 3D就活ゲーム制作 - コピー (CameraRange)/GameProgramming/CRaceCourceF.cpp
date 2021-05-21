#include "CRaceCourceF.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CObjCheckPoint.h"
#include "CObjNonCol.h"
#include "CSceneTitle.h"

void CRaceCourceF::Init(){
	//シーンの設定
	mScene = ERACE6;

	CSceneRace::Init();

	//敵のポイント(目的地)の設定
	if (CSceneTitle::mDifficulty == 1){//難易度：EASY
		CEnemy::mPoint = new CPoint(CVector(3217.0f, 140.0f, -325.0f), 200.0f);
		CEnemy::mPoint3 = new CPoint(CVector(4547.0f, 140.0f, -3971.0f), 200.0f);
		CEnemy::mPoint2 = new CPoint(CVector(4980.0f, 130.0f, -1621.0f), 200.0f);
		CEnemy::mPoint4 = new CPoint(CVector(3412.0f, 130.0f, -4695.0f), 200.0f);
		CEnemy::mPoint5 = new CPoint(CVector(1165.0f, 130.0f, -5113.0f), 200.0f);
		CEnemy::mPoint6 = new CPoint(CVector(-1155.0f, 130.0f, -4615.0f), 200.0f);
		CEnemy::mPoint7 = new CPoint(CVector(-2375.0f, 130.0f, -3717.0f), 200.0f);
		CEnemy::mPoint8 = new CPoint(CVector(-2595.0f, 130.0f, -1083.0f), 200.0f);
		CEnemy::mPoint9 = new CPoint(CVector(-2024.0f, 130.0f, -240.0f), 200.0f);
		CEnemy::mPoint10 = new CPoint(CVector(-350.0f, 130.0f, 828.0f), 200.0f);
		CEnemy::mPoint11 = new CPoint(CVector(2661.0f, 130.0f, 3852.0f), 200.0f);
		CEnemy::mPoint12 = new CPoint(CVector(1613.0f, 30.0f, 6410.0f), 100.0f);
		CEnemy::mPoint13 = new CPoint(CVector(851.5f, 30.0f, 6761.0f), 100.0f);
		CEnemy::mPoint14 = new CPoint(CVector(-275.0f, 30.0f, 7050.0f), 100.0f);
		CEnemy::mPoint15 = new CPoint(CVector(-3475.0f, 30.0f, 6773.0f), 100.0f);
		CEnemy::mPoint16 = new CPoint(CVector(-5192.0f, 30.0f, 5519.0f), 100.0f);
		CEnemy::mPoint17 = new CPoint(CVector(-6522.0f, 30.0f, 3027.0f), 100.0f);
		CEnemy::mPoint18 = new CPoint(CVector(-6177.0f, 30.0f, 1502.0f), 100.0f);
		CEnemy::mPoint19 = new CPoint(CVector(-4967.0f, 30.0f, 536.0f), 100.0f);
		CEnemy::mPoint20 = new CPoint(CVector(-2838.0f, 30.0f, 91.0f), 100.0f);
		CEnemy::mPoint21 = new CPoint(CVector(-1810.0f, 30.0f, 77.0f), 100.0f);
		CEnemy::mPoint22 = new CPoint(CVector(151.5f, 30.0f, 52.0f), 100.0f);
	}
	else if (CSceneTitle::mDifficulty == 2){//難易度：NORMAL
		CEnemy::mPoint = new CPoint(CVector(2767.0f, 140.0f, -137.0f), 100.0f);
		CEnemy::mPoint2 = new CPoint(CVector(3914.0f, 140.0f, -647.0f), 100.0f);
		CEnemy::mPoint3 = new CPoint(CVector(4923.0f, 130.0f, -1705.0f), 100.0f);
		CEnemy::mPoint4 = new CPoint(CVector(4547.0f, 140.0f, -3971.0f), 100.0f);
		CEnemy::mPoint5 = new CPoint(CVector(3436.0f, 130.0f, -4617.0f), 100.0f);
		CEnemy::mPoint6 = new CPoint(CVector(1165.0f, 130.0f, -5113.0f), 100.0f);
		CEnemy::mPoint7 = new CPoint(CVector(-1155.0f, 130.0f, -4615.0f), 100.0f);
		CEnemy::mPoint8 = new CPoint(CVector(-2375.0f, 130.0f, -3717.0f), 150.0f);
		CEnemy::mPoint9 = new CPoint(CVector(-2595.0f, 130.0f, -1083.0f), 150.0f);
		CEnemy::mPoint10 = new CPoint(CVector(-2024.0f, 130.0f, -240.0f), 150.0f);
		CEnemy::mPoint11 = new CPoint(CVector(-350.0f, 130.0f, 828.0f), 150.0f);
		CEnemy::mPoint12 = new CPoint(CVector(2661.0f, 30.0f - 100.0f, 3852.0f), 150.0f);
		CEnemy::mPoint13 = new CPoint(CVector(1546.0f, 30.0f - 100.0f, 6362.0f), 100.0f);
		CEnemy::mPoint14 = new CPoint(CVector(774.5f, 30.0f - 100.0f, 6741.0f), 100.0f);
		CEnemy::mPoint15 = new CPoint(CVector(-960.0f, 30.0f - 100.0f, 7108.0f), 100.0f);
		CEnemy::mPoint16 = new CPoint(CVector(-3475.0f, 30.0f - 100.0f, 6773.0f), 100.0f);
		CEnemy::mPoint17 = new CPoint(CVector(-5192.0f, 30.0f - 100.0f, 5519.0f), 100.0f);
		CEnemy::mPoint18 = new CPoint(CVector(-6522.0f, 30.0f - 100.0f, 3027.0f), 100.0f);
		CEnemy::mPoint19 = new CPoint(CVector(-6177.0f, 30.0f - 100.0f, 1502.0f), 100.0f);
		CEnemy::mPoint20 = new CPoint(CVector(-4967.0f, 30.0f - 100.0f, 536.0f), 100.0f);
		CEnemy::mPoint21 = new CPoint(CVector(-3355.0f, 30.0f - 100.0f, 91.0f), 100.0f);
		CEnemy::mPoint22 = new CPoint(CVector(-1810.0f, 30.0f - 100.0f, 77.0f), 100.0f);
		CEnemy::mPoint23 = new CPoint(CVector(151.5f, 30.0f - 100.0f, 52.0f), 100.0f);
	}
	else if (CSceneTitle::mDifficulty == 3){//難易度：HARD
		CEnemy::mPoint = new CPoint(CVector(3217.0f, 140.0f, -325.0f), 200.0f);
		CEnemy::mPoint3 = new CPoint(CVector(4547.0f, 140.0f, -3971.0f), 200.0f);
		CEnemy::mPoint2 = new CPoint(CVector(4980.0f, 130.0f, -1621.0f), 200.0f);
		CEnemy::mPoint4 = new CPoint(CVector(3412.0f, 130.0f, -4695.0f), 200.0f);
		CEnemy::mPoint5 = new CPoint(CVector(1165.0f, 130.0f, -5113.0f), 200.0f);
		CEnemy::mPoint6 = new CPoint(CVector(-1155.0f, 130.0f, -4615.0f), 200.0f);
		CEnemy::mPoint7 = new CPoint(CVector(-2375.0f, 130.0f, -3717.0f), 200.0f);
		CEnemy::mPoint8 = new CPoint(CVector(-2595.0f, 130.0f, -1083.0f), 200.0f);
		CEnemy::mPoint9 = new CPoint(CVector(-2024.0f, 130.0f, -240.0f), 200.0f);
		CEnemy::mPoint10 = new CPoint(CVector(-350.0f, 130.0f, 828.0f), 200.0f);
		CEnemy::mPoint11 = new CPoint(CVector(2661.0f, 130.0f, 3852.0f), 200.0f);
		CEnemy::mPoint12 = new CPoint(CVector(1613.0f, 30.0f, 6410.0f), 100.0f);
		CEnemy::mPoint13 = new CPoint(CVector(851.5f, 30.0f, 6761.0f), 100.0f);
		CEnemy::mPoint14 = new CPoint(CVector(-275.0f, 30.0f, 7050.0f), 100.0f);
		CEnemy::mPoint15 = new CPoint(CVector(-3475.0f, 30.0f, 6773.0f), 100.0f);
		CEnemy::mPoint16 = new CPoint(CVector(-5192.0f, 30.0f, 5519.0f), 100.0f);
		CEnemy::mPoint17 = new CPoint(CVector(-6522.0f, 30.0f, 3027.0f), 100.0f);
		CEnemy::mPoint18 = new CPoint(CVector(-6177.0f, 30.0f, 1502.0f), 100.0f);
		CEnemy::mPoint19 = new CPoint(CVector(-4967.0f, 30.0f, 536.0f), 100.0f);
		CEnemy::mPoint20 = new CPoint(CVector(-2838.0f, 30.0f, 91.0f), 100.0f);
		CEnemy::mPoint21 = new CPoint(CVector(-1810.0f, 30.0f, 77.0f), 100.0f);
		CEnemy::mPoint22 = new CPoint(CVector(151.5f, 30.0f, 52.0f), 100.0f);
	}
	else{
		//VERYHARD
	}
	//プレイヤーの生成
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//カメラの生成
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();
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
		//初期配置座標を設定する
		mEnemys[i]->mPosition = CVector(0.0f - 30.0f - 80.0f*i, -13.538f, 0.0f);
		mEnemys[i]->mRotation.mY = 90.0f;
		if (i % 2 == 0){
			mEnemys[i]->mPosition.mZ += 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}

	printf("開発中\n");
	//中間地点(順に通らないと1周したことにならないし、順番を飛ばしてもいけない)
	new CObjCheckPoint(&mCheckPoint, CVector(1127.4f, -100.0f, -5054.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 1);
	new CObjCheckPoint(&mCheckPoint, CVector(777.0f, -100.0f, 1925.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 2);
	new CObjCheckPoint(&mCheckPoint, CVector(-5861.0f, -300.0f, 1165.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 3);
	//ゴール地点
	new CObjNonCol(&mMiniGoal, CVector(140.0f, -159.0f, 90.0f - 30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(5.1f, 10.0f, 5.1f));

	//優先度変更
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}
}
void CRaceCourceF::Update(){
	CSceneRace::Update();

}