#ifndef CENEMY_H
#define CENEMY_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"
#include "CPoint.h"

class CEnemy :public CCharacter{
private:
	//�v���C���[�̑̂̓����蔻��
	CCollider mColBody;
	//�v���C���[�̃^�C���̓����蔻��
	CCollider mColTire;

	//�W�����v���x�̕ϐ�
	float mVelocityJump;

	//�ړ����x
	float mADMoveX;
	float mWSMoveZ;
	float mCarSpeed;

	//��]���x
	float mTurnSpeed;

	float mStartPoint[3];//{ X,Y,Z }	

	bool isBoost;//�u�[�X�g����(�������ň�莞�ԗL��)
	float mBoostMaxSpeed;//�u�[�X�g�Œ�グ�����ō����x�̐��l
	int mBoostTime;//�u�[�X�g��Ԃ��p������鎞��

	//���̃|�C���g�܂łɏo���ō����x
	float mMaxSpeed_PtoP;
	
	//�R���C�_
	CCollider mSearch;

	CVector mVPoint;
	CVector mVPoint_prev;//��O�̖ڕW�|�C���g	
protected:

public:
	static CEnemy*mpEnemy;
	//�f�t�H���g�R���X�g���N�^
	CEnemy();

	//�X�V
	void Update();	

	//�Փˏ���
	void Collision(CCollider *mc, CCollider *yc);
	
	int mEnemyLap;
	bool isTouchGoal;//�S�[���n�_�ɓ����Ă��邩
	bool isEnemyGoaled;
	int mGoalTime;
	int mRank;		
	int mPointTime;//�Ō�Ƀ|�C���g�ʉ߂��Ă���̌o�ߎ���
	int mChecks;//�`�F�b�N�|�C���g
	bool CanMove;//�v���C���[������\���ۂ�(�J�E���g�_�E���O�E�S�[����Ȃǂ͔�)
	
	//�R���C�_�̍X�V
	void TaskCollision();

	//�U���|�C���g//���S�A�S�G�l�~�[���ʂ̃|�C���g
	static CPoint *mPoint;

	CPoint *mpPoint;//�ڎw���|�C���g
	
	CPoint* GetNextPoint(CPoint *current_point, bool iscurrentpointlast);
	//���݂̒n�_,�덷�̗L��,���݂̖ڕW�n�_���Ō�̃|�C���g��
	void SetNextPoint(CPoint *current_point, int gap_amount, bool iscurrentpointlast);

	//�G��AI
	enum EEnemyAI{
		ENEWBIE, //��،������Ȃ�
		EPRO, //�K�x�Ɍ�������
	};
	EEnemyAI mEnemyAI;

	//float corve;
};


#endif