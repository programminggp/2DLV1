#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CCameraControl.h"
#include "CMap.h"
#include "CFelguard.h"
#include "CKnight.h"
#include "CMap2.h"
#include "CMap3.h"
#include "CMap4.h"
#include "CMap5.h"
/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
//	CKnight mKnight;
//	CFelguard mFelguard;
	CMap5 mMap;
//	CMap2 mMap;
public:
	//�L�����N�^�̃C���X�^���X
//	CXPlayer mPlayer;
	//�G�̃C���X�^���X
//	CXEnemy mEnemy;
	CSceneGame();
	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

};

#endif
