#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CFreeMonster.h"
#include "CFelguard.h"
#include "CFbxMutant.h"
#include "CBee.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	CFbxMutant mFbxMutant;
//	CModelX mIdle3;

	//�L�����N�^�̃C���X�^���X
	CXPlayer mPlayer;
	//�G�̃C���X�^���X
	CXEnemy mEnemy;

	CXEnemy mDummy[3];

	//
	CFreeMonster mFMonster;
	CFreeMonster mFMonster2;
	//
	CFelguard mFelguard;
	//
	CBee mBee;

	CSceneGame();

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

};

#endif
