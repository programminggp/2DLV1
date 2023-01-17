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
	CVector mScale; //�g��k���{��
	bool mPushFlg;
	float mOldMousePosX;
	CTransform mTransform; //��]�k���p�s��
	CModelX mModelX; //X���f���f�[�^
	CXCharacter mXCharacter; 	//�L�����N�^�̃C���X�^���X
};
#endif

