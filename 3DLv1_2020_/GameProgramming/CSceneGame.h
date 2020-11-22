#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CVector.h"
//���f���N���X�̃C���N���[�h
#include "CModel.h"
//
#include "CCharacter.h"
//
#include "CPlayer.h"
//
#include "CColliderTriangle.h"
//
#include "CColliderMesh.h"
/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;
	//�O�p�R���C�_�̍쐬
	//�폜CColliderTriangle mColliderTriangle;
	//�폜CColliderTriangle mColliderTriangle2;
	//C5���f��
	CModel mModelC5;
	CModel mBackGround;
	//���f���N���X�̃C���X�^���X�쐬
	CModel mModel;
	//
//	CCharacter mCharacter;
	CPlayer mPlayer;

	CVector mEye;
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif
