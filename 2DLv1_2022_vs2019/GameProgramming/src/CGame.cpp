#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer.h"

void CGame::Start()
{
	//定数の定義
	const int ROWS = 15;
	const int COLS = 20;
	//2次元配列のマップ
	int map[ROWS][COLS] =
	{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},

{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
	}
	;

	CApplication::Texture()->Load(TEXTURE);
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (map[row][col] == 1)
			{
				CApplication::CharacterManager()->Add(
					new CBlock(col * TIPSIZE * 2 + TIPSIZE,
						row * TIPSIZE * -2 + ROWS * 2 * TIPSIZE - TIPSIZE,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
		}
	}
	//プレイヤー生成
	CApplication::CharacterManager()->Add(
		new CPlayer(TIPSIZE *10.0f, TIPSIZE *3,
			TIPSIZE, TIPSIZE, CApplication::Texture()));
}

void CGame::Update()
{
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
}
