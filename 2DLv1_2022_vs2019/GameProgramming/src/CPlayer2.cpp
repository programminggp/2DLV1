#include "CPlayer2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 158, 128	//テクスチャマッピング
#define TEXCRY 196, 216, 158, 128	//テクスチャマッピング
#define GRAVITY (TIPSIZE / 20.0f)	//重力加速度
#define JUMPV0 (TIPSIZE / 1.4f)		//ジャンプの初速

void CPlayer2::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CPlayer2::Collision(CCharacter* m, CCharacter* o)
{
	float x, y;
	switch (o->Tag())
	{
	case ETag::EENEMY:
		if (CRectangle::Collision(o, &x, &y))
		{
			//敵の衝突判定を実行
			o->Collision(o, m);
			X(X() + x);
			Y(Y() + y);
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
				else
				{	//ジャンプでなければ泣く
					mState = EState::ECRY;
				}
			}
			else
			{	//ジャンプでなければ泣く
				mState = EState::ECRY;
			}
		}
		break;
	case ETag::EPLAYER:
		break;
	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
		break;
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
	if (mState != EState::EJUMP)
	{
		if (mInput.Key('J'))
		{
			mVy = JUMPV0;
			mState = EState::EJUMP;
		}
	}
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
	//Y座標にY軸速度を加える
	Y(Y() + mVy);
	//Y軸速度に重力を減算する
	mVy -= GRAVITY;

	if (mState == EState::ECRY)
	{
		//泣く画像を設定
		Texture(Texture(), TEXCRY);
	}
	else
	{
		//通常の画像を設定
		Texture(Texture(), TEXCOORD);
	}
}
