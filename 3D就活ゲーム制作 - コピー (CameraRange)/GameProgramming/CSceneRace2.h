#ifndef CSCENERACE2_H
#define CSCENERACE2_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
//CSound.h���C���N���[�h�����特�̍Đ��̓��삪�y���Ȃ����H
#include "CSound.h"
#include "CSceneGame.h"
/*
�Q�[���̃V�[��
*/
class CSceneRace2 : public CScene {
public:
	//���̃V�[���̎擾
	EScene GetNextScene();

	~CSceneRace2();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�~�j�}�b�v�֘A�̏���
	void RenderMiniMap();
	
	CModel mMiami;

	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCarRed;
	CModel mCarBlue;
	CModel mCube;
	CModel mPlane;
	CModel mStairs;//�K�i
	CModel mTarget;//�I
	CModel mOnBlock;//OFF�ɂȂ�Ə�����

	CModel mItem;
	

	CModel mCube2;//�{���ɓ���
	CModel mCube3;//�����ۂ��F

	CModel mCheckPoint;//�����y���ׂ̈�1�������̃|���S���ŁA�����^�C����\��

	CModel mWater;//���^�C��

	CModel mSpringS;//�΂�
	CModel mSpringL;//�΂ːL��

	CModel mTileBlack;//������
	CModel mTileWhite;//������

	CModel mCarsol;//���(�~�j�}�b�v)
	CModel mMiniGoal;//�S�[��Icon(�~�j�}�b�v)

	CModel mCource01;//�R�[�X01
	CModel mGrass01;//�Ő�01
	CModel mFence01;//��
	CModel mRWTile;//�Ő��ƃA�X�t�@���g�̋���
	
	CModel mFenceTop;//��̏��
	CModel mFenceSide;//��̑���

	CModel mPole;//�|�[��

	CModel mDashBoard;//�������鏰

	CPlayer *mPlayer;

	CEnemy *mEnemy1;
	CEnemy *mEnemy2;

	CSound BGM;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;
	

	int mBlockAmoX;//X���W�̍ő�u���b�N��
	int mBlockAmoY;//Y���W�̍ő�u���b�N��
	int mBlockAmoZ;//Z���W�̍ő�u���b�N��
	int mBlockAmount;//��̎O�̐ςɂ���

	float mCamY;//�v���C���[�̎�����O���O��(����������)

	bool mPutCol;

	int mFrame;
	int mCountDown;
	bool isStartRace;
	int mTime;
	int mBestTime;
	int mLap;
	bool isNewRecord;

	float mXXX, mYYY, mZZZ;
	float mXX0, mZZ0;

	CModel mSumple;

	int mCamPoV;
};

#endif
