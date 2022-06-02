#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
//#include "CPlayer.h"

CGame::CGame()
{
	//テクスチャの入力
	CApplication::Texture()->Load(TEXTURE);
	//ブロックを生成して、キャラクタマネージャに追加
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
//	//定数の定義
//	const int ROWS = 15; //行数
//	const int COLS = 20; //列数
//	//2次元配列のマップ
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
//	//テクスチャの入力
//	CApplication::Texture()->Load(TEXTURE);
//	//マップの作成
//	//行数分繰り返し
//	for (int row = 0; row < ROWS; row++)
//	{
//		//列数分繰り返し
//		for (int col = 0; col < COLS; col++)
//		{
//			//1の時、ブロック生成
//			if (map[row][col] == 1)
//			{
//				//ブロックを生成して、キャラクタマネージャに追加
//				CApplication::CharacterManager()->Add(
//					new CBlock(col * TIPSIZE * 2 + TIPSIZE,
//						row * TIPSIZE * -2 + ROWS * 2 * TIPSIZE - TIPSIZE,
//						TIPSIZE, TIPSIZE, CApplication::Texture()));
//			}
//		}
//	}
//	//プレイヤー生成を生成して、キャラクタマネージャに追加
//	CApplication::CharacterManager()->Add(
//		new CPlayer(TIPSIZE *10.0f, TIPSIZE * 3,
//			TIPSIZE, TIPSIZE, CApplication::Texture()));
//}

void CGame::Update()
{
	//更新、衝突、削除、描画
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
}
