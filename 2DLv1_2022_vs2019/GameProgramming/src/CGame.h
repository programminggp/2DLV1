#pragma once
#include "CUi.h"

//�萔�̒�`
#define TEXTURE "image.png" //�e�N�X�`���̃t�@�C����
#define TIPSIZE 20.0f //�}�b�v�v�f�̃T�C�Y
/*
* CGame�N���X
* �Q�[���N���X
* �Q�[���̃}�b�v���쐬���A
* �L�����N�^��z�u����
*/
class CGame
{
public:
	static CUi* Ui();
	CGame(); //�f�t�H���g�R���X�g���N�^�i���������j
	void Update(); //�X�V����
private:
	static CUi *spUi;
};
