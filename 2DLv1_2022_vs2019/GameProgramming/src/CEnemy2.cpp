#include "CEnemy2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160	//テクスチャマッピング
#define TEXCRY 196, 216, 190, 160	//テクスチャマッピング

void CEnemy2::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CEnemy2::Collision(CCharacter* m, CCharacter* o)
{
//	float x, y;
	switch (o->Tag())
	{
	case ETag::EENEMY:
		break;
	case ETag::EPLAYER:
		if (CRectangle::Collision(o))
		{
			if (o->State() == EState::EJUMP)
			{
				mState = EState::ECRY;
			}
		}
		break;
	}
}

CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EENEMY;
}

void CEnemy2::Update()
{
	switch (mState)
	{
	case EState::ECRY:
		//泣く画像を設定
		Texture(Texture(), TEXCRY);
		break;
	}
}
