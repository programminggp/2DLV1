#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "CTaskManager.h"
#include "main.h"

//コンストラクタ
CGame::CGame()
	: mpUi(nullptr)    
	, mTime(0)
	, mCdx(0)
	, mCdy(0)
	, mH(0)
	, mCt(0)
{
	mpUi = new CUi();
}

//デストラクタ
//デストラクタ
CGame::~CGame()
{
	//全てのインスタンス削除
	CTaskManager::Instance()->AllDelete();
	if (mpUi != nullptr)
	{	//UIを削除し、初期化
		delete mpUi;
		mpUi = 0;
	}
}

//ゲームクリア処理
void CGame::Clear()
{
	CTaskManager::Instance()->Update();
	CTaskManager::Instance()->Render();
	if (mH == 1)
	{
		mpBackGround4 = new CBackGround4(640.0f, 400.0f, 640.0f, 400.0f, 0, 1281, 801, 0, CApplication::Texture5());
		mH = 0;
	}
	mpUi->DrawResult();
}

//ゲームオーバー処理
void CGame::Over()
{
	CTaskManager::Instance()->Update();
	CTaskManager::Instance()->Render();
	if (mH == 1)
	{
		mpBackGround4 = new CBackGround4(640.0f, 400.0f, 640.0f, 400.0f, 0, 1281, 801, 0, CApplication::Texture4());
		mH = 0;
	}
}

//スタート処理
void CGame::Start()
{
	CTaskManager::Instance()->Update();
	CTaskManager::Instance()-> Render();
	if (mH == 0)
	{
		mpBackGround4 = new CBackGround4(640.0f, 400.0f, 640.0f, 400.0f, 0, 1281, 801, 0, CApplication::Texture3());
		mH = 1;
	}
}

void CGame::Stage1()
{
	mId = 0;
	mH = 1;
	mpBlock = new CBlock(640.0f, 460.0f, 1000.0f, 10.0f, CApplication::Texture9());
	mpBlock = new CBlock(640.0f, -10.0f, 1000.0f, 10.0f, CApplication::Texture9());
	mpBlock = new CBlock(-10.0f, 400.0f, 10.0f, 800.0f, CApplication::Texture9());
	mpBlock = new CBlock(1290.0f, 400.0f, 10.0f, 800.0f, CApplication::Texture9());
	mpPlayer = new CPlayer(400.0f, 250.0f, 110.0f, 110.0f, CApplication::Texture());
	mpSlime = new CSlime(1000.0f, 300.0f, 80.0f, 60.0f, CSlime::Texture6());
	mpSlime = new CSlime(1000.0f, 100.0f, 80.0f, 60.0f, CSlime::Texture6());
	mpSlime = new CSlime(800.0f, 300.0f, 80.0f, 60.0f, CSlime::Texture6());
	mpSlime = new CSlime(800.0f, 200.0f, 80.0f, 60.0f, CSlime::Texture6());
	mpSlime = new CSlime(800.0f, 100.0f, 80.0f, 60.0f, CSlime::Texture6());
	//mpSlime = new CSlime(600.0f, 300.0f, 80.0f, 60.0f, CSlime::Texture6());
	//mpSlime = new CSlime(600.0f, 100.0f, 80.0f, 60.0f, CSlime::Texture6());
	mpBackGround = new CBackGround(640.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture6());
	mpBackGround2 = new CBackGround2(640.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture7());
	mpBackGround3 = new CBackGround3(640.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture8());
	mpBackGround = new CBackGround(1920.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture6());
	mpBackGround2 = new CBackGround2(1920.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture7());
	mpBackGround3 = new CBackGround3(1920.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture8());
	mpBackGround = new CBackGround(3200.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture6());
	mpBackGround2 = new CBackGround2(3200.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture7());
	mpBackGround3 = new CBackGround3(3200.0f, 400.0f, 640.0f, 400.0f, 0, 1279, 799, 0, CApplication::Texture8());
}

void CGame::Stage2()
{
	mpWolf = new CWolf(1000.0f, 100.0f, 80.0f, 60.0f, CWolf::Texture7());
	mpWolf = new CWolf(1000.0f, 300.0f, 80.0f, 60.0f, CWolf::Texture7());
	//mpWolf = new CWolf(800.0f, 200.0f, 80.0f, 60.0f, CWolf::Texture7());
	//mpWolf = new CWolf(600.0f, 300.0f, 80.0f, 60.0f, CWolf::Texture7());
	mpWolf = new CWolf(600.0f, 200.0f, 80.0f, 60.0f, CWolf::Texture7());
	mpWolf = new CWolf(600.0f, 100.0f, 80.0f, 60.0f, CWolf::Texture7());
}

void CGame::Boss()
{
	mpBoss = new CBoss(900.0f, 300.0f, 240.0f, 240.0f, CBoss::Texture8());
}

//更新処理
void CGame::Update()
{
	mNum = CWolf::Num() + CSlime::Num();
	//更新、衝突、描画
	CTaskManager::Instance()->Update();
	CTaskManager::Instance()->Collision();
	CTaskManager::Instance()->Render();
	
	if (CApplication::Di() == 1)
	{
		mNum = 0;
	}
	if (mId == 0)
	{
		if (CApplication::Si() == 1)
		{
			mpItem = new CItem(400.0f, 200.0f, 30.0f, 30.0f, CApplication::Texture9());
			mId = 1;
		}
	}
	CameraSet();
	CCamera::End();
	//UI
	mCt++;
	if (mCt == 60)
	{
		mpUi->Time(mTime++);
		mCt = 0;
	}
	mpUi->Hp(CPlayer::HP());
	mpUi->Stamina(CPlayer::Stamina());
	mpUi->Enemy(CEnemy2::Num());
	mpUi->Render();
}

void CGame::CameraSet()
{
}
int CGame::mNum = 0;
int CGame::Num()
{
	return mNum;
}
int CGame::mId = 0;
int CGame::Id()
{
	return mId;
}
