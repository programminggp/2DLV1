#include "CCharacter.h"
#include "CApplication.h"
#include "CTaskManager.h"

//�R���X�g���N�^
CCharacter::CCharacter(int priority)
	: CTask(priority)
	, mpTexture(nullptr), mLeft(0), mRight(0), mBottom(0), mTop(0)
	, mEnabled(false)
	, mState(EState::ENULL)
	, mVx(0.0f)
	, mVy(0.0f)
{
}

//�f�X�g���N�^
CCharacter::~CCharacter()
{
}

//��Ԃ��擾
CCharacter::EState CCharacter::State()
{
	return mState;
}

void CCharacter::Texture(CTexture* pTexture,
	int left, int right, int bottom, int top)
{
	mpTexture = pTexture;
	mLeft = left;
	mRight = right;
	mBottom = bottom;
	mTop = top;
}

CTexture* CCharacter::Texture()
{
	return mpTexture;
}

//�`�揈��
void CCharacter::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop);
}

bool CCharacter::Enabled()
{
	return mEnabled;
}

void CCharacter::Update()
{
	if (mState != EState::EJUMP)
	{
		CTask::Setpriority(Z());
	}
}