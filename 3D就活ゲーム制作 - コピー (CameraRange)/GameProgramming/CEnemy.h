#ifndef CENEMY_H
#define CENEMY_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"
#include "CPoint.h"

class CEnemy :public CCharacter{
public:
	static CEnemy*mpEnemy;
	//�f�t�H���g�R���X�g���N�^
	CEnemy();

	//�X�V
	void Update();

	//�v���C���[�̑̂̓����蔻��
	CCollider mColBody;
	//�v���C���[�̃^�C���̓����蔻��
	CCollider mColTire;

	//�Փˏ���
	void Collision(CCollider *mc, CCollider *yc);

	//�W�����v���x�̕ϐ�
	float mVelocityJump;
	//�W�����v��(�W�����v����)�̕ϐ�
	float mJumpV0;

	//�ړ����x
	float mMoveSpeed;
	float mADMoveX;
	float mWSMoveZ;
	float mCarSpeed;
	//�GAI�̋����ɂ��X�s�[�h��
	float mCPULevelSpeed;

	//��]���x
	float mTurnSpeed;

	bool mCanJump;//�W�����v�\��(���n�ʂɑ��������Ă邩)

	CSound SoundBoost;
	CSound SoundEngine;//��Ԃ̓��
	bool isSoundEngine;
	CSound SoundCollision;
	CSound SoundCollisionSmall;
	CSound SoundRespawn;
	CSound SoundRespawn2;
	int mRespawnCount;

	float mStartPoint[3];//{ X,Y,Z }

	int mChecks;

	bool isBoost;//�u�[�X�g����(�������ň�莞�ԗL��)
	float mBoostMaxSpeed;//�u�[�X�g�Œ�グ�����ō����x�̐��l
	int mBoostTime;//�u�[�X�g��Ԃ��p������鎞��

	bool CanMove;//�v���C���[������\���ۂ�(�J�E���g�_�E���O�E�S�[����Ȃǂ͔�)

	static int RenderType;//�Q�[����ʂ̕`��ƃ~�j�}�b�v�̕`��𕪂���ϐ�

	//�R���C�_�̍X�V
	void TaskCollision();

	//�U���|�C���g//���S�A�S�G�l�~�[���ʂ̃|�C���g
	static CPoint *mPoint;
	static CPoint *mPoint2;
	static CPoint *mPoint3;
	static CPoint *mPoint4;
	static CPoint *mPoint5;
	static CPoint *mPoint6;
	static CPoint *mPoint7;
	static CPoint *mPoint8;
	static CPoint *mPoint9;
	static CPoint *mPoint10;
	static CPoint *mPoint11;
	static CPoint *mPoint12;
	static CPoint *mPoint13;
	static CPoint *mPoint14;
	static CPoint *mPoint15;
	static CPoint *mPoint16;
	static CPoint *mPoint17;
	static CPoint *mPoint18;
	static CPoint *mPoint19;
	static CPoint *mPoint20;
	static CPoint *mPoint21;
	static CPoint *mPoint22;
	static CPoint *mPoint23;
	//
	static CPoint *mPoint24;
	static CPoint *mPoint25;
	static CPoint *mPoint26;
	static CPoint *mPoint27;
	static CPoint *mPoint28;
	static CPoint *mPoint29;
	static CPoint *mPoint30;
	static CPoint *mPoint31;
	static CPoint *mPoint32;
	static CPoint *mPoint33;
	static CPoint *mPoint34;
	static CPoint *mPoint35;
	static CPoint *mPoint36;
	static CPoint *mPoint37;
	static CPoint *mPoint38;
	static CPoint *mPoint39;
	static CPoint *mPoint40;
	static CPoint *mPoint41;
	static CPoint *mPoint42;
	static CPoint *mPoint43;
	static CPoint *mPoint44;
	static CPoint *mPoint45;
	static CPoint *mPoint46;
	static CPoint *mPoint47;
	static int mPointSize;//�|�C���g�̐�
	CPoint *mpPoint;//�ڎw���|�C���g
	int mPointCnt;//�|�C���g�̃J�E���^
	//���̃|�C���g�܂łɏo���ō����x
	float mMaxSpeed_PtoP;

	//�R���C�_
	CCollider mSearch;

	CVector mVPoint;

	int mEnemyLap;
	bool isTouchGoal;//�S�[���n�_�ɓ����Ă��邩
	bool isEnemyGoaled;
	int mGoalTime;
	int mRank;

	//�|�C���g�ւ̃x�N�g�������߂�
	//CVector dir = mpPoint->mPosition - mPosition;
	CVector dir;
	//�������ւ̃x�N�g�������߂�
	CVector left;
};


#endif