#ifndef CPLAYER_H
#define CPLAYER_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"

class CPlayer :public CCharacter{
private:
	CVector mVCheckPositions[4];//mChecks�ɉ��������X�|�[���n�_�̍��W
	CVector mVCheckRotations[4];//mChecks�ɉ��������X�|�[���n�_�̉�]�l

	//�W�����v���x�̕ϐ�
	float mVelocityJump;
	//�W�����v�𓖂��蔻����������������������
	//int mJumpPrio;

	bool isBoost;//�u�[�X�g����(�������ň�莞�ԗL��)
	float mBoostMaxSpeed;//�u�[�X�g�Œ�グ�����ō����x�̒l
	int mBoostTime;//�u�[�X�g��Ԃ̌��ʎ���
protected:
public:
	static CPlayer*mpPlayer;
	//�f�t�H���g�R���X�g���N�^
	CPlayer();

	//�X�V
	void Update();

	//�v���C���[�̑̂̓����蔻��
	CCollider mColBody;
	//�v���C���[�̃^�C���̓����蔻��
	CCollider mColTire;

	//�Փˏ���
	void Collision(CCollider *mc, CCollider *yc);
	
	//�ړ����x
	float mADMoveX;
	float mWSMoveZ;
	float mCarSpeed;
	//��]���x
	float mTurnSpeed;
	
	CSound SoundJump;
	CSound SoundShot;
	CSound SoundItemGet;
	CSound SoundBoost;
	CSound SoundEngine;//�G���W����
	CSound SoundEngine_Turf;//�Ő��̏�ł̉�
	bool isSoundEngine;
	CSound SoundHorn;
	CSound SoundCollision;
	CSound SoundCollisionSmall;
	bool isRespawn;
	CSound SoundSink;
	bool isSink;

	//���X�|�[���n�_�̐ݒ�(�`�F�b�N�|�C���g�̒ʉߏ󋵂ɉ����ă��X�|�[���n�_�͕ω�)
	void SetRespawnPoint(int checknumber, CVector position, CVector rotation);
	//����̈ʒu(�X�^�[�g�n�_)�ɒ���
	void GetReady();

	bool mFlyingMode;//�f�o�b�O�p�F���R�����𖳌���

	int mChecks;
	bool isTouchGoal;//�S�[���n�_�ɓ����Ă��邩
	int mGoalTime;
	int mRank;

	

	bool CanMove;//�v���C���[������\���ۂ�(�J�E���g�_�E���O�E�S�[����Ȃǂ͔�)
	
	//�R���C�_�̍X�V
	void TaskCollision();

	enum Sound_Engine{
		ENONE,//�����l
		EONGRASS,//�Ő��̏�
		ENOTONGRASS,//�Ő��̏�łȂ�
	};
	Sound_Engine mSound_Engine, mSound_Engine_Prev;//�ڐG��,1f�O�́V	
};

#endif