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
	CVector mScale;
	bool mPushFlg;
	float mOldMousePosX;
	CTransform mTransform;
	CModelX mModelX;
	//�L�����N�^�̃C���X�^���X
	CXCharacter mXCharacter;
};

#endif