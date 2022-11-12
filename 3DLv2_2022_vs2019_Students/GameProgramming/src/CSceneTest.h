#ifndef CSCENETEST_H
#define CSCENETEST_H
#include "CScene.h"
#include "CXCharacter.h"
#include "CActionCamera.h"
#include "CPaladin.h"
#include "CColliderMesh.h"

/*
�Q�[���̃V�[��
*/
class CSceneTest : public CScene {
public:
	CSceneTest()
		: mActionCamera(3.0f,-15.0f,180.0f)
	{}
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
private:
	CColliderMesh mColliderMesh;
	CPaladin* mpPlayer;
	CActionCamera mActionCamera;
	CModel mGround;
	CVector mScale;
	bool mPushFlg;
	float mOldMousePosX;
	CTransform mTransform;
	CModelX mModelX;
	//�L�����N�^�̃C���X�^���X
	//CXCharacter mXCharacter;
};

#endif