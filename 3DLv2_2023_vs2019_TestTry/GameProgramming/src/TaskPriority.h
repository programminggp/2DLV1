#pragma once

// Task�̗D�揇��
enum class ETaskPriority
{
	eNone = -1,

	// 3D�֘A
	eBackground,// �w�i
	eDefault,	// �f�t�H���g
	ePlayer,	// �v���C���[
	eEnemy,     // �G�l�~�[

	eWeapon,	// ����
	eExp,       // �o���l
	eItem,      // �A�C�e��

	eEffect,	// �G�t�F�N�g
	eBillboard,	// �r���{�[�h�C���[�W

	eCamera,	// �J����

	// 2D�֘A
	eUI,		// UI�֘A�̃f�t�H���g
	eFade,		// ��ʃt�F�[�h
	eSystem,	// �V�X�e���֘A
	eDebug,		// �f�o�b�O�֘A

	Num,

	// 2D�֘A�̃^�X�N�̊J�n�ʒu
	Start2d = eUI,
};