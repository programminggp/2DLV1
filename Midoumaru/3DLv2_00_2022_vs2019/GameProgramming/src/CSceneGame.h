#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"
#include"CXCharacter.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include"CXMutant.h"
#include "CActionCamera.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {

	CText mFont;
	//�G�̃C���X�^���X
	CXEnemy mEnemy;
public:
	CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

private:
	CActionCamera mActionCamera;
	//�L�����N�^�̃C���X�^���X
	CXPlayer* mPlayer;
	CXMutant* mMutant;
	
	CModel Underground;
	
	//CXCharacter mCharacter;

};

#endif