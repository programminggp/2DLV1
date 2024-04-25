#pragma once
#include "CTask.h"
#include "CObjectBase.h"

class CElectricShock;

// �d���G�t�F�N�g�N���X
class CElectricShockEffect : public CTask
{
public:
	// �R���X�g���N�^
	CElectricShockEffect(CObjectBase* owner, const CMatrix* attach,
		const CVector& offsetPos = CVector::zero,
		const CMatrix& offsetRot = CMatrix::identity);
	// �f�X�g���N�^
	~CElectricShockEffect();

	// �d�����J�n
	void Start();
	// �d�����~
	void Stop();

	// �d�������Ă��邩�ǂ���
	bool IsThrowing() const;

	// �d�����̃I�t�Z�b�g�ʒu��ݒ�
	void SetThrowOffsetPos(const CVector& pos);
	// �d�����̃I�t�Z�b�g��]�l��ݒ�
	void SetThrowOffsetRot(const CMatrix& rot);

	// �X�V
	void Update() override;

private:
	// �d�����쐬
	void CreateSlash();

	// �d���̈ʒu���擾
	CVector GetThrowPos() const;
	// �d���̕������擾
	CVector GetThrowDir() const;

	// ���˂������̃G�t�F�N�g�̃��X�g
	std::list<CElectricShock*> mElectricShock;
	CObjectBase* mpOwner;		// ���̃G�t�F�N�g�̎�����
	const CMatrix* mpAttachMtx;	// �G�t�F�N�g���A�^�b�`����s��
	CVector mThrowOffsetPos;	// �r�[�����̃I�t�Z�b�g�ʒu
	CMatrix mThrowOffsetRot;	// �r�[�����̃I�t�Z�b�g��]�l
	float mElapsedTime;			// �o�ߎ��Ԍv���p
	bool mIsThrowing;			// �d�������Ă��邩
};