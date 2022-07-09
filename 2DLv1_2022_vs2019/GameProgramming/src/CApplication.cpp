#include "CApplication.h"
#include "CRectangle.h"

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	mFont.Load("FontWhite.png", 1, 64);
	mState = EState::ESTART;
	mpGame = new CGame();
}

void CApplication::Update()
{
	switch (mState)
	{
	case EState::ESTART:	//��Ԃ��X�^�[�g
		mpGame->Start();	//�X�^�[�g��ʕ\��
		//Enter�L�[�������ꂽ��
		if (mInput.Key(VK_RETURN))
		{	//��Ԃ��v���C���ɂ���
			mState = EState::EPLAY;
		}
		break;
	case EState::EPLAY:
		mpGame->Update();
		//�Q�[���I�[�o�[������
		if (mpGame->IsOver())
		{	//��Ԃ��Q�[���I�[�o�[�ɂ���
			mState = EState::EOVER;
		}
		//�Q�[���N���A������
		if (mpGame->IsClear())
		{	//��Ԃ��Q�[���N���A�ɂ���
			mState = EState::ECLEAR;
		}
		break;
	case EState::EOVER:
		//�Q�[���I�[�o�[����
		mpGame->Over();
		if (mInput.Key(VK_RETURN))
		{
			delete mpGame;
			mpGame = new CGame();
			mState = EState::ESTART;
		}
		break;
	case EState::ECLEAR:
		//�Q�[���N���A����
		mpGame->Clear();
		if (mInput.Key(VK_RETURN))
		{
			delete mpGame;
			mpGame = new CGame();
			mState = EState::ESTART;
		}
		break;
	}
}
