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
	//ƒQ[ƒ€‚Ì•`‰æ
	CApplication::CharacterManager()->Render();
}

bool CGame::IsOver()
{
	return false;
	//HP‚ª0ˆÈ‰º‚©”»’èŒ‹‰Ê‚ð–ß‚·
	return CPlayer2::Hp() <= 0;
}

void CGame::Over()
{
	//ƒQ[ƒ€‚Ì•`‰æ
	CApplication::CharacterManager()->Render();
}

CGame::~CGame()
{
	//‘S‚Ä‚ÌƒCƒ“ƒXƒ^ƒ“ƒXíœ
	CApplication::CharacterManager()->AllDelete();
}

bool CGame::IsClear()
{
	return false;
	return CEnemy2::Num() <= 0;
}

void CGame::Clear()
{
	//ƒQ[ƒ€‚Ì•`‰æ
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
	//XVAÕ“ËAíœA•`‰æ
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
