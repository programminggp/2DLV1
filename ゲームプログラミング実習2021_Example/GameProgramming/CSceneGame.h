#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CCameraControl.h"
#include "CMap.h"
#include "CFelguard.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
	CFelguard mFelguard;
	CCameraControl mCameraControl;
	CMap mMap;
public:
	//�L�����N�^�̃C���X�^���X
	CXPlayer mPlayer;
	//�G�̃C���X�^���X
	CXEnemy mEnemy;

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

};

#endif
