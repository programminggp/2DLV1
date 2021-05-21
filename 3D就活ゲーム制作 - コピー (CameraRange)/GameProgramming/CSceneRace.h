#ifndef CSCENERACE_H
#define CSCENERACE_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCameraRange.h"
#include "CCameraPos.h"
#include "CRigidObj.h"
//CSound.h���C���N���[�h�����特�̍Đ��̓��삪�y���Ȃ����H
#include "CSound.h"

#define ENEMYS_AMOUNT 7-2 //0�ȉ��ɂ͐ݒ�ł��Ȃ�
/*
�Q�[���̃V�[��
*/
class CSceneRace : public CScene {
public:
	//���̃V�[���̎擾
	EScene GetNextScene();

	~CSceneRace();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�~�j�}�b�v�֘A�̏���
	void RenderMiniMap();
	//�o�b�N�~���[�̕`��
	void RenderBackMirror();

	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCarRed;
	CModel mCarBlue;
	CModel mCarGreen;
	CModel mCarYellow;
	CModel mCarPink;
	CModel mCarCyan;
	CModel mCarWhite;
	CModel mCarBlack;
	CModel mCarGray;
	CModel mCube;
	CModel mPlane;
	CModel mStairs;//�K�i
	CModel mTarget;//�I
	CModel mOnBlock;//OFF�ɂȂ�Ə�����
	CModel mCube2;//�����x100��
	CModel mCube3;//���̂悤�ȐF�A�������Ő��F
	CModel mCheckPoint;//�|���S��1���̂݁A����
	CModel mTileBlack;//������
	CModel mTileWhite;//������
	CModel mCarsol;//���(�~�j�}�b�v)
	CModel mCarsol_Enemy;//�G�̖��(�~�j�}�b�v)
	CModel mMiniGoal;//�S�[��Icon(�~�j�}�b�v)
	CModel mCource01;//�R�[�X01
	CModel mGrass01;//�Ő�01
	CModel mRWTile;//�Ő��ƃA�X�t�@���g�̋���
	CModel mFenceTop;//��̏��
	CModel mFenceSide;//��̑���
	CModel mPole;//�|�[��
	CModel mDashBoard;//������

	CPlayer *mPlayer;
	CEnemy *mEnemys[ENEMYS_AMOUNT];
	CCameraRange *mCamRange;
	CCameraPos *mCam;

	CSound BGM;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;
	
	float mCamY;//�v���C���[�̎������](����������)
	

	//�X�^�[�g�O�̃J�E���g�_�E��
	int mFrame;
	int mCountDown;
	//�R�[�X�^�C���A���b�v�֘A
	bool isStartRace, isGoal;
	int mTime, mTime_Output;
	static int mBestTime;
	int mLap, mMaxLap;
	bool isNewRecord;
	static int mRecord_A, mRecord_B, mRecord_C, mRecord_D, mRecord_E, mRecord_F;

	int mCamPoV;

	int mTextBlinkTime;
		
	bool isPause;

	int mRanking;
	int mAfterGoalTime;

	//�f�o�b�O�R�}���h�p�̕ϐ�
	bool isRender_BackMirror;//�o�b�N�~���[�\����ON�EOFF
	bool mPutCol;//�����蔻��̕`���ON�EOFF
	bool isRendPoint;//���Ԓn�_���~�j�}�b�v�ɕ\������邩

	//�R�[�X2,3�̃��f��
	CModel mCource02Road;
	CModel mCource02Wall;
	CModel mCource02Jump;
	CModel mCource03Road;
	CModel mCource03Wall;
	CModel mCource03Fence;

	CModel mJumper01;//�W�����v��
	//��������
	CModel mTile_Curve01_Floor;
	CModel mTile_Curve02_Floor;
	CModel mTile_Curve03_Floor;
	CModel mTile_Curve04_Floor;
	CModel mTile_Straight01_Floor;
	CModel mTile_Straight02_Floor;
	CModel mTile_Curve01_Wall;
	CModel mTile_Curve02_Wall;
	CModel mTile_Curve03_Wall;
	CModel mTile_Curve04_Wall;
	CModel mTile_Straight01_Wall;
	CModel mTile_Straight02_Wall;
	//��n
	CModel mTile_Slope01_Floor;
	CModel mTile_Slope02_Floor;
	CModel mTile_Slope03_Floor;
	CModel mTile_Slope04_Floor;
	CModel mTile_Slope01_Wall;
	CModel mTile_Slope02_Wall;
	CModel mTile_Slope03_Wall;
	CModel mTile_Slope04_Wall;
	//�ł��߂̃^�C��
	CModel mTile_Wide_Floor;
	CModel mTile_Wide_Wall;
	CModel mBlock_Floor;
	CModel mBlock_Wall;
	//�R�[�X5�̃��f��
	CModel mCource05Mountain;
	CModel mCource05Wall;
	CModel mCource05Road;
	CModel mCource05Lake;
	CModel mCource05Grass_Floor;
	CModel mCource05Grass_Wall;
	CModel mCource05GoalTile;
	//�W��
	CModel mSign_Left;
	CModel mSign_Right;
};

#endif
