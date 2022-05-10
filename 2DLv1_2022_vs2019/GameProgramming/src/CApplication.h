#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include "CMiss.h"
#include "CCharacterManager.h"
#include <vector>

class CApplication
{
private:
	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};
	EState mState;
//	CCharacter mRectangle;
	CPlayer mPlayer;
	CTexture mTexture;
	CEnemy mEnemy;
	CEnemy mEnemy2;
//	CBullet mBullet;
	CInput mInput;
	CFont mFont;
	CMiss mMiss;
	//CCharacter�̃|�C���^�̉ϒ��z��
	std::vector<CCharacter*> mCharacters;
	CCharacterManager mCharacterManager;
public:
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};