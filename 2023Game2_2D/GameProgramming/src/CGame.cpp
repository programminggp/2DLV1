#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer2.h"
#include "CEnemy2.h"
#include "CPoint.h"
#include "CCamera.h"
#include "main.h"

void CGame::Start()
{
	//ゲームの描画
	CApplication::CharacterManager()->Render();
}

bool CGame::IsOver()
{
	return false;
	//HPが0以下か判定結果を戻す
	return CPlayer2::Hp() <= 0;
}

void CGame::Over()
{
	//ゲームの描画
	CApplication::CharacterManager()->Render();
}

CGame::~CGame()
{
	//全てのインスタンス削除
	CApplication::CharacterManager()->AllDelete();
}

bool CGame::IsClear()
{
	return false;
	return CEnemy2::Num() <= 0;
}

void CGame::Clear()
{
	//ゲームの描画
	CApplication::CharacterManager()->Render();
}

CGame::CGame()
	: mpUi(nullptr)
	, mTime(0)
	, mCdx(0)
	, mCdy(0)
{
}

void CGame::Update()
{
	//更新、衝突、削除、描画
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
}

void CGame::CameraSet()
{
	float x = mpPlayer->X() + mCdx;
	float y = mpPlayer->Y() + mCdy;
	CCamera::Start(x - WINDOW_WIDTH / 2
		, x + WINDOW_WIDTH / 2
		, y - WINDOW_HEIGHT / 2
		, y + WINDOW_HEIGHT / 2
	);
}
