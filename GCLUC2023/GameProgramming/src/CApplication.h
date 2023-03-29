#pragma once
#include <vector>
#include "CRectangle.h"
#include "CCharacter.h"
#include "CCharacterManager.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CInput.h"
#include "CFont.h"
#include "CGame.h"
#include "CSound.h"
#include "CBackGround.h"
#include "CHeart.h"
#include "CGage.h"
#include "CFont2.h"


class CApplication
{
private:
	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ESTAGE1,
		ESTAGE2,
		EBOSS,
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};

	CGame* mpGame;      //�Q�[���N���X�̃|�C���^
	CPlayer* mpPlayer;  //�v���C���[�N���X�̃|�C���^
	CEnemy* mpEnemy;    //�G�N���X�̃|�C���^
	EState mState;
	CInput mInput;
	CFont mFont;
	CFont2 mFont2;
	CBackGround* mpBackGround;

	static CTexture mTexture;  //�v���C���[�e�N�X�`��
	static CTexture mTexture2; //�w�i�e�N�X�`��
	static CTexture mTexture3; //�X�^�[�g��ʃe�N�X�`��
	static CTexture mTexture4; //�Q�[���I�[�o�[��ʃe�N�X�`��
	static CTexture mTexture5; //�Q�[���N���A��ʃe�N�X�`��
	static CTexture mTexture6;
	static CTexture mTexture7;
	static CTexture mTexture8;
	static CTexture mTexture9;
	static CTexture mTexture100; //�n�[�g�\���e�N�X�`��
	int mRb;
	int mMc;
	int mEs;
	int mNc;
	int mIg;
	//int mBd;
	static int mMm;
	static int mSi;
	static int mMu;
	static int mDi;
	static int mBd;
	static CTexture mTexture101; //�X�^�~�i�\���e�N�X�`��
	static CTexture mTexture102; //�X�^�~�i�Q�[�W�\���e�N�X�`��

public:
	static CTexture* Texture();
	static CTexture* Texture2();
	static CTexture* Texture3();
	static CTexture* Texture4();
	static CTexture* Texture5();
	static CTexture* Texture6();
	static CTexture* Texture7();
	static CTexture* Texture8();
	static CTexture* Texture9();
	static CTexture* Texture100();
	static CTexture* Texture101();
	static CTexture* Texture102();
	static int Mm();
	static int Si();
	static int Mu();
	static int Di();
	static int Bd();
	CApplication();
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};