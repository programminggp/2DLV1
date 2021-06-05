#ifndef CXCHARCTER_H
#define CXCHARCTER_H

#include "CModelX.h"
#include "CMatrix44.h"
#include "CTask.h"

//27 �R���C�_�N���X�̐錾
class CCollider;

class CXCharacter : public CTask {
public:
	//27 �L�����N�^�[�̎���
	enum ECharTag {
		EPLAYER = 1,
		EENEMY,
	};
	ECharTag mTag;	//�L�����N�^���ʃ^�O
	enum EState {
		EIDLE,
		EWALK,
		EATTACK,
		EATTACKR,
		EAVOIDANCEL,
		EAVOIDANCER,
		EDOWN,
	};
	EState mState;

	CModelX *mpModel;	//���f���f�[�^
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�J��Ԃ�
	float mAnimationFrame; //�A�j���[�V�����̍Đ��t���[��
	float mAnimationFrameSize;	//�A�j���[�V�����̍Đ��t���[����
	CVector3 mPosition;	//�ʒu
	CVector3 mRotation;	//��]
	CVector3 mScale;
	CMatrix44 mMatrix;	//�ʒu��]�s��
	CMatrix44 *mpCombinedMatrix;	//�����s��ޔ�

	//30
	float mVelocityG; //�d�͑��x

	//35
	CVector3 mCameraRotation; //�J�����̉�]

	bool mHitFlg;

	CVector3 mAdjust;

	CXCharacter()
		: mpCombinedMatrix(0), mVelocityG(0.0f), mHitFlg(true), mState(EIDLE), mScale(1.0f, 1.0f, 1.0f)
	{

	}

	~CXCharacter() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}

	//����������
	void Init(CModelX *model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix44 &m, bool addframe);
	//�`�揈��
	void Render();
	//�X�V����
	void Update();
	//27 �Փˏ���
	virtual bool Collision(CCollider*, CCollider*){
		return false;
	};
	//30 �d�͏���
	void Gravity();
	//35 �J�����ʒu�̎擾
	CVector3 GetCameraPosition();
	CVector3 GetTargetPosition();
	void UpdateAdjust(const CVector3 v);
};

#endif
