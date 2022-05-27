#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer.h"

//定数の定義
#define TEXTURE "image.png"
#define SIZE 20.0f

void CGame::Start()
{
	//定数の定義
	const int ROWS = 15;
	const int COLS = 20;
	//2次元配列のマップ
	int map[ROWS][COLS] =
	{
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	CApplication::Texture()->Load(TEXTURE);
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (map[row][col] == 1)
			{
				CApplication::CharacterManager()->Add(
					new CBlock(col * SIZE * 2 + SIZE,
						row * SIZE * -2 + ROWS * 2 * SIZE - SIZE,
						SIZE, SIZE, CApplication::Texture()));
			}
		}
	}
	//プレイヤー生成
	CApplication::CharacterManager()->Add(
		new CPlayer(SIZE*10.0f,SIZE*3,
			SIZE, SIZE, CApplication::Texture()));
}

void CGame::Update()
{
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
}
