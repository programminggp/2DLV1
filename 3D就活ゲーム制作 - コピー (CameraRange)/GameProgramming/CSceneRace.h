#ifndef CSCENERACE_H
#define CSCENERACE_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCameraRange.h"
#include "CCameraPos.h"
#include "CSound.h"
#include "CObjFloor.h"


#include <stdlib.h>

#define ENEMYS_AMOUNT (5)//0�ȉ��ɂ͐ݒ�ł��Ȃ�

#define RACES_PER_1CUP 3//1�J�b�v�ōs�����[�X��
#define COURCE_TOTAL 5//�S�R�[�X��
#define LIST_SIZE (ENEMYS_AMOUNT+1)
/*
�Q�[���̃V�[��
*/
class CSceneRace : public CScene {
private:
	GLuint mFb;
	static bool isEnableShadow;//�e�̕`��̗L��
	static bool isEnableMiniMap;//�~�j�}�b�v�\����ON�EOFF
	static bool isEnableBackMirror;//�o�b�N�~���[�\����ON�EOFF
	static bool isEnableSpeedometer;//���x�v��ON�EOFF

	GLuint mDepthTextureID;

	float mCamY;//�v���C���[�̎������](����������)	

	//�X�^�[�g�O�̃J�E���g�_�E��
	int mFrame;//60f=1�b
	int mCountDown;
	//�R�[�X�^�C���A���b�v�֘A
	bool isStartRace, isGoal;
	int mTime, mTime_Output;


	static int mBestTime;
	int mLap, mMaxLap;
	bool isNewRecord;
	int mTextBlinkTime;//�e�L�X�g�̓_�łɊւ��ϐ�

	bool isPause;
	int mPause_SelectCarsol;
	int mPause_OptionCarsol;
	enum EPauseScreen{
		EPAUSE,//�|�[�Y���(�I������resume,option,quit)
		EOPTION,//�I�v�V�������(�ݒ��ύX�ł�����)
	};
	EPauseScreen mPauseScreen;

	int mRanking;
	int mAfterGoalTime;

	//�f�o�b�O�R�}���h�p�̕ϐ�
	bool mPutCol;//�����蔻��̕`���ON�EOFF
	
	bool isFadeIn, isFadeOut;
	int isBlackOutTime;

	bool isOpening;
	int mTime_Opening;

	enum ECameraAngle{
		EANGLE_FRONTCAR,
		EANGLE_THIRDPERSON
	};
	ECameraAngle mCameraAngle;

	int mPushEnter_WaitTime;
	bool isGoaledAll;//�S���S�[��������
	bool isResult_FinalRace;//�ŏI����(�O�����v�����[�h�̂�)
	bool canPushEnter;

	CTexture Texture_GoldTrophy;
	CTexture Texture_SilverTrophy;
	CTexture Texture_BronzeTrophy;
protected:
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
	CModel mPlane;
	CModel mCheckPoint;//�|���S��1���̂݁A����
	CModel mTileBlack;//������
	CModel mTileWhite;//������
	CModel mCarsol;//���(�~�j�}�b�v)
	CModel mCarsol_Enemy;//�G�̖��(�~�j�}�b�v)
	CModel mMiniGoal;//�S�[��Icon(�~�j�}�b�v)
	CModel mCource01;//�R�[�X01
	CModel mGrass01;//�Ő�01
	CModel mGoalTile01;
	CModel mCurb01;//�g���̉���
	CModel mFenceTop;//��̏��
	CModel mFenceSide;//��̑���
	CModel mPole;//�|�[��
	CModel mDashBoard;//������

	CPlayer *mPlayer;
	CEnemy *mEnemys[ENEMYS_AMOUNT];
	CCameraRange *mCamRange;
	CCameraPos *mCam;

	CSound BGM;
	CSound JingleOpening;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;
	CSound SoundMoveCarsol;
	CSound SoundDecide;
	CSound SoundPauseOn;
	CSound SoundPauseOff;


	//�R�[�X2,3�̃��f��
	CModel mCource02Road;
	CModel mCource02Wall;
	CModel mCource02Jump;
	CModel mCource03Road;
	CModel mCource03Wall;
	CModel mCource03Fence;

	CModel mJumper01;//�W�����v��
	//����ȃ^�C��
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
	
	CModel mGoalGate;

	enum EStartPos{
		ESTARTPOS_RANDOM,//���ʃ����_���ŃX�^�[�g
		ESTARTPOS_TOP,//1�ʂ���̃X�^�[�g
	};
	EStartPos mStartPos;

	int list[LIST_SIZE];//
public:
	//���̃V�[���̎擾
	EScene GetNextScene();

	~CSceneRace();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�e�L�X�g���̕`��
	void Render();
	//�~�j�}�b�v�֘A�̏���
	void RenderMiniMap();
	//�o�b�N�~���[�̕`��
	void RenderBackMirror();
	//�e�̕`��
	void RenderShadowMap();
	void RenderShadow();
	//�t�F�[�h�C�������ăQ�[����ʂɓ���
	void FadeIn();
	//���V�[���ɍs���ۂ̉��o�E����
	void SceneChange();
	//CPU�Ԃ̐F�̏o��
	void PutCPUColor();
	
	//�e�R�[�X�̃x�X�g�^�C��
	static int mRecords[COURCE_TOTAL + 1];//0:edit 1�`:cource1, 2, ...	
	static int mTotalPoint;//�l���������_�̍��v
	static int mTotalPoint_Enemys[ENEMYS_AMOUNT];
	static int mCurrent_RaceNumber;//���݂̃��[�X��
};
#endif
