#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXCharacter.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//�L�����N�^�̃C���X�^���X
	CXCharacter mCharacter;
	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

};

#endif
