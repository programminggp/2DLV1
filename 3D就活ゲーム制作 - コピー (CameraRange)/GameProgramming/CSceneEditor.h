#ifndef CSCENEEDITOR_H
#define CSCENEEDITOR_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCameraRange.h"
#include "CCameraPos.h"
#include "CSound.h"

/*
�G�f�B�^�[���
*/
class CSceneEditor : public CScene {	
private:
	float mCamY;//�v���C���[�̎������](����������)	
	int mTextBlinkTime;
	bool isPause;
	bool mPutCol;//�����蔻��̕`���ON�EOFF	
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
	CModel mRWTile;//�Ő��ƃA�X�t�@���g�̋���
	CModel mFenceTop;//��̏��
	CModel mFenceSide;//��̑���
	CModel mPole;//�|�[��
	CModel mDashBoard;//������

	CPlayer *mPlayer;
	//CEnemy *mEnemys[ENEMYS_AMOUNT];
	CCameraRange *mCamRange;
	CCameraPos *mCam;

	CSound BGM;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;

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
public:
	//���̃V�[���̎擾
	EScene GetNextScene();

	~CSceneEditor();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�~�j�}�b�v�֘A�̏���
	void RenderMiniMap();
	//�o�b�N�~���[�̕`��
	void RenderBackMirror();
};

#endif
