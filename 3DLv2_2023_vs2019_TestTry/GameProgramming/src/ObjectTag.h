#pragma once
#include <initializer_list>

// �I�u�W�F�N�g���ʗp�̃^�O
enum class ETag
{
	eNone = -1,

	eField,	 // �t�B�[���h���\������I�u�W�F�N�g
	eExp,    // �o���l
	eRideableObject,	// ��邱�Ƃ��ł���I�u�W�F�N�g
	eItem,	 // �A�C�e���̍U���̓A�b�v
	eItem2,  // �A�C�e���̉�
	eItem3,  // �A�C�e���̈ړ����x�A�b�v

	eWeapon, // ����

	ePlayer, // �v���C���[
	eEnemy,  // �G�l�~�[
	eBullet, // �e��
	eFlame,	 // ��
	eSlash,	 // �X���b�V��
	eWave,   // �g��
	eNeedle, // �j
	eLightningBall,  // ����
	eElectricShock,  // �d��
	eImpact, // �Ռ�

	eCamera, // �J����

	Num
};
// �I�u�W�F�N�g���ʗp�̃^�O�̏��������X�g
using Tags = std::initializer_list<ETag>;
