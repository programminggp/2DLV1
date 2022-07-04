#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer2.h"
#include "CEnemy2.h"
#include "CPoint.h"

CGame::CGame()
	: mpUi(nullptr)
	, mTime(0)
//	, mpPlayer(nullptr)
{
	mpUi = new CUi();
	//テクスチャの入力
	CApplication::Texture()->Load(TEXTURE);

	//定数の定義
	const int ROWS = 15; //行数
	const int COLS = 20; //列数
	//2次元配列のマップ
	int map[ROWS][COLS] =
	{
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,2,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
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
			//2の時、プレイヤー生成
			if (map[row][col] == 2)
			{
				//プレイヤーを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CPlayer2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
			//3の時、敵生成
			if (map[row][col] == 3)
			{
				//敵を生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CEnemy2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
			//4の時、折り返しポイント作成
			if (map[row][col] == 4)
			{
				//折り返しポイントを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CPoint(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE, CCharacter::ETag::ETURN));
			}
		}
	}
}

void CGame::Update()
{
	//更新、衝突、削除、描画
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CApplication::CharacterManager()->Render();
	//UI
	mpUi->Time(mTime++);
	mpUi->Hp(CPlayer2::Hp());
//	mpUi->Hp(1);
	mpUi->Render();
}
