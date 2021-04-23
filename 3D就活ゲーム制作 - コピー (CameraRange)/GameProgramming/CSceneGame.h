#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
//CSound.h���C���N���[�h�����特�̍Đ��̓��삪�y���Ȃ����H
#include "CSound.h"
/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//���̃V�[���̎擾
	EScene GetNextScene();

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCube;
	CModel mPlane;
	CModel mStairs;//�K�i
	CModel mTarget;//�I
	CModel mOnBlock;//OFF�ɂȂ�Ə�����

	CModel mItem;
	CModel mItemGun;

	CModel mCube2;//�{���ɓ���
	CModel mCube3;//�����ۂ��F

	CModel mWater;//���^�C��

	CModel mBoat;
	CModel mWarpPoint;
	CModel mSpringS;//�΂�
	CModel mSpringL;//�΂ːL��

	CPlayer *mPlayer;

	CSound BGM;

	int mBlockAmoX;//X���W�̍ő�u���b�N��
	int mBlockAmoY;//Y���W�̍ő�u���b�N��
	int mBlockAmoZ;//Z���W�̍ő�u���b�N��
	int mBlockAmount;//��̎O�̐ςɂ���

	float mCamY;//�v���C���[�̎�����O���O��(����������)

	bool mPutCol;
};

#endif
