#include "CSceneRaceB.h"
#include "CSceneTitle.h"
#include "CObj.h"

void CSceneRaceB::Init() {
	//親クラスの初期化処理を呼ぶ
	CSceneRace::Init();

	/* 敵車の準備 */
	if (CSceneTitle::mDifficulty == 1){//難易度：EASY
		CEnemy::mPointSize = 6;//ポイント数の設定
		CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
	}
	else if (CSceneTitle::mDifficulty == 2){//難易度：NORMAL
		//現在、仮の設定
		CEnemy::mPointSize = 12;//ポイント数の設定
		CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
		CEnemy::mPoint7 = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint8 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint9 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint10 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint11 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint12 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
	}
	else if (CSceneTitle::mDifficulty == 3){//難易度：HARD
		//現在、仮の設定
		CEnemy::mPointSize = 12;//ポイント数の設定
		CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
		CEnemy::mPoint7 = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint8 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint9 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint10 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint11 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint12 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
	}
	else{
		//隠しHARDの予定
	}
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
			mEnemys[i]->mpModel = &mCarWhite;
		}
		else if (i % 8 == 7){
			mEnemys[i]->mpModel = &mCarCyan;
		}

		//初期の配置座標を設定する
		mEnemys[i]->mPosition = CVector(CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY,
			CPlayer::mpPlayer->mPosition.mZ - 80.0f*i);
		if (i % 2 == 0){
			mEnemys[i]->mPosition.mX -= 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}

	/* ※透明度の高い物から先に描画する */
	//中間地点(順に通らないと1周したことにならないし、順番を飛ばしてもいけない)
	new CObj(&mCheckPoint, CVector(2893.0f, -100.0f, 2473.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 101);
	new CObj(&mCheckPoint, CVector(-1020.0f, -100.0f, 4594.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 102);
	new CObj(&mCheckPoint, CVector(-1277.0f, -100.0f, -448.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 103);
	//new CObj(&msumple2, CVector(320.0f, -58.0f, 450.0f), CVector(0.0f, 180.0f, 0.0f), CVector(4.0f, 3.0f, 3.0f), 1);
	new CObj(&mCource02Road, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f), 1);
	new CObj(&mCource02Wall, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f), 200);
	new CObj(&mCource02Jump, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f), 202);
	//ゴール地点
	//new CObj(&mMiniGoal, CVector(2222.0f, -1.0f, -2300.0f), CVector(0.0f, 0.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f), 99);
	new CObj(&mMiniGoal, CVector(2315.0f, -1.0f, -2300.0f), CVector(0.0f, 0.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f), 99);
	new CObj(&mMiniGoal, CVector(2107.0f, -1.0f - 0.05f, -2300.0f), CVector(0.0f, 180.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f), 99);
	//new CObj(&mCube, CVector(2216.0f, -1.0f, -2300.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 300.0f, 40.0f), 1);

	//シーンの設定
	mScene = ERACEB;

	return;
}

void CSceneRaceB::Update()
{
	CSceneRace::Update();

	//ゴール地点通過時の処理
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
			}
			isStartRace = false;
			isGoal = true;
			BGM.Stop();
			SoundGoal.Play();
			//CPlayer::mpPlayer->CanMove = false;//動きストップ
			CPlayer::mpPlayer->mChecks = 0;
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
				//プレイヤーの未ゴール時はプレイヤーの最終順位が落ちる
				if (isGoal == false){
					mRanking++;
				}
				mEnemys[i]->isEnemyGoaled = true;
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