#include "CSceneGameStage2.h"
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

extern CSound BGM;

CSceneGameStage2::~CSceneGameStage2() {
	CTaskManager::Get()->Disabled();

	CTaskManager::Get()->Delete();
}


void CSceneGameStage2::Init() {
	//シーンの設定
	mScene = ESTAGE2;

	//的の残数の初期化
	CItem::mTargetAmount = 0;

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//背景の読み込み
	mSky.Load("sky.obj", "sky.mtl");
	//岩の読み込み
	mRock.Load("Rock1.obj", "Rock1.mtl");
	//車の読み込み
	mRover.Load("untitled.obj", "cube.mtl");
	//立方体の読み込み
	mCube.Load("cube.obj", "material\\cube.mtl");
	//地面の読み込み
	mPlane.Load("plane.obj", "plane.mtl");

	mItem.Load("Rock1.obj", "Rock1.mtl");
	//銃の読み込み
	mItemGun.Load("銃.obj", "Rover1.mtl");
	mSpring.Load("ばね伸び.obj", "cube.mtl");

	mCube2.Load("cube.obj", "cube2.mtl");
	mCube3.Load("cube.obj", "cube3.mtl");

	mGrass.Load("cube.obj", "material\\grass.mtl");
	mSoil.Load("cube.obj", "material\\soil.mtl");

	mWater.Load("cube.obj", "material\\clearwater.mtl");

	mBridge.Load("cube.obj", "material\\bridge.mtl");

	mInvWall.Load("cube.obj", "cube2.mtl");

	mRoof.Load("cube.obj", "material\\roof.mtl");
	mHouseWall.Load("cube.obj", "material\\housewall.mtl");
	mDoor.Load("cube.obj", "material\\door.mtl");
	mKey.Load("cube.obj", "material\\key.mtl");
	mWindow.Load("cube.obj", "material\\window.mtl");

	

	//ボートの読み込み
	mBoat.Load("ふね.obj", "cube.mtl");

	//ステージ2BGMの読み込み
	BGM.Load("BGM\\game_maoudamashii_4_field02.wav");

	////透明な奴を先に描画する？
	//new CObj(&mInvWall, CVector(0.0f, 6.1f, 57.0f-14.4f), CVector(0.0f, 0.0f, 0.0f), CVector(14.5f, 1.1f, 31.8f-13.6f), 1);//橋の当たり判定、透明度100%

	//new CObj(&mInvWall, CVector(0.0f, 6.1f, 57.0f - 242.4f), CVector(0.0f, 0.0f, 0.0f), CVector(14.5f, 1.1f, 31.8f - 13.6f), 1);//橋判定、透明度100%、かなり手前の方
	//new CObj(&mInvWall, CVector(2.0f, 4.0f, -213.0f), CVector(0.0f, 0.0f, 0.0f), CVector(15.0f, 2.5f, 6.5f), 1);//ボートの当たり判定
	//
	////new CObj(&mCube3, CVector(-73.0f, 5.0f, 100.0f), CVector(0.0f, 0.0f, 0.0f), CVector(30.0f, 45.0f, 1.0f), 9);

	//new CObj(&mWindow, CVector(27.0f, 16.0f, 320.1f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 8.0f, 1.0f), 0);//窓、透明度30%

	//new CObj(&mWater, CVector(0.0f, -4.0f, -57.0f), CVector(0.0f, 0.0f, 0.0f), CVector(199.9f, 1.0f, 320.0f), 20);//川

	mPlayer = new CPlayer();
	mPlayer->mpModel = &mRover;

	//岩の生成　モデルmRock　位置|-20.0 0.0 20.0|
	//回転|0.0 0.0 0.0|　拡大|5.0 5.0 5.0|
//	new CRock(&mRock, CVector(-20.0f, 0.0f, 20.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//岩の生成　モデルmRock　位置|-20.0 0.0 20.0|
	//回転|0.0 0.0 0.0|　拡大|5.0 5.0 5.0|
//	new CRock(&mRock, CVector(20.0f, 0.0f, 40.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//立方体の生成
	//	new CObj(&mCube, CVector(0.0f, 0.0f, 60.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 10.0f, 1.0f), 1);
	////地面の生成
	//new CObj(&mPlane, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(200.0f, 1.0f, 200.0f), 1);
	/*for (int i = 0; i < 30; i++){
		new CObj(&mWater, CVector(0.0f, 40.0f, 0.0f + i), CVector(i * 3, i * 3, i * 3), CVector(5.0f, 5.0f, 1.0f), 1);
	}*/

//	//水の生成
////	new CObj(&mWater, CVector(0.0f, -35.0f, 0.0f), CVector(), CVector(199.8f, 16.0f, 25.0f), 20);
//	//草原・土の生成
////	new CObj(&mGrass, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(200.0f, 1.0f, 200.0f), 1);
//	//new CObj(&mGrass, CVector(0.0f, 3.0f, 284.0f), CVector(), CVector(200.0f, 1.5f, 200.0f), 1);
//	new CObj(&mGrass, CVector(0.0f, 3.0f, -70.0f), CVector(), CVector(200.0f, 1.5f, 100.0f), 1);
//	//new CObj(&mSoil, CVector(0.0f, -35.0f, 284.0f), CVector(), CVector(200.0f, 19.0f, 200.0f), 1);
//	new CObj(&mSoil, CVector(0.0f, -35.0f, -70.0f), CVector(), CVector(200.0f, 19.0f, 100.0f), 1);
//
//	new CObj(&mGrass, CVector(0.0f, 3.0f, 334.0f), CVector(), CVector(200.0f, 1.5f, 100.0f), 1);
//	new CObj(&mSoil, CVector(0.0f, -35.0f, 334.0f), CVector(), CVector(200.0f, 19.0f, 100.0f), 1);
//
//
//
//	//for (int i = 0; i < 3; i++){
//	//	for (int j = 0; j < 3; j++){
//	//		for (int k = 0; k < 3; k++){
//	//			if ((i == 1 && j == 1) || (j == 1 && k == 1) || (k == 1 && i == 1) || (k == 2 && j != 1)) {
//	//			}
//	//			else{
//	//				new CObj(&mCube, CVector(-20.0f + 20.0f * i, 0.0f + 20.0f * k - 2.0f, 80.0f + 20.0f * j), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 10.0f, 10.0f), 1);
//	//			}
//	//		}
//	//	}
//	//}
//
//	//new CObj(&mCube, CVector(0.0f, 60.0f, 100.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 10.0f, 10.0f), 1);
//	//new CItem(&mItemGun, CVector(0.0f, 80.0f, 100.0f), CVector(), CVector(2.0f, 2.0f, 2.0f), 4);//銃
//	//for (int i = 0; i < 5; i++){
//	//	new CItem(&mItem, CVector(-10.0f + i * 7.5f, 93.0f, 150.0f), CVector(), CVector(2.1f, 2.1f, 2.1), 1);//ごみ
//	//}
//
//
//
////	new CItem(&mItem, CVector(43.0f, 111.0f, 118.0f), CVector(), CVector(2.0f, 2.0f, 2.0f), 3);//スクリュー
//
//	for (int l = 0; l < 5; l++){
//		new CObj(&mBridge, CVector(0.0f, 6.1f, 28.0f + l * 7.2f), CVector(0.0f, 0.0f, 0.0f), CVector(14.0f, 1.0f, 3.3f), 20);//橋
//	}
//	//new CObj(&mCube, CVector(0.0f, -26.0f, 5.0f), CVector(-25.0f, 0.0f, 0.0f), CVector(15.0f, 16.0f, 36.0f), 1);
//
//	new CItem(&mSpring, CVector(0.0f, 10.0f, 40.0f), CVector(), CVector(5.0f, 5.0f, 5.0f), 2);//バネ
//
////	new CItem(&mBoat, CVector(30.0f, 7.0f, 30.0f), CVector(), CVector(3.0f, 3.0f, 3.0f), 1);//ボート
//	
//
//	//new CObj(&mCube, CVector(30.0f, 0.0f, 30.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 2.0f, 10.0f), 2);
//
//	//家の作成
//	new CObj(&mRoof, CVector(-6.4f, 54.4f, 346.1f), CVector(0.0f, 0.0f, 30.0f), CVector(23.5f, 2.0f, 33.3f), 0);////屋根
//	new CObj(&mRoof, CVector(30.4f, 54.4f, 346.1f), CVector(0.0f, 0.0f, -30.0f), CVector(23.5f, 2.0f, 33.3f), 0);////屋根
//
//	new CObj(&mHouseWall, CVector(12.0f, 5.1f, 346.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 0.5f, 25.0f), 20);//家の床
//
//	//new CObj(&mHouseWall, CVector(27.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(20.0f, 20.0f, 2.0f), 0);//手前側の壁
//	
//	new CObj(&mHouseWall, CVector(42.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(5.0f, 13.0f, 2.0f), 0);//手前・窓付近左
//	new CObj(&mHouseWall, CVector(12.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(5.0f, 13.0f, 2.0f), 0);//手前・窓付近右
//	new CObj(&mHouseWall, CVector(27.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 5.0f, 2.0f), 0);//手前・窓付近下
//
//	new CObj(&mHouseWall, CVector(-15.5f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(7.5f, 13.0f, 2.0f), 0);//手前側の壁
//	new CObj(&mHouseWall, CVector(12.0f, 32.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 8.1f, 2.0f), 0);//手前・扉の上くらいの壁
//
//	//new CObj(&mHouseWall, CVector(12.0f, 6.0f, 321.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 20.0f, 2.0f), 0);//手前側の壁
//	new CObj(&mHouseWall, CVector(20.0f, 43.5f, 321.1f), CVector(0.0f, 0.0f, -30.0f), CVector(21.0f, 8.0f, 2.0f), 0);////手前側
//	new CObj(&mHouseWall, CVector(4.0f, 43.5f, 321.1f), CVector(0.0f, 0.0f, 30.0f), CVector(21.0f, 8.0f, 2.0f), 0);////手前側
//
//	new CObj(&mHouseWall, CVector(12.0f, 6.0f, 371.1f), CVector(0.0f, 0.0f, 0.0f), CVector(35.0f, 20.0f, 2.0f), 0);//後ろ側の壁
//	new CObj(&mHouseWall, CVector(19.0f, 41.5f, 371.1f), CVector(0.0f, 0.0f, -30.0f), CVector(20.0f, 10.0f, 2.0f), 0);////後ろ側
//	new CObj(&mHouseWall, CVector(5.0f, 41.5f, 371.1f), CVector(0.0f, 0.0f, 30.0f), CVector(20.0f, 10.0f, 2.0f), 0);////後ろ側
//	new CObj(&mHouseWall, CVector(-21.0f, 6.0f, 346.1f), CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 20.0f, 25.0f), 0);//右壁
//	new CObj(&mHouseWall, CVector(45.0f, 6.0f, 346.1f), CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 20.0f, 25.0f), 0);//左壁
//	new CObj(&mDoor, CVector(-0.5f, 6.0f, 320.0f), CVector(0.0f, 0.0f, 0.0f), CVector(7.5f, 13.0f, 1.0f), 22);//扉
//	new CItem(&mKey, CVector(38.0f, 60.0f, 321.0f), CVector(), CVector(2.5f, 2.5f, 2.5f), 5);//鍵
//
//	new CObj(&mBridge, CVector(-11.0f, 6.0f, 394.0f), CVector(0.0f, 0.0f, 0.0f), CVector(11.0f, 11.0f, 11.0f), 0);//木箱(？)
//
//
//	new CObj(&mCube, CVector(100.0f, 0.0f, 80.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 21);//川を流れる物体
//	new CObj(&mCube, CVector(-100.0f, 0.0f, 80.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 21);//川を流れる物体
//
//	//new CObj(&mCube, CVector(-100.0f, 15.0f, 62.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//水車？？？
//	//new CObj(&mCube, CVector(0.0f, 15.0f, 62.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//水車？？？
//	//new CObj(&mCube, CVector(100.0f, 15.0f, 62.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//水車？？？
//
//	new CObj(&mCube, CVector(100.0f, 15.0f, 117.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 0);//水車？？？
//	for (int i = 0; i < 7; i++){
//		new CObj(&mCube, CVector(70.0f-30.0*i, 30.0f+ 15.0f *i, 117.0f), CVector(0.0f + 90.0f*i , 0.0f, 0.0f), CVector(10.0f, 1.5f, 10.0f), 25);//水車？？？
//	}
//	new CObj(&mCube, CVector(100.0f - 245.0f, 15.0f + 105.0f, 157.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.5f, 50.0f), 0);//ぐるぐるの先の足場
//
//	for (int l = 0; l < 5; l++){
//		new CObj(&mBridge, CVector(0.0f, 6.1f, -200.0f + l * 7.2f), CVector(0.0f, 0.0f, 0.0f), CVector(14.0f, 1.0f, 3.3f), 20);//橋
//	}
//	new CItem(&mBoat, CVector(0.0f, 6.0f, -213.0f), CVector(0.0f, 0.0f, 0.0f), CVector(2.5f, 2.5f, 2.5f), 0);//ボート…このステージでは使えない


	mCamY = 0.0f;
	mPutCol = false;

	//TaskManager.ChangePriority(&mPlayer, 15);
	CTaskManager::Get()->ChangePriority(mPlayer, 15);

	//CPlayer::mpPlayer->mPosition.mX = 0.0f; CPlayer::mpPlayer->mPosition.mY = 21.3f; CPlayer::mpPlayer->mPosition.mZ = -189.2f;
	
	////ステージ2音楽をループ再生する
	BGM.Repeat();
}


void CSceneGameStage2::Update() {
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(-2.0f, 17.0f, -40.0f) * CMatrix().RotateY(mCamY + 90) * mPlayer->mMatrix;
	//注視点を求める
	c = mPlayer->mPosition;
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer->mMatrixRotate;

	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//背景の描画
//	mSky.Render();

	////タスクマネージャの更新
	//TaskManager.Update();
	////タスクマネージャの描画
	//TaskManager.Render();

	//タスクマネージャの更新・描画
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Render();


	////岩の描画
	//mRock.Render(CMatrix().Scale(5.0f, 5.0f, 5.0f));
	////車の描画
	//mRover.Render(CMatrix().Translate(-20.0f, 0.0f, 10.0f));

	//あ゛
	//コリジョンマネージャの衝突処理
	CollisionManager.Collision();
	//TaskManager.Delete();
	CTaskManager::Get()->Delete();


	//デバッグ用
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
		//衝突判定の描画
		CollisionManager.Render();
	}
#endif


	//2D描画開始
	Start2D(0, 800, 0, 600);

	

	if ((CPlayer::mpPlayer->mPosition.mX > -21.0f && CPlayer::mpPlayer->mPosition.mX < 45.0f)
		&& (CPlayer::mpPlayer->mPosition.mY > 5.9f +13.0f && CPlayer::mpPlayer->mPosition.mY < 46.1f +13.0f)
		&& (CPlayer::mpPlayer->mPosition.mZ > 321.1f && CPlayer::mpPlayer->mPosition.mZ < 371.1f)){
		CText::DrawString("STAGE CLEAR !", 300, 300, 10, 12);
	}
	
	CText::DrawString("STAGE 2", 20, 20, 10, 12);

	//2D描画終了
	End2D();


	//if (CKey::Push('Q')){//でば
	//	mCamY += 1.0f;
	//}
	//if (CKey::Push('E')){//つぐ
	//	mCamY += -1.0f;
	//}




	if (CKey::Once(VK_RETURN)){
		mScene = ESTAGE1;
	}

	if (CKey::Once('1')){//的の残数を出力する
		printf("%d\n", CItem::mTargetAmount);
	}
	if (CKey::Once('2')){//Playerの座標を出力する
		printf("X:%f Y:%f Z:%f\n", CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY, CPlayer::mpPlayer->mPosition.mZ);
	}
	if (CKey::Once('3')){//扉を開けるor閉める(現状Stage2専用のデバッグ用コマンド)
		if (CPlayer::mpPlayer->mIsGetKey){
			CPlayer::mpPlayer->mIsGetKey = false;
		}
		else{
			CPlayer::mpPlayer->mIsGetKey = true;
		}
	}
	if (CKey::Once('5')){//飛行モードのON・OFF切り替え(デバッグ用)
		if (CPlayer::mpPlayer->mFlyingMode){
			CPlayer::mpPlayer->mFlyingMode = false;
		}
		else{
			CPlayer::mpPlayer->mFlyingMode = true;
		}
	}

	return;
}


//次のシーンの取得
CScene::EScene CSceneGameStage2::GetNextScene(){
	return mScene;
}