#pragma once

//------------------------------
// �|�[�Y��ނ�define�i�r�b�g�l�j
//------------------------------

//�Q�[���|�[�Y��
#define PAUSE_GAME (1 << 0)
//���j���[���J������
#define PAUSE_MENU_OPEN (1 << 1)

//------------------------------

//Task�̃|�[�Y���
enum class ETaskPauseType
{
	//�|�[�Y���Ȃ�
	eNone = -1,
	//�f�t�H���g�i�|�[�Y���Ȃ��j
	eDefault = eNone,
	//�Q�[�����̃I�u�W�F�N�g
	//�i�Q�[���|�[�Y���ƃ��j���[���J�������Ƀ|�[�Y����Task�ɐݒ�j
	eGame = PAUSE_GAME | PAUSE_MENU_OPEN,
	//���j���[���̃I�u�W�F�N�g
	//�i�Q�[���|�[�Y���̂݃|�[�Y����Task�ɐݒ�j
	eMenu = PAUSE_GAME,
	//�V�X�e���֘A
	//�i�V�X�e���֘A��Task�͏�ɓ������̂Ń|�[�Y���Ȃ��j
	eSystem = eNone,

	Num
};
