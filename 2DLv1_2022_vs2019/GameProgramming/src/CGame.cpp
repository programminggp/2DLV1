#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
//#include "CPlayer.h"

CGame::CGame()
{
	//テクスチャの入力
	CApplication::Texture()->Load(TEXTURE);

	//定数の定義
	const int ROWS = 5; //行数
	const int COLS = 20; //列数
	//2次元配列のマップ
	int map[ROWS][COLS] =
	{
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},

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
	};

	//マップの作成
	//行数分繰り返し
	for (int row = 0; row < ROWS; row++)
	{
		//列数分繰り返し
		for (int col = 0; col < COLS; col++)
		{
			//1の時、ブロック生成
			if (map[row][col] == 1)
			{
				//ブロックを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CBlock(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
		}
	}
	//プレイヤー生成を生成して、キャラクタマネージャに追加
	/*CApplication::CharacterManager()->Add(
		new CPlayer(TIPSIZE *16.0f, TIPSIZE * 5,
			TIPSIZE, TIPSIZE, CApplication::Texture()));*/
}

void CGame::Update()
{
	//更新、衝突、削除、描画
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
}
