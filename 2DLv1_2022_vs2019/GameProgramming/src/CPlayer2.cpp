#include "CPlayer2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 158, 128	//テクスチャマッピング

void CPlayer2::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CPlayer2::Collision(CCharacter* m, CCharacter* o)
{
	float x, y;
	switch (o->Tag())
	{
	case ETag::EPLAYER:
		break;
	default:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
		}
	}
}

CPlayer2::CPlayer2(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EPLAYER;
}

void CPlayer2::Update()
{
	if (mInput.Key('A'))
	{
		float x = X() - 4.0f;
		X(x);
	}

	if (mInput.Key('D'))
	{
		float x = X() + 4.0f;
		X(x);
	}
}
