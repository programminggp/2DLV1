#pragma once
#include "CUi.h"
#include "CPlayer2.h"

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
	~CGame();
	bool IsClear();
	void Clear();
	bool IsOver();
	void Over();
	void Start();
	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};
	CGame(); //�f�t�H���g�R���X�g���N�^�i���������j
	void Update(); //�X�V����
private:
	CInput mInput;
	EState mState;
	int mTime; //�o�ߎ���
	CUi *mpUi; //UI�N���X�̃|�C���^
};
