#pragma once
#include "CObjectBase.h"
#include "CharaStatus.h"


//�L�����̃X�e�[�^�X
struct CharaStatus
{
	int level;          // ���x��
	int exp;            // �o���l
	int hp;             // HP
	int power;          // �U����
	int defense;        // �h���
	float mobility;     // �ړ���
	int SpecialAttack;  // ����U��
	float volume;       // �傫��
	float cameraHeight; // �J�����̍���

	// �X�e�[�^�X�̃��Z�b�g
	void Reset()
	{
		level = 1;
		exp = 0;
		power = 5;
		defense = 0;
		mobility = 1.0f;
		SpecialAttack = 2;
		volume = 1.02f;
		cameraHeight = 0.0f;
	}
};

// �v���C���[�̍ő僌�x��
#define PLAYER_LEVEL_MAX 100
// �v���C���[�̃��x�����ƂɃX�e�[�^�X�̃e�[�u��
extern const CharaStatus PLAYER_STATUS[PLAYER_LEVEL_MAX];

// �G�̍ő僌�x��
#define ENEMY__LEVEL_MAX 5
// �G�̃��x�����ƂɃX�e�[�^�X�̃e�[�u��
extern const CharaStatus ENEMY_STATUS[ENEMY__LEVEL_MAX];    // �X���C��
extern const CharaStatus ENEMY2_STATUS[ENEMY__LEVEL_MAX];   // �}�b�V�����[��
extern const CharaStatus ENEMY3_STATUS[ENEMY__LEVEL_MAX];   // �T
extern const CharaStatus ENEMY4_STATUS[ENEMY__LEVEL_MAX];   // �G�C
extern const CharaStatus ENEMY5_STATUS[ENEMY__LEVEL_MAX];   // �I
extern const CharaStatus ENEMY6_STATUS[ENEMY__LEVEL_MAX];   // �T�{�e��
extern const CharaStatus ENEMY7_STATUS[ENEMY__LEVEL_MAX];   // �`�F�X�g�����X�^�[
extern const CharaStatus ENEMY8_STATUS[ENEMY__LEVEL_MAX];   // ���̂̃����X�^�[
extern const CharaStatus ENEMY9_STATUS[ENEMY__LEVEL_MAX];   // �{�N�T�[
extern const CharaStatus ENEMY10_STATUS[ENEMY__LEVEL_MAX];  // �h���S��


/// <summary>
/// �L�����N�^�[�̃x�[�X�N���X
/// </summary>
class CCharaBase : public CObjectBase
{
public:
	CCharaBase(ETag tag, ETaskPriority prio, int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eGame);
	virtual ~CCharaBase();

	/// <summary>
	/// ��_���[�W����
	/// </summary>
	/// <param name="damage">�󂯂鏈��</param>
	virtual void TakeDamage(int damage, CObjectBase* causedObj);

	/// <summary>
	/// �ő�X�e�[�^�X���擾
	/// </summary>
	/// <returns></returns>
	const CharaStatus& MaxStatus() const;
	/// <summary>
	/// ���݂̃X�e�[�^�X���擾
	/// </summary>
	/// <returns></returns>
	const CharaStatus& Status() const;

	virtual float GetAtkBuff()const;

	virtual float GetDefBuff(const CVector&attackDir)const;

protected:
	CharaStatus mCharaMaxStatus;  //�ő�X�e�[�^�X
	CharaStatus mCharaStatus;  //���݂̃X�e�[�^�X

	float mBaseAttackBuffRatio;  // �U���͂̋������� (1.0�œ��l)
	float mBaseDefenseBuffRatio; // �h��͂̋������� (1.0�œ��l)
};

/// <summary>
/// �_���[�W�ʂ��Z�o
/// </summary>
/// <param name="attaker">�U�����̃L����</param>
/// <param name="defender">�h��͂̃L����</param>
/// <returns>�_���[�W��</returns>
extern int CalcDamage(const CCharaBase* attaker, const CCharaBase* defender);
