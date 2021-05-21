#include "CRaceCourceE.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CObjCheckPoint.h"
#include "CObjNonCol.h"
#include "CObjGrass.h"
#include "CObjJumper.h"
#include "CSceneTitle.h"

void CRaceCourceE::Init(){
	//シーンの設定
	mScene = ERACE5;

	CSceneRace::Init();

	//敵の目標地点の生成
	CEnemy::mPoint = new CPoint(CVector(-5492.0f, 130.0f, 13030.0f), 100.0f);
	CEnemy::mPoint2 = new CPoint(CVector(-4879.0f, 500.0f, 11355.0f), 100.0f);
	CEnemy::mPoint3 = new CPoint(CVector(-4254.0f, 555.0f, 10627.0f), 100.0f);
	CEnemy::mPoint4 = new CPoint(CVector(-4156.0f, 675.0f, 10020.0f), 100.0f);
	CEnemy::mPoint5 = new CPoint(CVector(-4640.0f, 900.0f, 9125.0f), 100.0f);
	CEnemy::mPoint6 = new CPoint(CVector(-5666.0f, 1050.0f, 8679.0f), 100.0f);
	CEnemy::mPoint7 = new CPoint(CVector(-7207.0f, 1320.0f, 8818.0f), 100.0f);
	CEnemy::mPoint8 = new CPoint(CVector(-7943.0f, 1421.0f, 9162.0f), 100.0f);
	CEnemy::mPoint9 = new CPoint(CVector(-8595.0f, 1570.0f, 9218.0f), 100.0f);
	CEnemy::mPoint10 = new CPoint(CVector(-9434.0f, 1850.0f, 8411.0f), 100.0f);//	
	CEnemy::mPoint11 = new CPoint(CVector(-9640.0f, 2148.0f, 7427.0f), 100.0f);//
	CEnemy::mPoint12 = new CPoint(CVector(-9377.0f, 2233.0f, 6699.0f), 100.0f);//
	CEnemy::mPoint13 = new CPoint(CVector(-7355.0f, 2075.0f, 6084.0f), 100.0f);//
	CEnemy::mPoint14 = new CPoint(CVector(-6883.0f, 2161.0f, 5038.0f), 100.0f);//
	CEnemy::mPoint15 = new CPoint(CVector(-7272.0f, 2312.0f, 4513.0f), 100.0f);
	CEnemy::mPoint16 = new CPoint(CVector(-7810.0f, 2425.0f, 4349.0f), 100.0f);
	CEnemy::mPoint17 = new CPoint(CVector(-9549.0f, 2700.0f, 4348.0f), 100.0f);
	CEnemy::mPoint18 = new CPoint(CVector(-13393.0f, 3333.0f, 3628.0f), 100.0f);
	CEnemy::mPoint19 = new CPoint(CVector(-14827.0f, 3966.0f, 1878.0f), 100.0f);
	CEnemy::mPoint20 = new CPoint(CVector(-15975.0f, 4870.0f, -1342.0f), 100.0f);
	CEnemy::mPoint21 = new CPoint(CVector(-16072.0f, 4970.0f, -3791.0f), 100.0f);
	CEnemy::mPoint22 = new CPoint(CVector(-14540.0f, 4960.0f, -5115.0f), 100.0f);
	CEnemy::mPoint23 = new CPoint(CVector(-13104.0f, 4671.0f, -5555.0f), 100.0f);
	CEnemy::mPoint24 = new CPoint(CVector(-9216.0f, 3625.0f, -6044.0f), 100.0f);
	CEnemy::mPoint25 = new CPoint(CVector(-6842.0f, 2983.0f, -5783.0f), 100.0f);
	CEnemy::mPoint26 = new CPoint(CVector(-4360.0f, 2420.0f, -4840.0f), 100.0f);
	CEnemy::mPoint27 = new CPoint(CVector(-1279.0f, 1575.0f, -2653.0f), 100.0f);
	CEnemy::mPoint28 = new CPoint(CVector(1002.5f, 955.0f, -645.0f), 100.0f);
	CEnemy::mPoint29 = new CPoint(CVector(2091.5f, 584.0f, 897.0f), 100.0f);
	CEnemy::mPoint30 = new CPoint(CVector(2494.5f, 500.0f, 1206.0f), 100.0f);
	CEnemy::mPoint31 = new CPoint(CVector(2925.5f, 375.0f, 955.0f), 100.0f);
	CEnemy::mPoint32 = new CPoint(CVector(7484.0f, 64.0f, -6189.0f), 100.0f);//
	CEnemy::mPoint33 = new CPoint(CVector(8055.0f, 64.0f, -6644.0f), 100.0f);//
	CEnemy::mPoint34 = new CPoint(CVector(10123.0f, 64.0f, -7222.0f), 100.0f);
	CEnemy::mPoint35 = new CPoint(CVector(12680.0f, 64.0f, -6967.0f), 100.0f);
	CEnemy::mPoint36 = new CPoint(CVector(14829.0f, 64.0f, -2543.0f), 100.0f);
	CEnemy::mPoint37 = new CPoint(CVector(15461.0f, 64.0f, 165.0f), 100.0f);
	CEnemy::mPoint38 = new CPoint(CVector(14424.0f, 64.0f, 6273.0f), 100.0f);
	CEnemy::mPoint39 = new CPoint(CVector(13473.0f, 64.0f, 8125.0f), 100.0f);
	CEnemy::mPoint40 = new CPoint(CVector(12230.0f, 64.0f, 8710.0f), 100.0f);
	CEnemy::mPoint41 = new CPoint(CVector(10595.0f, 64.0f, 8612.0f), 120.0f);
	CEnemy::mPoint42 = new CPoint(CVector(9990.0f, 64.0f, 7720.0f), 120.0f);
	CEnemy::mPoint43 = new CPoint(CVector(9530.0f, 64.0f, 7065.0f), 120.0f);
	CEnemy::mPoint44 = new CPoint(CVector(8371.0f, 64.0f, 7235.0f), 140.0f);
	CEnemy::mPoint45 = new CPoint(CVector(7260.0f, 64.0f, 8450.0f), 100.0f);
	CEnemy::mPoint46 = new CPoint(CVector(6830.0f, 64.0f, 10230.0f), 100.0f);
	CEnemy::mPoint47 = new CPoint(CVector(6945.0f, 64.0f, 13182.0f), 100.0f);
	CEnemy::mPoint48 = new CPoint(CVector(6410.0f, 64.0f, 15188.0f), 100.0f);
	CEnemy::mPoint49 = new CPoint(CVector(5310.0f, 64.0f, 17000.0f), 100.0f);
	CEnemy::mPoint50 = new CPoint(CVector(4095.0f, 64.0f, 18200.0f), 100.0f);
	CEnemy::mPoint51 = new CPoint(CVector(2191.0f, 64.0f, 18783.0f), 100.0f);
	CEnemy::mPoint52 = new CPoint(CVector(-244.0f, 64.0f, 18457.0f), 100.0f);
	CEnemy::mPoint53 = new CPoint(CVector(-2086.0f, 64.0f, 17555.0f), 100.0f);
	CEnemy::mPoint54 = new CPoint(CVector(-3543.0f, 64.0f, 16338.0f), 100.0f);	
	//プレイヤーの生成
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//カメラの生成
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();
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
		////初期の配置座標を設定する
		////mStartPoint[0] = 0.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = 0.0f;
		////mStartRotation = 90.0f;
		//mEnemys[i]->mPosition = CVector(0.0f - 30.0f - 80.0f*i, -13.538f, 0.0f);
		//mEnemys[i]->mRotation.mY = 90.0f;

		//mStartPoint[0] = -3884.5f;  mStartPoint[1] = 13.5f;  mStartPoint[2] = 15952.5f;
		//mStartRotation = -145.0f;
		mEnemys[i]->mPosition = CVector(-3884.5f+50.0f - 60.0f*i, 13.5f, 15952.5f - 100.0f*i);
		mEnemys[i]->mRotation.mY = -145.0f;

		if (i % 2 == 0){
			mEnemys[i]->mPosition.mZ += 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}

	//中間地点(順に通らないと1周したことにならないし、順番を飛ばしてもいけない)
	new CObjCheckPoint(&mCheckPoint, CVector(-16054.4f, 4915.0f, -2180.0f), CVector(0.0f, 0.0f, 0.0f), CVector(180.0f, 100.0f, 180.0f), 1);
	new CObjCheckPoint(&mCheckPoint, CVector(4680.0f, 13.5f, -2027.0f), CVector(0.0f, 0.0f, 0.0f), CVector(200.0f, 100.0f, 200.0f), 2);
	new CObjCheckPoint(&mCheckPoint, CVector(14809.0f, 13.5f, 4270.0f), CVector(0.0f, 0.0f, 0.0f), CVector(200.0f, 100.0f, 200.0f), 3);
	//ゴール地点
	new CObjCheckPoint(&mCheckPoint, CVector(-3862.5f, 21.3f, 15925.5f), CVector(0.0f, 0.0f - 145.3f, 0.0f), CVector(240.0f, 100.0f, 30.0f), 9);
	new CObjNonCol(&mCource05GoalTile, CVector(-3862.5f, 21.3f, 15925.5f), CVector(0.0f, -145.3f, 0.0f), CVector(3.9f, 3.9f, 3.9f));


	
	//コース全体のサイズ感を設定
	float mtsize = 35.0f;
	float height = 11.0f;
	new CObjFloor(&mCource05Road, CVector(0.0f, 21.0f, 0.0f), CVector(), CVector(mtsize, height, mtsize));//
	new CObjWall(&mCource05Wall, CVector(0.0f, 21.0f, 0.0f), CVector(), CVector(mtsize, height, mtsize));//
	new CObjGrass(&mCource05Mountain, CVector(0.0f, 21.0f, 0.0f), CVector(), CVector(mtsize, height, mtsize));//
	new CObjGrass(&mCource05Grass_Floor, CVector(0.0f, 20.0f, 0.0f), CVector(), CVector(mtsize, 30.0f, mtsize));
	new CObjWall(&mCource05Grass_Wall, CVector(0.0f, 20.0f, 0.0f), CVector(), CVector(mtsize, 30.0f, mtsize));
	new CObjNonCol(&mCource05Lake, CVector(0.0f, 221.0f, 0.0f), CVector(), CVector(mtsize, 30.0f, mtsize));//湖は当たり判定無し

	new CObjNonCol(&mSign_Left, CVector(2440.0f, 321.0f, 1432.0f), CVector(0.0f, 33.0f, 0.0f), CVector(4.0f, 4.0f, 4.0f));//標識：左折
	new CObjNonCol(&mSign_Right, CVector(13277.0f, 12.0f, -6939.0f), CVector(0.0f, 82.3f, 0.0f), CVector(4.0f, 4.0f, 4.0f));//標識：右折

	//ジャンプ台
	new CObjJumper(&mOnBlock, CVector(9911.0f, -13.1f + 33.0f, 8264.0f), CVector(-30.0f, -114.0f, 0.0f), CVector(77.0f, 5.0f, 50.0f));

	//優先度変更
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}
}
void CRaceCourceE::Update(){
	CSceneRace::Update();

}