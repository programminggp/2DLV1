#ifndef CSCENETEST_H
#define CSCENETEST_H
#include "CScene.h"
#include "CXCharacter.h"

/*
�Q�[���̃V�[��
*/
class CSceneTest : public CScene {
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
private:
	CModelX mModelX;
	//�L�����N�^�̃C���X�^���X
	CXCharacter mXCharacter;
};

#endif