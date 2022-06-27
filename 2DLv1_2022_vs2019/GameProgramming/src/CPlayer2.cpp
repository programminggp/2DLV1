#include "CPlayer2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 158, 128	//テクスチャマッピング
#define TEXCRY 196, 216, 158, 128	//テクスチャマッピング
#define GRAVITY (TIPSIZE / 20.0f)	//重力加速度
#define JUMPV0 (TIPSIZE / 1.4f)		//ジャンプの初速

#define TEXCOORD2 136,156,158,128	//右向き2
#define TEXLEFT1 188,168,158,128	//左向き1
#define TEXLEFT2 156,136,158,128	//左向き2
#define VELOCITY 4.0f	//移動速度

int CPlayer2::Hp()
{
	return mHp;
}

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
	: mHp(3)
	, mInvincble(0)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EPLAYER;
}

void CPlayer2::Update()
{
	if (mInvincble > 0)
	{
		mInvincble--;
	}
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
		mVx = -VELOCITY;
		//		float x = X() - 4.0f;
		X(X() + mVx);
	}
	if (mInput.Key('D'))
	{
		mVx = VELOCITY;
		//		float x = X() - 4.0f;
		X(X() + mVx);
	}
	//Y座標にY軸速度を加える
	Y(Y() + mVy);
	//Y軸速度に重力を減算する
	mVy -= GRAVITY;

	if (mState == EState::ECRY)
	{
		//泣く画像を設定
		Texture(Texture(), TEXCRY);
		if (mInvincble == 0)
		{
			mInvincble = 60;
			mHp--;
		}
	}
	else
	{
		const int PITCH = 32;//画像を切り替える間隔
		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mVx < 0.0f) //左へ移動
			{
				//左向き１を設定
				Texture(Texture(), TEXLEFT1);
			}
			else
			{
				//通常の画像を設定
				Texture(Texture(), TEXCOORD);
			}
		}
		else
		{
			if (mVx < 0.0f) //左へ移動
			{
				//左向き2を設定
				Texture(Texture(), TEXLEFT2);
			}
			else
			{
				//2番目の画像を設定
				Texture(Texture(), TEXCOORD2);
			}
		}
	}
}
