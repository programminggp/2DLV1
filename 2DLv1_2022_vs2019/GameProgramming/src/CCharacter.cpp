#include "CCharacter.h"

CCharacter::EState CCharacter::State()
{
	return mState;
}

bool CCharacter::Enabled()
{
	return mEnabled;
}

CCharacter::ETag CCharacter::Tag()
{
	return mTag;
}

CCharacter::CCharacter()
	: mpTexture(nullptr)
	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)
	, mState(EState::EMOVE)
	, mTag(ETag::EZERO)
	, mEnabled(true)
	, mVy(0.0f)
	, mVx(0.0f)
{

}

void CCharacter::Texture(CTexture *pTexture, int left, int right, int bottom, int top)
{
	mpTexture = pTexture;
	mLeft = left;
	mRight = right;
	mBottom = bottom;
	mTop = top;
}

void CCharacter::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop
	);
}

void CCharacter::Move()
{
	mState = EState::EMOVE;
}

CTexture* CCharacter::Texture()
{
	return mpTexture;
}
