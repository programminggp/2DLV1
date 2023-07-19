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
	, mCountFly(0)
	, mIntervalFly(180)
{
	mpPlayer = new CPlayer(400,50,20,20,nullptr);
	CApplication::CharacterManager()->Add(mpPlayer);

	for (int y = 4; y > 0; y--)
	{
		for (int x = 0; x < 8; x++)
		{
			CApplication::CharacterManager()->Add(new CEnemy((800 - 7 * 80)/2+ x * 80, 600 - y * 60, 20.0f, 20.0f, 0, 0, 0, 0, nullptr));
		}
	}
}

void CGame::Update()
{
	if(++mCountFly > mIntervalFly) {
		std::vector<CCharacter*> character = CApplication::CharacterManager()->Characters();
		float max = 0.0f;
		CEnemy* flyEnemy = nullptr;
		for (int i = 0; i < character.size(); i++)
		{
			if (character[i]->Tag() == CCharacter::ETag::EENEMY && character[i]->State() != CCharacter::EState::EFLY)
			{
				float length = (character[i]->X() - mpPlayer->X()) * (character[i]->X() - mpPlayer->X())
					+ (character[i]->Y() - mpPlayer->Y()) * (character[i]->Y() - mpPlayer->Y());
				if (max < length)
				{
					max = length;
					flyEnemy = (CEnemy*)character[i];
				}
			}
		}
		if (flyEnemy != nullptr)
		{
			flyEnemy->Fly();
			flyEnemy->Txy(mpPlayer->X(), mpPlayer->Y() - 100.0f);
			mCountFly = 0;
			mIntervalFly -= 6;
			if (mIntervalFly < 90)
				mIntervalFly = 90;
		}
	}

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
