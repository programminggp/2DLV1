#ifndef CSCENEGAMESTAGE2_H
#define CSCENEGAMESTAGE2_H

#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CSound.h"

/*
�X�e�[�W2�̏��
*/
class CSceneGameStage2 : public CScene{
public:
	//���̃V�[���̎擾
	EScene GetNextScene();

	~CSceneGameStage2();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCube;
	CModel mPlane;
	
	CModel mGrass;//����
	CModel mSoil; //�y

	CModel mItem;
	CModel mItemGun;
	CModel mSpring;

	CModel mCube2;//�{���ɓ���
	CModel mCube3;//�����ۂ��F

	CModel mWater;//���^�C��
	CModel mBridge;//��

	CModel mInvWall;//�����Ȃ���

	CModel mBoat;

	CModel mRoof;//����
	CModel mHouseWall;//�Ƃ̕�
	CModel mDoor;//�h�A
	CModel mKey;//��
	CModel mWindow;//��

	CPlayer *mPlayer;

	int mBlockAmoX;//X���W�̍ő�u���b�N��
	int mBlockAmoY;//Y���W�̍ő�u���b�N��
	int mBlockAmoZ;//Z���W�̍ő�u���b�N��
	int mBlockAmount;//��̎O�̐ςɂ���

	float mCamY;//�v���C���[�̎�����O���O��(����������)

	bool mPutCol;//�Փ˔���̕\��

	CSound BGM;
};

#endif