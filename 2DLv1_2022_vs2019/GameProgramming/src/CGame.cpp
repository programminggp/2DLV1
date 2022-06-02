#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
//#include "CPlayer.h"

CGame::CGame()
{
	//�e�N�X�`���̓���
	CApplication::Texture()->Load(TEXTURE);
	//�u���b�N�𐶐����āA�L�����N�^�}�l�[�W���ɒǉ�
	CApplication::CharacterManager()->Add(
		new CBlock(400.0f, 300.0f, TIPSIZE, TIPSIZE,
			CApplication::Texture()));
	CApplication::CharacterManager()->Add(
		new CBlock(TIPSIZE, TIPSIZE, TIPSIZE, TIPSIZE,
			CApplication::Texture()));
	CApplication::CharacterManager()->Add(
		new CBlock(TIPSIZE, 600.0f - TIPSIZE, TIPSIZE, TIPSIZE,
			CApplication::Texture()));
}
//
//	//�萔�̒�`
//	const int ROWS = 15; //�s��
//	const int COLS = 20; //��
//	//2�����z��̃}�b�v
//	int map[ROWS][COLS] =
//	{
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
//{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
//{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
//{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
//{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
//
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
//{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
//{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
//{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
//{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
//
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
//{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
//{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
//{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
//{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
//	};
//	//�e�N�X�`���̓���
//	CApplication::Texture()->Load(TEXTURE);
//	//�}�b�v�̍쐬
//	//�s�����J��Ԃ�
//	for (int row = 0; row < ROWS; row++)
//	{
//		//�񐔕��J��Ԃ�
//		for (int col = 0; col < COLS; col++)
//		{
//			//1�̎��A�u���b�N����
//			if (map[row][col] == 1)
//			{
//				//�u���b�N�𐶐����āA�L�����N�^�}�l�[�W���ɒǉ�
//				CApplication::CharacterManager()->Add(
//					new CBlock(col * TIPSIZE * 2 + TIPSIZE,
//						row * TIPSIZE * -2 + ROWS * 2 * TIPSIZE - TIPSIZE,
//						TIPSIZE, TIPSIZE, CApplication::Texture()));
//			}
//		}
//	}
//	//�v���C���[�����𐶐����āA�L�����N�^�}�l�[�W���ɒǉ�
//	CApplication::CharacterManager()->Add(
//		new CPlayer(TIPSIZE *10.0f, TIPSIZE * 3,
//			TIPSIZE, TIPSIZE, CApplication::Texture()));
//}

void CGame::Update()
{
	//�X�V�A�ՓˁA�폜�A�`��
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
}
