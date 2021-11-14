#include "CRaceCourceC.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CRoadManager.h"
#include "CObjCheckPoint.h"
#include "CObjNonCol.h"
#include "CSceneTitle.h"

void CRaceCourceC::Init(){
	//シーンの設定
	mScene = ERACE3;

	CSceneRace::Init();

	//プレイヤーの生成
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//プレイヤーのリスポーンするCheckPointの設定
	mPlayer->SetRespawnPoint(0, CVector(0.0f, -13.538f, 80.0f), CVector(0.0f, 90.0f, 0.0f));
	mPlayer->SetRespawnPoint(1, CVector(1127.4f, 87.5f, -5054.0f), CVector(0.0f, -59.0f, 0.0f));
	mPlayer->SetRespawnPoint(2, CVector(777.0f, -13.538f, 1925.0f), CVector(0.0f, 405.1f, 0.0f));
	mPlayer->SetRespawnPoint(3, CVector(-5861.0f, -13.538f, 1165.0f), CVector(0.0f, -583.5, 0.0f));
	mPlayer->GetReady();
	//カメラの生成
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();
	//コース全体のサイズ感を設定
	float size = 40.0f;
	float height = 20.0f;
	//コースの生成
	new CRoadManager(&mCource03Road, CVector(0.0f, 5.0f - 373.0f, -350.0f), CVector(), CVector(size, height, size), mPlayer->mPosition, CVector(0.0f, 0.0f, -1.0f), 120.0f, 0.0f);
	//new CObjFloor(&mCource03Road, CVector(0.0f, 5.0f - 373.0f, -350.0f), CVector(), CVector(40.0f, 20.0f, 40.0f));
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
		mEnemys[i]->mPosition = CVector(-30.0f - 80.0f*i, -13.538f, 0.0f);
		mEnemys[i]->mRotation.mY = 90.0f;
		if (i % 2 == 0){
			mEnemys[i]->mPosition.mZ += 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}

	//中間地点(順に通らないと1周したことにならないし、順番を飛ばしてもいけない)
	new CObjCheckPoint(&mCheckPoint, CVector(1127.4f, -100.0f, -5054.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 1);
	new CObjCheckPoint(&mCheckPoint, CVector(777.0f, -100.0f, 1925.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 2);
	new CObjCheckPoint(&mCheckPoint, CVector(-5861.0f, -300.0f, 1165.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 3);
	//ゴール地点
	new CObjCheckPoint(&mCheckPoint, CVector(140.0f, -300.0f, 0.0f), CVector(), CVector(30.0f, 300.0f, 222.0f), 9);

	
	new CObjWall(&mCource03Wall, CVector(0.0f, 5.0f - 373.0f, -350.0f), CVector(), CVector(40.0f, 20.0f, 40.0f));
	new CObjWall(&mCource03Fence, CVector(0.0f, 5.0f - 373.0f, -350.0f), CVector(), CVector(40.0f, 20.0f, 40.0f));
	//ゴール地点
	new CObjNonCol(&mMiniGoal, CVector(140.0f, -159.0f, 90.0f-30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(5.1f, 10.0f, 5.1f));

	//優先度変更
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}
}
void CRaceCourceC::Update(){
	CSceneRace::Update();

}