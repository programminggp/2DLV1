#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer2.h"

CGame::CGame()
{
	//�e�N�X�`���̓���
	CApplication::Texture()->Load(TEXTURE);

	//�萔�̒�`
	const int ROWS = 15; //�s��
	const int COLS = 20; //��
	//2�����z��̃}�b�v
	int map[ROWS][COLS] =
	{
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,2,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
	};

	//�}�b�v�̍쐬
	//�s�����J��Ԃ�
	for (int row = 0; row < ROWS; row++)
	{
		//�񐔕��J��Ԃ�
		for (int col = 0; col < COLS; col++)
		{
			//1�̎��A�u���b�N����
			if (map[row][col] == 1)
			{
				//�u���b�N�𐶐����āA�L�����N�^�}�l�[�W���ɒǉ�
				CApplication::CharacterManager()->Add(
					new CBlock(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
			//2�̎��A�v���C���[����
			if (map[row][col] == 2)
			{
				//�v���C���[�𐶐����āA�L�����N�^�}�l�[�W���ɒǉ�
				CApplication::CharacterManager()->Add(
					new CPlayer2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
		}
	}
}

void CGame::Update()
{
	//�X�V�A�ՓˁA�폜�A�`��
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
}